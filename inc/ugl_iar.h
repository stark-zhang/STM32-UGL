/**
 * Title	UGL Module IARCC User Header files(Compiler Modules)
 * Author	Stark Zhang
 * Date		2017-09-30
 * Debug	None
**/

#ifndef __UGL_IARCC_H
#define __UGL_IARCC_H

#include "ugl.h"

#ifdef __ICCARM__

inline void ASM_NVIC_Disable(void);
inline void ASM_NVIC_Enable(void);
inline void ASM_WFI_Set(void);
inline void ASM_StackTopAddr_Set(uint32_t Addr);

#endif /*__ICCARM__*/

#endif /*__UGL_IARCC_H*/

//EOF