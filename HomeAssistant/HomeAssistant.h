#ifndef HOMEASSISTANT_H
#define HOMEASSISTANT_H

#include <Arduino.h>

extern const uint16_t tclPowerRaw[];

#define IR_SEND_PIN 7
#define IR_RECV_PIN 4
#define FREQ 38

void setupIR();
void sendIRSignal(uint16_t* rawData);

#endif