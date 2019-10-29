#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
int toggleButton = 5;
int sleepButton = 6;
int pot = A1;

int toggleState = HIGH;
int sleepState = HIGH;

int readingToggle;
int readingSleep;
int readingPot;

int previousToggle = LOW;

long sleepTimer;

long time = 0;
long debounce = 200;


void setup() {
  Serial.begin(9600);
  mySwitch.enableTransmit(3);
  pinMode(toggleButton, INPUT);
  pinMode(sleepButton, INPUT);
}

void loop() {
  readingToggle = digitalRead(toggleButton);

  readingSleep = digitalRead(sleepButton);

  readingPot = analogRead(pot);
  Serial.print(readingPot);
  Serial.print("\n");

  if (readingToggle == HIGH && millis() - time > debounce) {
    if (toggleState == HIGH) {
      Serial.print("Turning off lights \n");
      toggleState = LOW;
      mySwitch.send(83028, 24); 
      mySwitch.send(70740, 24);

    } else {
      Serial.print("Turning on lights \n");
      toggleState = HIGH;
      mySwitch.send(83029, 24); 
      mySwitch.send(70741, 24);
    }
    time = millis();
    previousToggle = readingToggle;
  }

  if (readingSleep == HIGH && millis() - time > debounce) {
    Serial.print("Turning off lights - Sleep \n");
    mySwitch.send(70740, 24);
    sleepTimer = readingPot*1757L;
    Serial.print(readingPot);
    Serial.print("\n");
    Serial.print(sleepTimer);
    delay(sleepTimer);
    mySwitch.send(83028, 24);
    toggleState = LOW;
    time = millis();
  }
}
