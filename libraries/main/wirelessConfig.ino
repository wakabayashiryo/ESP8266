/*
 * File:wirelessConfig.ino
 * Author: Ryo Wakabayashi
 *
 * Created on 2019/04/20, 
 * Version:1.2.0
 * 
 */

// needed for WiFiManager
#include <WiFiManager.h>        // https://github.com/tzapu/WiFiManager 
#include <DNSServer.h>          
#include <ESP8266WebServer.h>

// needed for ArduinoOTA           
#include <ArduinoOTA.h>         // http://arduino.esp8266.com/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html
#include <ESP8266mDNS.h>        
#include <WiFiUdp.h>

#define _MANAGER_SSID         "esp8266"
#define _MANAGER_PSK          "password"
#define _MANAGER_TIMEOUT      120 //second
#define _MANAGER_IP           IPAddress(192,168,82,66)
#define _MANAGER_GATEWAY      IPAddress(192,168,82,1)
#define _MANAGER_SUBNET       IPAddress(255,255,255,0)

#define _OTA_HOSTNAME         "esp8266"
#define _OTA_PASSWORD         "password"
#define _OTA_PORT             8266

/* The LED for indicating operation(NOTE:active LOW)
 * Turn on : connecting with AP
 * Flush   : OTA uploading
 * Turn off: ocoured error or disconnected
 */
#define _WC_STATUS_PIN      16


void wirelessConfig_begin(void)
{
  // WiFiManager
  // Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  // Setup the LED for status
  pinMode(_WC_STATUS_PIN,OUTPUT);
  digitalWrite(_WC_STATUS_PIN,HIGH);
    
  // The specified IP configuration instead of using DHCP in station mode.
  wifiManager.setAPStaticIPConfig(_MANAGER_IP, _MANAGER_GATEWAY, _MANAGER_SUBNET);
  wifiManager.setConfigPortalTimeout(_MANAGER_TIMEOUT);    

  // fetches ssid and pass from eeprom and tries to connect
  // and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect(_MANAGER_SSID, _MANAGER_PSK); 

  // Turn on the LED. it means successful connected
  digitalWrite(_WC_STATUS_PIN,LOW);
  Serial.println("Successful autoConnecting process");
  Serial.print("Ready\nIP address: "); Serial.println(WiFi.localIP());

  // Setup ArduinoOTA
  ArduinoOTA.setHostname(_OTA_HOSTNAME);
  ArduinoOTA.setPassword(_OTA_PASSWORD);
  ArduinoOTA.setPort    (_OTA_PORT);
  
  ArduinoOTA.onStart([]() 
  {
    if (ArduinoOTA.getCommand() == U_FLASH) 
      Serial.println(F("Start updating sketch"));
    else 
      Serial.println(F("Start updating filesystem"));
  });
  
  ArduinoOTA.onProgress([](uint32_t progress, uint32_t total) 
  {
    static bool stat = false;
    if((progress % 4) == 0)
    {
        stat = !stat;    
        digitalWrite(_WC_STATUS_PIN,(stat) ? HIGH : LOW);
    }
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  
  ArduinoOTA.onEnd([]() 
  {
    digitalWrite(_WC_STATUS_PIN,LOW);
    Serial.println(F("\nEnd"));
  });
  
  ArduinoOTA.onError([](ota_error_t error) 
  {    
    digitalWrite(_WC_STATUS_PIN,HIGH);
    
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
      Serial.println(F("Auth Failed"));
    else if (error == OTA_BEGIN_ERROR)
      Serial.println(F("Begin Failed"));
    else if (error == OTA_CONNECT_ERROR)
      Serial.println(F("Connect Failed"));
    else if (error == OTA_RECEIVE_ERROR)
      Serial.println(F("Receive Failed"));
    else if (error == OTA_END_ERROR)
      Serial.println(F("End Failed"));
  });

  //Start OTA process
  ArduinoOTA.begin();
  
  Serial.println(F("Starting ArduinoOTA."));
};

void wirelessConfig_Handle(void)
{
  //Always must call ArduinoOTA.handle in loop 
  ArduinoOTA.handle();    
}
