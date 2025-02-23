/*
 * Name: ESP32_SatCom_Interfacing
 * Version: 02
 * Author: Arshia Keshvari
 * Date: 15th of Febuary 2025
 * 
 * Description:
 * This sketch was written for an Arduino Uno originally where software serial is required
 * This sketch performs the following actions
 * 'check9603linkquality' Requests the link quality and returns on serial port
 * 'get9603time' Requests the network time and returns on serial port
 * 'send9603message' sends a message to the network in for form of a char*
 * 'check9603recieve' checks for messages on the network
 * loops checks for messages every 60 seconds.
 *
 */

#include <IridiumSBD.h>
#include <time.h>

#define TX 26 // ESP32 Microcontroller TX 
#define RX 25 // ESP32 Microcontroller RX

// #include <SoftwareSerial.h>
// const byte rxPin = 2;
// const byte txPin = 3;
// SoftwareSerial mySerial(rxPin, txPin);

//Setup Serial for ESP32
#include <HardwareSerial.h>
HardwareSerial IridiumSerial(1);

char* codeNAME = "Gatway_SatComs_Example";
char* codeVER = "03";

//Setup for Iridium module
#define DIAGNOSTICS false // Debug mode
//#define IridiumSerial mySerial
IridiumSBD modem(IridiumSerial);
char version[12];
int signalQuality = -1;
int err;
char* TESTmessage = "{'Sensor Report': {'last recording': [{'id': '123','position latitude': '17.66586','position longitude': '-156.18582','temperature_c': '12','humidity': '52','co2ppm': '10000','linkquality': '4','battery': '74','fwver': '03'},]}}";
uint8_t buffer[200] = { 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };
struct tm t;
static bool messageSent = false;
size_t bufferSize = sizeof(buffer);

void setup()
{
  
  Serial.begin(115200);
  delay(2000); // Give time for Serial Monitor to start
  Serial.print("\nCode: " );
  Serial.println(codeNAME);
  Serial.print("Version: ");
  Serial.println(codeVER);
  Serial.print("\nSTARTUP...\n");
  // Initialize UART2 for Iridium communication
  IridiumSerial.begin(19200, SERIAL_8N1, RX, TX); // Set baud rate for Iridium module (19200) and use UART2
  //IridiumSerial.begin(19200);
  Serial.println("IridiumSerial initialized.");

  start9603();
  check9603FWversion();
  check9603linkquality();
  get9603time();
  send9603message(TESTmessage);
}

void loop()
{
  check9603recieve();
  Serial.print("No Messages... checking again in 60 seconds...\n");
  delay(60000);
 }



