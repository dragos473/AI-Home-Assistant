#include "commands.h"
#include "HomeAssistant.h"

void setup() {
  Serial.begin(9600);
  setupIR();
  setupOLED();
}

void loop() {
  if (Serial.available() > 0) {
    currentMsg = Serial.readStringUntil('\n');
    currentMsg.trim();

    if (currentMsg == TV_ON){
      if (!tv_on) {
      sendIRSignal(tclPowerRaw);
      tv_on = true;
      }
    } else if (currentMsg == TV_OFF) {
      if (tv_on) {
      sendIRSignal(tclPowerRaw);
      tv_on = false;

      }
    } else if (currentMsg == GET_TEMP) {
        readTempAndHumidity();
        sprintf(currentMsg.c_str(), "Temp:%d \xB0\C  Humidity:%d%%\n", temp, humid);
        currentMsg.trim();
    } else if (currentMsg == TV_OFF) {
      
    } else {
      msg = currentMsg;
    }
  }

  // currentMsg = msg;
  //Serial.print(msg);
  printOLED(msg);
  

  delay(200);
}
