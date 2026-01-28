#include "HomeAssistant.h"
#include <IRremote.hpp>

// IRrecv irrecv(RECV_PIN);

const uint16_t tclPowerRaw[] PROGMEM = {
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
  //IrReceiver.begin(IR_RECV_PIN, ENABLE_LED_FEEDBACK);
  IrSender.begin(IR_SEND_PIN);
}

void sendIRSignal(uint16_t* rawData) {
	IrSender.sendRaw_P(rawData, 51, FREQ);
}
