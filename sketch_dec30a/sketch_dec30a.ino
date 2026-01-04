#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// SH1106 Driver for 1.3" OLED
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

String currentMsg = "haha penis";
int typewriterIdx = 0;
unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(9600);
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB10_tr); 
}

void loop() {
  if (Serial.available() > 0) {
    currentMsg = Serial.readStringUntil('\n');
    currentMsg.trim();
    typewriterIdx = 0;
  }

  if (millis() - lastUpdate > 100 && typewriterIdx <= currentMsg.length()) {
    typewriterIdx++;
    lastUpdate = millis();
  }

  // 3. Render Loop
  u8g2.clearBuffer();
  
  int x = 0;
  int y = 20;

  for (int i = 0; i < typewriterIdx; i++) {
    char c = currentMsg[i];
    char buf[2] = {c, '\0'};
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

  u8g2.sendBuffer();
}