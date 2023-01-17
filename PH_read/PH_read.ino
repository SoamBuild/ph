#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>
#include <EasyButton.h>

#define ROTARYSTEPS 1

int newPos; //Value Rotary
int lastPos = -1; //Value x rotary
int check = 0; // value x rotary
int displayNumber =1; // id display
int count_SW=1;  //Click count x SW_ENCODER
int showDisplay=1; // Update value rotary

float const ph4 = 4.00; // Value x PH Calculated
float const ph7 = 7.00;// Value x PH Calculated
float const ph10 = 10.00;// Value x PH Calculated
float R1 = 222.00;// Value x PH Calculated
float R2 = 395.00;// Value x PH Calculated
float R3 = 561.00;// Value x PH Calculated

float globalPh; //Variable global para actualizar valor de PH

LiquidCrystal_I2C lcd(0x27, 16, 2); //Setup x lcd

const int ENCODER_CLK = 14;// Pins x Encoder
const int ENCODER_DT = 15;// Pins x Encoder
const int ENCODER_SW = 16;// Pins x Encoder
RotaryEncoder encoder(ENCODER_CLK, ENCODER_DT); // Setup x Encoder


const int button_NEXT = 18;
const int button_ENTER = 5;

EasyButton btn_ENTER(button_ENTER);// Check x click rotarys
EasyButton btn_NEXT(button_NEXT);// Check x click rotarys

//Enter or Out Menus
boolean subMenu_Medir = false;
boolean subMenu_Calibrar=false;
boolean subMenu_Calibrar_2=false;
boolean mainMenu= true;



void setup()
{
  // Init and function btn_ENTER pressed
  btn_ENTER.begin();
  btn_NEXT.begin();
  btn_ENTER.onPressed(onPressed);
  btn_NEXT.onPressed(onPressed2);
  //Serial init
  Serial.begin(9600);
  //LCD INIT 
  lcd.init();
  lcd.backlight();
  //Print hello Message
  lcd.print("PH Ducasse");
 delay (3000);
  lcd.clear();
}


void loop()
{
  btn_ENTER.read(); //Read change btn_ENTER
  btn_NEXT.read();
  
  
  if (mainMenu == true && displayNumber==1 ) {
    //rotary(0,1);
    firtsDisplay(showDisplay);
  }
  //Menu de lectura
  if(subMenu_Medir==true&& displayNumber==2){
 
    rotary(0,1);
    readingDisplay(showDisplay);
    getPH();
  }
  //Menu de calibracion 
  if(subMenu_Calibrar==true&& displayNumber==3){
    
    rotary(0,3);
    calibrateDisplay(showDisplay);
  }
  //Calibracion de R1
  if(subMenu_Calibrar_2 ==true && displayNumber ==4){
    calibrationPH4();
  }
  //Calibracion de R2
  if(subMenu_Calibrar_2 ==true && displayNumber ==5){
    calibrationPH7();
  }
  //Calibracion de R3
    if(subMenu_Calibrar_2 ==true && displayNumber ==6){
    calibrationPH10();
  }
  
    
}
void getPH(){
  int sensorValue = analogRead(12);
  // primer recta 4 y 7
  //float ph = ((ph7 - ph4) / (R2 - R1)) * (sensorValue - R1) + ph4;
  //Segunda recta 4 y 10
  //float phv2 = ((ph10 - ph7) / (R3 - R2)) * (sensorValue - R2) + ph7;
 
    if (sensorValue <= R2 && sensorValue >= R1)
    {
      float ph = ((ph7 - ph4) / (R2 - R1)) * (sensorValue - R1) + ph4;
      globalPh= ph;
      Serial.println("PH RECT12 ;" + String(ph));
    }
    // si no alcanza el minimo buffer minimo
    if (sensorValue < R1)
    {
      float ph = ((ph7 - ph4) / (R2 - R1)) * (sensorValue - R1) + ph4;
      globalPh = ph;
      Serial.println("PH RECT12 ;" + String(ph));
    }

    // si se pasa del buffer
    if (sensorValue > R3)
    {
      float phv2 = ((ph10 - ph7) / (R3 - R2)) * (sensorValue - R2) + ph7;
      globalPh= phv2;
      Serial.println("PH RECTA2 ;" + String(phv2));
    }

    if (sensorValue <= R3 && sensorValue > R2)
    {
      float phv2 = ((ph10 - ph7) / (R3 - R2)) * (sensorValue - R2) + ph7;
      globalPh = phv2;
      Serial.println("PH RECTA2 ;" + String(phv2));
    }


}
void toCloud(int valuetoSave){
  //function X save value firebase

}
//Calibracion R1 x 1 minuto
void calibrationPH4(){
  for(int i=0;i<60;i++){
    R1 = analogRead(A0);
    calibration_analog_Display(4,i);
    delay(1000);
  }
  //Volver a menu de calibracion
  lcd.clear();
  subMenu_Calibrar_2=false;
  subMenu_Calibrar=true;
  displayNumber=3;
}
//Calibracion R2 x 1 minuto
void calibrationPH7(){
  for(int i=0;i<60;i++){
    R2 = analogRead(A0);
    calibration_analog_Display(7,i);
    delay(1000);
  }
  //Volver a menu de calibracion
  lcd.clear();
  subMenu_Calibrar_2=false;
  subMenu_Calibrar=true;
  displayNumber=3;
  
}
//Calibracion R3 x 1 minuto
void calibrationPH10(){
  for(int i=0;i<60;i++){
    R3 = analogRead(A0);
    calibration_analog_Display(10,i);
    delay(1000);
  }
  //Volver a menu de calibracion
  lcd.clear();
  subMenu_Calibrar_2=false;
  subMenu_Calibrar=true;
  displayNumber=3;
  
}