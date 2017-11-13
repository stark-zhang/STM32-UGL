/**
* Title    Includes files for User-defined General Library (without source file)
* Author   Stark Zhang
* Date     2017-09-30
* Debug    None
* version  0.9.0 alpha
**/

#ifndef __INCLUDES_UGL_H
#define __INCLUDES_UGL_H

/* User-defined General Library Header File */

#include "./inc/ugl.h"
#include "./inc/ugl_cortex.h"

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
#if (__User_Malloc == 1)

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

#endif /*__INCLUDES_UGL_H*/

//EOF
