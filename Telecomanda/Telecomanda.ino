#include <Arduino.h>
// the setup function runs once when you press reset or power the board

#define IR_PIN 7
#define RECV_PIN 4
#define DATA 0x20DF10EF

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

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  IrSender.begin(IR_PIN);
}

// the loop function runs over and over again forever
void loop() {
  // IrSender.sendNEC(DATA, 32);
  // IrSender.sendNECRaw(0xAB054F, 0);
  // Serial.println("Sent.");
  // if (IrReceiver.decode()) {
  //   if (IrReceiver.decodedIRData.protocol != UNKNOWN) {
  //       Serial.print("Protocol: ");
  //       Serial.print(IrReceiver.getProtocolString());
  //       Serial.print(" | Data: ");
  //       Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
  //   } else {
  //       // This was likely noise
  //       //Serial.println("Noise detected (Unknown Protocol)");
  //   }
  //   IrReceiver.resume();
  // }
  // if (IrReceiver.decode()) {
  //   // This command generates the EXACT array you need to copy
  //   IrReceiver.printIRResultRawFormatted(&Serial, true);
  //   IrReceiver.resume();
  // }
  IrSender.sendRaw(tclPowerRaw, sizeof(tclPowerRaw) / sizeof(tclPowerRaw[0]), 38);
  delay(5000);
}
