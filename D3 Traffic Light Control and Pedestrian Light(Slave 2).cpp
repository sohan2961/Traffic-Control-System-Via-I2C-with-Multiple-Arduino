//Slave 2: D3 Traffic Light Control and Pedestrian Light
#include <Wire.h>

enum TrafficState { RED, GREEN, YELLOW };
TrafficState currentState = RED;

void setup() {
  Wire.begin(9);          // Slave 2 address
  Wire.onReceive(receiveEvent);

  pinMode(3, OUTPUT);     // Red
  pinMode(5, OUTPUT);     // Yellow
  pinMode(8, OUTPUT);     // Green (d3 and pedestrian green)

  // Start with d3 red
  digitalWrite(3, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(8, LOW);
}

void loop() {
  switch (currentState) {
    case GREEN:
      digitalWrite(3, LOW);
      digitalWrite(8, HIGH);
      break;

    case YELLOW:
      digitalWrite(8, LOW);
      digitalWrite(5, HIGH);
      delay(2000);
      digitalWrite(5, LOW);
      digitalWrite(3, HIGH);
      currentState = RED;
      break;

    case RED:
      // d3 remains red unless instructed otherwise
      break;
  }
}

void receiveEvent(int bytes) {
  char command = Wire.read();
  if (command == 'P') {
    currentState = GREEN; // Turn d3 and pedestrian lights green
  } else if (command == 'R') {
    currentState = YELLOW; // Transition to yellow and then red
  }
}
