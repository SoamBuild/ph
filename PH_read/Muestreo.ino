
void capturedata(){

 unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= muestreo) {
    previousMillis = currentMillis;
   
    timestamp = getTime();
  
  //  datoSD = String(timestamp) + "," + String(ph_avg) + "\n";
   // Serial.println(datoSD);
   // appendFile(SD, filenameCSV, datoSD.c_str());
    // digitalWrite(LED, HIGH);
  //  delay(1000);
  publish();
  }}
  void publish()
{
 
  //Get current timestamp
  timestamp = getTime();
  Serial.print ("time: ");
  Serial.println (timestamp);
  parentPath = databasePath + "/" + String(timestamp);
  json.set(id.c_str(), String(numeroID));
  json.set(phPath.c_str(), String(globalPh));
  json.set(timePath, String(timestamp));
  Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
  }