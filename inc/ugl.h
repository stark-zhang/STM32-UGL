/**
* Title		STM32F407xx User-defined General Library Header File(only for HAL Library)
* Ref		STM32F4xx Manual(RM0090)
* Author	Stark Zhang
* Date		2017-09-30
* Debug		None
**/

#ifndef __User_defined_General_Library_H
#define __User_defined_General_Library_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"
#include "intrinsics.h"
#include "main.h"
#include "stdlib.h"
#include "ugl_conf.h"

//ARM Math Library
#if defined(ARM_MATH_CM0) || defined(ARM_MATH_CM0PLUS) || defined(ARM_MATH_CM3) || defined(ARM_MATH_CM4) || defined(ARM_MATH_CM7)

#include "arm_math.h"

#endif /*ARM_MATH_CMx*/

/* Interrupt Control */
#define 	IRQn_Enable()	__set_PRIMASK(0)
#define		IRQn_Disable()	__set_PRIMASK(1)

/* Bit & Band Operations */
#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))

#define GPIOA_ODR_Addr (GPIOA_BASE + 20) //0x40020014
#define GPIOB_ODR_Addr (GPIOB_BASE + 20) //0x40020414
#define GPIOC_ODR_Addr (GPIOC_BASE + 20) //0x40020814
#define GPIOD_ODR_Addr (GPIOD_BASE + 20) //0x40020C14
#define GPIOE_ODR_Addr (GPIOE_BASE + 20) //0x40021014
#define GPIOF_ODR_Addr (GPIOF_BASE + 20) //0x40021414
#define GPIOG_ODR_Addr (GPIOG_BASE + 20) //0x40021814
#define GPIOH_ODR_Addr (GPIOH_BASE + 20) //0x40021C14
#define GPIOI_ODR_Addr (GPIOI_BASE + 20) //0x40022014

#define GPIOA_IDR_Addr (GPIOA_BASE + 16) //0x40020010
#define GPIOB_IDR_Addr (GPIOB_BASE + 16) //0x40020410
#define GPIOC_IDR_Addr (GPIOC_BASE + 16) //0x40020810
#define GPIOD_IDR_Addr (GPIOD_BASE + 16) //0x40020C10
#define GPIOE_IDR_Addr (GPIOE_BASE + 16) //0x40021010
#define GPIOF_IDR_Addr (GPIOF_BASE + 16) //0x40021410
#define GPIOG_IDR_Addr (GPIOG_BASE + 16) //0x40021810
#define GPIOH_IDR_Addr (GPIOH_BASE + 16) //0x40021C10
#define GPIOI_IDR_Addr (GPIOI_BASE + 16) //0x40022010

#define PAout(n) BIT_ADDR(GPIOA_ODR_Addr, n)
#define PAin(n) BIT_ADDR(GPIOA_IDR_Addr, n)

#define PBout(n) BIT_ADDR(GPIOB_ODR_Addr, n)
#define PBin(n) BIT_ADDR(GPIOB_IDR_Addr, n)

#define PCout(n) BIT_ADDR(GPIOC_ODR_Addr, n)
#define PCin(n) BIT_ADDR(GPIOC_IDR_Addr, n)

#define PDout(n) BIT_ADDR(GPIOD_ODR_Addr, n)
#define PDin(n) BIT_ADDR(GPIOD_IDR_Addr, n)

#define PEout(n) BIT_ADDR(GPIOE_ODR_Addr, n)
#define PEin(n) BIT_ADDR(GPIOE_IDR_Addr, n)

#define PFout(n) BIT_ADDR(GPIOF_ODR_Addr, n)
#define PFin(n) BIT_ADDR(GPIOF_IDR_Addr, n)

#define PGout(n) BIT_ADDR(GPIOG_ODR_Addr, n)
#define PGin(n) BIT_ADDR(GPIOG_IDR_Addr, n)

#define PHout(n) BIT_ADDR(GPIOH_ODR_Addr, n)
#define PHin(n) BIT_ADDR(GPIOH_IDR_Addr, n)

#define PIout(n) BIT_ADDR(GPIOI_ODR_Addr, n)
#define PIin(n) BIT_ADDR(GPIOI_IDR_Addr, n)

/**
* Defination of Empty Byte
**/
#define Dummy_Byte 0xFF

/**
 * Defination of STM32 Operating mode(maybe not useful)
**/
typedef enum {
	Operate_Polling = 0x00,
	Operate_IT,
	Operate_DMA,
} UGL_Operate_Mode;

/* General Core Functions */
extern void UGL_Delay_us(uint32_t nus);
extern void UGL_Soft_Reset(void);
extern void UGL_Sys_Standby(void);

/* General DataType Functions*/

//string buffet
extern void UGL_Float2String(float data, uint8_t* str, uint8_t fbit, uint8_t mode);
extern uint16_t UGL_Buffer_Compare(uint8_t *pBuffer1, uint8_t *pBuffer2, uint16_t Length);
extern void UGL_Buffer_Flush(uint8_t* pBuffer, uint16_t Length);

//float/int32_t/uint32_t to uint8_t
void UGL_Float2Uint8(float num, uint8_t *p);

//STM32 HAL Assert Function
extern void assert_failed_callback(uint8_t* file, uint32_t line);


#endif /*__User_defined_General_Library_H*/

//EOF
