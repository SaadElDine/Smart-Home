#define limit_switch 10
#define limit_led 11
void setup() 
  {
    pinMode(limit_switch,INPUT);
    pinMode(limit_led,OUTPUT);
  }
void loop() 
  {
    int limit_touch = digitalRead(limit_switch);
    if (limit_touch == 0)
      {
        digitalWrite(limit_led,HIGH);
      }    
    else
      {          
        digitalWrite(limit_led,LOW);
      }      
  }
