#ifndef SETTITNGS_H
#define SETTITNGS_H

#include <stdint.h>

#define SPI_SCK_PIN  25
#define SPI_MISO_PIN 22
#define SPI_MOSI_PIN 19
#define SPI_SS_PIN   26

#define LORA_RESET_PIN 14
#define LORA_D0_PIN    27

float loraFrequency = 439E6;
float loraBandwidth = 125E3;
uint8_t loraSF = 7;
uint8_t loraTxPower = 14;

#endif