#include <Wire.h>
#include <LiquidCrystal_I2C_Hangul.h>
LiquidCrystal_I2C_Hangul lcd(0x27, 16, 4);

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "HX711.h"

// ===================== PIN CONFIGURATION =====================
const int IR_Sensor        = 13;
const int Buzzer           = 5;
const int LOADCELL_DOUT_PIN = 16;
const int LOADCELL_SCK_PIN  = 4;
const int Relay_Pump       = 15;
const int Motor_Data1      = 18;
const int Motor_Data2      = 19;

// ===================== WiFi & Telegram CONFIG =====================
const char* ssid     = "YOUR_WIFI_SSID";       // Replace with your WiFi name
const char* password = "YOUR_WIFI_PASSWORD";   // Replace with your WiFi password
#define BOTtoken "YOUR_TELEGRAM_BOT_TOKEN"     // Replace with your Telegram Bot token
#define CHAT_ID  "YOUR_TELEGRAM_CHAT_ID"       // Replace with your Telegram Chat ID

// ===================== OBJECTS =====================
HX711 scale;
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

String inputString = "";
boolean RX_ST_Flag = false;
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;
int i;
String Tele_Mess = "";

// ===================== FUNCTION DECLARATIONS =====================
void NewMessagesHandle(int NewMessages);
void LoadCell_Init(void);
void LoadCalc(void);

// ===================== SETUP =====================
void setup()
{
  delay(200);
  pinMode(IR_Sensor,   INPUT);
  pinMode(Buzzer,      OUTPUT);
  pinMode(Relay_Pump,  OUTPUT);
  pinMode(Motor_Data1, OUTPUT);
  pinMode(Motor_Data2, OUTPUT);

  // LCD Init
  lcd.init();
  lcd.backlight();
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("   AUTOMATIC    ");
  lcd.setCursor(0, 1);
  lcd.print("  PET FEEDING   ");

  Serial.begin(9600);
  delay(500);

  WiFi.mode(WIFI_STA);
  delay(500);

  LoadCell_Init();
  delay(500);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  // Buzzer alert on startup
  digitalWrite(Buzzer, HIGH);
  delay(1000);
  digitalWrite(Buzzer, LOW);
  delay(1000);

  // Motor test on startup
  digitalWrite(Motor_Data1, HIGH);
  digitalWrite(Motor_Data2, LOW);
  delay(2000);
  digitalWrite(Motor_Data1, LOW);
  digitalWrite(Motor_Data2, LOW);
  delay(2000);
  digitalWrite(Motor_Data1, LOW);
  digitalWrite(Motor_Data2, HIGH);
  delay(2000);
  digitalWrite(Motor_Data1, LOW);
  digitalWrite(Motor_Data2, LOW);
  delay(1000);

  // Water pump test on startup
  digitalWrite(Relay_Pump, HIGH);
  delay(2000);
  digitalWrite(Relay_Pump, LOW);
  delay(1000);

  // Send startup notification
  bot.sendMessage(CHAT_ID, "Automatic Pet Feeding System");
  delay(500);
}

// ===================== LOOP =====================
void loop()
{
  lcd.clear();
  delay(300);

  delay(500);
  LoadCalc();

  // IR Sensor - Pet Detection
  if (digitalRead(IR_Sensor) == LOW)
  {
    lcd.setCursor(0, 1);
    lcd.print(" OBSTACLE DETECT");
    delay(500);
    digitalWrite(Buzzer, HIGH);
    delay(1000);
    digitalWrite(Buzzer, LOW);
    delay(1000);
  }
}

// ===================== LOAD CELL WEIGHT DISPLAY =====================
void LoadCalc(void)
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("WEIGHT= ");
  lcd.print((int)scale.get_units(10));
  lcd.print("g");
  delay(2000);
}

// ===================== LOAD CELL INITIALIZATION =====================
void LoadCell_Init(void)
{
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  delay(200);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());
  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));
  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));
  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);

  scale.set_scale(243);  // Calibration factor — adjust as needed
  scale.tare();          // Reset scale to 0

  Serial.println("After setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());
  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));
  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));
  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);
  Serial.println("Readings:");
}
