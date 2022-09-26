/*
  Scan

  This example scans for Bluetooth® Low Energy peripherals and prints out their advertising details:
  address, local name, advertised service UUID's.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>

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
