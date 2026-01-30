#include "HomeAssistant.h"
#include <IRremote.hpp>
#include <U8g2lib.h>
#include <Wire.h>

// IRrecv irrecv(RECV_PIN);
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

String currentMsg;
String msg = "Hello! I am your new assistant";
bool tv_on = false;
int typewriterIdx = 0;
int lastUpdate = 0;

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

void setupOLED() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr);
}

void printOLED(String msg){
  msg.trim();
  //doar daca am mesaj nou
  if (currentMsg != msg) {
    typewriterIdx = 0;
  }
  if (millis() - lastUpdate > 100 && typewriterIdx <= msg.length()) {
    typewriterIdx++;
    lastUpdate = millis();
  }

  // 3. Render Loop
  u8g2.firstPage();
  do {
    int x = 0;
    int y = 20;

    for (int i = 0; i < typewriterIdx; i++) {
      char buf[2] = {msg[i], '\0'};
      int w = u8g2.getStrWidth(buf);

      if (x + w > 118) {
        x = 0;
        y += 20;
      }

      if (y < 70) {
        u8g2.drawStr(x, y, buf);
      }
      x += w + 2;
    }
  } while (u8g2.nextPage());
}
