#include <Servo.h>

Servo servos[12];         
int zeroPositions[12] = {90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90};
int directions[12] = {-1, -1, -1, -1, +1, +1, +1, -1, -1, +1, +1, +1};

const float l = 5;
const float L = 14.5;

void setup() {
  delay(1000);
  Serial.begin(9600);
  for(int i=0; i<12; i++){  //Asignamos servomotores a pines del Arduino
     servos[i].attach(i+2);      //Iniciamos con el pin 2 hasta el 12
     delay(100);
  }
  for(int i=0; i<12; i++){          //Asignamos posiciones iniciales a los servomotores
     servos[i].write(zeroPositions[i]);
     delay(100);
  }  
  delay(5000); 
}

void loop() {    
}
