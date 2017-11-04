/**
 * Title	UGL Module Malloc User Header files(SoftWare Modules)
 * Author	Stark Zhang
 * Date		2017-10-03
 * Debug	None
**/

/* Note: This is only for STM32F407ZG with ISSI16WV51216(SRAM 1MiB)! */

#ifndef __UGL_MALLOC_H
#define __UGL_MALLOC_H

#include "ugl.h"
#include "stdbool.h"

/* For STM32F407 HAL*/
#if defined(STM32F407xx) && defined(USE_HAL_DRIVER) && (__Usr_Malloc == 1)

/**
 * Defination of NULL
**/
#ifndef NULL

#define NULL 0

#endif /*NULL*/

/**
 * definations of SRAM 
**/
#define     SRAM_Int                    0x00
#define     SRAM_Ext                    0x01
#define     SRAM_CCM                    0x02
#define     IS_SRAM_Check(SRAM_x)       (((SRAM_x) == (SRAM_CCM)) || \
                                         ((SRAM_x) == (SRAM_Int)) || \
                                         ((SRAM_x) == (SRAM_Ext)))

/**
 * SRAM BANK supprted
**/
#define     SRAM_BANK                   3

/**
 * Paramters of Every SRAM 
**/
//public definations
#define     SRAM_Block_Size             32      //32B

//for SRAM_Int
#define     SRAM_Int_MAX_SIZE           100*1024
#define     SRAM_Int_TABLE_SIZE         SRAM_Int_MAX_SIZE/SRAM_Block_Size 

//for SRAM_Ext
#define     SRAM_Ext_MAX_SIZE           960*1024
#define     SRAM_Ext_TABLE_SIZE         SRAM_Ext_MAX_SIZE/SRAM_Block_Size 

//for SRAM_CCM
#define     SRAM_CCM_MAX_SIZE           60*1024
#define     SRAM_CCM_TABLE_SIZE         SRAM_CCM_MAX_SIZE/SRAM_Block_Size 

/**
 * defination of UGL Malloc Handle
 * true is for ready and false is for unready, too
**/
typedef struct
{
    void (*init)(uint8_t);
    uint8_t (*percent)(uint8_t);
    uint8_t* MemBase[SRAM_BANK];
    uint16_t* MemMap[SRAM_BANK];
    bool MemReady[SRAM_BANK];
}UGL_Malloc_HandleTypeDef;

//Public Functions
extern void UGL_Mem_Init(uint8_t SRAM_x);
extern void UGL_Mem_Free(uint8_t SRAM_x, void* ptr);
extern void* UGL_Mem_Malloc(uint8_t SRAM_x, uint32_t length);
extern void* UGL_Mem_reMalloc(uint8_t SRAM_x, void* ptr, uint32_t length);
extern uint8_t UGL_Mem_GetPercent(uint8_t SRAM_x);

//Private Fucntions
extern void __memset(void* addr_start, uint8_t value, uint32_t length);
extern void __memcpy(void* addr_target, void* addr_origin, uint32_t length);
extern uint32_t __malloc(uint8_t SRAM_x, uint8_t length);
extern uint8_t __free(uint8_t SRAM_x, uint32_t offset);

#endif /*__UGL_MALLOC_H*/

#endif /*STM32F407xx && USE_HAL_DRIVER && __Usr_Malloc == 1*/

//EOF
