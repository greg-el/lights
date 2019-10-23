#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
int toggleButton = 5;
int sleepButton = 6;
int toggleState = HIGH;
int sleepState = HIGH;
int readingToggle;
int readingSleep;
int previousToggle = LOW;

long time = 0;
long debounce = 200;


void setup() {
  Serial.begin(9600);
  mySwitch.enableTransmit(2);
  pinMode(toggleButton, INPUT);
  pinMode(sleepButton, INPUT);
}

void loop() {
  readingToggle = digitalRead(toggleButton);
  readingSleep = digitalRead(sleepButton);

  if (readingToggle == HIGH && previousToggle == LOW && millis() - time > debounce) {
    if (toggleState == HIGH) {
      toggleState = LOW;
      mySwitch.send(83028, 24); 
      mySwitch.send(70740, 24);
    } else {
      toggleState = HIGH;
      mySwitch.send(83029, 24); 
      mySwitch.send(70741, 24);
    }
    time = millis();
    previousToggle = readingToggle;
  }

  Serial.print(readingSleep);
  Serial.print("\n");

  if (readingSleep == LOW && millis() - time > debounce) {
    mySwitch.send(83028, 24);
    delay(2000);
    mySwitch.send(70740, 24);
    time = millis();
  }
}
