/**
 * Title	UGL Module Configuration Header files£¨no source file)
 * Author	Stark Zhang
 * Date		2017-10-02
 * Debug	None
**/

/* This file is used to manage User Configurations */

#ifndef __UGL_CONF_H
#define __UGL_CONF_H

/* STM32 HAL Macros */
/**
 * Defination for ARM Math Library
**/
/*#define   ARM_MATH_CM0*/          	//ARM Math for Cortex-M0
/*#define   ARM_MATH_CM0PLUS*/      	//ARM Math for Cortex-M0+
/*#define   ARM_MATH_CM3*/          	//ARM Math for Cortex-M3
#define     ARM_MATH_CM4            	//ARM Math for Cortex-M4F(default)
/*#define   ARM_MATH_CM7*/          	//ARM Math for Cortex-M7


/**
 * Defination for Parameters Checking(Forced Open HAL Assert)
**/
#ifndef 	USE_FULL_ASSERT

#define     USE_FULL_ASSERT         	//defination for Parameters Checking

#endif /*USE_FULL_ASSERT*/

/* User defined Macros */
/**
 * Defination for FatFS, if not defined, FatFS is disabled(User's Defination)
**/
#define   	__FatFS_USED		0       //defination for FatFS

/**
 * defination for Lua Support
**/
#define     __Lua_Support       0       //defination for Lua

/**
 * Defination for User's Malloc(User's Defination)
**/
#define 	__User_Malloc		0		//defination for User's Malloc

/**
 * Defination for User Debugging(Note: it maybe conflict with other USART/UART application!)
**/
#define   	__Usr_UART_Debug	1		//defination for Output Debug information through UART

#endif /*__UGL_CONF_H*/

//EOF
