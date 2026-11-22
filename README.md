# ESP32 Medi Assist System 💊

An ESP32-based smart medicine reminder and monitoring system designed to help users take the correct medicine at the scheduled time.

The system uses six touch sensors to represent six medicine boxes. Each medicine has a specific time window. When the scheduled time arrives, the ESP32 activates a buzzer and red LED as a reminder. The user must select the correct medicine box.

If the correct box is selected, the alarm stops and the green LED indicates successful medicine intake.

If the wrong box is selected, the system generates a warning using the buzzer, red LED, and Bluetooth monitoring message.

The system also reports missed medicines through Bluetooth.

---

## Features

- Six medicine slots
- Six touch sensors for medicine selection
- Scheduled medicine reminders
- Buzzer alert
- Red LED warning/reminder indication
- Green LED successful-medicine indication
- Bluetooth monitoring using ESP32 Bluetooth
- Wrong medicine detection
- Missed medicine detection
- Serial Monitor status messages
- Bluetooth terminal monitoring
- Virtual-time mode for project demonstration and testing

---

## Medicine Schedule

| Medicine | Time | Purpose | Correct Box |
|---|---|---|---|
| Medicine 1 | 7:30 AM – 8:30 AM | Before Breakfast | Box 1 |
| Medicine 2 | 10:00 AM – 11:00 AM | After Breakfast | Box 2 |
| Medicine 3 | 12:30 PM – 1:00 PM | Before Lunch | Box 3 |
| Medicine 4 | 2:00 PM – 2:30 PM | After Lunch | Box 4 |
| Medicine 5 | 7:00 PM – 7:30 PM | Before Dinner | Box 5 |
| Medicine 6 | 9:30 PM – 10:00 PM | After Dinner | Box 6 |

---

## Hardware Components

- ESP32 Development Board
- 6 × Touch Sensors
- Buzzer
- Red LED
- Green LED
- 220 Ω resistors for LEDs
- Breadboard
- Jumper wires
- Medicine boxes/containers
- USB cable
- Android phone with Bluetooth terminal application

---

## Pin Configuration

| Component | ESP32 GPIO |
|---|---:|
| Touch Sensor 1 | GPIO 18 |
| Touch Sensor 2 | GPIO 19 |
| Touch Sensor 3 | GPIO 23 |
| Touch Sensor 4 | GPIO 4 |
| Touch Sensor 5 | GPIO 16 |
| Touch Sensor 6 | GPIO 17 |
| Buzzer | GPIO 5 |
| Red LED | GPIO 25 |
| Green LED | GPIO 26 |

---

## Working Principle

### 1. System Startup

After powering the ESP32, the system initializes the serial monitor, Bluetooth connection, six touch sensors, buzzer, and LEDs.

The Bluetooth device appears as:

```text
Medicine_Tracker
```

### 2. Medicine Reminder

When the virtual clock reaches a scheduled medicine time, the corresponding medicine slot becomes active.

The system:

- Turns ON the red LED
- Activates the buzzer
- Sends a medicine reminder through Bluetooth
- Displays the reminder on the Serial Monitor

Example:

```text
================================
       MEDICINE REMINDER
================================
Medicine 1 - Before Breakfast
Please take the correct medicine.
Correct Box: 1
================================
```

### 3. Correct Medicine

If the user selects the correct medicine box:

```text
Touch Sensor → Correct Box
        ↓
Medicine Accepted
        ↓
Buzzer OFF
Red LED OFF
Green LED ON
        ↓
Bluetooth SUCCESS message
```

Example:

```text
================================
       MEDICINE TAKEN
================================
Correct: Medicine 1 - Before Breakfast
Status: SUCCESS
Buzzer: OFF
Red LED: OFF
Green LED: ON
================================
```

### 4. Wrong Medicine

If the user selects an incorrect box:

```text
Wrong Touch Sensor
        ↓
Warning
        ↓
Buzzer
Red LED
        ↓
Bluetooth Warning
```

Example:

```text
⚠️ WARNING!
Wrong Box Selected: Box 3
Correct Box: Box 1
Medicine NOT taken.
```

### 5. Missed Medicine

If the user does not select the correct medicine before the scheduled time window expires, the system reports the medicine as missed.

Example:

```text
================================
       MEDICINE MISSED
================================
Medicine 3 - Before Lunch
Status: NOT TAKEN
Time window expired.
================================
```

---



## Bluetooth Monitoring

The ESP32 Bluetooth device name is:

```text
Medicine_Tracker
```

Connect the ESP32 to a Bluetooth serial terminal application.

The terminal can display:

- Medicine reminders
- Correct medicine confirmation
- Wrong medicine warnings
- Missed medicine notifications
- Current system status

---

## Virtual Time Demonstration

For project demonstration, the system uses a virtual clock.

The current implementation starts at:

```text
07:00 AM
```

and advances the virtual time using the program's timing mechanism.

For testing:

```text
1 real second = 1 virtual minute
```

This allows the complete daily medicine schedule to be demonstrated without waiting for the actual time.

---

## Example Demo

### Medicine 1

```text
07:30 AM
Medicine 1 Reminder

Red LED  → ON
Buzzer   → ON
```

Wrong box:

```text
Box 3 selected

WARNING!
Wrong Box Selected: Box 3
Correct Box: Box 1
```

Correct box:

```text
Box 1 selected

MEDICINE TAKEN
Status: SUCCESS

Buzzer   → OFF
Red LED  → OFF
Green LED → ON
```

---

## Software Requirements

- Arduino IDE
- ESP32 Board Package
- BluetoothSerial library
- ESP32 development board

---

## Installation

### Step 1: Install Arduino IDE

Install the Arduino IDE on your computer.

### Step 2: Install ESP32 Board Support

Add ESP32 board support to Arduino IDE.

### Step 3: Open the Project

Open:

```text
src/Medi_Assist_System.ino
```

### Step 4: Select Board

Select the appropriate ESP32 development board.

### Step 5: Select COM Port

Connect the ESP32 using USB and select the correct COM port.

### Step 6: Upload

Compile and upload the program.

### Step 7: Open Serial Monitor

Set:

```text
Baud Rate: 115200
```

### Step 8: Connect Bluetooth

Search for:

```text
Medicine_Tracker
```

and connect using a Bluetooth serial terminal application.

---

## Project Objective

The main objective of this project is to develop a simple embedded system that assists users in taking medicines at the correct time and selecting the correct medicine.

The project demonstrates practical concepts including:

- ESP32 programming
- Digital input/output
- Touch sensor interfacing
- Bluetooth communication
- Buzzer control
- LED indication
- Time-based scheduling
- Embedded system logic
- Event detection
- Status monitoring

---

## Future Improvements

The current project can be extended with:

- DS3231 RTC module for accurate timekeeping
- OLED/LCD display
- Wi-Fi connectivity
- Mobile application
- Cloud-based medicine monitoring
- Caregiver notification
- Medicine quantity monitoring
- Automatic medicine dispenser
- Voice reminders
- Battery backup
- Real-time notification system

---

## Project Status

**Prototype / Academic Embedded Systems Project**

Developed for learning and demonstration of embedded systems, sensor interfacing, Bluetooth communication, and time-based control.
