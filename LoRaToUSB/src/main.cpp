#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include "settings.h"

SPIClass hspi(HSPI);
String loraString;

void setup() {

    Serial.begin(115200);
    Serial.setTimeout(40);

    hspi.begin(SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, SPI_SS_PIN);
    LoRa.setSPI(hspi);
    LoRa.setPins(SPI_SS_PIN, LORA_RESET_PIN, LORA_D0_PIN);
    LoRa.setSignalBandwidth(loraBandwidth);
    int ret = LoRa.begin(loraFrequency);
    LoRa.setSpreadingFactor(loraSF);
    LoRa.setTxPower(loraTxPower);
    LoRa.setTimeout(100);

    pinMode(2, OUTPUT);

    if (ret) Serial.println("LoRa config done!");
    else Serial.println("LoRa not working. Check the pinout");
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