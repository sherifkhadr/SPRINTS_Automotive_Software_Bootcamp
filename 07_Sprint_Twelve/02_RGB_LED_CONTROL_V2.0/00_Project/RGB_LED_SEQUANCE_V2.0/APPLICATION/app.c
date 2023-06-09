
#include "app.h"

void systickCallback(void);


static ENU_PUSH_BTN_state_t btn;
static Uint8_t pressCounter = 0;
static VUint8_t systickFlag = 0;
static VUint8_t redStatusFlag = 0;
static VUint8_t blueStatusFlag = 0;
static VUint8_t greenStatusFlag = 0;
static VUint8_t allOnStatusFlag = 0;

void app_init(void)
{
	 LED_initialize(&a_ledCfgPins[0]);
	 LED_initialize(&a_ledCfgPins[1]);
	 LED_initialize(&a_ledCfgPins[2]);
	 PUSH_BTN_intialize(&a_pushBtnCfgPins[0]);
	 SYSTICK_init(&a_systickCfg[0]);


}
void app_superloop(void)
{
	   PUSH_BTN_read_state(&a_pushBtnCfgPins[0] , &btn);
    
		if(btn == PUSH_BTN_STATE_PRESSED)
		{
			while(btn == PUSH_BTN_STATE_PRESSED)
			{
				 PUSH_BTN_read_state(&a_pushBtnCfgPins[0] , &btn);
				 
				for(VUint8_t i=0;i<DEBOUNCING_ERROR_DETECT_1;i++)
				{
					for(VUint8_t j =0 ; j<DEBOUNCING_ERROR_DETECT_2;j++);
				}
			}
		
			 pressCounter++;
		}
		
		if(pressCounter == PRESS_ONE)
		{
			if(redStatusFlag == 0)
			{
				LED_turnOn(&a_ledCfgPins[0]);
			  LED_turnOff(&a_ledCfgPins[1]);
			  LED_turnOff(&a_ledCfgPins[2]);
			  SYSTICK_setDelayMs(1000);
				redStatusFlag++;
			}
			else
			{
				/* Do Nothing */
			}
		   if(systickFlag == SYSTICK_FLAG_FIRED)
			 {
				 	systickFlag = 0;
					LED_turnOff(&a_ledCfgPins[0]);
					LED_turnOff(&a_ledCfgPins[1]);
					LED_turnOff(&a_ledCfgPins[2]);
			 }
			 else
			 {
				 /* Do Nothing */
			 }
		}
		else if(pressCounter == PRESS_TWO)
		{
			if(blueStatusFlag == 0)
			{
			  LED_turnOff(&a_ledCfgPins[0]);
			  LED_turnOn(&a_ledCfgPins[1]);
			  LED_turnOff(&a_ledCfgPins[2]);
				SYSTICK_setDelayMs(1000);
				blueStatusFlag++;
			}
			else
			{
				 /* Do Nothing */
			}
			if(systickFlag == SYSTICK_FLAG_FIRED)
			{
				 systickFlag = 0;
				LED_turnOff(&a_ledCfgPins[0]);
			  LED_turnOff(&a_ledCfgPins[1]);
			  LED_turnOff(&a_ledCfgPins[2]);
			}
			else
			{
				 /* Do Nothing */
			}
		}
		else if(pressCounter == PRESS_THREE)
		{
			if(greenStatusFlag == 0)
			{
				LED_turnOff(&a_ledCfgPins[0]);
				LED_turnOff(&a_ledCfgPins[1]);
				LED_turnOn(&a_ledCfgPins[2]);
				SYSTICK_setDelayMs(1000);
				greenStatusFlag++;
			}
			else
			{
				/* Do Nothing */
			}
			if(systickFlag == SYSTICK_FLAG_FIRED)
			{
				 systickFlag = 0;
				 LED_turnOff(&a_ledCfgPins[0]);
				 LED_turnOff(&a_ledCfgPins[1]);
				 LED_turnOff(&a_ledCfgPins[2]);
			}
			else
			{
				 /* Do Nothing */
			}	
		}
		else if(pressCounter == PRESS_FOUR)
		{
			if(allOnStatusFlag == 0)
			{
				LED_turnOn(&a_ledCfgPins[0]);
			  LED_turnOn(&a_ledCfgPins[1]);
			  LED_turnOn(&a_ledCfgPins[2]);
				SYSTICK_setDelayMs(1000);
				allOnStatusFlag++;
			}
			else
			{
				/* Do Nothing */
			}
			
			if(systickFlag == SYSTICK_FLAG_FIRED)
			{
				systickFlag = 0;
				LED_turnOff(&a_ledCfgPins[0]);
			  LED_turnOff(&a_ledCfgPins[1]);
			  LED_turnOff(&a_ledCfgPins[2]);
			}
			else
			{
				 /* Do Nothing */
			}
		}
		else if(pressCounter == PRESS_FIVE)
		{  
			 redStatusFlag = 0;
			 greenStatusFlag = 0;
			 allOnStatusFlag = 0;
			 blueStatusFlag = 0;
			 pressCounter = 1;
			 LED_turnOff(&a_ledCfgPins[0]);
			 LED_turnOff(&a_ledCfgPins[1]);
			 LED_turnOff(&a_ledCfgPins[2]);
		}
		else
		{
			/* Do Nothing */
		}
}



void systickCallback(void)
{
	 systickFlag = SYSTICK_FLAG_FIRED;
}
