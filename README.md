# Automated Navigation Technology

## Overview
This project, developed as part of a Bachelor in Engineering (Electronics and Telecommunication) at Modern College of Engineering, Pune, presents an **Automated Navigation System** using the ESP32 microcontroller. The system enables a four-wheeled mobile robot to navigate indoor environments like bedrooms, kitchens, and living rooms through a web-based interface. It integrates IR sensors for real-time obstacle detection and dual L298N motor drivers for movement, showcasing a cost-effective solution for IoT-enabled robotics in smart homes.

**Team Members:**  
- Samiksha Tiwari  
- Samiksha  
- Rutvij Mahale  

**Academic Year:** 2024-2025  
**Institution:** Progressive Education Society’s Modern College of Engineering, Shivajinagar, Pune  
**Guide:** Mrs. Shreyasi Watve

## Features
- **Wi-Fi-Controlled Navigation:** Control the robot remotely via a web interface using the ESP32’s built-in HTTP server.  
- **Obstacle Detection:** IR sensors enable real-time collision avoidance and basic rerouting.  
- **Low-Cost Design:** Built with affordable components like ESP32, L298N motor drivers, and IR sensors.  
- **Scalable Framework:** Modular design allows future enhancements like LiDAR, voice commands, or SLAM.  
- **Applications:** Ideal for smart homes, indoor logistics, and educational robotics.

## Hardware Requirements
| Component            | Specification                          | Purpose                          |
|----------------------|----------------------------------------|----------------------------------|
| ESP32 Microcontroller| 5V DC, Dual-core, 240 MHz, Wi-Fi      | Central control and processing   |
| DC Geared Motors     | 6V–12V, 30–300 RPM, 1–5 kg.cm torque | Drives the robot’s wheels        |
| L298N Motor Driver   | 5V–35V, 2A per channel               | Controls motor direction/speed   |
| IR Sensors           | 5V DC, analog/digital output          | Obstacle detection               |
| Chassis              | Acrylic/plastic, 4WD                  | Mechanical base                  |
| Power Supply         | 7.4V LiPo or 9V battery               | Powers the system                |

## Software Requirements
- **Arduino IDE:** For programming the ESP32.  
- **Programming Language:** C/C++.  
- **Libraries:** 
  - ESP32 core libraries for Wi-Fi and GPIO control.  
  - Libraries for IR sensor interfacing (if needed).  
- **Web Interface:** Basic HTML page hosted on ESP32 for control.

## Project Setup
### Prerequisites
1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Add ESP32 board support in Arduino IDE via Boards Manager (URL: `https://raw.githubusercontent.com/espressif/arduino-esp32/master/package_esp32_index.json`).
3. Gather all hardware components as listed above.

### Hardware Assembly
1. Mount the ESP32, L298N motor drivers, and IR sensors on the chassis.
2. Connect the DC motors to the L298N motor driver.
3. Wire the IR sensors to the ESP32’s GPIO pins for obstacle detection.
4. Connect the L298N motor driver to the ESP32 for motor control.
5. Power the system using a 7.4V LiPo battery, ensuring stable voltage with a regulator (e.g., LM7805).

### Software Setup
1. Clone this repository:
   ```
   git clone https://github.com/<your-username>/automated-navigation-technology.git
   ```
2. Open the project code (`main.ino`) in Arduino IDE.
3. Install necessary libraries for ESP32 and IR sensors.
4. Configure the Wi-Fi credentials in the code for the ESP32 to host the web interface.
5. Upload the code to the ESP32 via USB.

## Usage
1. **Power On:** Turn on the robot using the battery power supply.
2. **Connect to Wi-Fi:** The ESP32 creates a local access point or connects to a specified Wi-Fi network (based on code configuration).
3. **Access Web Interface:** On a browser-enabled device, navigate to the IP address provided by the ESP32 (displayed on the Serial Monitor) to access the control interface.
4. **Control the Robot:** Use the web interface to send commands (e.g., forward, backward, turn) and navigate predefined zones.
5. **Obstacle Avoidance:** The robot automatically detects and avoids obstacles using IR sensors.

## Project Structure
- `main.ino`: Core Arduino sketch for ESP32 control, sensor reading, and motor control.
- `web_interface.html`: HTML file for the web-based control interface (embedded or served by ESP32).
- `docs/`: Project report and documentation.
- `schematics/`: Circuit diagrams and hardware setup guides (if added).

## Results
- The robot successfully navigates indoor environments, responding to web-based commands in real-time.
- IR sensors enable effective obstacle detection within a 20 cm range.
- The system operates for 2–3 hours on a single battery charge, depending on usage.

## Future Scope
- **Advanced Sensors:** Integrate LiDAR or ultrasonic sensors for better mapping and navigation.
- **Voice Control:** Add voice command support for hands-free operation.
- **SLAM Implementation:** Enable Simultaneous Localization and Mapping for autonomous navigation in unknown environments.
- **IoT Expansion:** Connect to broader IoT platforms for remote monitoring and control.

## Contributing
We welcome contributions to enhance this project! To contribute:
1. Fork this repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes and commit (`git commit -m "Add new feature"`).
4. Push to your branch (`git push origin feature-branch`).
5. Open a Pull Request with a detailed description of your changes.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments
- **Guide:** Mrs. Shreyasi Watve for her invaluable guidance.  
- **Institution:** Modern College of Engineering, Pune, for providing resources and support.  
- **Team:** Samiksha Tiwari, Samiksha, and Rutvij Mahale for their collaborative efforts.

---

For more details, refer to the full project report in the `docs/` directory.
