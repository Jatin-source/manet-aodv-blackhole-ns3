<h1 align="center">MANET Black Hole Detection & Mitigation (NS-3)</h1>

<p align="center">
Cyber security simulation project using <b>NS-3 (v3.47)</b> to analyze, detect, and mitigate
<b>Black Hole routing attacks</b> in <b>Mobile Ad-Hoc Networks (MANET)</b> using the
<b>AODV routing protocol</b>.
</p>

<hr>

<h2>📂 Repository Structure</h2>

<pre>
manet-aodv-blackhole-ns3
│
├── ns3-simulation
│   └── manet-baseline.cc
│
├── scripts
│   ├── extract_metrics.py
│   └── plot_baseline.py
│
├── results
│   └── baseline_results.csv
│
├── graphs
│   ├── pdr_vs_speed.png
│   ├── throughput_vs_speed.png
│   ├── delay_vs_speed.png
│   ├── routing_overhead_vs_speed.png
│   └── nrl_vs_speed.png
│
├── docs
│   └── phase3-baseline-analysis.md
│
└── README.md
</pre>

<hr>

<h2>⚙️ Prerequisites & Environment Setup</h2>

<p>This project requires a <b>Linux environment</b> (Ubuntu / Kali / Debian recommended).</p>

<h3>1️⃣ Install System Dependencies</h3>

<pre>
sudo apt update
sudo apt install g++ python3 python3-pip cmake ninja-build git
</pre>

<h3>2️⃣ Install Python Dependencies</h3>

<pre>
pip3 install -r requirements.txt
</pre>

Example dependencies:

<pre>
matplotlib
pandas
numpy
</pre>

<h3>3️⃣ Install NS-3.47</h3>

Download NS-3.47 from the official releases page and build it:

<pre>
cd ns-3.47
./ns3 configure --enable-examples --enable-tests
./ns3 build
</pre>

<hr>

<h2>🚀 How to Run the Simulation</h2>

<h3>Step 1 — Clone the Repository</h3>

<pre>
git clone https://github.com/YOUR_USERNAME/manet-aodv-blackhole-ns3.git
</pre>

<h3>Step 2 — Copy Simulation File to NS-3</h3>

<pre>
cp manet-aodv-blackhole-ns3/ns3-simulation/manet-baseline.cc /path/to/ns-3.47/scratch/
</pre>

<h3>Step 3 — Run the Simulation</h3>

<pre>
cd /path/to/ns-3.47

./ns3 run "scratch/manet-baseline --nNodes=20 --speed=5.0"
</pre>

Example scenarios tested:

<table>
<tr>
<th>Nodes</th>
<th>Speed</th>
</tr>
<tr>
<td>20</td>
<td>5 m/s</td>
</tr>
<tr>
<td>40</td>
<td>15 m/s</td>
</tr>
<tr>
<td>60</td>
<td>30 m/s</td>
</tr>
<tr>
<td>60</td>
<td>40 m/s</td>
</tr>
</table>

<hr>

<h3>Step 4 — Extract Metrics</h3>

<pre>
cd /path/to/manet-aodv-blackhole-ns3

python3 scripts/extract_metrics.py 20 5.0
</pre>

This script extracts performance metrics from the simulation output and stores them in CSV format.

<hr>

<h3>Step 5 — Generate Graphs</h3>

<pre>
python3 scripts/plot_baseline.py
</pre>

This script generates performance visualization graphs.

<hr>

<h2>📊 Current Implementation Status</h2>

<h3>Phase 3 — Baseline MANET Performance Established</h3>

<p>
A baseline AODV network was simulated to understand normal MANET behavior
before introducing attacks.
</p>

<p><b>Metrics analyzed:</b></p>

<ul>
<li>Packet Delivery Ratio (PDR)</li>
<li>Throughput</li>
<li>End-to-End Delay</li>
<li>Routing Overhead</li>
<li>Normalized Routing Load (NRL)</li>
</ul>

<p>
These experiments evaluate performance under different
<b>node densities</b> and <b>mobility speeds</b>.
</p>

<hr>

<h2>📈 Generated Graphs</h2>
<h2>📊 Phase 3 Results — Baseline Network Performance</h2>

<p align="center">
Baseline performance graphs of the AODV routing protocol under varying node speeds.
</p>

<h3>Packet Delivery Ratio (PDR)</h3>
<p align="center">
<img src="results/Phase3-Baseline network implementation/Graph_1_PDRPercent.png" width="750">
</p>

<h3>Throughput</h3>
<p align="center">
<img src="results/Phase3-Baseline network implementation/Graph_2_ThroughputKbps.png" width="750">
</p>

<h3>End-to-End Delay</h3>
<p align="center">
<img src="results/Phase3-Baseline network implementation/Graph_3_Delays.png" width="750">
</p>

<h3>Routing Overhead</h3>
<p align="center">
<img src="results/Phase3-Baseline network implementation/Graph_4_RoutingOverhead.png" width="750">
</p>

<h3>Normalized Routing Load (NRL)</h3>
<p align="center">
<img src="results/Phase3-Baseline network implementation/Graph_5_NRL.png" width="750">
</p>
These graphs represent the <b>baseline performance profile of the AODV routing protocol</b>.
</p>

<hr>

<h2>📄 Detailed Analysis</h2>

<pre>
docs/phase3-baseline-analysis.md
</pre>

Contains detailed explanations of simulation results and observations.

<h2>🧠 Research Roadmap</h2>

<table>
<tr>
<th>Phase</th>
<th>Description</th>
<th>Status</th>
</tr>

<tr>
<td>Phase 1</td>
<td>Research & System Understanding — Study MANET architecture, AODV routing protocol, and Black Hole attack behavior.</td>
<td>✔ Completed</td>
</tr>

<tr>
<td>Phase 2</td>
<td>Simulation Environment Setup — Install and configure NS-3, verify build environment, and prepare simulation workspace.</td>
<td>✔ Completed</td>
</tr>

<tr>
<td>Phase 3</td>
<td>Baseline MANET Simulation — Implement normal AODV network and measure baseline performance metrics.</td>
<td>✔ Completed</td>
</tr>

<tr>
<td>Phase 4</td>
<td>Black Hole Attack Implementation — Introduce malicious node behavior and analyze performance degradation.</td>
<td>⏳ In Progress</td>
</tr>

<tr>
<td>Phase 5</td>
<td>Lightweight Detection Algorithm — Design detection logic based on sequence number anomalies and packet drop patterns.</td>
<td>⏳ Planned</td>
</tr>

<tr>
<td>Phase 6</td>
<td>Attack Mitigation — Isolate malicious nodes and restore network performance.</td>
<td>⏳ Planned</td>
</tr>

<tr>
<td>Phase 7</td>
<td>Mobility Analysis — Evaluate protocol performance under high mobility scenarios.</td>
<td>⏳ Planned</td>
</tr>

<tr>
<td>Phase 8</td>
<td>Scalability Evaluation — Analyze performance across increasing node densities.</td>
<td>⏳ Planned</td>
</tr>

</table>
<h2>🛠 Technologies Used</h2>

<ul>
<li>NS-3 (v3.47)</li>
<li>C++</li>
<li>Python</li>
<li>Matplotlib</li>
<li>Pandas</li>
<li>Linux</li>
</ul>

<hr>

<h2>🎯 Research Objective</h2>

<p>
To analyze how <b>Black Hole attacks degrade MANET routing performance</b>
and develop a <b>lightweight intelligent mitigation mechanism</b>
for secure routing in highly mobile networks.
</p>

<hr>

<h2>👨‍💻 Author</h2>

<p>
<b>Jatin Hajare</b><br>
B.Tech CSE
</p>

<p>
<b>Research Interests:</b><br>
Network Security<br>
MANET Routing Protocols<br>
Cyber Security<br>
Simulation Based Security Analysis
</p>

<hr>

<h2>⭐ Project Status</h2>

<p>
✔ Phase 3 Completed – Baseline Network Established<br>
⏳ Phase 4 In Progress – Black Hole Attack Simulation
</p>
