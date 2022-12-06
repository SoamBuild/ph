void onPressed()
{
  Serial.println("Click Encoder Change Display:" + String(displayNumber);
  changeDisplay();
}
// Funcion para cambiar de pantallas
void changeDisplay() {
  //Cambiar a la pantalla de PH
  
  Serial.println("capture value: " + String(newPos));
  if (displayNumber == 0 && subMenu == false) {
    readingDisplay();
    Serial.println("read display");
    showDisplay = 1;
    lcd.clear();
  }
  
  //Cambiar a la pantalla de calibracion
  if (displayNumber == 1 && subMenu == false) {
    calibrateDisplay();
    Serial.println("calibrate display");
    showDisplay = 2;
    lcd.clear();
  }
}

//Funcion de encoder con valor min y max
void rotary(int ROTARYMIN, int ROTARYMAX)
{
  encoder.tick();
  int newPos = encoder.getPosition() * ROTARYSTEPS;
  if (newPos < ROTARYMIN)
  {
    encoder.setPosition(ROTARYMIN / ROTARYSTEPS);
    newPos = ROTARYMIN;
  }
  else if (newPos > ROTARYMAX)
  {
    encoder.setPosition(ROTARYMAX / ROTARYSTEPS);
    newPos = ROTARYMAX;
  } 
  if (lastPos != newPos)
  {
    Serial.print(newPos);
    Serial.println();
    lastPos = newPos;
    displayNumber = newPos; // Actualiza el numero de la pantalla
    cursorDisplay(newPos); // Muestra el cursos que se actualiza en Y segun el encoder
  }
}
