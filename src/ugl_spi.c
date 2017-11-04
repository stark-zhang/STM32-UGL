/**
 * Title	UGL Module SPI User Source files(HardWare Modules)
 * Author	Stark Zhang
 * Date		2017-09-30
 * Debug	None
**/

#include "../inc/ugl_spi.h"

#ifdef HAL_SPI_MODULE_ENABLED

/**
 * @brief	Set SPI Baud Rate
 * @param	SPI_HandleTypeDef hspi
				SPI Handler
 * @param 	uint32_t SPI_BAUDRATE_PSC
				Baud Rate values(only for definations in "stm32f4xx_hal_spi.h")
 * @return	None
 * @note	Not Adapt to I2S
**/
void UGL_SPI_SetBaudRate(SPI_HandleTypeDef hspi, uint32_t SPI_BAUDRATE_PSC)
{
	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BAUDRATE_PSC));
	hspi.Instance->CR1 &= 0xFFC7;
	hspi.Instance->CR1 |= (uint16_t)SPI_BAUDRATE_PSC;
}

/**
 * @brief	Get Status of SPI from SPIx_SR & SPIx_DR for Testing
 * @param	SPI_HandleTypeDef hspi
				SPI Handler
 * @return	UGL_SPI_StatusTypeDef*
				SPI status structure
 * @note	Not Adapt to I2S
**/
UGL_SPI_StatusTypeDef *UGL_SPI_GetSR(SPI_HandleTypeDef hspi)
{
	UGL_SPI_StatusTypeDef *p = {0};
	p->TIFRFE = hspi.Instance->SR & 0x0100 >> 8;
	p->BSY = hspi.Instance->SR & 0x0080 >> 7;
	p->OVR = hspi.Instance->SR & 0x0040 >> 6;
	p->MODF = hspi.Instance->SR & 0x0020 >> 5;
	p->CRCERR = hspi.Instance->SR & 0x0010 >> 4;
	p->UDR = hspi.Instance->SR & 0x0008 >> 3;
	p->CHSIDE = hspi.Instance->SR & 0x0004 >> 2;
	p->TXE = hspi.Instance->SR & 0x0002 >> 1;
	p->RXNE = hspi.Instance->SR & 0x0001 >> 0;
	p->DR = hspi.Instance->DR;
	p->ErrCode = hspi.ErrorCode;
	return p;
}

/**
 * @brief	Write a byte to SPI slave device & Read a Byte(Polling)
 * @param	SPI_HandleTypeDef *hspi
				SPI Handler
 * @param	uint8_t Buffer_TX
				Data Transmitted
 * @return	uint8_t
				Data Received
 * @note	None
**/
uint8_t UGL_SPI_ReadWrite(SPI_HandleTypeDef hspi, uint8_t Buffer_TX)
{
	uint8_t Buffer_RX = 0;
	if (HAL_SPI_TransmitReceive(&hspi, &Buffer_TX, &Buffer_RX, 1, HAL_MAX_DELAY) != HAL_OK)
	{
		Buffer_RX = Dummy_Byte;
	}

	return Buffer_RX;
}

/**
 * @brief	Read a byte to SPI slave device(Polling)
 * @param	SPI_HandleTypeDef *hspi
				SPI Handler
 * @return	uint8_t
				Data Received
 * @return	uint8_t
				Data Received
 * @note	None
**/
uint8_t UGL_SPI_OnlyRead(SPI_HandleTypeDef hspi)
{
	uint8_t Buffer_RX = 0;
	if (HAL_SPI_Receive(&hspi, &Buffer_RX, 1, HAL_MAX_DELAY) != HAL_OK)
	{
		Buffer_RX = Dummy_Byte;
	}

	return Buffer_RX;
}

/**
 * @brief	Write a byte to SPI slave device(Polling)
 * @param	SPI_HandleTypeDef hspi
				SPI Handler
 * @param	uint8_t Buffer_TX
				Data Transmitted
 * @return	None
 * @note	None
**/
void UGL_SPI_OnlyWrite(SPI_HandleTypeDef hspi, uint8_t Buffer_TX)
{
	HAL_SPI_Transmit(&hspi, &Buffer_TX, 1, HAL_MAX_DELAY);
}


#endif /*HAL_SPI_MODULE_ENABLED*/

//EOF
