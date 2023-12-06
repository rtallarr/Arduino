//mostrar termistor, TMP, DHT, por pantallas (1,2,3)

int tempPin = 0;
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <dht.h>
#define dht_apin A2 // Analog Pin sensor is connected to
dht DHT;
LiquidCrystal_I2C lcd(0x27,16,2);
const int tmp = A3;
int pantalla = 1;

void setup(){
  pinMode(2,INPUT);
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
  lcd.init();                     
  lcd.backlight();
  lcd.setBacklight(HIGH);
}

void loop(){

  int boton = digitalRead(2);
  if (boton==HIGH){
    pantalla=pantalla+1;
    if (pantalla==4){
      pantalla=1;
    }
  }
  
  //cabeza negra
  if (pantalla==1){
    int tempReading = analogRead(tempPin);
    double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
    tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
    float tempC = tempK - 273.15;            // Convert Kelvin to Celcius

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("temp 1:");
    lcd.setCursor(8,0);
    lcd.print(tempC);
  }
  //TMP
  else if (pantalla==2){
  int val = analogRead(tmp);
  float volt = (val/1024.0)*5.0;
  float temp = (volt - .5)*100;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp 2:");
  lcd.setCursor(8,0);
  lcd.print(temp);
  }
  //DHT
  else if (pantalla==3){
    DHT.read11(dht_apin);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("temp: ");
    lcd.setCursor(6,0);
    lcd.print(DHT.temperature);
    lcd.setCursor(11,0);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("humd: ");
    lcd.setCursor(6,1);
    lcd.print(DHT.humidity);
    lcd.setCursor(11,1);
    lcd.print("%");
    /*
  Serial.print("Current humidity = ");
  Serial.print(DHT.humidity);   
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature);
  Serial.println("C  "); */
  }
  delay(2000)
}
