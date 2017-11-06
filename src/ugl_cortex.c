/**
 * Title	UGL Module Cortex_Mx User Source files(HardWare Core Modules)
 * Author	Stark Zhang
 * Date		2017-11-05
 * Debug	None
**/

#include "ugl_cortex.h"

/* STIM */
#if (__User_STIM == 1)

//Public Variables for STIM

//Private Variables for STIM
static uint8_t stim_max_count = STIM_MAX_Count;
static STIM_HandleTypeDef _stim[STIM_MAX_Count];

//Public Functions
/**
 * @brief	STIM Initialization
 * @param	STIM_HandleTypeDef *stim
				STIM Handle	pointer
 * @param 	uint8_t _count
				Quantity of STIMs
 * @return
 * @note	STIM_Handle->Instance >= 0
**/
void UGL_STIM_Init(STIM_HandleTypeDef *stim, uint8_t _count)
{
	if(_count > STIM_MAX_Count)
	{
		assert_failed_callback(__FILE__, __LINE__);
		return ;
	}
	else
	{
		IRQn_Disable();
		
		if(_count > STIM_MAX_Count)
		{
			assert_failed_callback(__FILE__, __LINE__);
			return ;
		}
		else
			stim_max_count = _count;
		
		for(uint8_t i = 0; i < stim_max_count; i++)
		{
			(_stim+i)->_state = STIM_IS_STANDBY;
		}
		
		IRQn_Enable();
	}
}

/**
 * @brief	STIM Start
 * @param	STIM_HandleTypeDef *stim
				STIM Handle	pointer	
 * @return	None
 * @note	None
**/
void UGL_STIM_Start(STIM_HandleTypeDef *stim)
{
	static uint8_t i = 0;
	
	IRQn_Disable();
	
	for( ; i < stim_max_count; i++)
	{
		if(stim->Instance == (_stim+i)->Instance)
			break;
	}
	
	(_stim+i)->_state = STIM_IS_WORKING;
	
	IRQn_Enable();
}

/**
 * @brief	STIM Stop
 * @param	STIM_HandleTypeDef *stim
				STIM Handle	pointer	
 * @return	None
 * @note	None
**/
void UGL_STIM_CheckTimer(STIM_HandleTypeDef *stim)
{
	static uint8_t i = 0;
	
	IRQn_Disable();
	
	for( ; i < stim_max_count; i++)
	{
		if(stim->Instance == (_stim+i)->Instance)
			break;
	}
	
	(_stim+i)->_state = STIM_IS_STOPED;
	(_stim+i)->Flag = 0;
	
	(_stim+i)->Init->Mode = STIM_ONCE_MODE;
	(_stim+i)->Init->Count = 0;
	(_stim+i)->Init->PreLoad = 0;
	
	IRQn_Enable();
}

/**
 * @brief	Check STIM is Overflow or not
 * @param	STIM_HandleTypeDef *stim
				STIM Handle	pointer
 * @return	uint8_t
	 			1 -> overflow
				0 -> not overflow
 * @note	None
**/
uint8_t UGL_STIM_TimerCheck(STIM_HandleTypeDef *stim)
{
	static uint8_t i = 0;
	
	for( ; i < stim_max_count; i++)
	{
		if(stim->Instance == (_stim+i)->Instance)
			break;
	}
	
	if((_stim+1)->Flag == 1)
	{
		(_stim+1)->Flag = 0;
		return 1;
	}
	else return 0;
}

//Private Functions

/**
 * @brief	STIM Count Down Operation(per 1ms)
 * @param	STIM_HandleTypeDef *stim
				STIM Handle pointer
 * @return	None
 * @note	This Function need to be called in the Systick Interrupt Callback
**/
static void UGL_STIM_Dec(STIM_HandleTypeDef *stim)
{
	if(stim->Init->PreLoad > 0)
	{
		if(--stim->Init->PreLoad == 0)
		{
			stim->Flag = 1;
			
			//Automatically reload
			if(stim->Init->Mode == STIM_AUTO_MODE)
			{
				stim->Init->Count = stim->Init->PreLoad;
			}
		}
	}
}

#endif /*__User_STIM == 1*/

/* uptime */
#if (__User_uptime == 1)

//private variables for uptime check
static int32_t __time = 0;

/**
 * @brief	Get System Run time
 * @param	None
 * @return 	int32_t
				Run Time(in ms)(max 24.855 days)
 * @note	max_Tims <= 0x7FFFFFFF ms, there maybe overflow!
**/
int32_t UGL_Cortex_GetRunTime(void)
{
	int32_t runtime = 0;
	
	IRQn_Disable();
	
	runtime = __time;
	
	IRQn_Enable();
	
	return runtime;
}

/**
 * @brief	Get difference between this time and order time
 * @param	int32_t _LastTime
				present time
 * @return	int32_t
				time difference
 * @note	None
**/
int32_t UGL_Cortex_CheckRunTime(int32_t _LastTime)
{
	int32_t now_time;
	int32_t time_diff;

	IRQn_Disable(); 	

	now_time = __time;	

	IRQn_Enable();
	
	if (now_time >= _LastTime)
	{
		time_diff = now_time - _LastTime;
	}
	else
	{
		time_diff = 0x7FFFFFFF - _LastTime + now_time;
	}

	return time_diff;
}

#endif /*__User_STIM == 1*/

/* User-defined Functions*/

/**
 * @brief	User Operations every 1ms
 * @param	None
 * @return	None
 * @note	User should re-define this function not modify this
**/
__weak void UGL_Cortex_IDLE(void)
{
	/*Note:																	*/
	/*		User should better re-define this function in own source files! */
	__no_operation();
}

/**
 * @brief	Systick interrupt callback in HAL
 * @param	None
 * @return	None
 * @note	None
**/
void HAL_SYSTICK_Callback(void)
{
	//for STIM Run Time Check
#if (__User_STIM == 1)
	
	for(uint8_t i = 0; i < stim_max_count; i++)
	{
		if((_stim+i)->_state == STIM_IS_WORKING)
			UGL_STIM_Dec(_stim+i);
		else continue;
	}
	
#endif /*__User_STIM == 1*/
	
	//for Run Time Check
#if (__User_uptime == 1)

	__time++;
	if(__time == 0x7FFFFFFF)
		__time = 0;
	
#endif /*__User_STIM == 1*/
	
	UGL_Cortex_IDLE();
	
	//User Callback code BEGIN
	
	//User Callback code END
}

//EOF
