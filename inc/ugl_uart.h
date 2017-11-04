/**
 * Title	UGL Module UART User Header files(HardWare Modules)
 * Author	Stark Zhang
 * Date		2017-10-01
 * Debug	None
**/

#ifndef __UGL_UART_H
#define __UGL_UART_H

#include "ugl.h"

#ifdef HAL_UART_MODULE_ENABLED

//General Functions with UART
extern void UGL_UART_SetBaudRateUGL_UART_SetBaudRate(UART_HandleTypeDef huart, uint32_t BaudRate);

//Working in Polling

//Working in IT

//Working in DMA

#endif /*HAL_UART_MODULE_ENABLED*/

#endif /*__UGL_UART_H*/

//EOF
