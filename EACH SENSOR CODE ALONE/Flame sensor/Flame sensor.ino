#define Flame_sensor 5
#define Flame_led 6
#define Flame_buzzer 7
void setup() 
{
  pinMode(Flame_sensor,INPUT);
  pinMode(Flame_led,OUTPUT);
  pinMode(Flame_buzzer,OUTPUT);
  Serial.begin(9600);
}
void loop() 
{
  int Flame = digitalRead(Flame_sensor);
  if (Flame == 0)
  {
    digitalWrite(Flame_led,HIGH);
    digitalWrite(Flame_buzzer,HIGH);
    Serial.println("house on fire");
    delay(200);
  }  
  else
  {
    digitalWrite(Flame_led,LOW);
    digitalWrite(Flame_buzzer,LOW); 
  }
}
