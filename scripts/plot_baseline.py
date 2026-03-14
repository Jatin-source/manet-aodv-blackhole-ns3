import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('baseline_results.csv')

metrics = {
    'PDR(%)': 'Packet Delivery Ratio (%)',
    'Throughput(Kbps)': 'Throughput (Kbps)',
    'Delay(s)': 'End-to-End Delay (Seconds)',
    'RoutingOverhead': 'Routing Overhead (Packets)',
    'NRL': 'Normalized Routing Load (NRL)'  # <-- Added NRL here
}

node_counts = [20, 40, 60]
colors = {20: 'blue', 40: 'green', 60: 'red'}
markers = {20: 'o', 40: 's', 60: '^'}

for idx, (column, y_label) in enumerate(metrics.items(), start=1):
    plt.figure(figsize=(8, 6))
    
    for nodes in node_counts:
        subset = df[df['Nodes'] == nodes]
        plt.plot(subset['Speed'], subset[column], 
                 label=f'{nodes} Nodes', 
                 color=colors[nodes], 
                 marker=markers[nodes], 
                 linestyle='-', linewidth=2, markersize=8)

    plt.title(f'Baseline AODV: {y_label} vs Node Speed', fontsize=14, fontweight='bold')
    plt.xlabel('Node Speed (m/s)', fontsize=12)
    plt.ylabel(y_label, fontsize=12)
    plt.xticks([5, 15, 30, 40])
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend(title="Network Density", fontsize=10)
    
    # Save the graph as a high-res PNG
    filename = f'Graph_{idx}_{column.replace("%", "Percent").replace("(", "").replace(")", "").replace("/", "_")}.png'
    plt.savefig(filename, dpi=300, bbox_inches='tight')
    plt.close()
    
    print(f"Generated {filename}")

print("All 5 Phase 3 graphs have been successfully generated!")  