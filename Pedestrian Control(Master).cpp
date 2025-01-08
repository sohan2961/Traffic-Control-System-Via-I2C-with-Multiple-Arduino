//Master: Pedestrian Controls Synchronization

#include <Wire.h>

#define BUTTON 8          // Button input pin
#define PEDESTRIAN_GREEN 6
#define PEDESTRIAN_RED 9

void setup() {
  Wire.begin();           // Master starts I2C
  pinMode(BUTTON, INPUT);
  pinMode(PEDESTRIAN_GREEN, OUTPUT);
  pinMode(PEDESTRIAN_RED, OUTPUT);

  // Start with pedestrian red
  digitalWrite(PEDESTRIAN_GREEN, LOW);
  digitalWrite(PEDESTRIAN_RED, HIGH);
}

void loop() {
  if (digitalRead(BUTTON) == HIGH) {
    // Signal to Slave 1 to change d1/d2 lights to yellow
    Wire.beginTransmission(8); // Slave 1 address
   
    Wire.write('Y');           // Yellow signal for d1/d2
    Wire.endTransmission();
    
    delay(2000); // Time for yellow light
    
    // Signal to Slave 2 to turn d3 and pedestrian lights green
    Wire.beginTransmission(9); // Slave 2 address
    Wire.write('P');           // Green for d3 and pedestrian
    Wire.endTransmission();

    digitalWrite(PEDESTRIAN_GREEN, HIGH);
    digitalWrite(PEDESTRIAN_RED, LOW);
    
    delay(6000); // Time for pedestrians to cross
    
    digitalWrite(PEDESTRIAN_GREEN, LOW);
    digitalWrite(PEDESTRIAN_RED, HIGH);

    // Signal to Slave 2 to change d3 lights back to red
    Wire.beginTransmission(9);
    Wire.write('R');           // Red signal for d3
    Wire.endTransmission();
    
    delay(2000); // Time for yellow after red
    
    // Reset d1/d2 back to green
    Wire.beginTransmission(8);
    Wire.write('G');           // Green for d1/d2
    Wire.endTransmission();
  }
}
