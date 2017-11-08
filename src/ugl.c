/**
 * Title	STM32F407xx User-defined General Library Source File(only for HAL Library)
 * Ref		STM32F4xx Manual(RM0090)
 * Author	Stark Zhang
 * Date		2017-09-30
 * Debug	None
**/

#include "../inc/ugl.h"

/* for difference of ASM with every Compiler */
#if defined(__CC_AARM)              //for ARM MDK
#include "../inc/ugl_mdk.h"
#elif defined(__GNUC__)             //for GCC ARM
#include "../inc/ugl_gcc.h"
#elif defined(__ICCARM__)           //for IAR ARM
#include "../inc/ugl_iar.h"
#endif  /*Compilers*/

/* Variables for UGL_Delay Function */
static uint8_t fac_us = 0;

/* General Functions */

/**
 * UGL_Delay_ms() 
 * no-defined, used HAL_Delay()
**/

/**
 * @brief	Delay on us level
 * @func	void UGL_Delay_us()
 * @param	uint32_t nus
 * @return 	None
 * @note	nus <= 798915us(2^24/fac_us @fac_us=21)
**/
void UGL_Delay_us(uint32_t nus)
{
	uint32_t temp;
	//Get System Clock Frequency(in MHz)
	fac_us = HAL_RCC_GetSysClockFreq() / 1000000 / 8;
	SysTick->LOAD = nus*fac_us;   		 
	SysTick->VAL = 0x00;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; 	 
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01) && !(temp&(1<<16)));   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL = 0X00;     
}

/**
 * @brief	System/Cortex-M Core Reset softly
 * @param	None
 * @return	None
 * @note	None
**/
void UGL_Soft_Reset(void)
{
	SCB->AIRCR =0X05FA0000|(uint32_t)0x04;
}

/**
 * @brief	System/Cortex-M Core To Stanging by
 * @param	None
 * @return	None
 * @note	None
**/
void UGL_Sys_Standby(void)
{
	SCB->SCR 		|= 1 << 2;   
	RCC->APB1ENR 	|= 1 << 28;
	PWR->CSR 		|= 1 << 8;
	PWR->CR 		|= 1 << 2;
	PWR->CR 		|= 1 << 1;  	
	ASM_WFI_Set();
}

/**
 * @brief	Float converts to String(char arr)
 * @param	float data
				data will be converted
 * @param	uint8_t *str
				pointer to string after converting)
 * @param	uint8_t fbit
				Decimal places after converting
 * @param	uint8_t mode
				working mode,if mode = 0, result includes plus sign, else doesn't include
 * @return	None
 * @note	it also can be used for integer converting, but fbit must be zero
**/
void UGL_Float2String(float data, uint8_t* str, uint8_t fbit, uint8_t mode)
{
	int i, j, k, l;
    long temp, tempoten;
    uint8_t intpart[20], dotpart[20];

    if(mode == 0)
    {
        if(data < 0) 
        {
            str[0] = '-';
            data = -data;
        }
        else 
            str[0] = '+';
    }
    else str[0] = ' ';
    
    temp = (long)data;
    
    i = 0;
    tempoten = temp / 10;
    while(tempoten != 0)
    {
        intpart[i] = temp - 10 * tempoten + 48; //to ascii code
        temp = tempoten;
        tempoten = temp/10;
        i++;
    }
    intpart[i] = temp + 48;
    
    data = data - (long)data;
    for(j = 0; j < 12 ; j++)
    {
        dotpart[j] = (int)(data * 10) + 48;
        data = data * 10.0;
        data = data - (long)data;
		if(j >= fbit)
		{
			dotpart[j] = '\0';
			break;
		}
    }

    for(k = 1; k <= i + 1; k++) 
    {
        str[k] = intpart[i+1-k];
        str[i+2] = '.';
    }
    for(k = i + 3; k < i + j + 3; k++) 
    {
        str[k] = dotpart[k-i-3];
        str[i+j+3] = 0x0D;
    }
    
    for(l = 0; l < 100; l++)
    {
        if(*(str+l) == '.')
            break;
        else continue;
    }
    for(int m = l; m < 25; m++)
    {
        *(str + m + fbit + 1) = '\0';
    }
}

/**
 * @brief  	Compares two buffers.
 * @param  	pBuffer1, pBuffer2
				buffers to be compared.
 * @param  	Length
				buffer's length
 * @return 	0  : pBuffer1 identical to pBuffer2
 *         >0 : pBuffer1 differs from pBuffer2 
 * @Note	None
**/
uint16_t UGL_Buffer_Compare(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t Length)
{
	while(Length--)
	{
		if((*pBuffer1) != *pBuffer2)
		{
			return Length;
		}
		pBuffer1++;
		pBuffer2++;
	}
	return 0;
}

/**
 * @brief 	Flush the buffer
 * @param	uint8_t* pBuffer
				buffer will be flushed
 * @param  	Length
				buffer's length
 * @return 	None
 * @Note	None
**/
void UGL_Buffer_Flush(uint8_t* pBuffer, uint16_t Length)
{
	while(Length--)
	{
		*pBuffer = 0;
		pBuffer++;
	}
}

/**
 * @brief	float converts to uint8_t(in arr)
 * @param	float* p1_Buffer
				float array to convert
 * @param	uint16_t f_size
				size of float array
 * @param	uint8_t* p2_Buffer
				integer array after converting
 * @param	uint32_t i_size
				size of integer array
 * @return	None
 * @note	i_size >= 4 * f_size
**/
void UGL_Float2Uint8_t(float* p1_Buffer, uint16_t f_size, uint8_t* p2_Buffer, uint32_t i_size)
{
	if(i_size < f_size * 4)
		return;
	else
	{
		UGL_Float2Uint8_TypeDef temp[f_size];
		uint32_t k = 0;

		for(uint16_t i = 0; i < f_size; i++)
		{
			temp[i].f_num = *(p1_Buffer+i);
			
			for(uint8_t j = 0; j < sizeof(float); j++)
			{
				*(p2_Buffer+k) = temp[i].arr[j];
				k++;
			}
		}
	}
}

/**
 * @brief	uint8_t converts to float(in arr)
 * @param	uint8_t* p1_Buffer
				integer array to convert
 * @param	uint32_t i_size
				size of integer array
 * @param	float* p2_Buffer
				float array after converting
 * @param	uint16_t f_size
				size of float array
 * @return	None
 * @note	i_size >= 4 * f_size
**/
void UGL_Uint8_t2Float(uint8_t* p1_Buffer, uint32_t i_size, float* p2_Buffer, uint16_t f_size)
{
	if(i_size < f_size * 4)
		return;
	else
	{
		UGL_Float2Uint8_TypeDef temp[f_size];
		uint32_t k = 0;
		
		for(uint16_t i = 0; i < f_size; i++)
		{
			for(uint8_t j = 0; j < sizeof(float); j++)
			{
				temp[i].arr[j] = *(p1_Buffer+k);
				k++;
			}
			*(p2_Buffer+i) = temp[i].f_num;
		}
	}
}

/**
 * @brief 	Reports the name of the source file and the source line number
 * 			where the assert_param error has occurred.
 * @param 	file: pointer to the source file name
 * @param 	line: assert_param error line source number
 * @return 	None
 * @note	Set UART & ugl_conf.h before using it
**/
void assert_failed_callback(uint8_t* file, uint32_t line)
{
#if defined(HAL_UART_MODULE_ENABLED) && (__User_UART_Debug == 1)
	printf("%s, %d \r\n", file, line);
#else
	__no_operation();
#endif /*HAL_UART_MODULE_ENABLED && __Usr_UART_Debug == 1*/
}



//EOF
