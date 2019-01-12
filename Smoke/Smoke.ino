# define LED 8
# define buzzer 10
# define smoke A1

// Your threshold value
int sensorThres_LPG = 515;
int sensorThres_SMOKE = 520;
int sensorThres_CO = 518;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smoke, INPUT);
  Serial.begin(9600);
}

void loop() {
  int analogSensor = analogRead(smoke);

  Serial.print("smoke_level: ");
  Serial.println(analogSensor);
  
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres_LPG)
  
  {
    Serial.println("LPG THRESHOLD REACHED!");
    digitalWrite(buzzer, HIGH);
  }
  else
  {
    Serial.println("LPG VALUES ARE WITHIN RANGE");
    digitalWrite(buzzer, LOW);
  }
  delay(2000);

  if (analogSensor > sensorThres_SMOKE)
  
  {
    Serial.println("SMOKE THRESHOLD REACHED!");
    
  }
  else
  {
    Serial.println("SMOKE VALUES ARE WITHIN RANGE");
  }

  delay(2000);

  if (analogSensor > sensorThres_CO)
  
  {
    Serial.println("CO THRESHOLD REACHED!");
    
  }
  else
  {
    Serial.println("CO VALUES ARE WITHIN RANGE");
  }

  delay(2000);
}
