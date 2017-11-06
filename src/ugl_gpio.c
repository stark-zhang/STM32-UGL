/**
 * Title	UGL Module GPIO User Source files(HardWare Modules)
 * Author	Stark Zhang
 * Date		2017-09-30
 * Debug	None
**/

#include "../inc/ugl_gpio.h"

#ifdef HAL_GPIO_MODULE_ENABLED

/**
 * @brief	Read a group of GPIO(GPIOA as example) Input Data
 * @param	GPIO_TypeDef* GPIOx
				name of GPIO group
 * @return	None
 * @note	None
**/
uint16_t UGL_GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
	assert_param(IS_GPIO_PORT(GPIOx));
	return (uint16_t)GPIOx->IDR;
}

/**
 * @brief	Read a group of GPIO(GPIOA as example) Output Data
 * @param	GPIO_TypeDef* GPIOx
				name of GPIO group
 * @return 	None
 * @note	None
**/
uint16_t UGL_GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
	assert_param(IS_GPIO_PORT(GPIOx));
	return (uint16_t)GPIOx->ODR;
}

/**
 * @brief	Write Output Data to whole group GPIO
 * @param	GPIO_TypeDef* GPIOx
				name of GPIO group
 * @param	uint16_t pBuffer
				Data will be written to ODR
 * @return 	None
 * @note	None
**/
void UGL_GPIO_WruteOutPutData(GPIO_TypeDef* GPIOx, uint16_t pBuffer)
{
	assert_param(IS_GPIO_PORT(GPIOx));
	GPIOx->ODR = (uint16_t)pBuffer;
}

#endif /*HAL_GPIO_MODULE_ENABLED*/

//EOF
