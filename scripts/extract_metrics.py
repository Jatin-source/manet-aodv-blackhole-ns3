import xml.etree.ElementTree as ET
import sys
import os

if len(sys.argv) != 3:
    print("Usage: python3 extract_metrics.py <nodes> <speed>")
    sys.exit(1)

nodes = sys.argv[1]
speed = sys.argv[2]

overhead = 0
with open("trace.tr", "r") as f:
    for line in f:
        if line.startswith('t') and 'aodv' in line.lower():
            overhead += 1

tree = ET.parse("flowmon.xml")
root = tree.getroot()

tx_packets = 0
rx_packets = 0
rx_bytes = 0
total_delay = 0.0
time_first_tx = 999999.0
time_last_rx = 0.0

for flow in root.findall('.//FlowStats/Flow'):
    tx = int(flow.get('txPackets'))
    if tx > 50: # Focus on the main UDP traffic
        rx = int(flow.get('rxPackets'))
        tx_packets += tx
        rx_packets += rx
        rx_bytes += int(flow.get('rxBytes'))
        
        delay_ns = float(flow.get('delaySum').replace('+', '').replace('ns', ''))
        total_delay += delay_ns / 1e9 # Convert to seconds
        
        t_first = float(flow.get('timeFirstTxPacket').replace('+', '').replace('ns', '')) / 1e9
        t_last = float(flow.get('timeLastRxPacket').replace('+', '').replace('ns', '')) / 1e9
        
        if t_first < time_first_tx: time_first_tx = t_first
        if t_last > time_last_rx: time_last_rx = t_last

pdr = (rx_packets / tx_packets) * 100 if tx_packets > 0 else 0

throughput = 0
if rx_packets > 0 and time_last_rx > time_first_tx:
    throughput = (rx_bytes * 8.0) / (time_last_rx - time_first_tx) / 1024 # Kbps
    
delay = total_delay / rx_packets if rx_packets > 0 else 0
nrl = overhead / rx_packets if rx_packets > 0 else 0

csv_file = "baseline_results.csv"
write_header = not os.path.exists(csv_file)

with open(csv_file, "a") as f:
    if write_header:
        f.write("Nodes,Speed,TxPackets,RxPackets,PDR(%),Throughput(Kbps),Delay(s),RoutingOverhead,NRL\n")
    f.write(f"{nodes},{speed},{tx_packets},{rx_packets},{pdr:.2f},{throughput:.2f},{delay:.5f},{overhead},{nrl:.2f}\n")

print(f"Logged: Nodes={nodes} | Speed={speed}m/s | PDR={pdr:.2f}% | Overhead={overhead} | NRL={nrl:.2f}")       