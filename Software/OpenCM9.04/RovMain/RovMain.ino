//----------------------------------------------------------------------------
//    프로그램명   : RovMain
//
//    만든이       :  
//
//    날  짜     : 
//    
//    최종 수정   : 
//
//    MPU_Type  : 
//
//    파일명       : RovMain.ino
//----------------------------------------------------------------------------

#include "Command.h"

Command RovCommand;

void setup() 
{
  Serial.begin(115200);
  RovCommand.RovSerial_begin(115200);

  RovCommand.RovMotor_init();
  RovCommand.IMU_init();
  Led_setup();
 
  IsConnected = false;
}

void loop() 
{
  static uint32_t tTime[3];

  RovCommand.recv_status_IMU();
  RovCommand.process_recv_cmd();
  
  //-- 100ms마다 ROV정보 전달
  if( (millis() - tTime[1]) >= 200 )
  {
    tTime[1] = millis();
   
    RovCommand.sout_status_IMU(); 
    RovCommand.send_cmd_info();
  }
  RovCommand.cali_acc_IMU();

  //-- 연결이 끊어진 상태 
/* 
  if( IsConnected == false )
  {
    RovServo[RC_MOTOR_L].writeMicrosecond(MOTOR_NEUTRAL);
    RovServo[RC_MOTOR_C].writeMicrosecond(MOTOR_NEUTRAL);
    RovServo[RC_MOTOR_R].writeMicrosecond(MOTOR_NEUTRAL);    
  }
  */
}
