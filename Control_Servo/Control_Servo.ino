#include "IRremote.h"
#include <Servo.h>

int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11
int angulo = 0;

IRrecv irrec(receiver);     // create instance of 'irrecv'
decode_results results;
Servo servo;

void setup(){
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrec.enableIRIn(); // Start the receiver
  servo.attach(9);
}

void loop(){
  if (irrec.decode(&results)){ // have we received an IR signal?
    Serial.println("");
    Serial.println(results.value);
    
    switch (results.value){
    case 16734375: Serial.println("IZQUERDA_AROS");
    if (angulo>0){
      angulo-=5;
    }
    break;
    case 16730295: Serial.println("ARRIBA_AROS");
    break;
    case 16742535: Serial.println("DERECHA_AROS");
    if (angulo<180){
      angulo+=5;
    }
    break;
    
    case 16744575: Serial.println("ON");
    if (angulo==0){
      angulo = 180;
    } else if (angulo <= 90){
      angulo = 0;
    }
    break;
    case 16760895: Serial.println("BLANK" );
    angulo = 0;
    break;
    case 16716015: Serial.println("CENTRO");
    
    }
    irrec.resume(); // receive the next value
  }
  Serial.print("Angulo: ");
  Serial.println(angulo);
  servo.write(angulo);
  delay(100);
}
