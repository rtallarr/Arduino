#include "IRremote.h"

int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11
bool algo_prendido = false;
int intensidad_rojo = 0;
int intensidad_verde = 0;
int intensidad_azul = 0;
int cont_blank = 0;

IRrecv ir(receiver);     // create instance of 'irrecv'
decode_results results;  

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decoder"); 
  ir.enableIRIn(); // Start the receiver
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop(){   /*----( LOOP: RUNS CONSTANTLY )----*/
  if (ir.decode(&results)){ // have we received an IR signal?
    Serial.println("");
    Serial.println(results.value);

    if (intensidad_rojo>=1 || intensidad_azul>=1 || intensidad_verde>=1){
      algo_prendido = true;
    }
    
    switch (results.value){
    
    case 16744575: Serial.println("ON");
    if (algo_prendido){
      apagar_todo();
      algo_prendido = false;
    } else {
      analogWrite(3,255);
      analogWrite(5,255);
      analogWrite(6,255);
      intensidad_rojo = 3;
      intensidad_azul = 3;
      intensidad_verde = 3;
      algo_prendido = true;
    }
    break;
    
    case 16760895: Serial.println("BLANK");
    cont_blank+=1;
    reset();
    break;
    
    case 16730295: Serial.println("ARRIBA_AROS");
    intensidad_verde+=1;

    if (intensidad_verde == 1){
     analogWrite(5,85);
    } else if (intensidad_verde == 2){
      analogWrite(5,170);
    } else if (intensidad_verde == 3){
      analogWrite(5,255);
    } else if (intensidad_verde == 4){
      analogWrite(5,0);
      intensidad_verde = 0;
      algo_prendido = false;
    }
    break;
    
    case 16734375: Serial.println("IZQUERDA_AROS");
    intensidad_rojo+=1;
    
    if (intensidad_rojo == 1){
      analogWrite(6,85);
    } else if (intensidad_rojo == 2){
      analogWrite(6,170);
    } else if (intensidad_rojo == 3){
      analogWrite(6,255);
    } else if (intensidad_rojo == 4){
      analogWrite(6,0);
      intensidad_rojo = 0;
      algo_prendido = false;
    }
    break;
    
    case 16742535: Serial.println("DEREHCA_AROS");
    intensidad_azul+=1;

    if (intensidad_azul == 1){
      analogWrite(3,85);
    } else if (intensidad_azul == 2){
      analogWrite(3,170);
    } else if (intensidad_azul == 3){
      analogWrite(3,255);
    } else if (intensidad_azul == 4){
      analogWrite(3,0);
      intensidad_azul = 0;
      algo_prendido = false;
    }
    break;

    case 16716015: Serial.println("CENTRO");
    party();
    break;
    case 16728255: Serial.println("PLAY/PAUSE");
    break;
  }
  
    ir.resume(); // receive the next value

    //DEBUGEO 
    Serial.println("");
    Serial.print("algo prendido: ");
    Serial.println(algo_prendido);
    Serial.print("rojo: ");
    Serial.println(intensidad_rojo);
    Serial.print("verde: ");
    Serial.println(intensidad_verde);
    Serial.print("Azul: ");
    Serial.println(intensidad_azul);
    Serial.print("Resets: ");
    Serial.println(cont_blank);
  }
  delay(1000);
}

void apagar_todo(){
  analogWrite(3,0);
  analogWrite(5,0);
  analogWrite(6,0);
  intensidad_rojo = 0;
  intensidad_verde = 0;
  intensidad_azul = 0;
}

void reset(){
  apagar_todo();
  algo_prendido = false;
}

void party(){
  delay(100);
  analogWrite(3,random(256));
  analogWrite(5,random(256));
  analogWrite(6,random(256));
  algo_prendido = true;
}
