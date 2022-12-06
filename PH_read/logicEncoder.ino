void onPressed()
{

 Serial.println("Click");
 changeDisplay();

}

void changeDisplay() {
  
  Serial.println("capture value: " + String(newPos));
  if (displayNumber == 0 && subMenu == false) {
    readingDisplay();
    Serial.println("read display");
    showDisplay = 1;
    lcd.clear();
  }
  if (displayNumber == 1 && subMenu == false) {
    calibrateDisplay();
    Serial.println("calibrate display");
    showDisplay = 2;
    lcd.clear();

  }
  clickMenu = false;
}

void rotary(int ROTARYMIN, int ROTARYMAX)
{
  encoder.tick();

  // get the current physical position and calc the logical position
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
  } // if

  if (lastPos != newPos)
  {

    Serial.print(newPos);
    Serial.println();
    lastPos = newPos;
    displayNumber =newPos;
    cursorDisplay(newPos);
    if (clickMenu == true) {
      //changeDisplay(newPos);
      //clickMenu = false;
    }
  }
}
