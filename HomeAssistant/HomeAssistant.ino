#include "commands.h"
#include "HomeAssistant.h"

String currentMsg;

void setup() {
  Serial.begin(9600);
  setupIR();
}

void loop() {
  if (Serial.available() > 0) {
    currentMsg = Serial.readStringUntil('\n');
    currentMsg.trim();
  }

  if (currentMsg == TV_ON){
    sendIRSignal(tclPowerRaw);
    currentMsg = "";
  }
  delay(5000);
}
