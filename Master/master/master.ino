#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include "SIM900.h"
#include <SoftwareSerial.h>

#include "sms.h"
SMSGSM sms;

// The LCD constructor - address shown is 0x27 - may or may not be correct for yours
// Also based on YWRobot LCM1602 IIC V1
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#define dht_apin A0
# define green 8
#define blue 12
# define buzzer 10
# define smoke A1
#define red 7
#define MQ5 A2


// Your threshold value
int sensorThres_LPG = 330;
int sensorThres_SMOKE = 300;
int sensorThres_CO = 380;
int sensorThres_NO2 = 300;
int sensorThres_SO2 = 270;

dht DHT;

int numdata;
boolean started=false;
char smsbuffer[160];
char n[20];

void setup() {
  lcd.begin(16,2); // sixteen characters across - 2 lines
  lcd.backlight();
  delay(500);

  Serial.begin(9600);
  
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smoke, INPUT);
  pinMode(MQ5, INPUT);
  
  delay(1000);
}

void loop() {
  //lcd.clear();

  DHT.read11(dht_apin);
  
  Serial.println(DHT.humidity);

  lcd.setCursor(0,0);
  lcd.print("humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%  ");

  delay(9000);
    
  Serial.println(DHT.temperature);

  lcd.setCursor(0,1);
  lcd.print("temp: ");
  lcd.print(DHT.temperature); 
  lcd.println("C  ");

  delay(9000);
  
  int analogSensor = analogRead(smoke);
  int lpg_value = analogRead(smoke) - 60;
  int co_value = analogRead(smoke) - 20;

  int mq5 = analogRead(MQ5);
  int nitrous_oxide = analogRead(MQ5);
  int sulphur_oxide = analogRead(MQ5) - 20;


  Serial.println(co_value);

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Pollutants");
  
  lcd.setCursor(0,1);
  lcd.print("CO: ");
  lcd.print(co_value);
  lcd.print(" PPM");
  
  delay(9000);
  
  Serial.println(analogSensor);

  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Pollutants");

  lcd.setCursor(0,1);
  lcd.print("SMOKE: ");
  lcd.print(analogSensor);
  lcd.print(" PPM");

  delay(9000);
  
  Serial.println(lpg_value);

  lcd.clear();
    
  lcd.setCursor(0,0);
  lcd.print("Pollutants");
  
  lcd.setCursor(0,1);
  lcd.print("LPG: ");
  lcd.print(lpg_value);
  lcd.print(" PPM");

  delay(9000);

  Serial.println(nitrous_oxide);

  lcd.clear();
    
  lcd.setCursor(0,0);
  lcd.print("Pollutants");
  
  lcd.setCursor(0,1);
  lcd.print("NO2: ");
  lcd.print(nitrous_oxide);
  lcd.print(" PPM");

  delay(9000);


 Serial.println(sulphur_oxide);

  lcd.clear();
    
  lcd.setCursor(0,0);
  lcd.print("Pollutants");
  
  lcd.setCursor(0,1);
  lcd.print("SO2: ");
  lcd.print(sulphur_oxide);
  lcd.print(" PPM");

  delay(1000);

  
  // Checks if it has reached the threshold value
  
  if (analogSensor > sensorThres_SMOKE){
    Serial.println("SMOKE THRESHOLD ALARM");
    digitalWrite(buzzer, HIGH);
    digitalWrite(red, HIGH);
    
    if (gsm.begin(2400)){
    Serial.println("\nstatus=READY");
    started=true;  
  }
  else Serial.println("\nstatus=IDLE");
  digitalWrite(buzzer, LOW);
  
  if(started){
    //Enable this two lines if you want to send an SMS.
    if (sms.SendSMS("233249313974", "Air pollution threshold VALUES exceeded at lat: -5.2331356 and long: 1.23579987"))
      Serial.println("\nSMS sent OK");
  }
  }
  
  else if(analogSensor < sensorThres_LPG){
    Serial.println("SMOKE WITHIN THRESHOLD");
    digitalWrite(green, HIGH);
  }

  else {
    digitalWrite(blue, HIGH);
    digitalWrite(buzzer, LOW);
    }
  
  delay(2000);

}
