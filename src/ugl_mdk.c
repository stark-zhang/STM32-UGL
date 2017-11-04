/**
 * Title	UGL Module ARMCC User Header files(Compiler Modules)
 * Author	Stark Zhang
 * Date		2017-09-30
 * Debug	None
**/

#include "../inc/ugl_mdk.h"

/**
 * @brief	Disable all of interrupts except Fault & NMI
 * @param	None
 * @return	None
 * @note	None
**/
void ASM_NVIC_Disable(void)
{
	#asm{
        CPSID   I
        BX      LR
    }
}

/**
 * @brief	Enable all of interrupts
 * @param	None
 * @return	None
 * @note	None
**/
void ASM_NVIC_Enable(void)
{
	#asm{
        CPSIE   I
        BX      LR
    }
}

/**	
 * @brief	Set WFI
 * @param	None
 * @return	None
 * @note	None
**/
void ASM_WFI_Set(void)
{
	#asm{
        WFI
    }
}

/**
 * @brief	Set Stack Top Address by ASM
 * @param	uint32_t Addr
				User-defined Address of Stack Top
 * @return	None
 * @note	None
**/
void ASM_StackTopAddr_Set(uint32_t Addr)
{
	#asm{
        MSR MSP,    r0
        BX          r14
    }
}

//EOF
