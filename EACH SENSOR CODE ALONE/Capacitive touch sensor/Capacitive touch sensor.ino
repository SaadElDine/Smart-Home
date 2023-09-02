#define touch_sensor 8
#define touch_led 9

void setup() 
{
  pinMode(touch_sensor,INPUT);
  pinMode(touch_led,OUTPUT);
}
void loop() 
{
  int touch = digitalRead(touch_sensor);
  if (touch == 1)
  {
    digitalWrite(touch_led,HIGH);
  }
  else
  {
  digitalWrite(touch_led,LOW);
  }  
}
