# Phase 3: Baseline Network Analysis

## Objective
To establish a normal performance profile for the AODV routing protocol in a MANET before introducing malicious Black Hole nodes. 

## Simulation Parameters
* **Simulator:** NS-3 (v3.47)
* **Grid Area:** 300m x 300m (Dense Network)
* **Mobility Model:** Random Waypoint
* **Node Densities:** 20, 40, 60 nodes
* **Speeds Tested:** 5, 15, 30, 40 m/s
* **Traffic:** UDP CBR (512B packets), 100s simulation time

## Key Scientific Findings

### 1. The Impact of High Mobility
Across all node densities, increasing speed from 5 m/s to 40 m/s resulted in a severe degradation of Packet Delivery Ratio (PDR) and Throughput. As nodes move faster, Wi-Fi links break more frequently than AODV can repair them.

### 2. Network Density "Sweet Spot"
The 40-node network demonstrated the highest resilience, maintaining a ~75% PDR at 5 m/s. 
* The **20-node network** was too sparse, leading to network partitioning.
* The **60-node network** was too crowded, leading to signal interference and reduced throughput.

### 3. Routing Overhead and Inefficiency
Under extreme stress (60 nodes at 40 m/s), the network generated nearly 25,000 AODV routing control packets. The Normalized Routing Load (NRL) spiked to 176, meaning it took 176 control packets to successfully deliver a single data packet. This proves the necessity for a highly lightweight security algorithm in future phases.