//Function click encoder
void onPressed()
{
  /*
  delay(1000);
  changeDisplay(showDisplay);
  if(mainMenu==false){
  count_SW = count_SW+1; // debounce click x submenus
}else{
  count_SW=1;// en menu principal reestablece el valor
}
*/
}
void onPressed2()
{
 showDisplay= showDisplay +1;
 Serial.println(showDisplay);
}

void changeDisplay(int display) {
 // Menu principal
  if(mainMenu==true){
    // In medir submenu
    if(display==0){
      lcd.clear();
      displayNumber=2;
      mainMenu=false;
      subMenu_Medir=true;
    }
    if(display==1){
      // In medir calibracion menu
      lcd.clear();
      displayNumber=3;
      mainMenu=false;
      subMenu_Calibrar=true;
    }
  }
  //Medir menu
  if(subMenu_Medir == true){
    //Click para enviar dato a la nube
    if(display==0 && count_SW==2 ){
       mainMenu=true;
      subMenu_Medir=false;
      count_SW=1;
      lcd.clear();
      delay(1000);
      lcd.setCursor(0,0);
      lcd.print("Enviando Medicion");
      delay(2000);
       lcd.clear();
      displayNumber=1;
      }
      //Volver al menu principal
    if(display==1){
      lcd.clear();
      displayNumber=1;
      mainMenu=true;
      subMenu_Medir=false;
      count_SW=1;
    }
  }
  //menu de calibracion
  if(subMenu_Calibrar == true){
    // Calibrar R1
    if(display==0 && count_SW==2){
      lcd.clear();
      mainMenu=false;
      subMenu_Calibrar=false;
      subMenu_Calibrar_2=true;
      displayNumber=4;
      count_SW=1;
    }
    //Calibrar R2
     if(display==1 && count_SW==2 ){
      
      lcd.clear();
      mainMenu=false;
      subMenu_Calibrar=false;
      subMenu_Calibrar_2=true;
      displayNumber=5;
      count_SW=1;
      
    }
    //Calibrar R3
     if(display==2 && count_SW==2){
         lcd.clear();
      mainMenu=false;
      subMenu_Calibrar=false;
      subMenu_Calibrar_2=true;
      displayNumber=6;
      count_SW=1;
    }
    //Volver al menu principal
    if(display==3 && count_SW==2){
      lcd.clear();
      displayNumber=1;
      mainMenu=true;
      subMenu_Calibrar=false;
      count_SW=1;
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
   // showDisplay = newPos; // Actualiza el numero de la pantalla
    
   // cursorDisplay(newPos); // Muestra el cursos que se actualiza en Y segun el encoder
  }
}
