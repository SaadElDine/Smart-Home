#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include<Servo.h>
#include <SimpleDHT.h>
#define rain_sensor A1
#define IR_sensor 22
#define PIR_sensor 3
#define PIR_led 52
#define Flame_sensor 5
#define LDR A0 
#define LDR_led 2
#define touch_sensor 53
#define water_sensor A2
#define gaz_sensor A3

const int trigPin = 34;
const int echoPin = 35;
long duration;
int distance;
LiquidCrystal_I2C lcd(0x27, 16, 2);
LiquidCrystal_I2C lcd2(0x26, 16, 2);
int pinDHT11 = 12;

SimpleDHT11 dht11(pinDHT11);
const byte ROWS = 4; 
const byte COLS = 4; 

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {32, 31, 30, 29}; 
byte colPins[COLS] = {28, 27, 26, 25}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

Servo myservo;
Servo myservo2;
Servo myservo3;
Servo myservo4;
int pos3 = 0;
int pos = 0; 
char* password="1234";
int currentposition=0;
int buzz=7;
int invalidcount=0;
int p = 0;
int p1 = 0;
int p2 = 0;
int p3 = 0;
int p4 = 0;
int p5 = 0;
int p6 = 0;
int p7 = 0;
int Incoming_value = 0;
long unsigned int Time_old=0;
byte temperature = 0;
int Temp;
byte humidity = 0;
 
void setup()
{
  displayscreen();
  Serial.begin(9600);
  pinMode(buzz, OUTPUT);
  myservo4.attach(6);  
  myservo3.attach(8); 
  myservo.attach(9);  
  myservo2.attach(10);    
  lcd.init();
  lcd.backlight();
  pinMode(IR_sensor,INPUT);
  myservo.write(0);
  myservo2.write(180);
  pinMode(Flame_sensor,INPUT);
  pinMode(PIR_led,OUTPUT);
  pinMode(PIR_sensor,INPUT);
  lcd2.init();
  lcd2.backlight();
  pinMode(rain_sensor,INPUT);
  pinMode(gaz_sensor,INPUT);  
  pinMode(LDR_led,OUTPUT);
  pinMode(touch_sensor,INPUT);
  pinMode(trigPin , OUTPUT); 
  pinMode(echoPin , INPUT);
  myservo3.write(150); 
  myservo4.write(180);
}
 
void loop()
{
     
  if( currentposition==0)
  {
    displayscreen();
  }
  int l ;
  char code=keypad.getKey();
  if(code!=NO_KEY)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PASSWORD:");
    lcd.setCursor(7,1);
    lcd.print(" ");
    lcd.setCursor(7,1);
        
    for(l = 0;l <= currentposition;++l)
    {
      lcd.print("*");
      keypress();
    }
    
    if (code==password[currentposition])
    {
      ++currentposition;
      if(currentposition==4)
      {
        unlockdoor();
        currentposition=0;
      }   
    }
    else
    {
      ++invalidcount;
      incorrect();
      currentposition=0;  
    }
    if(invalidcount == 3)
    {
      ++invalidcount;
      torture1();
    }
    if(invalidcount >= 5)
    {
      torture2();
    }
  }


  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
  {
    return;
  }

    
    lcd2.print("Tempature:  "); lcd2.print((int)temperature);
    lcd2.print("'C");
    lcd2.setCursor(0, 1);
    lcd2.print("Humidity:   ");
    lcd2.print((int)humidity);
    lcd2.print(" %     "); 

  
  int obstacle = digitalRead(IR_sensor);
  if (obstacle == 0)
  {
    p=1;
    lcd2.clear();
    lcd2.setCursor(0,0);
    lcd2.print(" Garage Opened! ");
    myservo3.write(10);
    unlockbuzz();
    delay(3000);    
  } 
  else
  {
    if(p==1) {
      digitalWrite(buzz, HIGH);
      delay(50);
      digitalWrite(buzz, LOW);
      delay(50);
      digitalWrite(buzz, HIGH);
      delay(50);
      digitalWrite(buzz, LOW);
      delay(50);
      digitalWrite(buzz, HIGH);
      delay(50);
      digitalWrite(buzz, LOW);
      delay(50);
      digitalWrite(buzz, HIGH);
      delay(50);
      digitalWrite(buzz, LOW);
      delay(50);
      myservo3.write(150);
      lcd2.clear();
      lcd2.print("Tempature:  "); lcd2.print((int)temperature);
      lcd2.print("'C");
      lcd2.setCursor(0, 1);
      lcd2.print("Humidity:   ");
      lcd2.print((int)humidity);
      lcd2.print(" %     "); 
      p=0;
    }
  }  

  int Flame = digitalRead(Flame_sensor);
  if (Flame == 0)
  {
    p1 = 1;
    digitalWrite(buzz,HIGH);
    lcd2.clear();
    lcd2.setCursor(0,0);
    lcd2.print(" House on fire !");
  }  
  else
  {
    if(p1 == 1) {
      digitalWrite(buzz,LOW); 
      lcd2.clear();
      lcd2.print("Tempature:  "); lcd2.print((int)temperature);
      lcd2.print("'C");
      lcd2.setCursor(0, 1);
      lcd2.print("Humidity:   ");
      lcd2.print((int)humidity);
      lcd2.print(" %     "); 
      p1 = 0;
    }
  }

   int analogSensor = analogRead(gaz_sensor);
  if (analogSensor < 400)
  {
    digitalWrite(buzz,HIGH);
    lcd2.clear();
    lcd2.setCursor(0,0);
    lcd2.print("Smoke detected !");
    p2 = 1;
  }
  else
  {
    if(p2 == 1) {
      digitalWrite(buzz,LOW); 
      lcd2.clear();
      lcd2.print("Tempature:  "); lcd2.print((int)temperature);
      lcd2.print("'C");
      lcd2.setCursor(0, 1);
      lcd2.print("Humidity:   ");
      lcd2.print((int)humidity);
      lcd2.print(" %     "); 
      p2 = 0;
    }
  }

  

  int light = analogRead(LDR);
  if (light < 200)
  {
    if(p3 == 0) {
      digitalWrite(LDR_led,HIGH);    
      p3 = 1;  
    }
  }  
  else 
  {
    if(p3 == 1) {
      digitalWrite(LDR_led,LOW); 
      p3 = 0;     
    }
  }

  int touch = digitalRead(touch_sensor);
  if (touch == 1)
  {
    if(p4 == 0) {
      myservo4.write(10);
      p4 = 1;
    }
  }
  else
  {
    if(p4 == 1) {
      delay(1000);
      myservo4.write(180);
      p4 = 0;      
    }
  }  

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  if(distance < 50) {
      digitalWrite(buzz,HIGH);    
      lcd2.clear();
      lcd2.setCursor(0,0);
      lcd2.print("Attention Thief!");      
      p5 = 1;
  }
  else {
    if(p5 == 1) {
      digitalWrite(buzz,LOW);
      lcd2.clear();
      lcd2.print("Tempature:  "); lcd2.print((int)temperature);
      lcd2.print("'C");
      lcd2.setCursor(0, 1);
      lcd2.print("Humidity:   ");
      lcd2.print((int)humidity);
      lcd2.print(" %     ");      
      p5 = 0;   
    }
  } 

  int water = analogRead(water_sensor);
  if (water > 500)
  {
	  digitalWrite(buzz,HIGH);
    lcd2.clear();
    lcd2.setCursor(0,0);
    lcd2.print("Piscine Level Up");
    p6 = 1;
  }  
  else
  {
    if(p6 == 1) {
      digitalWrite(buzz,LOW);
      lcd2.clear();
      lcd2.print("Tempature:  "); lcd2.print((int)temperature);
      lcd2.print("'C");
      lcd2.setCursor(0, 1);
      lcd2.print("Humidity:   ");
      lcd2.print((int)humidity);
      lcd2.print(" %     ");
      p6 = 0;
    }
  }

  int dryness = analogRead(rain_sensor);
  if (dryness < 900) 
  {
    p7 = 1;
    lcd2.clear();
    lcd2.setCursor(0,0);
    lcd2.print("Rainny Outside !");
  }  
  else 
  {
    if(p7 == 1) {
      lcd2.clear();
      lcd2.print("Tempature:  "); lcd2.print((int)temperature);
      lcd2.print("'C");
      lcd2.setCursor(0, 1);
      lcd2.print("Humidity:   ");
      lcd2.print((int)humidity);
      lcd2.print(" %     ");    
      p7 = 0;   
    }
  }

  if(Serial.available() > 0)  
  {
    Incoming_value = Serial.read(); 
    Serial.print(temperature);                 
    if(Incoming_value == 201)             
      digitalWrite(PIR_led, HIGH);  
    else if(Incoming_value == 200)       
      digitalWrite(PIR_led, LOW);  
    else if (Incoming_value == 202){
      lcd2.clear();
      lcd2.setCursor(0,0);
      lcd2.print(" Garage Opened! ");
      myservo3.write(10);
      unlockbuzz();
      delay(3000);    
    }
    else if (Incoming_value == 203){
        digitalWrite(buzz, HIGH);
        delay(50);
        digitalWrite(buzz, LOW);
        delay(50);
        digitalWrite(buzz, HIGH);
        delay(50);
        digitalWrite(buzz, LOW);
        delay(50);
        digitalWrite(buzz, HIGH);
        delay(50);
        digitalWrite(buzz, LOW);
        delay(50);
        digitalWrite(buzz, HIGH);
        delay(50);
        digitalWrite(buzz, LOW);
        delay(50);
        myservo3.write(150);
        lcd2.clear();
        lcd2.print("Tempature:  "); lcd2.print((int)temperature);
        lcd2.print("'C");
        lcd2.setCursor(0, 1);
        lcd2.print("Humidity:   ");
        lcd2.print((int)humidity);
        lcd2.print(" %     "); 
    } 
    else if (Incoming_value>=0 && Incoming_value<=100) {
      analogWrite(A7,Incoming_value*255.0/100);
    }  
  }



}

 
//***OPEN THE DOOR FUNCTION!!!!****//
 
void unlockdoor()
{
delay(900);
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(1,0);
lcd.print("Access Granted");
lcd.setCursor(4,1);
lcd.println("WELCOME!!");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(16,1);
lcd.println(" ");
lcd.setCursor(14,1);
lcd.println(" ");
lcd.setCursor(13,1);
lcd.println(" ");
unlockbuzz();
 
for(pos = 90; pos>=0; pos-=5) // goes from 90 degrees to 0 degrees
{
myservo.write(90-pos); // tell servo to go to position in variable 'pos'
myservo2.write(pos);
delay(5); // waits 15ms for the servo to reach the position
}

delay(2000);
delay(1000);
counterbeep();
delay(1000);
 
for(pos = 0; pos <= 90; pos +=5) // goes from 0 degrees to 90 degrees
{ // in steps of 1 degree
myservo.write(90-pos); // tell servo to go to position in variable 'pos'
myservo2.write(pos); 
delay(15);
currentposition=0;
lcd.clear();
displayscreen();
}
}
 
//*****WRONG CODE FUNCTION***//
 
void incorrect()
{
  delay(500);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Pin ");
  lcd.setCursor(6,0);
  lcd.print("INCORRECT");
  lcd.setCursor(15,1);
  lcd.println(" ");
  lcd.setCursor(4,1);
  lcd.println("GET AWAY!!!");
  
  lcd.setCursor(13,1);
  lcd.println(" ");
  //Serial.println("CODE INCORRECT YOU ARE UNAUTHORIZED");
  digitalWrite(buzz, HIGH);
  delay(3000);
  lcd.clear();
  digitalWrite(buzz,LOW);
  displayscreen();
}
//***** CLEAR THE SCREEN!!!****//
void clearscreen()
{
  lcd.setCursor(0,0);
  lcd.println(" ");
  lcd.setCursor(0,1);
  lcd.println(" ");
  lcd.setCursor(0,2);
  lcd.println(" ");
  lcd.setCursor(0,3);
  lcd.println(" ");
}
//*****KEYPRESS*******//
void keypress()
{
  digitalWrite(buzz, HIGH);
  delay(50);
  digitalWrite(buzz, LOW);
}

//***DISPALAY FUNCTION!!!****//
void displayscreen()
{
  lcd.setCursor(0,0);
  lcd.println(" ENTER THE PIN  ");
  lcd.setCursor(1 ,1); 
  lcd.println("TO _/_ (OPEN)!!");
}

//***** ARM SERVO*****//
void armservo()
{
  for (pos=90;pos<=90;pos+=50)
  {
    myservo.write(pos);
    myservo2.write(pos);
    delay(5);
  }
  
  delay(5000);
  
  for(pos=90;pos>=0;pos-=50)
  {
   myservo.write(90-pos);
   myservo2.write(pos);
  }
}
//***UNLOCK BUZZ****//
void unlockbuzz()
{
  digitalWrite(buzz, HIGH);
  delay(80);
  digitalWrite(buzz, LOW);
  delay(80);
  digitalWrite(buzz, HIGH);
  delay(80);
  digitalWrite(buzz, LOW);
  delay(200);
  digitalWrite(buzz, HIGH);
  delay(80);
  digitalWrite(buzz, LOW);
  delay(80);
  digitalWrite(buzz, HIGH);
  delay(80);
  digitalWrite(buzz, LOW);
  delay(80);
}
 
//***COUNTER BEEP***//
void counterbeep()
{
  delay(1200);
  
  lcd.clear();
  digitalWrite(buzz, HIGH);
  
  lcd.setCursor(2,15);
  lcd.println(" ");
  lcd.setCursor(2,14);
  lcd.println(" ");
  lcd.setCursor(2,0);
  delay(200);
  lcd.println("GET IN WITHIN:::");
  
  lcd.setCursor(4,1);
  lcd.print("5");
  delay(200);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN:");
  digitalWrite(buzz,LOW);
  delay(1000);
  //2
  digitalWrite(buzz, HIGH);
  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN:");
  lcd.setCursor(4,1); //2
  lcd.print("4");
  delay(100);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN:");
  digitalWrite(buzz,LOW);
  delay(1000);
  //3
  digitalWrite(buzz, HIGH);
  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN:");
  lcd.setCursor(4,1); //3
  lcd.print("3");
  delay(100);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN:");
  digitalWrite(buzz,LOW);
  delay(1000);
  //4
  digitalWrite(buzz, HIGH);
  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN:");
  lcd.setCursor(4,1); //4
  lcd.print("2");
  delay(100);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN:");
  digitalWrite(buzz,LOW);
  delay(1000);
  //
  digitalWrite(buzz, HIGH);
  lcd.setCursor(4,1);
  lcd.print("1");
  delay(100);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.println("GET IN WITHIN:");
  digitalWrite(buzz,LOW);
  delay(1000);
  //5
  digitalWrite(buzz, HIGH);
  delay(40);
  digitalWrite(buzz,LOW);
  delay(40);
  digitalWrite(buzz, HIGH);
  delay(40);
  digitalWrite(buzz,LOW);
  delay(40);
  digitalWrite(buzz, HIGH);
  delay(40);
  digitalWrite(buzz,LOW);
  delay(40);
  digitalWrite(buzz, HIGH);
  delay(40);
  digitalWrite(buzz,LOW);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("RE-LOCKING");
  delay(500);
  lcd.setCursor(12,0);
  lcd.print(".");
  delay(500);
  lcd.setCursor(13,0);
  lcd.print(".");
  delay(500);
  lcd.setCursor(14,0);
  lcd.print(".");
  delay(400);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("LOCKED!");
  delay(440);
  }
  //****TORTURE1****//
  void torture1()
  {
    delay(1000);
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("WAIT FOR ");
    lcd.setCursor(5,1);
    lcd.print("15 SECONDS");
    digitalWrite(buzz, HIGH);
    delay(15000);
    digitalWrite(buzz, LOW);
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("LOL..");
    lcd.setCursor(1,1);
    lcd.print(" HOW WAS THAT??");
    delay(3500);
    lcd.clear();
}
//**TORTURE2**//
void torture2()
{
  delay(1000);
  lcd.setCursor(1,0);
  lcd.print(" ");
  lcd.setCursor(2,0);
  lcd.print("EAR DRUMS ARE");
  lcd.setCursor(0,1);
  lcd.print(" PRECIOUS!! ");
  delay(1500);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print(" WAIT FOR");
  lcd.setCursor(4,1);
  lcd.print(" 1 MINUTE");
  digitalWrite(buzz, HIGH);
  delay(55000);
  counterbeep();
  lcd.clear();
  digitalWrite(buzz, LOW);
  lcd.setCursor(2,0);
  lcd.print("WANT ME TO");
  lcd.setCursor(1,1);
  lcd.print("REDICULE MORE??");
  delay(2500);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Ha Ha Ha Ha");
  delay(1700);
  lcd.clear();
}