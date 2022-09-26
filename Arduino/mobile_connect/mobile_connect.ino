#include <ArduinoBLE.h>

void setup() {
  Serial.begin(115200);
  while (!Serial);
  pinMode(LED_BUILTIN, OUTPUT);
 
   // begin initialization
   if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
   }

  BLE.setLocalName("RSSI TEST");
  BLE.setAdvertisedServiceUuid("3de2545d-9de6-47ce-84a9-68c5ead85c67");
  // start advertising
  BLE.advertise();
  Serial.println("Bluetooth device active, waiting for connections...");
}


void loop() {
  // wait for a BLE central
  BLEDevice central = BLE.central();
  if (central) {a
    Serial.print("Connected to central: ");
    Serial.println("-----------------------");
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, HIGH);

    // print address
    Serial.print("Address: ");
    Serial.println(central.address());

    // print the local name, if present
    if (central.hasLocalName()) {
      Serial.print("Local Name: ");
      Serial.println(central.localName());
    }

    // print the RSSI
//    Serial.print("RSSI: ");
//    Serial.println(central.rssi());

    Serial.println();
    while (central.connected()) {
    // do nothing
    }

  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("Disconnected from central: ");
  Serial.println(central.address());
  }
}
