#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

SPIClass hspi(HSPI);
String loraString;

void setup() {

    Serial.begin(115200);
    Serial.setTimeout(40);

    hspi.begin(25, 22, 19, 26);
    LoRa.setSPI(hspi);
    LoRa.setPins(26, 14, 27);
    LoRa.setSignalBandwidth(125E3);
    LoRa.begin(439E6);
    LoRa.setTimeout(100);

    pinMode(2, OUTPUT);
}

void loop() {

    // USB to LoRa:
    if (Serial.available()) {

        loraString = Serial.readString();

        LoRa.beginPacket();
        LoRa.println(loraString);
        LoRa.endPacket();
    }

    // LoRa to USB:
    if (LoRa.parsePacket()) {
        while (LoRa.available()) {

            digitalWrite(2, digitalRead(2));
            loraString = LoRa.readString();
            Serial.print(loraString);
        }
    }

    vTaskDelay(1);
}