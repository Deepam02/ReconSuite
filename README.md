Certainly! Here's the full README file content with proper formatting for copy-pasting:

```markdown
# ReconSuite

ReconSuite is a comprehensive GUI (Graphical User Interface) application built using Qt C++ that integrates a suite of reconnaissance tools for network analysis and information gathering. This project aims to provide a user-friendly interface for common reconnaissance tasks, streamlining the process for both beginners and experienced users.

## Features

ReconSuite integrates the following reconnaissance tools:

- **Ping**: Check the reachability of a host on an IP network.
- **Nmap**: Perform network discovery and security auditing.
- **Dig**: Query DNS servers for information about host addresses, mail exchanges, and other data.
- **Traceroute**: Trace the route taken by packets across an IP network.
- **Whois**: Retrieve registration information for domain names.
- **Dnsenum**: Perform DNS enumeration to gather information about DNS nameservers and zones.
- **Subfinder**: Discover subdomains belonging to a domain.
- **Ffuf**: A fast web fuzzer used for directory and parameter brute-forcing.

## How to Run ReconSuite Application

### Requirements:

- C++ compiler compatible with Qt
- Qt Kit: Desktop Qt 6.7.0
- Qt Creator IDE

Install Qt Desktop 6.7.0 and Qt Creator from [Qt Downloads page](https://www.qt.io/download-qt-installer-oss).

Before starting the Qt installer, install required libraries:

```bash
sudo apt install libxcb-cursor0
sudo apt update
```

Make the installer runnable using chmod command:

```bash
chmod +x <path_to_installer>
```

### Option a) Import directly from Git:

1. Run Qt Creator.
2. Select "Create Project" > "Import Project" > "Clone Repository".
3. Paste the repository link: `https://github.com/Deepam02/ReconSuite.git`.
4. Open the DigiRecon_V1.pro file in the project.
5. Select "Build" > "Release" option and run.

This will create a binary file, so you don't have to run Qt Creator to use ReconSuite.

### Option b) Clone the Git repository:

1. Clone the repository: `git clone https://github.com/Deepam02/ReconSuite.git`.
2. Open Qt Creator.
3. Select "Open Project" and open the `DigiRecon_V1.pro` file from the cloned project.
4. Similarly, select "Build" > "Release" option and run.

If there are errors with configuring the project (it should already be configured), it means the C++ compiler is not auto-detected or not compatible. Install a C++ compiler such as g++ on Linux:

```bash
sudo apt install build-essential
```

Qt Creator should auto-detect the compiler after installing it. If it does not, select the compiler in "Manage Kits" in Project Mode.
```

