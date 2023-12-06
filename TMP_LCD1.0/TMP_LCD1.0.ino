//mostrar tmp de TMP35 en lcd 16 pins

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int tmp = A0;
int cont = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(tmp,INPUT);
}

void loop() {
  int val = analogRead(tmp);
  float volt = (val/1024.0)*5.0;
  float temp = (volt - .5)*100;
  Serial.print("Temperature:");
  Serial.println(temp);
  
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.setCursor(6,0);
  lcd.print(temp);
  
  cont+=1;
  delay(10);
}
