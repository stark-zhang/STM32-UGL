/**
 * Title	UGL Module Configuration Header files£¨no source file)
 * Author	Stark Zhang
 * Date		2017-10-02
 * Debug	None
**/

/* This file is used to manage User Configurations */

#ifndef __UGL_CONF_H
#define __UGL_CONF_H

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
 * Defination for User's Software Timer(STIM)(User's Defination)
**/
#define 	__User_STIM			1		//defination for User's STIM

/**
 * Defination for User's uptime(User's Defination)
**/

#define 	__User_uptime		1		//defination for User's uptime

/**
 * Defination for User Debugging(Note: it maybe conflict with other USART/UART application!)
**/
#define   	__User_UART_Debug	1		//defination for Output Debug information through UART

#endif /*__UGL_CONF_H*/

//EOF
