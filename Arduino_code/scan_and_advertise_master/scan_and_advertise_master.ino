#include <bluefruit.h>
#include <ArduinoJson.h>

BLEUart bleuart; 
char rssi_buffer[4];

// uuid값 임의로 넣었는데 작동 되는지 테스트 필요, 안되면 찾아서 넣어야함
BLEClientService UService(0xcba174a9aed54c2f8ea998de50b2bb38);
BLEClientCharacteristic PeripheralModule_1(0x4007f5d26d384249b4b2c48062eaf30a);  
BLEClientCharacteristic PeripheralModule_2(0x6d813cfd2937495dbc1be91aa6742eca);
BLEClientCharacteristic PeripheralModule_3(0xeb00def4f7e94bb4a1d148dd87098f13);
  
void setup()
{  
  Serial.begin(9600);
  while ( !Serial ) delay(10);  


  Bluefruit.autoConnLed(true);
  Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);
  Bluefruit.begin();
  Bluefruit.setTxPower(8);    
  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);  
  Bluefruit.setName("module 4");  
  Bluefruit.setConnLedInterval(250);
  
  UService.begin();
  PeripheralModule_1.begin();
  PeripheralModule_2.begin();
  PeripheralModule_3.begin();
  bleuart.begin();
  
  Bluefruit.setRssiCallback(rssi_changed_callback);
  Bluefruit.Scanner.setRxCallback(scan_callback);
  Bluefruit.Scanner.restartOnDisconnect(true);
  Bluefruit.Scanner.filterRssi(-80);
  Bluefruit.Scanner.setInterval(160, 80);       
  Bluefruit.Scanner.useActiveScan(true);        
  Bluefruit.Scanner.start(0);                   
  startAdv();
}

void startAdv(void)
{
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.ScanResponse.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    
  Bluefruit.Advertising.setFastTimeout(30);      
  Bluefruit.Advertising.start(0);                  
}

void scan_callback(ble_gap_evt_adv_report_t* report)
{
  PRINT_LOCATION();
  uint8_t len = 0;
  uint8_t buffer[32];
  memset(buffer, 0, sizeof(buffer));
  String jsondata = "";
  DynamicJsonDocument doc(200);
  doc["rssi"] = String(report->rssi);
 
  if(Bluefruit.Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME, buffer, sizeof(buffer)))
  {
    const char* peripheral_name1 = "peripheral";
    //const char* peripheral_name2 = "module ";
    
    for(int i=0; i<7; i++) {
      if(peripheral_name1[i] != buffer[i])
      {
        Bluefruit.Scanner.resume();
        return;
      }
    }
    doc["name"]=buffer;
    
    serializeJson(doc, Serial);

    memset(buffer, 0, sizeof(buffer));
  }
  else
  {
    Bluefruit.Scanner.resume();
    return;
  }

  /* Shortened Local Name */
  if(Bluefruit.Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_SHORT_LOCAL_NAME, buffer, sizeof(buffer)))
  {
    memset(buffer, 0, sizeof(buffer));
  }

  /* Complete Local Name */
  if(Bluefruit.Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME, buffer, sizeof(buffer)))
  {
    memset(buffer, 0, sizeof(buffer));
  }

  /* TX Power Level */
  if (Bluefruit.Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_TX_POWER_LEVEL, buffer, sizeof(buffer)))
  {
    memset(buffer, 0, sizeof(buffer));
  }

  /* Check for UUID16 Complete List */
  len = Bluefruit.Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_COMPLETE, buffer, sizeof(buffer));
  if ( len )
  {
    printUuid16List(buffer, len);
  }

  /* Check for UUID16 More Available List */
  len = Bluefruit.Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_MORE_AVAILABLE, buffer, sizeof(buffer));
  if ( len )
  {
    printUuid16List(buffer, len);
  }

  /* Check for UUID128 Complete List */
  len = Bluefruit.Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_128BIT_SERVICE_UUID_COMPLETE, buffer, sizeof(buffer));
  if ( len )
  {
    printUuid128List(buffer, len);
  }

  /* Check for UUID128 More Available List */
  len = Bluefruit.Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_128BIT_SERVICE_UUID_MORE_AVAILABLE, buffer, sizeof(buffer));
  if ( len )
  {
    printUuid128List(buffer, len);
  }

  /* Check for Manufacturer Specific Data */
  len = Bluefruit.Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA, buffer, sizeof(buffer));
  if (len)
  {
    Serial.printf("%14s ", "MAN SPEC DATA");
    Serial.printBuffer(buffer, len, '-');
    Serial.println();
    memset(buffer, 0, sizeof(buffer));
  }  

  Serial.println();

  Bluefruit.Scanner.resume();
}

void printUuid16List(uint8_t* buffer, uint8_t len)
{
  Serial.printf("%14s %s", "16-Bit UUID");
  for(int i=0; i<len; i+=2)
  {
    uint16_t uuid16;
    memcpy(&uuid16, buffer+i, 2);
    Serial.printf("%04X ", uuid16);
  }
  Serial.println();
}

void printUuid128List(uint8_t* buffer, uint8_t len)
{
  (void) len;
  Serial.printf("%14s %s", "128-Bit UUID");

  // Print reversed order
  for(int i=0; i<16; i++)
  {
    const char* fm = (i==4 || i==6 || i==8 || i==10) ? "-%02X" : "%02X";
    Serial.printf(fm, buffer[15-i]);
  }

  Serial.println();  
}

void loop() 
{
  if(Bluefruit.connected()){
    DynamicJsonDocument doc(200);
    int a_num = PeripheralModule_1.read32();
    doc["name"] = "module 1";
    doc["rssi"] = String(a_num);
    serializeJson(doc, Serial);

    int b_num = PeripheralModule_2.read32();
    doc["name"] = "module 2";
    doc["rssi"] = String(b_num);
    serializeJson(doc, Serial);
    
    int c_num = PeripheralModule_3.read32();
    doc["name"] = "module 3";
    doc["rssi"] = String(c_num);
    serializeJson(doc, Serial);
  }
}

void connect_callback(uint16_t conn_handle)
{
  BLEConnection* connection = Bluefruit.Connection(conn_handle);
  connection->monitorRssi(10);
}

void rssi_changed_callback(uint16_t conn_hdl, int8_t rssi)
{
  (void) conn_hdl;
}

/**
 * Callback invoked when a connection is dropped
 * @param conn_handle connection where this event happens
 * @param reason is a BLE_HCI_STATUS_CODE which can be found in ble_hci.h
 */
void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;
}
