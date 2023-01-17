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
