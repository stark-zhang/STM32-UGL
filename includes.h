/**
* Title    Includes files for User-defined General Library (without source file)
* Author   Stark Zhang
* Date     2017-09-30
* Debug    None
* version  0.7.5
**/

#ifndef __INCLUDES_UGL_H
#define __INCLUDES_UGL_H

/* User-defined General Library Header File */

#include "./inc/ugl.h"

/* Cortex-M SoftWare Modules Header Files */

//FatFS
#if (__FatFS_USED == 1)

#include "./inc/ugl_fatfs.h"

#endif /*__FatFS_USED*/

//Lua Support
#if (__Lua_Support == 1)

#include "./inc/ugl_lua.h"

#endif /*__Lua_Support*/

//Malloc of User
#if (__Usr_Malloc == 1)

#include "./inc/ugl_malloc.h"

#endif /*__Usr_Malloc*/

/* Cortex-M HardWare Modules Header Files */

//GPIO
#ifdef HAL_GPIO_MODULE_ENABLED

#include "./inc/ugl_gpio.h"

#endif /*HAL_GPIO_MODULE_ENABLED*/

//RCC
#ifdef HAL_RCC_MODULE_ENABLED

//#include "./inc/ugl_rcc.h"

#endif /*HAL_RCC_MODULE_ENABLED*/

//SPI
#ifdef HAL_SPI_MODULE_ENABLED

#include "./inc/ugl_spi.h"

#endif /*HAL_SPI_MODULE_ENABLED*/

//UART
#ifdef HAL_UART_MODULE_ENABLED

#include "./inc/ugl_uart.h"

#endif /*HAL_UART_MODULE_ENABLED*/

//USART
#ifdef HAL_USART_MODULE_ENABLED

#include "./inc/ugl_usart.h"

#endif /*HAL_USART_MODULE_ENABLED*/

/* Compilers Special functions(optional) */

//ARM(MDK)
#ifdef __CC_ARM

#include "./inc/ugl_mdk.h"

#endif /*__CC_ARM*/

//GNU ARM
#ifdef __GNUC__

#include "./inc/ugl_gcc.h"

#endif /*__GNUC__*/

//IAR for ARM
#ifdef __ICCARM__

#include "./inc/ugl_iar.h"

#endif /*__ICCARM__*/

#endif /*__INCLUDES_UGL_H*/

//EOF
