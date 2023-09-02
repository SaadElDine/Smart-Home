#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>
#include <Wire.h> 
LiquidCrystal_I2C lcd(0x27,16,2);
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {32, 31, 30, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {28, 27, 26, 25}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char password[]="A1609";
int i=0,count=0,number=sizeof(password)-1;
char words[sizeof(password)-1];
#define security_switch 33
#define anti_security_switch 34
int pinDHT11 = 12;
SimpleDHT11 dht11(pinDHT11);
void setup()
{


  Serial.begin(9600);    
  lcd.begin();  
  pinMode(security_switch,INPUT_PULLUP);
  pinMode(anti_security_switch,INPUT_PULLUP);  
   
}

  
void loop()
{ 
int security = digitalRead(security_switch);
int anti_security = digitalRead(anti_security_switch);
char key = keypad.getKey(); 
if (security == 1)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter Password:  ");
}
if (key>='0'&&key!='D')
{   
  lcd.setCursor(i, 1);    
  lcd.print('*');
  words[i] = key;
  i++;
  delay(200);
}
if(key =='D')
    {
      if(i==number)
      {
        for(int j=0;j<number;j++)
        {
          if(words[j]==password[j])count++;
        }
        if(count==number)
        {
           right();
        }
        else
        {
           wrong();          
        }
      }       
      else 
      {
           wrong();
      }
    }


if  (anti_security == 1)
{ 
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
  {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  lcd.begin();  
  lcd.clear();
  lcd.print("tempature  "); lcd.print((int)temperature);
  lcd.setCursor(0, 1);
  lcd.print("humidity   ");  lcd.print((int)humidity);
  //delay(1000);

}
}


void wrong()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Wrong Pass :(  ");
  delay(2000);
  lcd.clear();
  lcd.print("TRY AGAIN!!!  ");
  delay(2000); 
  i=0;
  count=0;
  lcd.setCursor(0,0);
  lcd.print("Enter Password:  ");
  lcd.setCursor(0,1); 
}

void right()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Correct Pass :) ");
  delay(2000);
  lcd.clear();          
  lcd.print("Welcome Back!!!");
  delay(2000);          
  i=0;
  count=0;
  lcd.setCursor(0,0);
  lcd.print("Enter Password:   ");
  lcd.setCursor(0,1);
}
  






  

