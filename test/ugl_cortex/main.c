/* main.c example for ugl_cortex */
#include "stm32xx_hal.h"

int main(void)
{
    STM32_Init();   //HAL_Init & SystemClock_Init & MX_modulexx_Init

    STIM_HandleTypeDef uSTIM[2] = {0};      //STIM array
    int32_t tim = 0;                        //RunTime

    //STIM Init
    uSTIM[0].Instance = 0x00;
	uSTIM[0].Init.Mode = STIM_ONCE_MODE;
	uSTIM[0].Init.PreLoad = 200-1;
	uSTIM[0]._state = STIM_IS_STANDBY;
	
	uSTIM[1].Instance = 0x01;
	uSTIM[1].Init.Mode = STIM_AUTO_MODE;
	uSTIM[1].Init.PreLoad = 500-1;
	uSTIM[1]._state = STIM_IS_STANDBY;
	
	UGL_STIM_Init(uSTIM, 2);
	UGL_STIM_Start(uSTIM);
    UGL_STIM_Start(uSTIM+1);
    
    while(1)
    {
        if(UGL_STIM_TimerCheck(uSTIM+1) == 1)
        {
            LED_State() = !LED_State();     //User GPIO Output(BIT & BAND)
            tim = UGL_Cortex_GetRunTime();
            printf("%ld ms \r\n", tim);
        }
    }
}