/**
 * Title	UGL Module GPIO User Header files(HardWare Modules)
 * Author	Stark Zhang
 * Date		2017-09-30
 * Debug	None
**/

#ifndef __UGL_GPIO_H
#define __UGL_GPIO_H

#include "ugl.h"

#ifdef HAL_GPIO_MODULE_ENABLED

//Macros for Parameter Checking
#define IS_GPIO_PORT(GPIOx) (((GPIOx) == GPIOA) || \
                             ((GPIOx) == GPIOB) || \
                             ((GPIOx) == GPIOC) || \
                             ((GPIOx) == GPIOD) || \
                             ((GPIOx) == GPIOE) || \
                             ((GPIOx) == GPIOF) || \
                             ((GPIOx) == GPIOG) || \
                             ((GPIOx) == GPIOH) || \
                             ((GPIOx) == GPIOI))

extern inline uint16_t UGL_GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
extern inline uint16_t UGL_GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
extern inline void UGL_GPIO_WriteOutPutData(GPIO_TypeDef* GPIOx, uint16_t pBuffer);

#endif /*HAL_GPIO_MODULE_ENABLED*/

#endif /*__UGL_GPIO_H*/