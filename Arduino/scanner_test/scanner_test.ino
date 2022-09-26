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

long long setupTime = millis();

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1);
  }

  Serial.println("Bluetooth® Low Energy Central scan");
  BLE.setLocalName("RSSI Scanner");
  // start scanning for peripheral
  BLE.setEventHandler(BLEDiscovered, discovered);
  BLE.scanForName("RSSI TEST");
}

void logDevice(BLEDevice peripheral) {
  // check if a peripheral has been discovered
      // discovered a peripheral
      // Serial.println("Discovered a peripheral");
      // Serial.println("-----------------------");

      // print exceed time
      // Serial.print("Exceed time: ");
      // Serial.println(millis() - setupTime);
  
      // print address
      // Serial.print("Address: ");
      // Serial.println(peripheral.address());
  
      // print the local name, if present
      if (peripheral.hasLocalName() && peripheral.localName() == "RSSI TEST") {
        // Serial.print("Local Name: ");
        // Serial.println(peripheral.localName());
        Serial.println(peripheral.rssi());
        // Serial.println();
      }
  
      // print the advertised service UUIDs, if present
      if (peripheral.hasAdvertisedServiceUuid()) {
        // Serial.print("Service UUIDs: ");
        for (int i = 0; i < peripheral.advertisedServiceUuidCount(); i++) {
          // Serial.print(peripheral.advertisedServiceUuid(i));
          // Serial.print(" ");
        }
        // Serial.println();
      }
  
      // print the RSSI
      // Serial.print("RSSI: ");
      // Serial.println(peripheral.rssi());
      // Serial.println();
}

void discovered(BLEDevice peripheral) {
  BLE.stopScan();
  logDevice(peripheral);
  delay(250); // ms
  BLE.scanForName("RSSI TEST");
}

void loop() {
  BLE.poll(1000);
}
