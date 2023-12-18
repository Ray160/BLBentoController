#include <Arduino.h>
#include "wifi-manager.h"
#include "web-server.h"
#include "mqttmanager.h"
#include "filesystem.h"
#include "types.h"
#include "leds.h"
#include "serialmanager.h"

void setup(){
    Serial.begin(115200);
    delay(100);
    Serial.println(F("Initializing"));
    Serial.println(ESP.getFreeHeap());
    setupRelay();
    setupFileSystem();
    
    delay(2000);
    setupSerial();
    if (!setupWifi()){
        return;
    };
    delay(2000);
    setupWebserver();

    delay(2000);

    setupMqtt();
}

void loop(){
    serialLoop();
    if (WiFi.status() == WL_CONNECTED){
        mqttloop();
        webserverloop();
        relayloop();
        
        //TODO: Get free heap to check for more headroom.
    }
}