void firtsDisplay() {
  rotary(0, 1);
  subMenu = false;
  mainMenu = true;
  lcd.setCursor(1, 0);
  lcd.print("Medir      ");
  lcd.setCursor(1, 1);
  lcd.print("Calibrar    ");
}

void readingDisplay() {
  rotary (0, 1);
  subMenu = true;
    mainMenu = false;
  lcd.setCursor(1, 0);
  lcd.print("Medir      ");
  lcd.setCursor(1, 1);
  lcd.print("Volver     ");
}
void calibrateDisplay() {
  rotary (0, 1);
  subMenu = true;
    mainMenu = false;
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
