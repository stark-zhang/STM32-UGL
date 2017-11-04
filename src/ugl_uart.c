/**
 * Title	UGL Module UART User Source files(HardWare Modules)
 * Author	Stark Zhang
 * Date		2017-10-01
 * Debug	None
**/

#include "../inc/ugl_uart.h"

#ifdef HAL_UART_MODULE_ENABLED

//General Functions with UART

/* Retarget C Library */
#if (__Usr_UART_Debug == 1)

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printfset to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /*__GNUC__*/

/**
 * @brief   Retargets the C library printf function to the USART.
 * @param   Not Care
 * @return  None
 * @note    Only for USART1(in Asynchronous mode)
**/
PUTCHAR_PROTOTYPE
{
	while((USART1->SR & 0X40) == 0)
		;
	USART1->DR = (uint8_t)ch;
	return ch;
}

#endif /*__Usr_UART_Debug == 1*/

#endif /*HAL_UART_MODULE_ENABLED*/

//EOF
