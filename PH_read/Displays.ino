void firtsDisplay(int display) {
  lcd.setCursor(0,0);
  lcd.print("Ducasse PH CTRL");

  switch (display)
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
  /*
  rotary(0, 1);
  mainMenu=true;
  subMenu =false;
  lcd.setCursor(1, 0);
  lcd.print("Mediraaaaaa      ");
  lcd.setCursor(1, 1);
  lcd.print("Calibrar    ");
  */


void readingDisplay() {
  rotary (0, 1);
  mainMenu = false;
  subMenu = true;
  lcd.setCursor(1, 0);
  lcd.print("Medir      ");
  lcd.setCursor(1, 1);
  lcd.print("Volver     ");
}
void calibrateDisplay() {
  rotary (0, 1);
  mainMenu = false;
  subMenu = true;
  lcd.setCursor(1, 0);
  lcd.print("PH 10.0    ");
  lcd.setCursor(1, 1);
  lcd.print("Volver     ");
}
void cursorDisplay(int cursorindex) {
  lcd.clear();
  lcd.setCursor(0, cursorindex);
  lcd.print(">");
}
