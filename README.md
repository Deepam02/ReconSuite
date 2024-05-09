---

# ReconSuite: Revolutionizing Network Reconnaissance

Welcome to ReconSuite, your ultimate companion for network reconnaissance tasks. Developed with user convenience in mind, ReconSuite merges powerful tools into an intuitive graphical interface, catering to both beginners and experts alike. Let's embark on a journey of seamless exploration and discovery in the realm of networks.

## Unveil the Arsenal

ReconSuite is your gateway to a comprehensive suite of reconnaissance tools, designed to empower your network analysis endeavors:

- **Ping**: Swiftly assess the reachability of hosts on IP networks.
- **Nmap**: Conduct thorough network discovery and security audits effortlessly.
- **Dig**: Query DNS servers for crucial information about host addresses, mail exchanges, and more.
- **Traceroute**: Trace packet routes across IP networks to unveil hidden insights.
- **Whois**: Retrieve detailed registration information for domain names with ease.
- **Dnsenum**: Gather vital details about DNS nameservers and zones through DNS enumeration.
- **Subfinder**: Effortlessly discover subdomains associated with target domains.
- **Ffuf**: Harness the power of a lightning-fast web fuzzer for directory and parameter brute-forcing.

## Getting Started Made Easy

### Requirements:

Before diving into the world of ReconSuite, ensure you have the following essentials:

- A C++ compiler compatible with Qt
- Qt Kit: Desktop Qt 6.7.0
- Qt Creator IDE

Get your hands on Qt Desktop 6.7.0 and Qt Creator from the [Qt Downloads page](https://www.qt.io/download-qt-installer-oss).

Prior to running the Qt installer, make sure to install the required libraries:

```bash
sudo apt install libxcb-cursor0
sudo apt update
```

Make the installer executable using the chmod command:

```bash
chmod +x <path_to_installer>
```

### Option a) Direct Import from Git:

1. Launch Qt Creator.
2. Navigate to "Create Project" > "Import Project" > "Clone Repository".
3. Paste the repository link: `https://github.com/Deepam02/ReconSuite.git`.
4. Open the `DigiRecon_V1.pro` file located in the project directory.
5. Choose the "Build" > "Release" option and execute.

By following these steps, you'll generate a binary file, eliminating the need to open Qt Creator each time you use ReconSuite.

### Option b) Cloning the Git Repository:

1. Clone the repository: `git clone https://github.com/Deepam02/ReconSuite.git`.
2. Open Qt Creator.
3. Select "Open Project" and open the `DigiRecon_V1.pro` file from the cloned project directory.
4. Similarly, choose the "Build" > "Release" option and execute.

Encountering issues while configuring the project? If so, it might be due to the C++ compiler not being auto-detected or being incompatible. To address this, install a C++ compiler like g++ on Linux:

```bash
sudo apt install build-essential
```

Rest assured, Qt Creator should automatically detect the compiler after installation. If not, manually select the compiler in "Manage Kits" within Project Mode.

---

Elevate your network reconnaissance game with ReconSuite. Seamlessly unravel hidden insights and supercharge your workflow to new heights!
