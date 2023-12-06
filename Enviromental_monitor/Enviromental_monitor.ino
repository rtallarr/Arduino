#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <dht.h>
#define dht_apin A2 // Analog Pin sensor is connected to
dht DHT;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup(){
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
  lcd.init();                     
  lcd.backlight();
  lcd.setBacklight(HIGH);
}

void loop(){
 
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.setCursor(6, 0);
  lcd.print(DHT.temperature);
  lcd.setCursor(11,0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("humd:");
  lcd.setCursor(6,1);
  lcd.print(DHT.humidity);
  lcd.setCursor(11,1);
  lcd.print("%");
  DHT.read11(dht_apin);
    
  Serial.print("Current humidity = ");
  Serial.print(DHT.humidity);   
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature);
  Serial.println("C  ");

  delay(2500);
}
