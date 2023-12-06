//juego simple, tocar perder, pin 9 = conectado al course, pin 8 = piezo

void setup(){
  Serial.begin(9600);
  pinMode(9,INPUT);
}

void loop(){
  int ja = digitalRead(9);
  Serial.println(ja);
  if (ja==HIGH){
    tone(8,100); 
  }
  else {
    noTone(8);
  }
  delay(10);
}
