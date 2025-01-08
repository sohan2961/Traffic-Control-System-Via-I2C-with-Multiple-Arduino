//Slave 1: D1/D2 Traffic Light Control
#include <Wire.h>

enum TrafficState { GREEN, YELLOW, RED };
TrafficState currentState = GREEN;

void setup() {
  Wire.begin(8);           // Slave 1 address
  Wire.onReceive(receiveEvent);

  pinMode(2, OUTPUT);      // Red
  pinMode(4, OUTPUT);      // Yellow
  pinMode(7, OUTPUT);      // Green

  // Start with d1/d2 green
  digitalWrite(2, LOW);
  digitalWrite(4, LOW);
  digitalWrite(7, HIGH);
}

void loop() {
  switch (currentState) {
    case GREEN:
      // d1/d2 remain green unless interrupted
      break;

    case YELLOW:
      digitalWrite(7, LOW);
      digitalWrite(4, HIGH);
      delay(2000);
      digitalWrite(4, LOW);
      digitalWrite(2, HIGH);
      currentState = RED;
      break;

    case RED:
      // Wait for reset signal from Master
      break;
  }
}

void receiveEvent(int bytes) {
  char command = Wire.read();
  if (command == 'Y') {
    currentState = YELLOW; // Transition to yellow
  } else if (command == 'G') {
    // Reset to green
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(7, HIGH);
    currentState = GREEN;
  }
}

