#define water_sensor A2
#define water_led 24
#define buzzer 7

void setup()
{
  pinMode(water_led,OUTPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int water = analogRead(water_sensor);
  Serial.println(water);
  if (water > 690)
  {
    digitalWrite(water_led,HIGH);
	digitalWrite(buzzer,HIGH);

  }  
  else
  {
    digitalWrite(water_led,LOW);
	digitalWrite(buzzer,LOW);
  }
  delay(300);
  
}