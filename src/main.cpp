#include "../lib/commands.h"
#include "../lib/HomeAssistant.h"

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
      sendIRSignal(tclPowerRaw, TCL_SIZE);
      tv_on = true;
      }
    } else if (currentMsg == TV_OFF) {
      if (tv_on) {
      sendIRSignal(tclPowerRaw, TCL_SIZE);
      tv_on = false;

      }
    } else if (currentMsg == GET_TEMP) {
        readTempAndHumidity();
        delay(100); // Short delay to ensure sensor reading is updated
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "Temp:%d \xB0" "C  Humidity:%d%%\n", temp, humid);
        currentMsg = buffer;
        currentMsg.trim();
    } else if (currentMsg == SET_TEMP) {
        // String temp;
        // if (Serial.available() > 0) {
        //   temp = Serial.readStringUntil('\n');
        // }
        sendIRSignal(acPowerRaw, AC_SIZE);
    } else {
      msg = currentMsg;
    }
  }

  // currentMsg = msg;
  //Serial.print(msg);
  printOLED(msg);
  

  delay(200);
}
