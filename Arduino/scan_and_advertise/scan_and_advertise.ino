/*********************************************************************
 Scan & ADVERTISER  
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
#include <ArduinoJson.h>
BLEUart bleuart; // uart over ble

void setup()
{
 // Serial.begin(115200);
 // while ( !Serial ) delay(10);   // for nrf52840 with native usb
  
//  Serial.println("Bluefruit52 Scan + RSSI");
//  Serial.println("------------------------\n");

  // Setup the BLE LED to be enabled on CONNECT
  // Note: This is actually the default behaviour, but provided
  // here in case you want to control this LED manually
  Bluefruit.autoConnLed(true);

  // Config the peripheral connection with maximum bandwidth 
  // more SRAM required by SoftDevice
  // Note: All config***() function must be called before begin()
  Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);

  Bluefruit.begin();
  Bluefruit.setTxPower(8);    // Check bluefruit.h for supported values
  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);  
  Bluefruit.setName("scan & advertise module");  

  /* Set the LED interval for blinky pattern on BLUE LED */
  Bluefruit.setConnLedInterval(250);

  // Configure and Start BLE Uart Service
  bleuart.begin();

  // Set up Rssi changed callback
  Bluefruit.setRssiCallback(rssi_changed_callback);

  Bluefruit.Scanner.setRxCallback(scan_callback);
  Bluefruit.Scanner.restartOnDisconnect(true);
  Bluefruit.Scanner.filterRssi(-80);
  //Bluefruit.Scanner.filterUuid(BLEUART_UUID_SERVICE); // only invoke callback if detect bleuart service
  Bluefruit.Scanner.setInterval(160, 80);       // in units of 0.625 ms
  Bluefruit.Scanner.useActiveScan(true);        // Request scan response data
  Bluefruit.Scanner.start(0);                   // 0 = Don't stop scanning after n seconds

  // Set up and start advertising
  startAdv();

//  Serial.println("Please use Adafruit's Bluefruit LE app to connect");
}

void startAdv(void)
{
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addData(0, "rssi test\0", 10);

  // Include bleuart 128-bit uuid
  Bluefruit.Advertising.addService(bleuart);

  // Secondary Scan Response packet (optional)
  // Since there is no room for 'Name' in Advertising packet
  Bluefruit.ScanResponse.addName();
  
  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   * 
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html   
   */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  
}

void scan_callback(ble_gap_evt_adv_report_t* report)
{
  PRINT_LOCATION();
  uint8_t len = 0;
  uint8_t buffer[32];
  memset(buffer, 0, sizeof(buffer));
  String jsondata = "";
  DynamicJsonDocument doc(200);
 // JsonObject root = doc.to<JsonObject>();
  doc["rssi"] = report->rssi;
 
   
  // 원하는 peripheral_name 없으면 리턴하고 새 모듈 찾음
  /* Complete Local Name */
  if(Bluefruit.Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME, buffer, sizeof(buffer)))
  {
    const char* peripheral_name1 = "peripheral module";
    const char* peripheral_name2 = "scan & advertise module";
    
    for(int i=0; i<18; i++) {
      if(peripheral_name2[i] != buffer[i])
      {
        Bluefruit.Scanner.resume();
        return;    
      }

    }
    // Serial.printf("\n");
    //Serial.printf("%14s %s\n", "COMPLETE NAME", buffer);
    //Name = root.add(buffer);
    doc["name"]=buffer;
    //Serial.printBufferReverse(report->peer_addr.addr,6,':');
    // Serial.println();
    char mac[18];

    snprintf(mac, 18, "%02X-%02X-%02X-%02X-%02X-%02X",  
    report->peer_addr.addr[5],
    report->peer_addr.addr[4],
    report->peer_addr.addr[3],
    report->peer_addr.addr[2],
    report->peer_addr.addr[1],
    report->peer_addr.addr[0]
    );

      
    doc["uuid"]=mac;
    serializeJson(doc, Serial);
 
    memset(buffer, 0, sizeof(buffer));
  }
  else
  {
    Bluefruit.Scanner.resume();
    return;
  }
  
  /* Display the timestamp and device address */
  if (report->type.scan_response)
  {
   // Serial.printf("[SR%10d] Packet received from ", millis());
  }
  else
  {
  //  Serial.printf("[ADV%9d] Packet received from ", millis());
  }
  // MAC is in little endian --> print reverse
 // Serial.printBufferReverse(report->peer_addr.addr, 6, ':');
 // Serial.print("\n");

  /* Raw buffer contents */
 // Serial.printf("%14s %d bytes\n", "PAYLOAD", report->data.len);
  if (report->data.len)
  {
 //   Serial.printf("%15s", " ");
  //  Serial.printBuffer(report->data.p_data, report->data.len, '-');
   // Serial.println();
  }

  /* RSSI value */
 // Serial.printf("%14s %d dBm\n", "RSSI", report->rssi);

  /* Adv Type */
 // Serial.printf("%14s ", "ADV TYPE");
  if ( report->type.connectable ) 
  {
  //  Serial.print("Connectable ");
  }else
  {
  //  Serial.print("Non-connectable ");
  }
  
  if ( report->type.directed )
  {
  //  Serial.println("directed");
  }else
  {
  //  Serial.println("undirected");
  }

  /* Shortened Local Name */
  if(Bluefruit.Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_SHORT_LOCAL_NAME, buffer, sizeof(buffer)))
  {
  //  Serial.printf("%14s %s\n", "SHORT NAME", buffer);
    memset(buffer, 0, sizeof(buffer));
  }

  /* Complete Local Name */
  if(Bluefruit.Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME, buffer, sizeof(buffer)))
  {
  //  Serial.printf("%14s %s\n", "COMPLETE NAME", buffer);
    memset(buffer, 0, sizeof(buffer));
  }

  /* TX Power Level */
  if (Bluefruit.Scanner.parseReportByType(report, BLE_GAP_AD_TYPE_TX_POWER_LEVEL, buffer, sizeof(buffer)))
  {
  //  Serial.printf("%14s %i\n", "TX PWR LEVEL", buffer[0]);
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

  /* Check for BLE UART UUID */
  if ( Bluefruit.Scanner.checkReportForUuid(report, BLEUART_UUID_SERVICE) )
  {
  //  Serial.printf("%14s %s\n", "BLE UART", "UUID Found!");
  }

  /* Check for DIS UUID */
  if ( Bluefruit.Scanner.checkReportForUuid(report, UUID16_SVC_DEVICE_INFORMATION) )
  {
  //  Serial.printf("%14s %s\n", "DIS", "UUID Found!");
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

  // For Softdevice v6: after received a report, scanner will be paused
  // We need to call Scanner resume() to continue scanning
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
  // nothing to do
}

void connect_callback(uint16_t conn_handle)
{
//  Serial.println("Connected");

  // Get the reference to current connection
  BLEConnection* connection = Bluefruit.Connection(conn_handle);

  // Start monitoring rssi of this connection
  // This function should be called in connect callback
  // Input argument is value difference (to current rssi) that triggers callback
  connection->monitorRssi(10);
}

void rssi_changed_callback(uint16_t conn_hdl, int8_t rssi)
{
  (void) conn_hdl;
//  Serial.printf("Rssi = %d", rssi);
//  Serial.println();
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

//  Serial.println();
//  Serial.print("Disconnected, reason = 0x"); Serial.println(reason, HEX);
}
