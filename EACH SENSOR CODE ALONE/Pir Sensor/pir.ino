#define PIR_sensor 3
#define PIR_led 4

void setup() 
{
  Serial.begin(9600);    
  pinMode(PIR_led,OUTPUT);
  pinMode(PIR_sensor,INPUT);
}

void loop() 
{
  int PIR_value = digitalRead(PIR_sensor);
  if (PIR_value == LOW)
  {
    digitalWrite(PIR_led,HIGH);
    Serial.println("motion detect.");
   }
  else
    {
    digitalWrite(PIR_led,LOW);
    }  
}