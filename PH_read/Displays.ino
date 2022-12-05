void firtsDisplay(){
  //lcd.clear();
  rotary(0,1);
  lcd.setCursor(1, 0);
  lcd.print("Medir");
  lcd.setCursor(1, 1);
  lcd.print("Calibrar");
}

void readingDisplay(){
  rotary (0,1);
  subMenu=true;
  //lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Medir");
  lcd.setCursor(1, 1);
  lcd.print("Volver");
  


  
}

void cursorDisplay(int cursorindex){
  lcd.clear();
  lcd.setCursor(0, cursorindex);
  lcd.print(">");
  


}
