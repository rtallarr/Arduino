#include "IRremote.h"

int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11

IRrecv irrec(receiver);     // create instance of 'irrecv'
decode_results results;  

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrec.enableIRIn(); // Start the receiver
}

void loop(){   /*----( LOOP: RUNS CONSTANTLY )----*/
  if (irrec.decode(&results)){ // have we received an IR signal?
    Serial.println(results.value);
    chuala();
    irrec.resume(); // receive the next value
  }
  delay(1000);
}

String chuala(){
  switch (results.value){
    case 16738455: Serial.println("1");
    break;
    case 16750695: Serial.println('2');
    break;
    case 16756815: Serial.println('3');
    break;
    case 16724175: Serial.println('4');
    break;
    case 16718055: Serial.println('5');
    break;
    case 16743045: Serial.println('6');
    break;
    case 16716015: Serial.println('7');
    break;
    case 16726215: Serial.println('8');
    break;
    case 16734885: Serial.println('9');
    break;
    case 16730805: Serial.println('0');
    break;
    case 16728765: Serial.println("*");
    break;
    case 16732845: Serial.println("#");

    case 16736925: Serial.println("arriba");
    break;
    case 16754775: Serial.println("abajo");
    break;
    case 16761405: Serial.println("derecha");
    break;
    case 16720605: Serial.println("izquerda");
    break;
    case 16712445: Serial.println("OK");
    break;
  }
}
