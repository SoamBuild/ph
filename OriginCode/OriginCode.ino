#include <Wire.h>
#include <LiquidCrystal_I2C.h>

float ph4 = 4.00;
float const ph7 = 7.00;
float const ph10 = 10.00;

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup()
{

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("PH Ducasse");
}

// the loop routine runs over and over again forever:
void loop()
{
  firtsDisplay();
  float R1 = 222.00;
  float R2 = 395.00;
  float R3 = 561.00;

  // read the input on analog pin 0:
  int sensorValue = analogRead(A1);
  Serial.println(sensorValue);
  // primer recta 4 y 7
  // float ph = ((ph7 - ph4) / (R2 - R1)) * (sensorValue - R1) + ph4;
  // Segunda recta 4 y 10
  // float phv2 = ((ph10 - ph7) / (R3 - R2)) * (sensorValue - R2) + ph7;

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
}
