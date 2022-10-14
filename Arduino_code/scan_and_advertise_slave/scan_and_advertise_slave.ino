#include <bluefruit.h>
#include <ArduinoJson.h>

uint8_t prev[40];

void setup()
{  
  Bluefruit.autoConnLed(true);
  Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);
  Bluefruit.begin();
  Bluefruit.setTxPower(8);    
  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);  
  Bluefruit.setName("PE3");  
  Bluefruit.setConnLedInterval(250);
    
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
  Bluefruit.ScanResponse.addName();
  Bluefruit.Advertising.addData(0, "123\0", 4);
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);
}

void scan_callback(ble_gap_evt_adv_report_t* report)
{
  uint8_t buffer[32];
  memset(buffer, 0, sizeof(buffer));
  
  if(Bluefruit.Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME, buffer, sizeof(buffer)))
  {
    const char* tag = "TAG";
    
     if(!(strcmp(tag,(const char*)buffer) == 0)) {
      Bluefruit.Scanner.resume();
      return;
    }
    
    memcpy(prev, Bluefruit.Advertising.getData(), 11);
    int val = -(report->rssi);
    prev[7] = '-';
    prev[8] = val/10 + '0';
    prev[9] = val%10 + '0';
    prev[10] = 0;
    Bluefruit.Advertising.setData(prev, 11);
  }
  Bluefruit.Scanner.resume();
}

void loop() 
{
  // nothing to do
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

void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;
}
