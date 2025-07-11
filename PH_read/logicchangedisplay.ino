void changeDisplay(int display)
{
  // Menu principal
  if (mainMenu == true)
  {
    
    if (display == 2)
    {
      lcd.clear();
      displayNumber = 2;
     
    }
    if (display == 3)
    {
      lcd.clear();
      displayNumber = 3;
    
    }
    if (display == 4)
    {
      lcd.clear();
      displayNumber = 4;
  
    }
    if (display == 5)
    {
      lcd.clear();
      displayNumber = 5;
        }
  }
}


