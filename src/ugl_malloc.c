/**
 * Title	UGL Module Malloc User Source files(SoftWare Modules)
 * Author	Stark Zhang
 * Date		2017-10-03
 * Debug	None
**/

#include "ugl_malloc.h"

/* For STM32F407 HAL*/
#if defined(STM32F407xx) && defined(USE_HAL_DRIVER) && (__Usr_Malloc == 1)

/**
 * definations of SRAM Pool, SRAM Control Table & SRAM Control Parameters
 * In ARM_MDK & IAR for ARM
**/
#if defined(__ICCARM__)

//SRAM Pools (32 bytes aligned)
__ALIGNED(32) uint8_t SRAM_Int_BASE[SRAM_Int_MAX_SIZE];						//for Internal SRAM
__ALIGNED(32) uint8_t SRAM_Ext_BASE[SRAM_Ext_MAX_SIZE] @(0x68000000);		//for External SRAM
__ALIGNED(32) uint8_t SRAM_CCM_BASE[SRAM_CCM_MAX_SIZE] @(0x10000000);		//for SRAM CCM
//SRAM Control Tables
__no_init uint16_t SRAM_Int_MapBASE[SRAM_Int_TABLE_SIZE];
__no_init uint16_t SRAM_Ext_MapBASE[SRAM_Ext_TABLE_SIZE] @(0x68000000 + SRAM_Ext_MAX_SIZE);
__no_init uint16_t SRAM_CCM_MapBASE[SRAM_CCM_TABLE_SIZE] @(0X10000000 + SRAM_CCM_MAX_SIZE);
//SRAM Control Parameters
const uint32_t SRAM_TableSize[SRAM_BANK] = {SRAM_Int_TABLE_SIZE, SRAM_Ext_TABLE_SIZE, SRAM_CCM_TABLE_SIZE};
const uint32_t SRAM_MemSize[SRAM_BANK] = {SRAM_Int_MAX_SIZE, SRAM_Ext_MAX_SIZE, SRAM_CCM_MAX_SIZE};
const uint32_t SRAM_BlockSize = SRAM_Block_Size;

#elif defined(__CC_ARM)

//SRAM Pools (32 bytes aligned)
__align(32) uint8_t SRAM_Int_BASE[SRAM_Int_MAX_SIZE];
__align(32) uint8_t SRAM_Ext_BASE[SRAM_Ext_MAX_SIZE] __attribute__((at(0X68000000)));
__align(32) uint8_t SRAM_CCM_BASE[SRAM_CCM_MAX_SIZE] __attribute__((at(0X10000000)));
//SRAM Control Tables
uint16_t SRAM_Int_MapBASE[SRAM_Int_TABLE_SIZE];
uint16_t SRAM_Ext_MapBASE[SRAM_Ext_TABLE_SIZE] __attribute__((at(0X68000000 + SRAM_Ext_MAX_SIZE)));
uint16_t SRAM_CCM_MapBASE[SRAM_CCM_TABLE_SIZE] __attribute__((at(0X10000000 + SRAM_CCM_MAX_SIZE)));
//SRAM Control Parameters
const uint32_t SRAM_TableSize[SRAM_BANK] = {SRAM_Int_TABLE_SIZE, SRAM_Ext_TABLE_SIZE, SRAM_CCM_TABLE_SIZE};
const uint32_t SRAM_MemSize[SRAM_BANK] = {SRAM_Int_MAX_SIZE, SRAM_Ext_MAX_SIZE, SRAM_CCM_MAX_SIZE};
const uint32_t SRAM_BlockSize = SRAM_Block_Size;

#endif /*Macros of Compiler*/

/**
 * UGL Memory Control UGL_Malloc_Handle
**/
static UGL_Malloc_HandleTypeDef UGL_Mem_Handle = 
{
	UGL_Mem_Init,
	UGL_Mem_GetPercent,
	SRAM_Int_BASE, SRAM_Ext_BASE, SRAM_CCM_BASE,
	SRAM_Int_MapBASE, SRAM_Ext_MapBASE, SRAM_CCM_MapBASE,
	true, true, true,
};
	
//Public Functions
/**
 * @brief
 * @param
 * @return
 * @note
**/
void UGL_Mem_Init(uint8_t SRAM_x)
{
	assert_param(IS_SRAM_Check(SRAM_x));
	
	__memset(UGL_Mem_Handle.MemMap[SRAM_x], 0, SRAM_TableSize[SRAM_x] * 2);
	__memset(UGL_Mem_Handle.MemMap[SRAM_x], 0, SRAM_MemSize[SRAM_x]);
	UGL_Mem_Handle.MemReady[SRAM_x] = true;
}

/**
 * @brief	Free Memory
 * @param	uint8_t SRAM_x
				SRAM Area
 * @param 	void* ptr
				pointer will be freed
 * @return	None
 * @note	None
**/
void UGL_Mem_Free(uint8_t SRAM_x, void* ptr)
{
	assert_param(IS_SRAM_Check(SRAM_x));
	
	uint32_t offset = 0;
	if(ptr == NULL)
		return;
	
	offset = (uint32_t)ptr - (uint32_t)UGL_Mem_Handle.MemBase[SRAM_x];
	__free(SRAM_x, offset);
}

/**
 * @brief	Memory Allocation
 * @param	uint8_t SRAM_x
				SRAM Area
 * @param	uint32_t length
				The number of memory bytes to allocate
 * @return	void*
				pointer has been allocated
 * @note	None
**/
void* UGL_Mem_Malloc(uint8_t SRAM_x, uint32_t length)
{
	assert_param(IS_SRAM_Check(SRAM_x));
	
	uint32_t offset = __malloc(SRAM_x, length);
	if(offset == 0xFFFFFFFF)
		return NULL;
	else
		return (void*)((uint32_t)UGL_Mem_Handle.MemBase[SRAM_x] + offset);
}

/**
 * @brief	Memory Re-allocate
 * @param	uint8_t SRAM_x
				SRAM Area
 * @param	uint32_t length
				The number of memory bytes to allocate
 * @return	void*
				pointer has been allocated
 * @note	None
**/
void* UGL_Mem_reMalloc(uint8_t SRAM_x, void* ptr, uint32_t length)
{
	uint32_t offset = __malloc(SRAM_x, length);
	if(offset == 0xFFFFFFFF)
		return NULL;
	else
	{
		__memcpy((void*)((uint32_t)UGL_Mem_Handle.MemBase[SRAM_x] + offset), ptr, length);
		UGL_Mem_Free(SRAM_x, ptr);
		return (void*)((uint32_t)UGL_Mem_Handle.MemBase[SRAM_x] + offset);
	}
}

/**
 * @brief	Get SRAM used percents
 * @param	uint8_t SRAM_x
				SRAM Area
 * @return	uint8_t
				percent used, 0-100
 * @note	None
**/
uint8_t UGL_Mem_GetPercent(uint8_t SRAM_x)
{
	uint32_t used = 0;
	for(int i = 0; i < SRAM_TableSize[SRAM_x]; i++)
	{
		if(UGL_Mem_Handle.MemMap[SRAM_x][i])
		   used++;
	}
	return (used * 100)/SRAM_TableSize[SRAM_x];
}

//Private Functions
/**
 * @brief	Set Value in special Memory Address
 * @param	void* addr_start
				Start of Memory Address
 * @param  	uint8_t value
				value will be set
 * @param	uint32_t length
				The number of memory bytes to set
 * @return	None
 * @note	None
**/
void __memset(void* addr_start, uint8_t value, uint32_t length)
{
	uint8_t* addr = addr_start;
	while(length--)
	{
		*addr++ = value;
	}
}

/**
 * @brief	Copy content to target Address of Memory from origin Address
 * @param	void* addr_target
				Target Address
 * @param	void* addr_origin
				Origin Address
 * @param	uint32_t length
				The number of memory bytes to set
 * @return	None
 * @note	None
**/
void __memcpy(void* addr_target, void* addr_origin, uint32_t length)
{
	uint8_t* _target = addr_target;
	uint8_t* _origin = addr_origin;
	while(length)
	{
		*_target++ = *_origin++;
	}
}

/**
 * @brief	Low Layer Memory Allocation function
 * @param	uint8_t SRAM_x
				SRAM area
 * @param	uint8_t length
				The number of memory bytes to allocate
 * @return	uint32_t
				0xFFFFFFFF is Error, other value is memory offset address
 * @note	None
**/
uint32_t __malloc(uint8_t SRAM_x, uint8_t length)
{
	int32_t offset = 0;			//address offset
	uint32_t mem_need;			//memory length needed
	uint32_t mem_count = 0;		//count of continuous memory blocks 
	
	//init
	if(!UGL_Mem_Handle.MemReady[SRAM_x])
	{
		UGL_Mem_Handle.init(SRAM_x);
	}
	
	//no allocation
	if(length == 0)
		return 0xFFFFFFFF;
	
	//calculate how many blocks needed
	mem_need = length / SRAM_BlockSize;
	if(length % SRAM_BlockSize)
		mem_need++;
	
	//search in whole memory control area
	for(offset = SRAM_TableSize[SRAM_x] - 1; offset >= 0; offset--)
	{
		if(!UGL_Mem_Handle.MemMap[SRAM_x][offset])
		   mem_count++;
		else mem_count = 0;
		
		//found continuous memory blocks
		if(mem_count == mem_need)
		{
			//marked as non-empty
			for(int i = 0; i < mem_need; i++)
			{
				UGL_Mem_Handle.MemMap[SRAM_x][offset+i] = mem_need;
			}
			return (offset * SRAM_BlockSize);		//return offset address
		}
	}
		   return 0xFFFFFFFF;						//cannot find Memory Block
}

/**
 * @brief	Low Layer Memory Free funcrion
 * @param	uint8_t SRAM_x
				SRAM area
 * @param	uint32_t offset
				address offset
 * @return	uint8_t
				status, 0 is succesful, 1 is failure, 2 is offset was beyond the memory
 * @note	None
**/
uint8_t __free(uint8_t SRAM_x, uint32_t offset)
{
	//init
	if(!UGL_Mem_Handle.MemReady[SRAM_x])
	{
		UGL_Mem_Handle.init(SRAM_x);
		return 1;
	}
	
	if(offset < SRAM_MemSize[SRAM_x])
	{
		uint8_t index = offset / SRAM_BlockSize;
		uint8_t mem_count = UGL_Mem_Handle.MemMap[SRAM_x][index];
		for(int i = 0; i < mem_count; i++)
		{
			UGL_Mem_Handle.MemMap[SRAM_x][index+i] = 0;
		}
		return 0;
	}
	else return 2;
}

#endif /*STM32F407xx && USE_HAL_DRIVER && __Usr_Malloc == 1*/

//EOF
