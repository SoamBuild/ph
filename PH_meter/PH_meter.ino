/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ReadAnalogVoltage
*/
float ph4 = 4.00;
float const ph7 = 7.00;
float const ph10 = 10.00;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  float R1 = 222.00;
  float R2 = 395.00;
  float R3 = 561.00;

  // read the input on analog pin 0:
  int sensorValue = analogRead(A1);
  Serial.println(sensorValue);
  // primer recta 4 y 7
  //float ph = ((ph7 - ph4) / (R2 - R1)) * (sensorValue - R1) + ph4;
  // Segunda recta 4 y 10
  //float phv2 = ((ph10 - ph7) / (R3 - R2)) * (sensorValue - R2) + ph7;

  if (sensorValue <= R2 && sensorValue >= R1) {
    float ph = ((ph7 - ph4) / (R2 - R1)) * (sensorValue - R1) + ph4;
    Serial.println("PH RECTA1 ;" + String(ph));
  }
  // si no alcanza el minimo buffer minimo
  if (sensorValue < R1) {
    float ph = ((ph7 - ph4) / (R2 - R1)) * (sensorValue - R1) + ph4;
    Serial.println("PH RECTA1 ;" + String(ph));
  }

 // si se pasa del buffer
  if (sensorValue > R3) {
    float phv2 = ((ph10 - ph7) / (R3 - R2)) * (sensorValue - R2) + ph7;
    Serial.println("PH RECTA2 ;" + String(phv2));
  }

  if (sensorValue <= R3 && sensorValue > R2) {
    float phv2 = ((ph10 - ph7) / (R3 - R2)) * (sensorValue - R2) + ph7;
    Serial.println("PH RECTA2 ;" + String(phv2));
  }

  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  // float voltage = sensorValue * (5.0 / 1023.0);

  // print out the value you read:

  //erial.pritl
}
