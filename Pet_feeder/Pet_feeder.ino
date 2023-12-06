#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>
Servo servo; //declarar objeto servo nombre servo
LiquidCrystal_I2C lcd(0x27,16,2);
const int boton = 13; //boton con salto de comida
bool estado_boton = false;
unsigned long tiempo;
unsigned long tiempo_restante;
unsigned long cont = 1;
long intervalo_comida = 43200; //cada cuantos segundos alimentar, 43200 = 12 horas

void setup() {
  servo.attach(9);
  lcd.init();                     
  lcd.backlight();
  lcd.setBacklight(HIGH);
  Serial.begin(9600);
  pinMode(boton,INPUT);
}

void loop() {
  servo.write(0);
  tiempo = millis()/1000; //tiempo en segundos
  tiempo_restante = intervalo_comida*cont - tiempo;
  estado_boton = digitalRead(boton);
  
  int horas = tiempo_restante / 3600;
  int minutos = (tiempo_restante % 3600)/60;
  int segundos = (tiempo_restante % 3600)%60; 

  if (estado_boton){ //dar comida y saltar la siguiente
    dar_comida();
  }

  Serial.print("Tiempo Restante: ");
  Serial.println(tiempo_restante);
  Serial.print("Cont: ");
  Serial.println(cont);
  Serial.print("Tiempo: ");
  Serial.println(tiempo);
  Serial.print("horas restantes: ");
  Serial.println(horas);
  Serial.print("Minutos restantes: ");
  Serial.println(minutos);
  Serial.print("Segundos restantes: ");
  Serial.println(segundos);

  if (tiempo_restante>0){
    lcd.setCursor(0,0);
    lcd.print("Proxima Comida");
    lcd.setCursor(0,1);
    lcd.print("En");

    int posH; //mostrar la hora con dos digitos siempre
    int posM;
    int posS;
  
    if (horas<10){ 
      if (minutos<10){
        if (segundos<10){
          posH = 4;
          posM = 7;
          posS = 10;
        } else {
          posH = 4;
          posM = 7;
          posS = 9;
        }
      } else {
        if (segundos<10){
          posH = 4; 
          posM = 6;
          posS = 10;
        } else {
          posH = 4;
          posM = 6;
          posS = 9;
        }
      }
    } else {
      if (minutos<10){
        if (segundos<10){
          posH = 3;
          posM = 7;
          posS = 10;
        } else {
          posH = 3;
          posM = 7;
          posS = 9;
        }
      } else {
        if (segundos<10){
          posH = 3;
          posM = 6;
          posS = 10;
        } else {
          posH = 3;
          posM = 6;
          posS = 9; 
        }
      }
    }

    if (posH == 4){
      lcd.setCursor(3,1);
      lcd.print("0");
    }
    if (posM == 7){
      lcd.setCursor(6,1);
      lcd.print("0");
    }
    if (posS == 10){
      lcd.setCursor(9,1);
      lcd.print("0");
    }
    
    lcd.setCursor(posH,1);
    lcd.print(horas);
    lcd.setCursor(5,1);
    lcd.print(":");
    lcd.setCursor(posM,1);
    lcd.print(minutos);
    lcd.setCursor(8,1);
    lcd.print(":");
    lcd.setCursor(posS,1);
    lcd.print(segundos);
    
    } else {
      dar_comida();
    }
    delay(500);
}

void dar_comida(){
  servo.write(90);
  lcd.clear();
  lcd.print("Sirviendo");
  lcd.setCursor(0,1);
  lcd.print("Comida...");
  cont+=1;
  delay(1000);
  lcd.clear();
}
