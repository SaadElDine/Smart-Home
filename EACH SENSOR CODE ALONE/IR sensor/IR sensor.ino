#define IR_sensor 22
#define IR_led 23
int obstacle = 1;
void setup() 
{
  pinMode(IR_sensor,INPUT);
  pinMode(IR_led,OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  int obstacle = digitalRead(IR_sensor);
  if (obstacle == 0)
  {
    digitalWrite(IR_led,HIGH);
    Serial.println("OBSTACLE!");
    delay(300);    
  } 
  else
  {
    digitalWrite(IR_led,LOW);
    Serial.println("clear");
    delay(300);    
  }  
}
