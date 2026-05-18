# ESP32 PS4 RC Robot 🚗🎮

A high-power 4WD RC robot built using an ESP32, dual TB6612FNG motor drivers, and a PS4 controller using the Bluepad32 library.

The robot supports:

* Differential steering
* Smooth joystick control
* Bluetooth gamepad connectivity
* Independent left/right motor drive
* PWM motor speed control

---

# 📌 Features

* 🎮 PS4 Wireless Controller Support
* ⚡ ESP32 Bluetooth Control
* 🚗 4 DC Motor Drive
* 🔄 Differential Steering
* 🎚 PWM Speed Control
* 🧠 Bluepad32 Library Integration
* 🔋 Separate Motor and ESP Power System
* 🛡 EMI Reduction with Capacitors

---

# 🧰 Hardware Used

| Component                            | Quantity |
| ------------------------------------ | -------- |
| ESP32 Dev Board                      | 1        |
| TB6612FNG Motor Driver               | 2        |
| DC Gear Motors                       | 4        |
| PS4 Controller                       | 1        |
| Li-ion Cells                         | 6        |
| Buck Converter                       | 1        |
| 0.1uF Ceramic Capacitors             | 4        |
| 470uF–2200uF Electrolytic Capacitors | Multiple |

---

# 🔌 Wiring Overview

## Left Driver

| ESP32 Pin | TB6612 Pin |
| --------- | ---------- |
| 21        | PWMA       |
| 22        | AIN1       |
| 23        | AIN2       |
| 19        | BIN1       |
| 18        | BIN2       |
| 5         | PWMB       |

## Right Driver

| ESP32 Pin | TB6612 Pin |
| --------- | ---------- |
| 13        | PWMA       |
| 14        | AIN1       |
| 12        | AIN2       |
| 27        | BIN1       |
| 26        | BIN2       |
| 25        | PWMB       |

## Other Connections

| ESP32 Pin | Function |
| --------- | -------- |
| 33        | STBY     |

---

# 🔋 Power System

## Recommended Setup

### Motors

* Powered directly from 3S battery pack (~11.1V)

### ESP32

* Powered using:

  * Separate buck converter
  * 5V regulated output

### Capacitors

* 0.1uF ceramic capacitor across each motor terminal
* 470uF–2200uF near motor drivers
* 1000uF near ESP32 power input

---

# 🛠 Libraries Required

## Bluepad32

Install from:

* Arduino Library Manager

or visit:

* https://github.com/ricardoquesada/bluepad32

---

# 🎮 Controls

| PS4 Control      | Action                |
| ---------------- | --------------------- |
| Left Joystick Y  | Forward / Backward    |
| Right Joystick X | Left / Right Steering |

---

# ⚙ PWM Configuration

```cpp
#define PWM_FREQ 1000
#define PWM_RES 8
```

Recommended PWM frequency:

* 1000Hz–2000Hz

Higher frequencies may create additional EMI and Bluetooth instability.

---

# ⚠ Common Issues

## Bluetooth Disconnects

Possible causes:

* Motor EMI
* Voltage dips
* Weak buck converter
* Missing capacitors
* Long motor wires

### Fixes

* Twist motor wires
* Add large capacitors
* Keep ESP32 away from motors
* Use separate regulated ESP32 power

---

# 🚀 Future Improvements

* PID Speed Control
* Current Monitoring
* Battery Voltage Display
* FPV Camera
* Autonomous Mode
* Obstacle Avoidance
* Suspension System

---

# 📷 Project Images

Add your build photos here.

Example:

```md
![Robot](images/robot.jpg)
```

---

# 📄 License

This project is open-source and available under the MIT License.

---

# 🙌 Credits

* ESP32 by Espressif
* Bluepad32 by Ricardo Quesada
* TB6612FNG Motor Driver

---

# ⭐ Support

If you like this project:

* Star the repository
* Fork the project
* Share improvements

