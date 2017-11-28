/**
 * Title	UGL Module SRAM User Header files(HardWare Modules)
 * Author	Stark Zhang
 * Date		2017-11-24
 * Debug	None
**/

/*It is a driver package for External SRAM with FSMC */

#ifndef __UGL_SRAM_H
#define __UGL_SRAM_H

#include "ugl.h"

#ifdef HAL_SRAM_MODULE_ENABLED

void UGL_SRAM_Read_1B(__IO uint32_t pAddress, uint8_t* pBuffer, uint32_t Size);
void UGL_SRAM_Write_1B(__IO uint32_t pAddress, uint8_t* pBuffer, uint32_t Size);

#endif /*HAL_SRAM_MODULE_ENABLED*/

#endif /*__UGL_SRAM_H*/

//EOF
