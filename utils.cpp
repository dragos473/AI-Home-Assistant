#include <Arduino.h>


#define IR_SEND_PIN 7
#define IR_RECV_PIN 4

#include <IRremote.hpp>

IRrecv irrecv(RECV_PIN);

uint16_t tclPowerRaw[] = {
  4050, 3900,  // Header
  550, 1950, 550, 1950, 550, 1950, 550, 1900, // Data bits
  600, 900,  550, 950,  550, 1950, 550, 950,
  550, 1900, 600, 900,  600, 1900, 550, 950,
  550, 950,  550, 950,  550, 950,  550, 950,
  550, 1950, 550, 1900, 550, 950,  550, 1950,
  550, 950,  550, 1900, 600, 900,  550, 1950,
  550 // Stop bit
};

void setupIR() {
	IrReceiver.begin(IR_RECV_PIN, ENABLE_LED_FEEDBACK);
	IrSender.begin(IR_SEND_PIN);
}

void sendIRSignal(const uint16_t rawData) {
	IrSender.sendRaw(rawData, sizeof(rawData) / sizeof(uint16_t), 38);

}
