#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>
#define rain_sensor A1

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd2(0x26, 16, 2);
int pinDHT11 = 12;
SimpleDHT11 dht11(pinDHT11);

void setup()
{
  lcd2.init();
  lcd2.backlight();
  Serial.begin(9600);
  pinMode(rain_sensor,INPUT);
}

void loop() 
{
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
  {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }

    lcd2.clear();
    lcd2.print("Tempature:  "); lcd2.print((int)temperature);
    lcd2.print("'C");
    lcd2.setCursor(0, 1);
    lcd2.print("Humidity:   ");
    lcd2.print((int)humidity);
    lcd2.print(" %     "); 

  int dryness = analogRead(rain_sensor);
  if (dryness < 900) {
    lcd2.clear();
    lcd2.print("Tempature:  "); lcd2.print((int)temperature);
    lcd2.print("'C");
    lcd2.setCursor(0, 1);
    lcd2.print("     Rainny     ");
    delay(5000);
  }
}

 

