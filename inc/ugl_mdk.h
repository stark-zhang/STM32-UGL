/**
 * Title	UGL Module ARMCC User Header files(Compiler Modules)
 * Author	Stark Zhang
 * Date		2017-10-12
 * Debug	None
**/

#ifndef __UGL_MDK_H
#define __UGL_MDK_H

#include "ugl.h"

#ifdef __CC_ARM

inline void ASM_NVIC_Disable(void);
inline void ASM_NVIC_Enable(void);
inline void ASM_WFI_Set(void);
inline void ASM_StackTopAddr_Set(uint32_t Addr);

#endif /*__CC_ARM*/

#endif /*__UGL_MDK_H*/

//EOF