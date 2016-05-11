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
#include "IMU.h"

//--모터 관련 상수, 변수
#define RC_MOTOR_L    0
#define RC_MOTOR_C    1
#define RC_MOTOR_R    2

#define RC_MOTOR_PIN_L  2
#define RC_MOTOR_PIN_C  3
#define RC_MOTOR_PIN_R  5

#define MOTOR_NEUTRAL 1488

////////////////////////////////

static bool    IsConnected;

class Command{
  private :
    uint32_t _baudrate;
  public : 
    Servo   RovMotor[3];
    RSP     RovSerial;
    cIMU    IMU;
    uint16_t Motor_pwm[3] = {MOTOR_NEUTRAL,MOTOR_NEUTRAL,MOTOR_NEUTRAL};
    uint8_t   err_code;
  public :
    Command();
    void RovSerial_begin(uint32_t _baudrate);
    void RovMotor_init();  //모터 초기화
    void process_recv_cmd( void );  //명령 수신 프로세스
    void send_cmd_info( void );   //수신 명령어 정보 송신
    void recv_cmd_control( RSP_CMD_OBJ *pCmd );  //LED, Motor 제어 명령
    void IMU_init();  //IMU 초기화(시작)
    void recv_status_IMU();   //IMU update
    void sout_status_IMU();   //IMU 정보 출력
    void cali_acc_IMU();  //가속도 계산
};

#endif
