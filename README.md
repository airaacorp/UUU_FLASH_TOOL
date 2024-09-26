# MFG_FLASH_TOOL

**MFG_FLASH_TOOL**  
(Manufacturing Flashing Tool) is an embedded flashing tool for Freescale/NXP I.MX chips. It provides a graphical user interface (UI) to flash software images and builds to **NXP i.MX processor chips** via USB, track flashing progress, monitor device connections, and handle exceptions like unexpected disconnections. Logging functionality is included.

---

## Table of Contents
- [Overview](#overview)
- [Repository URL](#repository-url)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Build Process](#build-process)
- [Usage](#usage)
- [Supported Boards](#supported-boards)
- [Example Logs and UI](#example-logs-and-ui)
- [Contributing](#contributing)
- [License](#license)

---

## Overview
**MFG_FLASH_TOOL** (Universal Update Utility), also known as mfgtools, is a **UI-based tool** for flashing Freescale/NXP I.MX chips. It allows users to track flashing progress, monitor USB devices in real-time, and handle unexpected events like disconnections while storing logs and providing a dynamic process view to the user.

- **Linux Version**: Available in the `linux` branch.
- **Windows Version**: Available in the `windows` branch.

## Repository URL
You can find the repository here:  
- [MFG_FLASH_TOOL GitHub Repository For Linux](https://github.com/airaacorp/UUU_FLASH_TOOL)
- [MFG_FLASH_TOOL GitHub Repository For Windows]() 

---

## Features
- **UI-based Universal Update Utility** for NXP i.MX chips.
- **Progress Bars** for current and overall progress based on real-time flashing. 
- **USB device monitoring**: Detect connection and disconnection events.
- **Exception handling** for fluctuations, cable removal, and disconnections, showing success and failure status codes based on flashing.
- **Dynamic Logging System** for monitoring everything while using the tool.
- **Drive Detection**: Displays connected drive information to the user, including port and hub detection.
- **Success and Failed Operations**: Provides feedback on successful and failed operations, displaying failure rates.
- Supports multiple devices for simultaneous flashing.

---

## Prerequisites
Before building and running the tool, ensure that you have the following dependencies installed:
- **CMake** 3.10 or higher
- **Qt 6** (for the graphical user interface)
- **libusb** (for USB communication)
- **Micro-USB to OTG** cable (for USB OTG communication)
- **Micro-USB to UART** port cable (for serial communication)

---

## Build Process

### 1. Clone the Repository
To get started, clone the repository from GitHub:
```bash
git clone https://github.com/airaacorp/UUU_FLASH_TOOL.git
cd UUU_FLASH_TOOL
```
## Linux Build
```
mkdir build
cd build
cmake ..
make
```
## Windows Build
```
mkdir build
cd build
cmake ..
cmake --build .
```
## Launch Tool
- After a successful build, launch the UI-based tool by running:
```
./mfgtool
```
## Usage
### Launch the Tool:
- Start the tool using the mfgtool command.
### Select Target:
- Choose the image file and build to be flashed to the NXP i.MX processor.
### Progress Tracking:
- Use the progress bars to monitor the flashing process.
### USB Device Monitoring:
- The tool automatically detects connected devices and shows real-time updates for connection/disconnection events.
### Error Handling:
- The tool captures errors like disconnections and other flashing issues, logging them for further inspection.
## Supported Boards
- MFG_FLASH_TOOL supports the following NXP i.MX boards:
- i.MX 6 (Quad, Dual, Solo)
- i.MX 7 series
- i.MX 8 series
  
## Example Logs and UI

### UI Example: 
![UI Example 1](https://raw.githubusercontent.com/airaacorp/UUU_FLASH_TOOL/main/Screenshot%20from%202024-09-26%2012-08-24.png)
![UI Example 2](https://raw.githubusercontent.com/airaacorp/UUU_FLASH_TOOL/main/Screenshot%20from%202024-09-26%2012-08-31.png)
![UI Example 3](https://raw.githubusercontent.com/airaacorp/UUU_FLASH_TOOL/main/Screenshot%20from%202024-09-26%2012-08-55.png)
![UI Example 4](https://raw.githubusercontent.com/airaacorp/UUU_FLASH_TOOL/main/Screenshot%20from%202024-09-26%2012-09-18.png)

Displays a progress bar showing the current status of the flashing process, as well as logs at the bottom for real-time monitoring.

## Contributing

We welcome contributions to **MFG_FLASH_TOOL**! Here’s how you can help:

### How to Contribute

1. **Fork the Repository**
   - Click on the "Fork" button at the top right corner of the repository page to create your own copy of the project.

2. **Clone Your Fork**
   - Clone your forked repository to your local machine:
     ```bash
     git clone https://github.com/your_username/UUU_FLASH_TOOL.git
     cd UUU_FLASH_TOOL
     ```

3. **Create a Branch**
   - Create a new branch for your feature or bug fix:
     ```bash
     git checkout -b feature/my-new-feature
     ```
   - or for a bug fix:
     ```bash
     git checkout -b bugfix/my-bug-fix
     ```

4. **Make Your Changes**
   - Implement your feature or fix in the codebase. Be sure to follow the coding style used in the project.

5. **Test Your Changes**
   - Ensure your changes do not break existing functionality by running the existing tests or adding new ones if necessary.

6. **Commit Your Changes**
   - Commit your changes with a descriptive message:
     ```bash
     git commit -m "Add my new feature"
     ```

7. **Push Your Changes**
   - Push your changes to your forked repository:
     ```bash
     git push origin feature/my-new-feature
     ```

8. **Create a Pull Request**
   - Navigate to the original repository and click on the "Pull Requests" tab.
   - Click the "New Pull Request" button and select your branch to create a pull request.
   - Provide a clear description of your changes and why they should be merged.

### Reporting Issues
If you encounter any issues or bugs, please report them by opening an issue in the [Issues](https://github.com/airaacorp/UUU_FLASH_TOOL/issues) section of the repository. Be sure to include the following:
- A clear description of the issue.
- Steps to reproduce the issue.
- Any relevant logs or screenshots.

### Contribution Guidelines
- Follow the existing coding style in the project.
- Write clear and concise commit messages.
- Ensure your code is well-documented.
- Test your changes thoroughly before submitting a pull request.

Thank you for contributing to **MFG_FLASH_TOOL**! Your help is greatly appreciated.

## License
- MFG_FLASH_TOOL is licensed under the MIT License.
