// Function click encoder
void onPressed()
{
  Serial.println("Anotherbtn");
  changeDisplay(showDisplay);
}
void onPressed2()
{
  showDisplay = showDisplay + 1;
  Serial.println(showDisplay);
  limits(1, 5); // limite de pantallas
  lcd.clear();
}

void limits(int min, int max)
{
  if (showDisplay == max + 1)
  {
    showDisplay = min;
    Serial.println("Limite Alcanzado");
  }
}
