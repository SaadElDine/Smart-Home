// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX A8
#define REMOTEXY_SERIAL_TX A9
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 200 bytes
  { 255,3,0,66,0,193,0,16,30,1,2,0,2,10,18,8,2,26,31,31,
  79,78,0,79,70,70,0,2,0,24,10,15,8,2,26,31,31,79,78,0,
  79,70,70,0,2,0,43,10,17,8,2,26,31,31,79,78,0,79,70,70,
  0,129,0,3,25,18,6,24,84,101,109,112,32,40,67,41,32,58,0,67,
  4,36,25,23,7,2,26,11,129,0,4,36,29,6,24,72,117,109,32,40,
  37,41,32,58,0,67,4,35,36,23,7,2,26,11,129,0,6,3,13,5,
  24,76,68,82,0,129,0,26,3,10,5,24,80,73,82,0,129,0,45,3,
  10,5,24,67,84,83,0,129,0,4,50,29,6,24,84,104,101,32,68,111,
  111,114,58,0,67,4,35,49,22,7,2,26,11,67,4,5,61,52,8,2,
  26,11,67,4,5,72,52,8,2,26,11,67,4,5,83,52,8,2,26,11 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t LDR_led_bt; // =1 if switch ON and =0 if OFF 
  uint8_t PIR_led_bt; // =1 if switch ON and =0 if OFF 
  uint8_t touch_led_bt; // =1 if switch ON and =0 if OFF 

    // output variables
  char text_1[11];  // string UTF8 end zero 
  char text_2[11];  // string UTF8 end zero 
  char text_3[11];  // string UTF8 end zero 
  char text_4[11];  // string UTF8 end zero 
  char text_5[11];  // string UTF8 end zero 
  char text_6[11];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_LDR_LED_BT 40
#define PIN_PIR_LED_BT 41
#define PIN_TOUCH_LED_BT 42


void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_LDR_LED_BT, OUTPUT);
  pinMode (PIN_PIR_LED_BT, OUTPUT);
  pinMode (PIN_TOUCH_LED_BT, OUTPUT);
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  digitalWrite(PIN_LDR_LED_BT, (RemoteXY.LDR_led_bt==0)?LOW:HIGH);
  digitalWrite(PIN_PIR_LED_BT, (RemoteXY.PIR_led_bt==0)?LOW:HIGH);
  digitalWrite(PIN_TOUCH_LED_BT, (RemoteXY.touch_led_bt==0)?LOW:HIGH);
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 


}