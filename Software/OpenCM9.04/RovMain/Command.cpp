//----------------------------------------------------------------------------
//    프로그램명 	: Command
//
//    만든이     	:  
//
//    날  짜     : 
//    
//    최종 수정  	: 
//
//    MPU_Type	: 
//
//    파일명     	: Command.cpp
//----------------------------------------------------------------------------

#include <Arduino.h> 
#include "Command.h"

Command::Command(){};

/*---------------------------------------------------------------------------
     TITLE   : RovSerial_begin
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Command::RovSerial_begin(uint16_t baudrate)
{
    RovSerial.begin(baudrate); 
}


/*---------------------------------------------------------------------------
     TITLE   : RovMotor_Init
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Command::RovMotor_init(int _motor_pin, int _motor_name)
{
   RovMotor[_motor_name].attach(_motor_pin, 1000, 2000, 0, 255 );
   RovMotor[_motor_name].writeMicroseconds(MOTOR_NEUTRAL);
}

/*---------------------------------------------------------------------------
     TITLE   : process_recv_cmd
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Command::process_recv_cmd( void )
{
  uint32_t tTime;
  RSP_CMD_OBJ  *pCmd;
  bool Ret;
  
  Ret = RovSerial.update();

  if( Ret == true )
  {
        pCmd  = RovSerial.Get_CmdPtr(); 

     switch( pCmd->Cmd )
    {
      case 0x01:
        IsConnected = true;
        recv_cmd_control( pCmd );
        break;

      case 0xFE:
        IsConnected = true;
        break;
    } 
  }
  /*else
  {
    if( (tTime-millis()) >= 1000 )
    {
      IsConnected = false;
    }
    tTime = millis();
  }*/
}


/*---------------------------------------------------------------------------
     TITLE   : send_cmd_info
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Command::send_cmd_info( void )
{
  RSP_CMD_OBJ  Cmd;
  
  Cmd.Cmd     = 0xFF;
  Cmd.Length  = 1;
  Cmd.Data[0] = 100;

  RovSerial.SendCmd( &Cmd );
}

/*---------------------------------------------------------------------------
     TITLE   : recv_cmd_control
     WORK    : 
     ARG     : void
     RET     : void
---------------------------------------------------------------------------*/
void Command::recv_cmd_control( RSP_CMD_OBJ *pCmd )
{
  //-- 모터 제어 
  //Moter_Left
  if(pCmd->Data[6] == 1)
  {
    Motor_pwm[RC_MOTOR_L] = (pCmd->Data[8]<<8) | (pCmd->Data[7]);
    Serial.print("Moter_L : ");
    Serial.println(Motor_pwm[RC_MOTOR_C]);
    RovMotor[RC_MOTOR_L].writeMicroseconds(Motor_pwm[RC_MOTOR_L]);
  }
  //Moter_Center
  if(pCmd->Data[9] == 1)
  {
    Motor_pwm[RC_MOTOR_C] = (pCmd->Data[11]<<8) | (pCmd->Data[10]);
    Serial.print("Moter_C : ");
    Serial.println(Motor_pwm[RC_MOTOR_C]);
    RovMotor[RC_MOTOR_C].writeMicroseconds(Motor_pwm[RC_MOTOR_C]);
  }
  //Moter_Right
  if(pCmd->Data[12] == 1)
  {
    Motor_pwm[RC_MOTOR_R] = (pCmd->Data[14]<<8) | (pCmd->Data[13]);
    Serial.print("Moter_R : ");
    Serial.println(Motor_pwm[RC_MOTOR_R]);
    RovMotor[RC_MOTOR_R].writeMicroseconds(Motor_pwm[RC_MOTOR_R]);
  }

  //-- LED 제어 
  //Led_Left
  if(pCmd->Data[0] == 1)
  {
    LED_pwm[LED_L] = (LED_OFF - (pCmd->Data[2]<<8) | (pCmd->Data[1]));   
    Serial.print("Led_L : ");
    Serial.println(LED_pwm[LED_L]);
    analogWrite(LED_PIN_L, LED_pwm[LED_L]);
  }
  //Led_Right
  if(pCmd->Data[3] == 1)
  {
    LED_pwm[LED_R] = (LED_OFF - (pCmd->Data[5]<<8) | (pCmd->Data[4]));
    Serial.print("Led_R : ");
    Serial.println(LED_pwm[LED_R]);
    analogWrite(LED_PIN_R, LED_pwm[LED_R]);
  }
}


