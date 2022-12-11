//Text x main menu
void firtsDisplay(int display_Home) {
  lcd.setCursor(0,0);
  lcd.print("Ducasse PH CTRL");

  switch (display_Home)
  {
  case  0:
    lcd.setCursor(0, 1);
    lcd.print("Medir      ");
    lcd.setCursor(13,1);
    lcd.print("1/2");
    /* code */
    break;
    case 1:
    lcd.setCursor(0, 1);
    lcd.print("Calibrar PH      ");
    lcd.setCursor(13,1);
    lcd.print("2/2");
    /* code */
    break;

  }
}
//Text x read menu
  void readingDisplay(int display_Medir) {
  lcd.setCursor(0,0);
  lcd.print("Medir PH");
  switch (display_Medir)
  {
  case  0:
    lcd.setCursor(0, 1);
    lcd.print("PH: "+String(random(0,10)));
    lcd.setCursor(13,1);
    lcd.print("1/2");
    /* code */
    break;
    case 1:
    lcd.setCursor(0, 1);
    lcd.print("Volver");
    lcd.setCursor(13,1);
    lcd.print("2/2");
    /* code */
    break;

  }
}
//Text x calibration menu
void calibrateDisplay(int display_Calibrar) {
  lcd.setCursor(0,0);
  lcd.print("Calibrar PH");
  switch (display_Calibrar)
  {
  case  0:
    lcd.setCursor(0, 1);
    lcd.print("PH 4.0");
    lcd.setCursor(13,1);
    lcd.print("1/4");
    /* code */
    break;
    case 1:
    lcd.setCursor(0, 1);
    lcd.print("PH 7.0");
    lcd.setCursor(13,1);
    lcd.print("2/4");
    /* code */
    break;
    case 2:
    lcd.setCursor(0, 1);
    lcd.print("PH 10.0");
    lcd.setCursor(13,1);
    lcd.print("3/4");
    /* code */
    break;
     case 3:
    lcd.setCursor(0, 1);
    lcd.print("Volver ");
    lcd.setCursor(13,1);
    lcd.print("4/4");
    /* code */
    break;

  }
}
//Text x calibration menu 
void calibration_analog_Display(int PH,int time){

    lcd.setCursor(0, 0);
    lcd.print("Adjust PH: "+String(PH));
    lcd.setCursor(0, 1);
    lcd.print("Tiempo Res: "+String(time));
  
    
}