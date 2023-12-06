#include <Servo.h>

Servo ServoX;  // crear objeto servo
Servo ServoY
int selenoid = 2;
bool cara;

void setup() {
  ServoX.attach(5); // informacion servo digital #5, cable blanco
  ServoY.attach(6)  
}

void loop() {
  digitalWrite(selenoid,LOW); //emepzar sin tirar awa
  
  cara = //input otro codigo, estado de los ojos, abiertos o cerrados.
  float eje_x = 
  float eje_y = 
  
  if cara == false{ // false = ojos cerrados, true = ojos abiertos
    
    ServoX.write(eje_x); //mover servo a la posicion
    ServoY.write(eje_y); //mover servo a la posicion
    digitalWrite(selenoid,HIGH); //tirar awa, activar selenoid
  }
  
  delay(1500); //tiempo que se dispara awa
}
