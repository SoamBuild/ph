void onPressed()
{
  delay(2000);
  changeDisplay(showDisplay);
}

void changeDisplay(int display) {
  Serial.println("changedisplay to:"+String(display));

  if(mainMenu==true){
    if(display==0){
      lcd.clear();
      displayNumber=2;
      mainMenu=false;
      subMenu_Medir=true;
    }
    if(display==1){
      lcd.clear();
      displayNumber=3;
      mainMenu=false;
      subMenu_Calibrar=true;
    }
  }
  if(subMenu_Medir == true){
    if(display==0){

    }
    if(display==1){
      lcd.clear();
      displayNumber=1;
      mainMenu=true;
      subMenu_Medir=false;
    }
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
    Serial.println(newPos);
    showDisplay = newPos; // Actualiza el numero de la pantalla
    
   // cursorDisplay(newPos); // Muestra el cursos que se actualiza en Y segun el encoder
  }
}
