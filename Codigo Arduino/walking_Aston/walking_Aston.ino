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
  takeStep(150, 1);   
}


void pos(float x, float y, float z, int leg){
  float groinRadians = atan(y/z);
  float groinDegrees = groinRadians * (180/PI);

  float hipRadians1 = atan(x/z);

  float z1 = sqrt(sq(z) + sq(y) + sq(x)); 
  
  float hipRadians2 = acos(z1/(2*l));
  float hipDegrees = (hipRadians1 + hipRadians2) * (180/PI);
  
  float kneeRadians = PI - 2*hipRadians2;
  float kneeDegrees = 180 - kneeRadians * (180/PI);

  Serial.println(groinDegrees);  //Grados de la Ingle
  Serial.println(hipDegrees);    //Grados de la Cadera
  Serial.println(kneeDegrees);   //Grados de la Rodilla
 
  servos[3*leg].write(zeroPositions[3*leg] + directions[3*leg]*groinDegrees);
  servos[3*leg+1].write(zeroPositions[3*leg+1] + directions[3*leg+1]*hipDegrees);
  servos[3*leg+2].write(zeroPositions[3*leg+2] + directions[3*leg+2]*kneeDegrees);
}

void takeStep(float stepSpeed, float stepLength){
  pos(+stepLength,0,9,0);  
  pos(-stepLength,0,9,1);
  pos(-stepLength,0,9,2);
  pos(+stepLength,0,9,3);
  delay(stepSpeed);
  pos(+stepLength,0,8,0);
  pos(-stepLength,0,9,1);
  pos(-stepLength,0,9,2);
  pos(+stepLength,0,8,3);
  delay(stepSpeed);
  pos(-stepLength,0,8,0);
  pos(+stepLength,0,9,1);
  pos(+stepLength,0,9,2);
  pos(-stepLength,0,8,3);
  delay(stepSpeed); 
  pos(-stepLength,0,9,0);
  pos(+stepLength,0,9,1);
  pos(+stepLength,0,9,2);
  pos(-stepLength,0,9,3);
  delay(stepSpeed); 
  pos(-stepLength,0,9,0);
  pos(+stepLength,0,8,1);
  pos(+stepLength,0,8,2);
  pos(-stepLength,0,9,3);
  delay(stepSpeed);
  pos(+stepLength,0,9,0);
  pos(-stepLength,0,8,1);
  pos(-stepLength,0,8,2);
  pos(+stepLength,0,9,3);
  delay(stepSpeed);
}
