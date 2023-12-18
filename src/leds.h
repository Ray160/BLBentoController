#ifndef _LED
#define _LED

#include <Arduino.h>
#include "mqttparsingutility.h"

#if defined(ESP8266)
    const int relayPin = 0;
#elif defined(ESP32)
    const int redPin = 19;
    const int greenPin = 18;
    const int bluePin = 21;
    const int warmPin = 22;
    const int coldPin = 23;
#endif

unsigned long previousMillis = 0; 
const long offDelay = 300000; 
bool relayTimer = false;

void offRelay(){
    previousMillis = millis();
    relayTimer = true;
}

void updateRelay(){
    if (printerConfig.debuging){
        Serial.println(F("Updating relay"));

        Serial.println(printerVariables.stage);
        Serial.println(printerVariables.gcodeState);
        Serial.println(printerVariables.ledstate);
        Serial.println(printerVariables.hmsstate);
        Serial.println(printerVariables.parsedHMS);
    }
    //OFF

    if (printerVariables.online == false){ //printer offline
        digitalWrite(relayPin, LOW); //OFF
        if (printerConfig.debuging){
            Serial.println(F("Printer offline, Turning relay off"));
        };
        return;
    }

    if (printerVariables.stage == 14){ //Cleaning nozzle
        digitalWrite(relayPin, HIGH); //ON
        if (printerConfig.debuging){
            Serial.println(F("Cleaning nozzle, Turning relay on"));
        };
        return;
    }

    if (printerVariables.stage == 9){ //Scaning surface
        digitalWrite(relayPin, HIGH); //ON
        if (printerConfig.debuging){
            Serial.println(F("Scanning Surface, Turning relay on"));
        };
        return;
    }
    
     //RED

    if (printerConfig.errordetection == true){ // allow errordetection to turn ledstrip red
        if (printerVariables.parsedHMS == "Serious"){
            offRelay();
            if (printerConfig.debuging){
                Serial.println(F("Serious problem, Turning relay off"));
            };
            return;
        }

        if (printerVariables.parsedHMS == "Fatal"){
            offRelay();
            if (printerConfig.debuging){
                Serial.println(F("Fatal problem, Turning relay off"));
            };
            return;
        }

        if (printerVariables.stage == 6){ //Fillament runout
            offRelay();
            if (printerConfig.debuging){
                Serial.println(F("Fillament runout, Turning relay off"));
            };
            return;
        }

        if (printerVariables.stage == 17){ //Front Cover Removed
            offRelay();
            if (printerConfig.debuging){
                Serial.println(F("Front Cover Removed, Turning relay off"));
            };
            return;
        }

        if (printerVariables.stage == 20){ //Nozzle Temp fail
            offRelay();
            if (printerConfig.debuging){
                Serial.println(F("Nozzle Temp fail, Turning relay off"));
            };
            return;
        }

        if (printerVariables.stage == 21){ //Bed Temp Fail
            offRelay();
            if (printerConfig.debuging){
                Serial.println(F("Bed Temp fail, Turning relay off"));
            };
            return;
        }
    };

    //GREEN

    if ((millis() - printerVariables.finishstartms) <= 300000 && printerVariables.gcodeState == "FINISH"){
        offRelay();
        if (printerConfig.debuging){
            Serial.println(F("Finished print, Turning Leds green"));
            Serial.println(F("Leds should stay on for: "));
            Serial.print((millis() - printerVariables.finishstartms));
            Serial.print(F(" MS"));
        };
        return;
    }

    //ON

    if (printerVariables.stage == 0){ //Printing
        digitalWrite(relayPin, HIGH); //ON
        if (printerConfig.debuging){
            Serial.println(F("Printing, Turning relay On"));
        };
        return;
    }

    if (printerVariables.stage == -1){ // Idle
        offRelay();
        if (printerConfig.debuging){
            Serial.println(F("Idle, Turning relay off"));
        };
        return;
    }

    if (printerVariables.stage == -2){ //Offline
        offRelay();
        if (printerConfig.debuging){
            Serial.println(F("Stage -2, Turning relay off"));
        };
        return;
    }
}

void setupRelay() {
    pinMode(relayPin, OUTPUT);
    updateRelay();
}

void relayloop(){
    if((millis() - printerVariables.finishstartms) >= 300000 && printerVariables.gcodeState == "FINISH"){
        printerVariables.gcodeState == "IDLE";
        updateRelay();
    }
    if (millis() - previousMillis >= offDelay && relayTimer) {
        digitalWrite(relayPin, LOW); //OFF
        relayTimer = false;
        if (printerConfig.debuging){
            Serial.println(F("Relay disabling in: "));
            Serial.print((millis() - previousMillis));
            Serial.print(F(" MS"));
        };
    }
}

#endif