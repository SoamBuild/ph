void onPressed()
{
  delay(2000);
  changeDisplay();
}
// Funcion para cambiar de pantallas
void changeDisplay() {
  //Cambiar a la pantalla de ph

  
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
