#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
int count = 0; //contador pa poner clave
int intentos = 0; //numero claves mal puestas
int cuentame_esta = 0; //contador para nueva clave
bool acceso_nuevaclave = false;
bool nalgas = true; //booleano para cndo te equivocai en la clave actual
bool access; //variable para ver si esta bien la clave
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13, 11, 9, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 5, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27,16,2);

char pass[5] = "1234"; //clave de la wea
char master[9] = "CA69CA69";
char typed[17];
String cambio = "olas"; //variable para cambiar la clave
bool flag = false;
unsigned long millis_ahora;
unsigned long demora;
long sec; //diferencia en segundos

void setup(){
  Serial.begin(9600);
  lcd.init();            
  lcd.backlight();
  lcd.setBacklight(HIGH);
  Serial.println(typed);
}
  
void loop(){
  char key = customKeypad.getKey();
  flag = false;
  
  if (!key && cambio=="olas"){
    lcd.setCursor(0,0);
    lcd.print("Clave: ");
  }

  if (key){
    if (key=='#'){//cambiar clave
      cambio = "baby";
      lcd.clear();
      lcd.print("Clave Actual: ");
      lcd.setCursor(0,1);
      lcd.print(typed);
      if (count>=4){
        if (typed[0]==master[0]){
          if (typed[1]==master[1]){
            if (typed[2]==master[2]){
              if (typed[3]==master[3]){
                if (typed[4]==master[4]){
                  if (typed[5]==master[5]){
                    if (typed[6]==master[6]){
                      if (typed[7]==master[7]){
                        lcd.clear();
                        lcd.print(pass);
                        lcd.setCursor(0,1);
                        lcd.print("Denada Master");
                        delay(2000);
                        flag = true;
                        limpiar();
                      }
                    }
                  }
                }
              }
            }
          }
        }
        if (typed[0]==pass[0]){
          if (typed[1]==pass[1]){
            if (typed[2]==pass[2]){
              if (typed[3]==pass[3]){
            acceso_nuevaclave = true; //aqui
            count = 0;
            clean(); //señor limpiador
          }
        } else {
          acceso_nuevaclave = false;
          nalgas = false;
        }
      } else {
        acceso_nuevaclave = false;
        nalgas = false;
      }
    } else {
      acceso_nuevaclave = false;
      nalgas = false;
    }
      }
    } else if (key=='*'){
      limpiar();
    } else {
      Serial.println(key);
      typed[count] = key;
      count+=1;
      lcd.setCursor(0,1);
      lcd.print(typed);
    }

    if (acceso_nuevaclave==true){
      lcd.clear();
      lcd.print("Nueva Clave: ");
      lcd.setCursor(0,1);
      lcd.print(typed);
      cuentame_esta+=1;
    }
    if (acceso_nuevaclave==false && nalgas==false && flag==false && cuentame_esta>=4){
      lcd.clear();
      lcd.print("Clave Incorrecta");
      delay(1500);
      limpiar();
    }
    if (acceso_nuevaclave==true && cuentame_esta==5){
    Serial.println("CAMBIANDO CLAVE");
    for (int i=0; i<4; i++){
      pass[i]=typed[i];
    }
    lcd.clear();
    lcd.print("CLAVE CAMBIADA: ");
    lcd.setCursor(0,1);
    lcd.print(pass);
    delay(1500);
    limpiar();
    } 
  }
  /*
  Serial.println(typed);
  Serial.print("Clave: ");
  Serial.println(pass);
  Serial.print("cambio: ");
  Serial.println(cambio);
  Serial.print("acceso clave nueva: ");
  Serial.println(acceso_nuevaclave);
  Serial.print("cuentame esta: ");
  Serial.println(cuentame_esta);
  Serial.print("Contador normal: ");
  Serial.println(count);
  Serial.print("Intentos: ");
  Serial.println(intentos);
  Serial.println(" ");
  */ 

  if (count==4 && cambio=="olas"){ //esta bien la clave?
    if (typed[0]==pass[0]){
      if (typed[1]==pass[1]){
        if (typed[2]==pass[2]){
          if (typed[3]==pass[3]){
            access = true;
          }
        } else {
          access = false;
        }
      } else {
        access = false;
      }
    } else {
      access = false;
    }
  }
  
  if (count == 4 && cambio=="olas"){ //que hacer si esta bien la clave
    if (access == true){
      Serial.println("ACCESS GRANTED");
      lcd.clear();
      lcd.print("ACCESS GRANTED");
      count = 0;
      intentos = 0;
      clean(); //señor limpiador
      Serial.println(typed);
      delay(2000);
      lcd.clear();
    } else if (access == false){//clave mal puesta
      if (typed[0]=='A'){ // easter egg
        if (typed[1]=='B'){
          if (typed[2]=='B'){
            if (typed[3]=='A'){
              lcd.clear();
              lcd.print("ola washo");
              delay(1000);
            }
          }
        }
      }
      Serial.println("ACCESS DENIED");
      lcd.clear();
      lcd.print("ACCESS DENIED");
      count = 0;
      intentos+=1; //clave mal puesta
      clean(); //señor limpiador
      delay(2000);
      lcd.clear();

      if (intentos>=3){
        demora = millis();
        pausa();
      }
    }
  }
  delay(100);
}

void limpiar(){ //maestro señor limpiador
  count = 0;
  cambio = "olas";
  acceso_nuevaclave = false;
  access = false;
  flag = false;
  cuentame_esta = 0;
  for (int i=0; i<16; i++){ //super señor limpiador
        typed[i]=' ';
      }
  nalgas = true;
  lcd.clear();
}

void clean(){
  for (int i=0; i<4; i++){ //limpiar clave, señor limpiador
        typed[i]=' ';
      }
}

void pausa(){ //segunda vez crushea
  lcd.clear();
  lcd.print("3ER INTENTO");
  lcd.setCursor(0,1);
  lcd.print("FALLIDO");
  delay(1000);
  lcd.clear();
  millis_ahora = millis(); //por si pasa mas veces
  while (sec<30){
  
    /* DEBUGEO
    Serial.print("Millis_ahora: ");
    Serial.println(millis_ahora);
    Serial.print("demora: ");
    Serial.println(demora);
    Serial.print("sec: ");
    Serial.println(sec);*/
    
    millis_ahora = millis(); //Ir aumentandos millis_ahora
    sec = (millis_ahora - demora)/1000; //diferencia entre ambos, en segundos
    
    lcd.print(30 - sec);
    delay(900);
  }
  intentos = 0;
}
