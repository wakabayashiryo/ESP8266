# Instruction install ESP8266 development envirment on arduino IDE

- ## Add ESP8266 borads on arduino

    1. input below URL in board manager URL box in enviroment configration
        > http://arduino.esp8266.com/stable/package_esp8266com_index.json   

        ![](./pictures/BoardManager.png)
    2. install esp8266 board 
        ![](./pictures/install.png)

- ## Require Device Configrations
    |contents|parameter|
    |:---:|:--:|
    |device|esp8266 generic|   
    |CpuFrequency|160MHz|
    |VTable|flash|
    |ResetMethod|ck|
    |CrystalFreq|26MHz|
    |FlashFreq|80MHz|
    |FlashMode|QIO|
    |FlashSize|4M1M|
    |led|2|
    |LwIPVariant|v2mss536|
    |Debug|Disabled|
    |DebugLevel|None|
    |FlashErase|None|  
    |UploadSpeed|115200bps| 
    can use 921600bps too.This speed can write to flash faster than 115200bps   
    - ### NOTE
        Must Set Crystal Frequency of board config to **26MHz**
    

- ## How to write program
    1. Wriring for write program
        ![](./pictures/wiring.png)
    1. Set to boot mode   
        While push down switch (Set IO0 Low),Reset ESP8266.

        |Mode|GPIO15 | GPIO2| GPIO0|
        |:--:|:--:|:--:|:--:|
        |UART Download Mode|Low|High|Low|
        |Flash Boot Mode|Low|High|High|
        |SD-Card Boot Mode|High|Low|Low|
    1. Write program using arduino IDE via UART

- ## Hardware difinition as Arduino(japanese)
    - [use ESP8266 as arduino](https://keijirotanabe.github.io/blog/2017/02/08/esp8266-how-to-170208/)   

- ## Free RTOS for ESP8266
    ***Currently development envirment for ESP8266 is not supported RTOS***   
    > https://github.com/esp8266/Arduino/issues/2118   
    
    user must use only single task program
- ## NOTE
    - ### truble shooting
        https://www.mgo-tec.com/blog-entry-esp8266-wroom-02-espr-developer-trouble-shooting.html

    - ### Easily setup WiFi & OTA upload   
        [WiFi Manager & Arduino OTA for ESP8266](./libraries/main/)

    - ### more information about ESP8266
        https://macsbug.wordpress.com/2015/06/21/information-of-esp8266-%E9%9A%8F%E6%99%82%E8%BF%BD%E5%8A%A0/

    - ### ESP8266 kanji(Japaneses) library SPIFFS version
        https://github.com/Tamakichi/ESP8266-KanjiFont-Library-SPIFFS

    - ### Triggering webhook of IFTTT 
        https://qiita.com/umi_kappa/items/89991cbf9832b629b419 

    - ### Kind of sleep modes 
        https://maro525.github.io/notebook/esp_sleep_mode.html  

 

Ambient(IoTプラットフォーム 

1. Download Arduino library that is compressed ZIP from [gihub](https://github.com/AmbientDataInc/Ambient_ESP8266_lib) 

2. Import library into Arduino IDE 

3. show exsample code and type your program

- ## Version

    |version  |Date|Contents|
    |:-----:|:-------:|:----------------|
    |ver1.0 |2018/12/15|add infomation of version|   
    |ver1.1 |2018/12/16|add infomation of version|   


- ## License Information
   This software is released under the MIT License, see LICENSE
