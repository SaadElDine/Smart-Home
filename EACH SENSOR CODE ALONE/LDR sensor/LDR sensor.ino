#define LDR A0 
#define LDR_led 2
void setup()
{
  Serial.begin(9600);
  pinMode(LDR_led,OUTPUT);
}

void loop() 
{
  int light = analogRead(LDR);
  Serial.println(light);
  delay(200);
  if (light < 200)
  {
    digitalWrite(LDR_led,HIGH);
  }  
  else 
    digitalWrite(LDR_led,LOW);
}
