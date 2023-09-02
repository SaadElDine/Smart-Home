#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>
#include <RemoteXY.h>
#define REMOTEXY_SERIAL_RX A8
#define REMOTEXY_SERIAL_TX A9
#define REMOTEXY_SERIAL_SPEED 9600
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   
  { 255,3,0,0,0,99,0,16,16,1,2,0,3,14,16,7,2,26,31,31,
  79,78,0,79,70,70,0,2,0,23,14,16,7,2,26,31,31,79,78,0,
  79,70,70,0,2,0,43,14,17,7,2,26,31,31,79,78,0,79,70,70,
  0,129,0,3,8,16,4,24,76,68,82,32,108,101,100,0,129,0,23,8,
  14,4,24,80,73,82,32,108,101,100,0,129,0,43,8,16,4,24,67,84,
  83,32,108,101,100,0 };

struct {

  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  uint8_t switch_2; // =1 if switch ON and =0 if OFF 
  uint8_t switch_3; // =1 if switch ON and =0 if OFF 

    
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)



#define PIN_SWITCH_1 2
#define PIN_SWITCH_2 4
#define PIN_SWITCH_3 9


void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_SWITCH_1, OUTPUT);
  pinMode (PIN_SWITCH_2, OUTPUT);
  pinMode (PIN_SWITCH_3, OUTPUT);
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1==0)?LOW:HIGH);
  digitalWrite(PIN_SWITCH_2, (RemoteXY.switch_2==0)?LOW:HIGH);
  digitalWrite(PIN_SWITCH_3, (RemoteXY.switch_3==0)?LOW:HIGH);
  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 


}