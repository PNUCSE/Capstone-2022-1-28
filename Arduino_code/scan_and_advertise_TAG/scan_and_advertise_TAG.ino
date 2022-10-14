/*********************************************************************
 ADVERTISER
 This is an example for our nRF52 based Bluefruit LE modules
 Pick one up today in the adafruit shop!
 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!
 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/
#include <bluefruit.h>

uint8_t buffer[40];
bool flag = true;
int val = 0;
uint8_t prev[40];

void setup()
{  
  //Bluefruit.autoConnLed(true);
  Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);
  Bluefruit.begin();
  Bluefruit.setTxPower(8);
  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);  
  Bluefruit.setName("TAG");  
  Bluefruit.setRssiCallback(rssi_changed_callback);
  //Bluefruit.setConnLedInterval(250);

  startAdv();
}

void startAdv(void)
{
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addData(0, "123456", 6);
  Bluefruit.ScanResponse.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 32);    // in unit of 40 ms, interval 32 => 20ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  
}

void loop()
{
    memcpy(prev, Bluefruit.Advertising.getData(), 16);
    for(int i=0; i<15; i++) {
        Serial.print(i);
        Serial.print(char(prev[i]));
        Serial.print(' ');
      }
    Serial.println();
    prev[8] = (val)/10000%10 + '0';
    prev[9] = (val)/1000%10 + '0';
    prev[10] = (val)/100%10 + '0';
    prev[11] = (val)/10%10 + '0';
    prev[12] = (val)%10 + '0';
    prev[13] = 0;
    val++;
    
    Bluefruit.Advertising.setData(prev, 16);
    
    if(val>=90000) val = 0;
  // do nothing
}

void connect_callback(uint16_t conn_handle)
{
  BLEConnection* connection = Bluefruit.Connection(conn_handle);

  // Start monitoring rssi of this connection
  // This function should be called in connect callback
  // Input argument is value difference (to current rssi) that triggers callback
  // connection->monitorRssi(1);
}

void rssi_changed_callback(uint16_t conn_hdl, int8_t rssi)
{
  (void) conn_hdl;
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;
}
