void onPressed()
{
  Serial.println("Click Encoder Change Display:" + String(displayNumber));
  Serial.println("MENU PRINCIPAL STATE: "+String(mainMenu));
  Serial.println("SUBMENU STATE: "+String(subMenu));
  Serial.println("ID DISPLAY: "+String(showDisplay));
  delay(2000);
  changeDisplay();
}
// Funcion para cambiar de pantallas
void changeDisplay() {
  //Cambiar a la pantalla de ph

  if (displayNumber == 0 && subMenu == false) {
    Serial.println("read display");
    showDisplay = 1;
    readingDisplay();
  }

  //Cambiar a la pantalla de calibracion
  if (displayNumber == 1 && subMenu == false ) {
    Serial.println("calibrate display");
    showDisplay = 2;
    calibrateDisplay();
  }

  if(mainMenu==false && displayNumber==1){
    Serial.println("main menu");
    showDisplay =0;
   // firtsDisplay();

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
   
    lastPos = newPos;
    //lcd.clear();
     Serial.print(newPos);
    Serial.println();
    showDisplay = newPos; // Actualiza el numero de la pantalla
   // cursorDisplay(newPos); // Muestra el cursos que se actualiza en Y segun el encoder
  }
}
