# Autonomous Fire-Fighting & Gas Detection Robot

An Arduino-based autonomous robotic vehicle designed to navigate toward a fire source, extinguish flames using an onboard water pump mechanism, detect hazardous gas leaks, and send real-time alerts via cellular network (SMS and voice call) using the SIM800L module.

---

## 🚀 Features

- **Automated Fire Navigation:** Utilizes three flame sensors (Left, Middle, Right) to detect nearby fire sources and dynamically steer the robot toward the hazard.
- **Dynamic Extinguishing Mechanism:** An onboard water pump combined with a sweeping micro servo motor creates a wide spray pattern to efficiently douse flames.
- **Gas & Smoke Detection:** Integrated gas sensor continuously monitors ambient air quality for flammable gas or smoke leaks.
- **GSM Remote Alerting System:** Automated cellular alerts powered by the SIM800L module:
  - Sends an SMS text alert upon gas/smoke detection.
  - Sends an SMS text alert when a fire breakout is detected.
  - Initiates an immediate voice call to emergency personnel upon flame confirmation.

---

## 🛠️ Hardware Components

To replicate or build this project, the following hardware components are required:

| Component | Description | Qty |
| :--- | :--- | :--- |
| **Arduino Uno / Nano** | Main microcontroller board | 1 |
| **SIM800L GSM Module** | Cellular transceiver for SMS and Voice Calls | 1 |
| **Flame Sensors** | Infrared receivers optimized for detecting fire wavelengths | 3 |
| **Gas Sensor (e.g., MQ-2)** | Gas/smoke detection sensor | 1 |
| **Servo Motor (SG90/MG90S)**| Directs/sweeps the water nozzle mechanism | 1 |
| **DC Motors & Wheels** | Robot chassis locomotion | 2 or 4 |
| **L298N Motor Driver** | Dual H-Bridge motor controller for driving DC motors | 1 |
| **5V Relay Module** | Controls the high-current submersed water pump | 1 |
| **Water Pump & Pipe** | Discharges water to extinguish the flame | 1 |
| **Power Supply** | Li-ion cells (e.g., 18650) or LiPo battery pack | 1 |

---

## 📌 Pin Configuration Matrix

The connections between the Arduino microcontroller and various modules are defined as follows:

### 1. Sensors & Inputs
- **Left Flame Sensor:** Digital Pin `9`
- **Right Flame Sensor:** Digital Pin `10`
- **Middle Flame Sensor:** Digital Pin `2`
- **Gas Sensor:** Digital Pin `8`

### 2. Actuators & Outputs
- **Servo Motor Signal:** Analog Pin `A0`
- **Water Pump Relay:** Digital Pin `7`
- **Motor Driver Inputs (L298N):**
  - `IN1`: Digital Pin `3` (Left Motor Forward)
  - `IN2`: Digital Pin `4` (Left Motor Reverse)
  - `IN3`: Digital Pin `5` (Right Motor Forward)
  - `IN4`: Digital Pin `6` (Right Motor Reverse)

### 3. GSM Module (SIM800L)
- **RX Pin:** Digital Pin `11`
- **TX Pin:** Digital Pin `12`
*Note: Make sure to check baud rates and use proper logic level converters if necessary for the SIM800L module.*

---

## ⚙️ Logic and Operational Workflow

### 🗺️ Locomotion & Steering Logic
The robot continuously scans inputs from three directional flame sensors to align itself with the source of fire:

| Left Sensor | Middle Sensor | Right Sensor | Robot Action | Drive Configuration |
| :---: | :---: | :---: | :---: | :--- |
| **LOW** | **LOW** | **LOW** | Move Forward | `IN1=HIGH`, `IN2=LOW`, `IN3=HIGH`, `IN4=LOW` |
| **HIGH**| **LOW** | **HIGH**| Move Forward | `IN1=HIGH`, `IN2=LOW`, `IN3=HIGH`, `IN4=LOW` |
| **LOW** | **HIGH**| **HIGH**| Turn Left | `IN1=LOW`, `IN2=HIGH`, `IN3=HIGH`, `IN4=LOW` |
| **HIGH**| **HIGH**| **LOW** | Turn Right | `IN1=HIGH`, `IN2=LOW`, `IN3=LOW`, `IN4=HIGH` |

### 🧯 Extinguishing Routine (`fireburn`)
Once the robot positions itself close to the fire, the primary drive system stops, and the fire mitigation sequence initiates:
1. The **Water Pump Relay** engages (`LOW` trigger).
2. The **Servo Motor** sweeps back and forth smoothly from `10°` to `170°` to wide-spray water over the area.
3. The servo returns to its center position (`90°`), and the water pump terminates safely.

### 📱 GSM Communication Loop
- **Gas Notification (`gassms`):** Transmits an text message (`"Gas Detected!!"`) to the designated emergency contact phone number.
- **Fire Alerts (`flamesms` & `flamecall`):** Dispatches an SMS (`"Flame Detected!!"`) and commands the SIM800L to dial out an emergency voice line over AT commands (`ATD+91...`).

---

## 💻 Software Installation & Setup

1. **Prerequisites:** Download and install the latest version of the [Arduino IDE](https://www.arduino.cc/en/software).
2. **Library Requirements:** Ensure the standard `Servo` library is available within your environment.
3. **Configure Phone Number:** Update the destination mobile number inside `Fire_Fighting_Robot.ino` with your region-specific country code:
   ```cpp
   sim800l.println("AT+CMGS=\"+91XXXXXXXXXX\"\r\n"); // Update target SMS number
   sim800l.println("ATD+91XXXXXXXXXX;");               // Update target calling number
   ```
4. **Compile & Upload:** Connect your Arduino board via your computer's USB port, select the correct COM Port and Board model (e.g., Arduino Uno), and hit **Upload**.

---

## 🛠️ Troubleshooting & Tips

* **Power Supply Issues:** The SIM800L module is notoriously power-hungry and can draw up to 2A bursts during network registration. If the module keeps resetting or failing to send messages, power it using an external 3.7V - 4.2V battery source (like an 18650 Li-ion cell) with a shared common ground to the Arduino, rather than relying solely on the Arduino's 5V pin.
* **Network Status LED:** Monitor the onboard LED on the SIM800L:
  * *Blinking every 1 second:* Searching for a network.
  * *Blinking every 3 seconds:* Successfully connected to the network.
* **Flame Sensor Calibration:** Each flame sensor module features a small blue potentiometer. Use a small screwdriver to adjust the sensitivity threshold so that ambient lighting doesn't accidentally trigger a false fire alarm.

---

## 🛡️ License

This project is open-source. Feel free to fork, modify, and improve the logic for educational, hobbyist, or real-world industrial safety implementations.

Developed with ❤️ by **[Mridul Saha](https://linkedin.com/in/mridulsaha)**
