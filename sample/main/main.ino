#include <ESP8266WiFi.h>       // https://github.com/esp8266/Arduino

void setup(void) 
{  
  Serial.begin(115200);
  
  wirelessConfig_begin();

  //The user cording area for initialize from here
  //module_initialize();
  
}

void loop(void) 
{
  //Always must call handle in loop 
  wirelessConfig_Handle();

  //The user cording area from here
  //Serial.print("Hello World");

}
