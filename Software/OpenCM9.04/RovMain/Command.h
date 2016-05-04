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
//    파일명     	: Command.h
//----------------------------------------------------------------------------
#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <inttypes.h>
#include <Servo.h>
#include "ROV_LED.h"
#include "RSP.h"

//--모터 관련 상수, 변수
#define RC_MOTOR_L    0
#define RC_MOTOR_C    1
#define RC_MOTOR_R    2

#define RC_MOTOR_PIN_L  2
#define RC_MOTOR_PIN_C  3
#define RC_MOTOR_PIN_R  5

#define MOTOR_NEUTRAL 1488

static uint16_t Motor_pwm[3] = {MOTOR_NEUTRAL,MOTOR_NEUTRAL,MOTOR_NEUTRAL};
////////////////////////////////

static bool    IsConnected;

class Command{
  private :
    Servo   RovMotor[3];
    RSP     RovSerial;
    uint16_t baudrate;
  public :
    Command();
    uint16_t _motor_pwm;
    void RovSerial_begin(uint16_t baudrate);
    void RovMotor_init();  //모터 초기화
    void process_recv_cmd( void );  //명령 수신 프로세스
    void send_cmd_info( void );   //수신 명령어 정보 송신
    void recv_cmd_control( RSP_CMD_OBJ *pCmd );  //LED, Motor 제어 명령
};

#endif
