#include <Adafruit_ATParser.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BLEBattery.h>
#include <Adafruit_BLEEddystone.h>
#include <Adafruit_BLEGatt.h>
#include <Adafruit_BLEMIDI.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BluefruitLE_UART.h>
//
///*
//  LED
//  This example creates a BLE peripheral with service that contains a
//  characteristic to control an LED.
//  The circuit:
//  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
//    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.
//  You can use a generic BLE central app, like LightBlue (iOS and Android) or
//  nRF Connect (Android), to interact with the services and characteristics
//  created in this sketch.
//  This example code is in the public domain.
//*/
//
//#include <ArduinoBLE.h>
//
//BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service
//
//// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
//BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
//
//const int ledPin = LED_BUILTIN; // pin to use for the LED
//
//void setup() {
//  Serial.begin(9600);
//  while (!Serial);
//
//  // set LED pin to output mode
//  pinMode(ledPin, OUTPUT);
//
//  // begin initialization
//  if (!BLE.begin()) {
//    Serial.println("starting BLE failed!");
//
//    while (1);
//  }
//
//  // set advertised local name and service UUID:
//  BLE.setLocalName("LED");
//  BLE.setAdvertisedService(ledService);
//
//  // add the characteristic to the service
//  ledService.addCharacteristic(switchCharacteristic);
//
//  // add service
//  BLE.addService(ledService);
//
//  // set the initial value for the characeristic:
//  switchCharacteristic.writeValue(0);
//
//  // start advertising
//  BLE.advertise();
//
//  Serial.println("BLE LED Peripheral");
//}
//
//void loop() {
//  // listen for BLE peripherals to connect:
//  BLEDevice central = BLE.central();
//
//  // if a central is connected to peripheral:
//  if (central) {
//    Serial.print("Connected to central: ");
//    // print the central's MAC address:
//    Serial.println(central.address());
//
//    // while the central is still connected to peripheral:
//    while (central.connected()) {
//      // if the remote device wrote to the characteristic,
//      // use the value to control the LED:
//      if (switchCharacteristic.written()) {
//        if (switchCharacteristic.value()) {   // any value other than 0
//          Serial.println("LED on");
//          digitalWrite(ledPin, HIGH);         // will turn the LED on
//        } else {                              // a 0 value
//          Serial.println(F("LED off"));
//          digitalWrite(ledPin, LOW);          // will turn the LED off
//        }
//      }
//    }
//
//    // when the central disconnects, print it out:
//    Serial.print(F("Disconnected from central: "));
//    Serial.println(central.address());
//  }
//}

/*
  Scan

  This example scans for Bluetooth® Low Energy peripherals and prints out their advertising details:
  address, local name, advertised service UUID's.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.

  This example code is in the public domain.
*/

//#include <ArduinoBLE.h>

void setup() {
//  Serial.begin(9600);
//  while (!Serial);

  // begin initialization
  if (!BLE.begin()) {
//    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1);
  }

  //Serial.println("Bluetooth® Low Energy Central scan");
  BLE.setLocalName("RSSI TEST");
  // start advertising
  BLE.advertise();
}

void loop() {
  // check if a central has been discovered
  BLEDevice central = BLE.central();
}
