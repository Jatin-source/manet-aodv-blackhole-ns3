#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/wifi-module.h"
#include "ns3/aodv-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("ManetBaseline");

int main(int argc, char *argv[])
{
    uint32_t nNodes = 20;
    double speed = 5.0;
    double simTime = 100.0;

    CommandLine cmd;
    cmd.AddValue("nNodes", "Number of nodes", nNodes);
    cmd.AddValue("speed", "Node speed", speed);
    cmd.Parse(argc, argv);

    NodeContainer nodes;
    nodes.Create(nNodes);

    WifiHelper wifi;
    wifi.SetStandard(WIFI_STANDARD_80211b);
    wifi.SetRemoteStationManager(
        "ns3::ConstantRateWifiManager",
        "DataMode", StringValue("DsssRate11Mbps"),
        "ControlMode", StringValue("DsssRate11Mbps"));

    YansWifiPhyHelper phy;
    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    phy.SetChannel(channel.Create());

    WifiMacHelper mac;
    mac.SetType("ns3::AdhocWifiMac");

    NetDeviceContainer devices = wifi.Install(phy, mac, nodes);

    AsciiTraceHelper ascii;
    phy.EnableAsciiAll(ascii.CreateFileStream("trace.tr"));

    Ptr<RandomRectanglePositionAllocator> positionAlloc = CreateObject<RandomRectanglePositionAllocator>();
    positionAlloc->SetAttribute("X", StringValue("ns3::UniformRandomVariable[Min=0|Max=300]"));
    positionAlloc->SetAttribute("Y", StringValue("ns3::UniformRandomVariable[Min=0|Max=300]"));

    MobilityHelper mobility;
    mobility.SetPositionAllocator(positionAlloc);

    std::ostringstream speedStr;
    speedStr << "ns3::ConstantRandomVariable[Constant=" << speed << "]";

    mobility.SetMobilityModel(
        "ns3::RandomWaypointMobilityModel",
        "Speed", StringValue(speedStr.str()),
        "Pause", StringValue("ns3::ConstantRandomVariable[Constant=2]"),
        "PositionAllocator", PointerValue(positionAlloc)
    );
    mobility.Install(nodes);

    AodvHelper aodv;
    InternetStackHelper stack;
    stack.SetRoutingHelper(aodv);
    stack.Install(nodes);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    uint16_t port = 9;

    PacketSinkHelper sink("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), port));
    ApplicationContainer sinkApp = sink.Install(nodes.Get(nNodes - 1));
    sinkApp.Start(Seconds(1.0));
    sinkApp.Stop(Seconds(simTime));

    OnOffHelper onoff("ns3::UdpSocketFactory", InetSocketAddress(interfaces.GetAddress(nNodes - 1), port));
    onoff.SetAttribute("DataRate", StringValue("50kbps"));
    onoff.SetAttribute("PacketSize", UintegerValue(512));
    onoff.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=1]"));
    onoff.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));

    ApplicationContainer clientApp = onoff.Install(nodes.Get(0));
    clientApp.Start(Seconds(2.0));
    clientApp.Stop(Seconds(simTime));

    FlowMonitorHelper flowmon;
    Ptr<FlowMonitor> monitor = flowmon.InstallAll();

    Simulator::Stop(Seconds(simTime));
    Simulator::Run();
    monitor->CheckForLostPackets();

    std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats();
    std::ifstream trace("trace.tr");
    std::string line;
    int routingOverhead = 0;

    if (trace.is_open()) {
        while (getline(trace, line)) {
            // "AODV" catches all routing overhead (RREQ, RREP, RERR)
            if (line.find("AODV") != std::string::npos) {
                routingOverhead++;
            }
        }
        trace.close();
    }

    monitor->SerializeToXmlFile("flowmon.xml", true, true);
    
    Simulator::Destroy();
    return 0;
}                                                                                                                              
