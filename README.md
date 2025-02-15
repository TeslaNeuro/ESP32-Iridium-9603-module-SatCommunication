# Gateway_SatComs_Example

This repository provides an example sketch for interfacing with the Iridium 9603 satellite communication module using the ESP32 and the Arduino framework. The sketch demonstrates basic operations like checking link quality, retrieving network time, sending messages, and checking for incoming messages over the satellite network.

## Overview
The `Gateway_SatComs_Example` sketch is designed to work with the Iridium 9603 module, enabling global communication through satellite networks. It includes the following functionality:
- **check9603linkquality**: Requests and returns the link quality from the Iridium network.
- **get9603time**: Requests the network time and returns it to the serial monitor.
- **send9603message**: Sends a custom message (e.g., sensor data) to the Iridium network.
- **check9603recieve**: Checks for incoming messages from the Iridium network, every 60 seconds.

This example assumes you are using an ESP32, but it can be adapted for other platforms by adjusting the serial connection.

## Setup Instructions

### Hardware Requirements:
1. **ESP32** (or compatible microcontroller with UART support)
2. **Iridium 9603 Module** (with a valid Iridium SIM card)
3. **Wiring**:
   - **Iridium 9603 TX** → **ESP32 RX (Pin 25)**
   - **Iridium 9603 RX** → **ESP32 TX (Pin 26)**
   - Power the Iridium 9603 module with a suitable power supply (typically 3.6V-5V depending on the module variant).
4. Optionally, you may use a **SoftwareSerial** setup (as noted in the comments) for other microcontrollers if not using the ESP32's hardware UARTs.

### Libraries:
- `IridiumSBD`: This library allows you to interface with the Iridium 9603 module for sending and receiving data. Make sure this is installed in your Arduino IDE.
- `time.h`: Standard time library for handling date and time functions.

### Code Breakdown:
1. **Pin Configuration**:
   - The **TX** and **RX** pins are defined for the ESP32 to communicate with the Iridium 9603 module. By default, **TX = 26** and **RX = 25**.

2. **Initialization**:
   - The `IridiumSerial` object is initialized to communicate with the Iridium 9603 module at 19200 baud using hardware serial.
   - The `start9603()`, `check9603FWversion()`, `check9603linkquality()`, and `get9603time()` functions initialize the Iridium module and perform initial checks.

3. **Sending a Test Message**:
   - A test message (JSON-like structure) is defined in `TESTmessage`, which includes sensor data. This message is sent to the Iridium network using the `send9603message()` function.

4. **Receiving Messages**:
   - The `check9603recieve()` function periodically checks for incoming messages from the Iridium network, logging results to the serial monitor every 60 seconds.

### Example Hardware:
- **ESP32**: You can use an ESP32 board with built-in UART capabilities. This board is a powerful option due to its dual-core processor, WiFi, and Bluetooth features, which can complement satellite communication.
- **Iridium 9603 Module**: The Iridium 9603 module is designed for remote, low-bandwidth communication. It operates via satellite and can be used in locations where other forms of communication (like cellular) are unavailable.

## Example Usage:

### Setting up the Hardware:
1. Connect the **TX** and **RX** pins of the Iridium 9603 module to the corresponding **RX** and **TX** pins of the ESP32 (Pin 25 and Pin 26).
2. Connect the Iridium module to a suitable power source (3.6V-5V).
3. Install the required libraries in your Arduino IDE:
   - `IridiumSBD`
   - `time.h`

### Uploading the Code:
1. Open the Arduino IDE and select your ESP32 board.
2. Copy the provided code into a new sketch.
3. Upload the code to the ESP32.

### Monitoring the Output:
1. Open the Serial Monitor in the Arduino IDE to observe the serial output.
2. The module will:
   - Display the Iridium module’s link quality.
   - Show the network time.
   - Send a test message to the network.
   - Periodically check for incoming messages.

## Additional Notes:
- **Diagnostics**: You can enable the `DIAGNOSTICS` flag to enable debugging mode and print detailed logs for troubleshooting.
- Ensure the Iridium module has a valid SIM card with an active satellite subscription for successful communication.

This repository offers a simple but effective introduction to working with Iridium satellite communications and can be expanded for more complex applications such as IoT or telemetry in remote locations.
