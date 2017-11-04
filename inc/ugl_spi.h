/**
 * Title	UGL Module SPI User Header files(HardWare Modules)
 * Author	Stark Zhang
 * Date		2017-09-30
 * Debug	None
**/

#ifndef __UGL_SPI_H
#define __UGL_SPI_H

#include "ugl.h"

//UGL SPI Status Structure
typedef struct
{
	//TI Frame Fommat Error -- SR
	uint8_t TIFRFE;
	//Busy Flag -- SR
	uint8_t BSY;
	//Overrun Flag -- SR
	uint8_t OVR;
	//Mode Fault -- SR
	uint8_t MODF;
	//CRC Error Flag -- SR
	uint8_t CRCERR;
	//Underrun Flag -- SR
	uint8_t UDR;
	//Channel Side -- SR
	uint8_t CHSIDE;
	//Transmit Buffer Empty -- SR
	uint8_t TXE;
	//Receive Buffer Not Empty -- SR
	uint8_t RXNE;
	//Data Register -- DR
	uint16_t DR;
	//Error Code in HAL SPI
	__IO uint32_t ErrCode;
} UGL_SPI_StatusTypeDef;

#ifdef HAL_SPI_MODULE_ENABLED

//General Function for SPI
extern inline void UGL_SPI_SetBaudRate(SPI_HandleTypeDef hspi, uint32_t SPI_BAUDRATE_PSC);
extern UGL_SPI_StatusTypeDef* UGL_SPI_GetSR(SPI_HandleTypeDef hspi);

//Working in Polling
extern uint8_t UGL_SPI_ReadWrite(SPI_HandleTypeDef hspi, uint8_t Buffer_TX);
extern uint8_t UGL_SPI_OnlyRead(SPI_HandleTypeDef hspi);
extern void UGL_SPI_OnlyWrite(SPI_HandleTypeDef hspi, uint8_t Buffer_TX);

//Working in IT
extern uint8_t UGL_SPI_ReadWrite_IT(SPI_HandleTypeDef hspi, uint8_t Buffer_TX);
extern uint8_t UGL_SPI_OnlyRead_IT(SPI_HandleTypeDef hspi);
extern void UGL_SPI_OnlyWrite_IT(SPI_HandleTypeDef hspi, uint8_t Buffer_TX);

//Working in DMA
extern uint8_t UGL_SPI_ReadWrite_DMA(SPI_HandleTypeDef hspi, uint8_t Buffer_TX);
extern uint8_t UGL_SPI_OnlyRead_DMA(SPI_HandleTypeDef hspi);
extern void UGL_SPI_OnlyWrite_DMA(SPI_HandleTypeDef hspi, uint8_t Buffer_TX);

#endif /*HAL_SPI_MODULE_ENABLED*/

#endif /*__UGL_SPI_H*/

//EOF
