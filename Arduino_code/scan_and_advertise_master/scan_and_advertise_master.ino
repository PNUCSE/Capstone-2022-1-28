#include <bluefruit.h>
#include <ArduinoJson.h>

int prev_val;

void setup()
{  
  Serial.begin(9600);
  while ( !Serial ) delay(10);  

  //Bluefruit.autoConnLed(true);
  Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);
  Bluefruit.begin();
  Bluefruit.setTxPower(-40);    
  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);  
  Bluefruit.setName("module 4");  
  //Bluefruit.setConnLedInterval(250);
  
  Bluefruit.setRssiCallback(rssi_changed_callback);
  Bluefruit.Scanner.setRxCallback(scan_callback);
  Bluefruit.Scanner.restartOnDisconnect(true);
  Bluefruit.Scanner.filterRssi(-80);
  Bluefruit.Scanner.setInterval(32, 32); // in unit of 40 ms       
  Bluefruit.Scanner.useActiveScan(true);        
  Bluefruit.Scanner.start(0);
}


void scan_callback(ble_gap_evt_adv_report_t* report)
{
  uint8_t buffer[32];
  char RSSI[4];
  char val_buffer[5];
  memset(buffer, 0, sizeof(buffer));
  DynamicJsonDocument doc(200);

  
  if(Bluefruit.Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME, buffer, sizeof(buffer)))
  {
    const char* tag = "TAG";
    const char* pe1 = "PE1";
    const char* pe2 = "PE2";
    const char* pe3 = "PE3";

    if(!(strcmp(tag,(const char*)buffer) == 0 || strcmp(pe1,(const char*)buffer) == 0 || 
    strcmp(pe2,(const char*)buffer) == 0 || strcmp(pe3,(const char*)buffer) == 0))
    {
      Bluefruit.Scanner.resume();
      return;
    }
    doc["name"] = buffer;

    if(strcmp(tag,(const char*)buffer) == 0)
    {
      doc["rssi"] = String(report->rssi);

//      for(int i=0; i<14; i++) {
//        Serial.print(i);
//        Serial.print(char(report->data.p_data[i]));
//        Serial.print(' ');
//      }
//      Serial.println();
      memcpy(val_buffer, report->data.p_data+8, 6);
      doc["val"] = String(val_buffer);
      int cur_val = (val_buffer[0]-'0')*10000 + (val_buffer[1]-'0')*1000 + (val_buffer[2]-'0')*100 + (val_buffer[3]-'0')*10 + (val_buffer[4]-'0')*1;
      if(prev_val >= cur_val) {
        Bluefruit.Scanner.resume();
        prev_val = 0;
        return;
      }
      prev_val = cur_val;
      if(cur_val >= 89000) {
        prev_val = 0;
      }
    }
    else
    {
      memcpy(RSSI, report->data.p_data+7, 4);
      doc["rssi"] = String(RSSI);
    }
    serializeJson(doc, Serial);
//    Serial print for Debug  
//    if (report->data.len)
//    {
//      Serial.printf("%15s", " ");
//      for(int i=0; i<10; i++) {
//        Serial.print(char(report->data.p_data[i]));
//        Serial.print(' ');
//      }
//    }
    Serial.println();
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
  //connection->monitorRssi(10);
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
