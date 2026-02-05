#define SW  2
//up pin
#define DT  3
//down pin
#define CLK 4

#define SWITCH 11
#define GND 12

int prev;
int pressed;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(SWITCH, INPUT_PULLUP);
  pinMode(GND, OUTPUT);

  prev = digitalRead(CLK);
  pressed = digitalRead(SW);
  digitalWrite(GND, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int press = digitalRead(SW);
  int curr = digitalRead(CLK);

  Serial.println(digitalRead(SWITCH));

  if (prev != curr) {
    if (digitalRead(DT) != curr) {
      rotateLeft();
    } else {
      rotateRight();
    }
  }

  if (!press && pressed) {
    buttonPress();
  }
  
  prev = curr;
  pressed = press;
  delay(5);
}


void rotateLeft(){
  Serial.println("0VUP0");
}

void rotateRight(){
  Serial.println("0VDW0");
}
void buttonPress(){
  Serial.println("0VMT0");
}