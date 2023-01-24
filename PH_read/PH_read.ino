#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EasyButton.h>
#include "FS.h"
#include <LittleFS.h>
#include <WiFiManager.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <Adafruit_NeoPixel.h>
#include "SD.h"
#include "SPI.h"

// spiffs
#define FORMAT_LITTLEFS_IF_FAILED true
int displayNumber = 1; // id display
int showDisplay = 1;   // Update value rotary

// PH CONTROL
float const ph4 = 4.00;   // Value x PH Calculated
float const ph7 = 7.00;   // Value x PH Calculated
float const ph10 = 10.00; // Value x PH Calculated
float R1 = 222.00;        // Value x PH Calculated
float R2 = 395.00;        // Value x PH Calculated
float R3 = 561.00;        // Value x PH Calculated
int sensorph = 32;
float globalPh; // Variable global para actualizar valor de PH

LiquidCrystal_I2C lcd(0x27, 20, 4); // Setup x lcd


// Buttons x navigations
const int button_NEXT = 17;
const int button_ENTER = 16;
EasyButton btn_ENTER(button_ENTER); // Check x click rotarys
EasyButton btn_NEXT(button_NEXT);   // Check x click rotarys
// Enter or Out Menus
boolean subMenu_Medir = false;
boolean subMenu_Calibrar = false;
boolean subMenu_Calibrar_2 = false;
boolean mainMenu = true;
// Variable x get memory spiffs
String value;
// object WifiManager
WiFiManager wm;
// Firebase Setting
#define API_KEY       ""
#define DATABASE_URL  ""
#define USER_EMAIL    ""
#define USER_PASSWORD ""
int counter = 1;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
String uid;
// Setup data to send
String databasePath;
String id = "/id";
String numeroID = "1"; //
String phPath = "/ph";
String timePath = "/timestamp";
String parentPath;
FirebaseJson json;
// NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
int timestamp;
//Neopixel pins and object
const int  neopin =26;
const int  numpixel =1;
Adafruit_NeoPixel pixels(numpixel, neopin, NEO_GRB + NEO_KHZ800);
// local sd variable
char filenameCSV[25] = "";
String datoSD;

// Muestreo
unsigned long previousMillis = millis();
long muestreo = 30000;
#define SD_CS   5
#define SD_SCLK   18
#define SD_MISO   19
#define SD_MOSI   23


void setup()
{
  // Serial init
  Serial.begin(115200);
  // Init and function btn_ENTER pressed
  btn_ENTER.begin();
  btn_NEXT.begin();
  btn_ENTER.onPressed(onPressed);
  btn_NEXT.onPressed(onPressed2);
  //Neopixel setup
  pixels.begin();
  // LCD INIT
  lcd.init();
  lcd.backlight();
  changePixel(255,0,0);
  // Print hello Message
  lcd.setCursor(0, 0);
  lcd.print("PH Ducasse Control2");
  delay(2000);
  // lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Setup Wifi          ");
  delay(2000);
 // lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print("Wifi AP             ");
  lcd.setCursor(0, 3);
  lcd.print("Estanque1 WM        ");
  // WIFI MANAGER
  const char *menu[] = {"wifi", "param", "restart", "exit"}; // Disabled infobtn
  wm.setMenu(menu, 4);
  wm.setConnectTimeout(60); // tiempo en segundo
  bool res;
  res = wm.autoConnect("Estanque1 WM");
  if (!res)
  {
    Serial.println("Failed to connect");
    setupcheck("Wifi", "Error");
    // ESP.restart();
  }
  else
  {
    setupcheck("Wifi", "Ok");
    Serial.println("connected");
  }
  setupcheck("DB connect", "Checking");
  // Firebase setup
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
  config.max_token_generation_retry = 5;
  Firebase.begin(&config, &auth);
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "")
  {
    Serial.print('.');
    delay(1000);
    counter++;
    if (counter == 180)
    {
      setupcheck("DB connect", "Error");
      ESP.restart();
    }
  }
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);
  databasePath = "/UsersData/" + uid + "/readings";
  // ntp setup
  timeClient.begin();
  //SD setup
  SPI.begin(SD_SCLK , SD_MISO, SD_MOSI);
   setupcheck("Mount local DB ", "SD CHECK");
  if (!SD.begin(SD_CS)) {
    Serial.println("Card Mount Failed");
       setupcheck("Mount local DB", "SD FAIL");
    return;
  }else{
    setupcheck("Mount local DB", "SD Ok");
  }
  int n = 0;
  snprintf(filenameCSV, sizeof(filenameCSV), "/datos%03d.csv", n); // includes a three-digit sequence number in the file name
  while (SD.exists(filenameCSV)) {
    n++;
    snprintf(filenameCSV, sizeof(filenameCSV), "/datos%03d.csv", n);
  }
  File file = SD.open(filenameCSV, FILE_READ);
  Serial.println(filenameCSV);
  file.close();
  // Mount spiff memory
  setupcheck("Mount localDB", "Mounting");
  if (!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED))
  {
    Serial.println("LittleFS Mount Failed");
    setupcheck("Mount localDB", "Error");
    return;
  }
  // Check Calibration PH4
  setupcheck("Calibracion check", "Ph4.0 Ok");
  readFile(LittleFS, "/r1.txt");
  Serial.println(" dato recuperado: " + value);
  R1 = value.toFloat();
  Serial.println(" calibracion recuperada: " + String(R1));
  delay(2000);
  // Check Calibration PH7
  setupcheck("Calibracion check", "Ph 7.0 Ok");
  readFile(LittleFS, "/r2.txt");
  Serial.println(" dato recuperado: " + value);
  R2 = value.toFloat();
  Serial.println(" calibracion recuperada: " + String(R2));
  delay(2000);
  // Check Calibration PH10
  setupcheck("Calibracion check", "Ph 10.0 Ok");
  readFile(LittleFS, "/r3.txt");
  Serial.println(" dato recuperado: " + value);
  R3 = value.toFloat();
  Serial.println(" calibracion recuperada: " + String(R3));
  delay(2000);
  lcd.clear();
}

void loop()
{
  btn_ENTER.read(); // Read change btn_ENTER
  btn_NEXT.read();
  if (Firebase.isTokenExpired())
  {
    Firebase.refreshToken(&config);
    Serial.println("Refresh token");
  }

  if (mainMenu == true)
  {
    firtsDisplay(showDisplay);
  }

  if (mainMenu == true && showDisplay == 1)
  {
    getPH();
  }
  if (mainMenu == true && displayNumber == 2)
  {
    calibrationPH4();
  }
  if (mainMenu == true && displayNumber == 3)
  {
    calibrationPH7();
  }
  if (mainMenu == true && displayNumber == 4)
  {
    calibrationPH10();
  }
  if (mainMenu == true && displayNumber == 5)
  {
    wm.resetSettings();
    ESP.restart();
  }
  capturedata();
}
// GetTimefromNTP
unsigned long getTime()
{
  timeClient.update();
  unsigned long now = timeClient.getEpochTime();
  return now;
}
void getPH()
{
  int sensorValue = analogRead(sensorph);
  // primer recta 4 y 7
  // float ph = ((ph7 - ph4) / (R2 - R1)) * (sensorValue - R1) + ph4;
  // Segunda recta 4 y 10
  // float phv2 = ((ph10 - ph7) / (R3 - R2)) * (sensorValue - R2) + ph7;

  if (sensorValue <= R2 && sensorValue >= R1)
  {
    float ph = ((ph7 - ph4) / (R2 - R1)) * (sensorValue - R1) + ph4;
    globalPh = ph;
    Serial.println("PH RECT12 ;" + String(ph));
  }
  // si no alcanza el minimo buffer minimo
  if (sensorValue < R1)
  {
    float ph = ((ph7 - ph4) / (R2 - R1)) * (sensorValue - R1) + ph4;
    globalPh = ph;
    Serial.println("PH RECT12 ;" + String(ph));
  }

  // si se pasa del buffer
  if (sensorValue > R3)
  {
    float phv2 = ((ph10 - ph7) / (R3 - R2)) * (sensorValue - R2) + ph7;
    globalPh = phv2;
    Serial.println("PH RECTA2 ;" + String(phv2));
  }

  if (sensorValue <= R3 && sensorValue > R2)
  {
    float phv2 = ((ph10 - ph7) / (R3 - R2)) * (sensorValue - R2) + ph7;
    globalPh = phv2;
    Serial.println("PH RECTA2 ;" + String(phv2));
  }
}
void toCloud(int valuetoSave)
{
  // function X save value firebase
}
// Calibracion R1 x 1 minuto
void calibrationPH4()
{
  for (int i = 0; i < 60; i++)
  {
    R1 = analogRead(sensorph);
    Serial.println(R1);
    calibration_analog_Display(4, i);
    delay(1000);
  }
  // guardando en spiff
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Guardando Calibracion ");
  lcd.setCursor(0, 1);
  lcd.print("PH 4.0 ");
  String NP = String(R1);
  writeFile(LittleFS, "/r1.txt", NP.c_str());
  delay(1000);
  readFile(LittleFS, "/r1.txt");
  Serial.println(" dato recuperado de la memoria r1: " + value);
  // Volver a menu de calibracion
  lcd.clear();
  showDisplay = 1;
  displayNumber = 0;
}
// Calibracion R2 x 1 minuto
void calibrationPH7()
{
  for (int i = 0; i < 60; i++)
  {
    R2 = analogRead(sensorph);
    Serial.println(R2);
    calibration_analog_Display(7, i);
    delay(1000);
  }
  // guardando en spiff
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Guardando Calibracion ");
  lcd.setCursor(0, 1);
  lcd.print("PH 7.0 ");
  String NP = String(R2);
  writeFile(LittleFS, "/r2.txt", NP.c_str());
  delay(1000);
  readFile(LittleFS, "/r2.txt");
  Serial.println(" dato recuperado: " + value);
  // Volver a menu de calibracion
  lcd.clear();
  showDisplay = 1;
  displayNumber = 0;
}
// Calibracion R3 x 1 minuto
void calibrationPH10()
{
  for (int i = 0; i < 60; i++)
  {
    R3 = analogRead(sensorph);
    Serial.println(R3);
    calibration_analog_Display(10, i);
    delay(1000);
  }
  // guardando en spiff
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Guardando Calibracion ");
  lcd.setCursor(0, 1);
  lcd.print("PH 10.1 ");
  String NP = String(R3);
  writeFile(LittleFS, "/r3.txt", NP.c_str());
  delay(1000);
  readFile(LittleFS, "/r3.txt");
  Serial.println(" dato recuperado: " + value);
  // Volver a menu de calibracion
  lcd.clear();
  showDisplay = 1;
  displayNumber = 0;
}
