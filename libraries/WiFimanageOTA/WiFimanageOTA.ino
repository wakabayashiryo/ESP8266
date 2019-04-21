/*
 * Author: Ryo Wakabayashi
 *
 * Created on 2019/04/20, 
 * Version:1.0.0
 */
 #include <ESP8266WiFi.h>       // https://github.com/esp8266/Arduino

// needed for WiFiManager
#include <WiFiManager.h>        // https://github.com/tzapu/WiFiManager 
#include <DNSServer.h>          
#include <ESP8266WebServer.h>

// needed for ArduinoOTA           
#include <ArduinoOTA.h>         // http://arduino.esp8266.com/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html
#include <ESP8266mDNS.h>        
#include <WiFiUdp.h>

#define _DISABLE              0
#define _ENABLE               1

#define _MANAGER_SSID         "esp8266"
#define _MANAGER_PSK          "password"
#define _MANAGER_TIMEOUT      120 //second
#define _MANAGER_IP           IPAddress(192,168,82,66)
#define _MANAGER_GATEWAY      IPAddress(192,168,82,1)
#define _MANAGER_SUBNET       IPAddress(255,255,255,0)

#define _OTA_HOSTNAME         "esp8266"
#define _OTA_PASSWORD         "password"
#define _OTA_PORT             8266

#define _MANAGER_RST_SETTING  _DISABLE  // If the pin assined is low when power on, previous manager setting will be cleard 
#define _MANAGER_RST_PIN      2         // Recommend to set PULLUP

#define _OTA_INDICATE_LED     _DISABLE  // Two LEDs will be light when LOW 
#define _OTA_STATUS_PIN       16        // The LED flashes during OTA operation
#define _OTA_ERROR_PIN        13        // When Error ocoued, the LED turns on. Check Serial message

void setup(void) 
{  
  Serial.begin(115200);
  
  // WiFiManager
  // Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  
#if _MANAGER_RST_SETTING
  pinMode(_MANAGER_RST_PIN,INPUT_PULLUP);
  delay(100);
  if(digitalRead(_MANAGER_RST_PIN) == LOW);
    wifiManager.resetSettings();
#endif
  
  // the specified IP configuration instead of using DHCP in station mode.
  wifiManager.setAPStaticIPConfig(_MANAGER_IP, _MANAGER_GATEWAY, _MANAGER_SUBNET);
  wifiManager.setConfigPortalTimeout(_MANAGER_TIMEOUT);    

  // fetches ssid and pass from eeprom and tries to connect
  // and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect(_MANAGER_SSID, _MANAGER_PSK); 

  // ArduinoOTA
  ArduinoOTA.setHostname(_OTA_HOSTNAME);
  ArduinoOTA.setPassword(_OTA_PASSWORD);
  ArduinoOTA.setPort    (_OTA_PORT);
  
#if _OTA_INDICATE_LED
  ArduinoOTA.onStart([]() 
  {
    pinMode(_OTA_STATUS_PIN,OUTPUT);
    digitalWrite(_OTA_STATUS_PIN,LOW);
  });
  
  ArduinoOTA.onProgress([](uint32_t progress, uint32_t total) 
  {
    static bool stat = false;
    if((progress % 4) == 0)
    {
        stat = !stat;    
        digitalWrite(_OTA_STATUS_PIN,(stat) ? HIGH : LOW);
    }
  });
  
  ArduinoOTA.onEnd([]() 
  {
    digitalWrite(_OTA_STATUS_PIN,HIGH);
  });
#endif
  
  ArduinoOTA.onError([](ota_error_t error) 
  {
#if _OTA_INDICATE_LED
    pinMode(_OTA_ERROR_PIN,OUTPUT);
    digitalWrite(_OTA_ERROR_PIN,LOW);
#endif

    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
      Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR)
      Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR)
      Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR)
      Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR)
      Serial.println("End Failed");
  });

  //Start OTA process
  ArduinoOTA.begin();
  
  //The user cording area for initialize from here
 
  
}

void loop(void) 
{
  //Always must call ArduinoOTA.handle in loop 
  ArduinoOTA.handle();    

  //The user cording area from here


}
