#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>
#include <EasyButton.h>


#define ROTARYSTEPS 1
#define ROTARYSTEPS 1
int newPos;
int lastPos = -1;
int showDisplay;
//Debounce encodervariable
int check = 0;
int displayNumber =1;
int count_SW=1;

float ph4 = 4.00;
float const ph7 = 7.00;
float const ph10 = 10.00;

LiquidCrystal_I2C lcd(0x3F, 16, 2);

const int ENCODER_CLK = 5;
const int ENCODER_DT = 6;
const int ENCODER_SW = 7;
RotaryEncoder encoder(ENCODER_CLK, ENCODER_DT);
EasyButton button(ENCODER_SW);

boolean subMenu_Medir = false;
boolean subMenu_Calibrar=false;
boolean subMenu_Calibrar_2=false;
boolean mainMenu= true;

float R1 = 222.00;
  float R2 = 395.00;
  float R3 = 561.00;

void setup()
{

  button.begin();
  button.onPressed(onPressed);

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("PH Ducasse");
  button.begin();
  button.onPressed(onPressed);
  lcd.clear();
}


void loop()
{
  button.read();
  if (mainMenu == true && displayNumber==1 ) {
    rotary(0,1);
    firtsDisplay(showDisplay);
  }
  if(subMenu_Medir==true&& displayNumber==2){
 
    rotary(0,1);
    readingDisplay(showDisplay);
  }
  if(subMenu_Calibrar==true&& displayNumber==3){
    
    rotary(0,3);
    calibrateDisplay(showDisplay);
  }
  if(subMenu_Calibrar_2 ==true && displayNumber ==4){
    calibrationPH4();
  }
  if(subMenu_Calibrar_2 ==true && displayNumber ==5){
    calibrationPH7();
  }
    if(subMenu_Calibrar_2 ==true && displayNumber ==6){
    calibrationPH10();
  }
    /*
  }
  if (subMenu == true && showDisplay == 1) {
    readingDisplay();
   
  }
  if (subMenu == true  && showDisplay == 2) {
    calibrateDisplay();
    
  }


  float R1 = 222.00;
  float R2 = 395.00;
  float R3 = 561.00;

  // read the input on analog pin 0:
  int sensorValue = analogRead(A1);
  //  Serial.println(sensorValue);
  // primer recta 4 y 7
  // float ph = ((ph7 - ph4) / (R2 - R1)) * (sensorValue - R1) + ph4;
  // Segunda recta 4 y 10
  // float phv2 = ((ph10 - ph7) / (R3 - R2)) * (sensorValue - R2) + ph7;
  /*
    if (sensorValue <= R2 && sensorValue >= R1)
    {
      float ph = ((ph7 - ph4) / (R2 - R1)) * (sensorValue - R1) + ph4;
      Serial.println("PH RECTA1 ;" + String(ph));
    }
    // si no alcanza el minimo buffer minimo
    if (sensorValue < R1)
    {
      float ph = ((ph7 - ph4) / (R2 - R1)) * (sensorValue - R1) + ph4;
      Serial.println("PH RECTA1 ;" + String(ph));
    }

    // si se pasa del buffer
    if (sensorValue > R3)
    {
      float phv2 = ((ph10 - ph7) / (R3 - R2)) * (sensorValue - R2) + ph7;
      Serial.println("PH RECTA2 ;" + String(phv2));
    }

    if (sensorValue <= R3 && sensorValue > R2)
    {
      float phv2 = ((ph10 - ph7) / (R3 - R2)) * (sensorValue - R2) + ph7;
      Serial.println("PH RECTA2 ;" + String(phv2));
    }

    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    // float voltage = sensorValue * (5.0 / 1023.0);

    // print out the value you read:

    // erial.pritl
  */
}
void toCloud(int valuetoSave){

}
void calibrationPH4(){
  for(int i=0;i<60;i++){
    R1 = analogRead(A0);
    calibration_analog_Display(4,i);
    delay(1000);
  }
  lcd.clear();
  subMenu_Calibrar_2=false;
  subMenu_Calibrar=true;
  displayNumber=3;
  
}
void calibrationPH7(){
  for(int i=0;i<60;i++){
    R2 = analogRead(A0);
    calibration_analog_Display(7,i);
    delay(1000);
  }
  lcd.clear();
  subMenu_Calibrar_2=false;
  subMenu_Calibrar=true;
  displayNumber=3;
  
}
void calibrationPH10(){
  for(int i=0;i<60;i++){
    R3 = analogRead(A0);
    calibration_analog_Display(10,i);
    delay(1000);
  }
  lcd.clear();
  subMenu_Calibrar_2=false;
  subMenu_Calibrar=true;
  displayNumber=3;
  
}