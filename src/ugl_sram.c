/**
 * Title	UGL Module SRAM User Source files(HardWare Modules)
 * Author	Stark Zhang
 * Date		2017-11-24
 * Debug	None
**/

#include "../inc/ugl_sram.h"

#ifdef HAL_SRAM_MODULE_ENABLED

/**
 * @brief	Read Data from ExtSRAM per 1 Byte
 * @param	uint32_t pAddress
				SRAM Address
 * @param 	uint8_t* pBuffer
				Buffer to receive Data
 * @param	uint32_t Size
				Buffer Size
 * @return	None
 * @note	Size <= 2^32
**/
void UGL_SRAM_Read_1B(__IO uint32_t pAddress, uint8_t* pBuffer, uint32_t Size)
{
	for( ; Size != 0; Size--)
	{
		*pBuffer = *(__IO uint8_t*)pAddress;
		pBuffer++;
		pAddress++;
	}
}

/**
 * @brief	Write Data to ExtSRAM per 1 Byte
 * @param	uint32_t pAddress
				SRAM Address
 * @param 	uint8_t* pBuffer
				Data will be wroten
 * @param	uint32_t Size
				Buffer Size
 * @return	None
 * @note	Size <= 2^32
**/
void UGL_SRAM_Write_1B(__IO uint32_t pAddress, uint8_t* pBuffer, uint32_t Size)
{
	for( ; Size != 0; Size--)
	{
		*(__IO uint8_t*)pAddress = *pBuffer;
		pBuffer++;
		pAddress++;
	}
}

#endif /*HAL_SRAM_MODULE_ENABLED*/

//EOF
