// Text x main menu
void firtsDisplay(int display_Home)
{
  lcd.setCursor(0, 0);
  lcd.print("Ducasse PH Control");

  switch (display_Home)
  {
  case 1:
    lcd.setCursor(0, 1);
    lcd.print("PH ACTUAL  ");
    lcd.setCursor(10, 1);
    lcd.print(globalPh);
    lcd.setCursor(0, 13);
    lcd.setCursor(17, 3);
    lcd.print("1/5");

    // lcd.print("1/5");
    /* code */
    break;
  case 2:
  
    lcd.setCursor(0, 1);
    lcd.print("Calibrar PH 4.0     ");
    lcd.setCursor(13, 1);
     lcd.setCursor(17, 3);
    lcd.print("2/5");

    // lcd.print("2/5");
    /* code */
    break;
  case 3:
    lcd.setCursor(0, 1);
    lcd.print("Calibrar PH 7.0     ");
    lcd.setCursor(13, 1);
    lcd.setCursor(17, 3);
    lcd.print("3/5");
    // lcd.print("3/5");
    /* code */
    break;
  case 4:
    lcd.setCursor(0, 1);
    lcd.print("Calibrar PH 10.0    ");
    lcd.setCursor(13, 1);
    lcd.setCursor(17, 3);
    lcd.print("4/5");
    // lcd.print("4/5");
    /* code */
    break;
  case 5:
    lcd.setCursor(0, 1);
    lcd.print("Delete WIFI");
    lcd.setCursor(13, 1);
    lcd.setCursor(17, 3);
    lcd.print("5/5");
    // lcd.print("5/5");
    /* code */
    break;
  }
}
void setupcheck(String part, String state)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PH Ducasse Boot");
  lcd.setCursor(0, 1);
  lcd.print("Check " + part);
  lcd.setCursor(0, 2);
  lcd.print(state);
  delay(1200);
}
// Text x read menu
void readingDisplay(int display_Medir)
{
  lcd.setCursor(0, 0);
  lcd.print("Medir PH");
  switch (display_Medir)
  {
  case 0:
    lcd.setCursor(0, 1);
    lcd.print("PH: " + String(globalPh));
    lcd.setCursor(13, 1);
    lcd.print("1/2");
    /* code */
    break;
  case 1:
    lcd.setCursor(0, 1);
    lcd.print("Volver");
    lcd.setCursor(13, 1);
    lcd.print("2/2");
    /* code */
    break;
  }
}
// Text x calibration menu
void calibrateDisplay(int display_Calibrar)
{
  lcd.setCursor(0, 0);
  lcd.print("Calibrar PH");
  switch (display_Calibrar)
  {
  case 0:
    lcd.setCursor(0, 1);
    lcd.print("PH 4.0");
    lcd.setCursor(13, 1);
    lcd.print("1/4");
    /* code */
    break;
  case 1:
    lcd.setCursor(0, 1);
    lcd.print("PH 7.0");
    lcd.setCursor(13, 1);
    lcd.print("2/4");
    /* code */
    break;
  case 2:
    lcd.setCursor(0, 1);
    lcd.print("PH 10.0");
    lcd.setCursor(13, 1);
    lcd.print("3/4");
    /* code */
    break;
  case 3:
    lcd.setCursor(0, 1);
    lcd.print("Volver ");
    lcd.setCursor(13, 1);
    lcd.print("4/4");
    /* code */
    break;
  }
}
// Text x calibration menu
void calibration_analog_Display(int PH, int time)
{

  lcd.setCursor(0, 0);
  lcd.print("Adjust PH: " + String(PH) + "   ");
  lcd.setCursor(0, 1);
  lcd.print("Tiempo Res: " + String(time) + "   ");
}