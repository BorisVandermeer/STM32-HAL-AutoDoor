// Created By ZBQ
// Created Date 2021_11_04
// Edit Date    2021_11_04

#ifndef _MOTORDRIVER_H_
#define _MOTORDRIVER_H_

extern int Motor_State;

//全局标志定义表
#define MOTORBRAKED 0
#define MOTORPULLING 1
#define MOTORPUSHING 2

#define USEIO
//#define USEPWM

#ifdef USEIO  //如果使用IO口来最快PUSH//PULL 而无需控制速度
#define MOTOR_PH_PIN GPIO_PIN_9
#define MOTOR_EN_PIN GPIO_PIN_8 

#define MOTOR_PH_PORT GPIOD  
#define MOTOR_EN_PORT GPIOD //端口初始化那儿Port写到一起了

#define MOTORINIT() MOTOR_INIT_IO()
#define MOTOR_PUSH() SET_MOTOR_PUSH_IO()
#define MOTOR_PULL() SET_MOTOR_PULL_IO()
#define MOTOR_BRAKE() SET_MOTOR_BRAKE_IO()

//四个函数被重定义过
void MOTOR_INIT_IO(void);      //初始化，设为BRAKE
void SET_MOTOR_PUSH_IO(void);  //设为推出状态
void SET_MOTOR_PULL_IO(void);  //设为拉回状态
void SET_MOTOR_BRAKE_IO(void); //设为能耗刹车状态


#endif

#ifdef USEPWN
	//还未实现
#endif

#endif
