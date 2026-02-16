#ifndef HOMEASSISTANT_H
#define HOMEASSISTANT_H

#include <Arduino.h>

extern const uint16_t tclPowerRaw[];
extern String currentMsg;
extern String msg;
extern bool tv_on;
extern int typewriterIdx;
extern int lastUpdate;
extern int temp;
extern int humid;
#define IR_SEND_PIN 7
#define IR_RECV_PIN 6
#define TEMP_HUMID_PIN 5
#define FREQ 38

void setupIR();
void sendIRSignal(const uint16_t* rawData);

void setupOLED();
void printOLED(String msg);

void readTempAndHumidity();
#endif