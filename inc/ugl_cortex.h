/**
 * Title	UGL Module Cortex_Mx User Header files(HardWare Core Modules)
 * Author	Stark Zhang
 * Date		2017-11-09
 * Debug	None
**/

/* This file is a package for Cortex-M Peripherals such as FPU & Systick */

/******************************************************************************
 * 1. Systick
 *	implement a series of soft timers with systick intertupt(STIM)
 *	- These STIMs can achieve timing functions as well as hardware basic timer
 *	- they also can be used to generate PWM, and input capture, but their per-
 *	- -formance cannot be good as well as hardware timers
 *	- only support to count down
 *
 * 2. MPU
 *
 * 3. FPU(optional)
 *
******************************************************************************/

#ifndef __UGL_CORTEX2_H
#define __UGL_CORTEX2_H

#include "ugl.h"

/* Definations & Functions of STIM */

/**
 * count of STIM, user-defined, default is 4
**/
#define 	STIM_MAX_Count		4

/**
 * STIM work mode enum
**/
typedef enum
{
	STIM_ONCE_MODE = 0,			//once mode
	STIM_AUTO_MODE,				//auto mode
}UGL_STIM_ModeTypDef;

/**
 * STIM work state enum
**/
typedef enum
{
	STIM_IS_WORKING= -1,		//Working
	STIM_IS_STANDBY,			//Stand By
	STIM_IS_STOPED,				//Stoped
}UGL_STIM_StateTypeDef;

/**
 * STIM Initialization structure
**/
typedef struct
{
	__IO UGL_STIM_ModeTypDef _mode;		//Working mode, default is once
	__IO uint32_t _preload;				//Timer Preload value
}UGL_STIM_InitTypeDef;

/**
 * STIM Handle strucure
**/
typedef struct 
{
	uint8_t _instance;					//STIM ID
	__IO uint8_t _overflow_flag;		//Overflow Flag
	__IO uint32_t _count;				//Count
	__IO UGL_STIM_InitTypeDef _init;	//Init
	__IO UGL_STIM_StateTypeDef _state; 	//STIM Work State
}STIM_HandleTypeDef;

//Public STIM Operation Functions
extern void UGL_STIM_Init(STIM_HandleTypeDef *stim, uint8_t _count);
extern void UGL_STIM_Start(STIM_HandleTypeDef *stim);
extern void UGL_STIM_Stop(STIM_HandleTypeDef *stim);
extern uint8_t UGL_STIM_TimerCheck(STIM_HandleTypeDef *stim);

//Private Functions for STIM
static void UGL_STIM_Dec(STIM_HandleTypeDef *stim);

/* Definations & Functions of Run Time Check */

//Public Functions
extern int32_t UGL_Cortex_GetRunTime(void);
extern int32_t UGL_Cortex_CheckRunTime(int32_t _LastTime);

/* User-defined Functions*/
extern void UGL_Cortex_IDLE(void);

/* Systick interrupt callback */
extern void HAL_SYSTICK_Callback(void);

#endif /*__UGL_CORTEX2_H*/

//EOF
