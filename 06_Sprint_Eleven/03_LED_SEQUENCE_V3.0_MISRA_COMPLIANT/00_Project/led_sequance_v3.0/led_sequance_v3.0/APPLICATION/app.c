/*
* APP.c
*
*  Created on: 6 Apr 2023
*      Author: 20101
*/


#include "APP.h"

static void INT2_ISR_HANDELER(void);
static void timer0_callback(void);
static void seq_change(void);

static EN_timer_flag_status enu_timer_state_flag = TIMER_FLAG_REST;
static EN_blank_mode_status enu_blank_states = BLANK_IN_TURN_ON;

static Uint8_t blankCounter = ONE_PRESS;
static Uint8_t seqCounter = ZERO_PRESS;
static EN_PUSH_BTN_state_t seq_counter_btn = PUSH_BTN_STATE_RELEASED;


static ST_led_t led0 =
{
	.port_name = GPIO_PORTB_INDEX,
	.pin = GPIO_PIN4,
	.led_status = LED_STATUS_OFF
};

static ST_led_t led1 =
{
	.port_name = GPIO_PORTB_INDEX,
	.pin = GPIO_PIN5,
	.led_status = LED_STATUS_OFF
};

static ST_led_t led2 =
{
	.port_name = GPIO_PORTB_INDEX,
	.pin = GPIO_PIN6,
	.led_status = LED_STATUS_OFF
};

static ST_led_t led3 =
{
	.port_name = GPIO_PORTB_INDEX,
	.pin = GPIO_PIN7,
	.led_status = LED_STATUS_OFF
};



static ST_PUSH_BTN_t btn0 =
{
	.PUSH_BTN_pin =
	{
		.port = GPIO_PORTC_INDEX,
		.pin = GPIO_PIN4,
		.direction = GPIO_DIRECTION_INPUT,
	},
	.PUSH_BTN_connection = PUSH_BTN_PULL_DOWN,
	.PUSH_BTN_state = PUSH_BTN_STATE_RELEASED
};


static ST_EXT_INTERRUPTS_CFG int2 =
{
	.EXTERNAL_INTERRUPRT_Number = EXT2_INTERRUPTS,
	.EXTERNAL_INTERRUPRT_Sense_Control = RISING_EDGE_SENSE_CONTROL,
	.INTERRUPT_EXTERNAL_HANDLER = INT2_ISR_HANDELER
};


static str_timer0_init_config_t timer0 =
{
	.enu_timer0_mode = TIMER0_NORMAL_MODE,
	.enu_timer0_oc0_output_mode = TIMER0_OC0_DISCONNECTED,
	.enu_timer0_prescaler = TIMER0_8_PRESCALER,
	.ptr_func_overflow_callback = timer0_callback,
	.ptr_func_ctc_callback = PTR_NULL
};





void appmain(void)
{

	LED_initialize(&led0);
	LED_initialize(&led1);
	LED_initialize(&led2);
	LED_initialize(&led3);
	EXT_vINTERRUPT_Init(&int2);
	EXT_INTERRUPT_SetInterruptHandler(&int2);
	PUSH_BTN_intialize(&btn0);
	TIMER0_init(&timer0);
	
	while(1)
	{
		PUSH_BTN_read_state(&btn0,&seq_counter_btn);
		if(seq_counter_btn == PUSH_BTN_STATE_PRESSED)
		{
			while(seq_counter_btn == PUSH_BTN_STATE_PRESSED)
			{
				PUSH_BTN_read_state(&btn0,&seq_counter_btn);
			}
			seq_change();
		}
		
		
		
		if(blankCounter == ONE_PRESS)
		{
			BlinkModes(100,900);
		}
		else if(blankCounter == TWO_PRESS)
		{
			BlinkModes(200,800);
			
		}
		else if(blankCounter == THREE_PRESS)
		{
			BlinkModes(300,700);
			
		}
		else if(blankCounter == FOUR_PRESS)
		{
			BlinkModes(500,500);
			
		}
		else if(blankCounter == FIVE_PRESS)
		{
			BlinkModes(800,200);
			
		}
		else
		{
			/* Do Nothing */
		}
	}
}



void BlinkModes(Uint32_t from,Uint32_t to)
{
	
	
	if(seqCounter == ONE_PRESS)
	{
		if((enu_blank_states == BLANK_IN_TURN_ON) && (enu_timer_state_flag == TIMER_FLAG_REST))
		{
			enu_blank_states = BLANK_IN_TURN_OFF;
			LED_turn_on(&led0);
			TIMER0_delay_ms(from);
			TIMER0_start(&timer0);
		}
		else if((enu_timer_state_flag == TIMER_FLAG_IS_FIRE) && (enu_blank_states == BLANK_IN_TURN_OFF))
		{
			enu_timer_state_flag = TIMER_FLAG_REST;
			enu_blank_states = BLANK_IN_RESET;
			LED_turn_off(&led0);
			TIMER0_delay_ms(to);
			TIMER0_start(&timer0);
		}
		else if((enu_timer_state_flag == TIMER_FLAG_IS_FIRE) && (enu_blank_states == BLANK_IN_RESET))
		{
			enu_timer_state_flag = TIMER_FLAG_REST;
			enu_blank_states = BLANK_IN_TURN_ON;
		}
	}
	else if(seqCounter == TWO_PRESS)
	{
		if((enu_blank_states == BLANK_IN_TURN_ON) && (enu_timer_state_flag == TIMER_FLAG_REST))
		{
			enu_blank_states = BLANK_IN_TURN_OFF;
			LED_turn_on(&led0);
			LED_turn_on(&led1);
			TIMER0_start(&timer0);
			TIMER0_delay_ms(from);
		}
		else if((enu_timer_state_flag == TIMER_FLAG_IS_FIRE) && (enu_blank_states == BLANK_IN_TURN_OFF))
		{
			enu_timer_state_flag = TIMER_FLAG_REST;
			enu_blank_states = BLANK_IN_RESET;
			LED_turn_off(&led0);
			LED_turn_off(&led1);
			TIMER0_start(&timer0);
			TIMER0_delay_ms(to);
		}
		else if((enu_timer_state_flag == TIMER_FLAG_IS_FIRE) && (enu_blank_states == BLANK_IN_RESET))
		{
			enu_timer_state_flag = TIMER_FLAG_REST;
			enu_blank_states = BLANK_IN_TURN_ON;
		}
	}
	else if(seqCounter == THREE_PRESS)
	{
		if((enu_blank_states == BLANK_IN_TURN_ON) && (enu_timer_state_flag == TIMER_FLAG_REST))
		{
			enu_blank_states = BLANK_IN_TURN_OFF;
			LED_turn_on(&led0);
			LED_turn_on(&led1);
			LED_turn_on(&led2);
			TIMER0_start(&timer0);
			TIMER0_delay_ms(from);
		}
		else if((enu_timer_state_flag == TIMER_FLAG_IS_FIRE) && (enu_blank_states == BLANK_IN_TURN_OFF))
		{
			enu_timer_state_flag = TIMER_FLAG_REST;
			enu_blank_states = BLANK_IN_RESET;
			LED_turn_off(&led0);
			LED_turn_off(&led1);
			LED_turn_off(&led2);
			TIMER0_start(&timer0);
			TIMER0_delay_ms(to);
		}
		else if((enu_timer_state_flag == TIMER_FLAG_IS_FIRE) && (enu_blank_states == BLANK_IN_RESET))
		{
			enu_timer_state_flag = TIMER_FLAG_REST;
			enu_blank_states = BLANK_IN_TURN_ON;
		}
	}
	else if(seqCounter == FOUR_PRESS)
	{
		if((enu_blank_states == BLANK_IN_TURN_ON) && (enu_timer_state_flag == TIMER_FLAG_REST))
		{
			enu_blank_states = BLANK_IN_TURN_OFF;
			LED_turn_on(&led0);
			LED_turn_on(&led1);
			LED_turn_on(&led2);
			LED_turn_on(&led3);
			TIMER0_start(&timer0);
			TIMER0_delay_ms(from);
		}
		else if((enu_timer_state_flag == TIMER_FLAG_IS_FIRE) && (enu_blank_states == BLANK_IN_TURN_OFF))
		{
			enu_timer_state_flag = TIMER_FLAG_REST;
			enu_blank_states = BLANK_IN_RESET;
			LED_turn_off(&led0);
			LED_turn_off(&led1);
			LED_turn_off(&led2);
			LED_turn_off(&led3);
			TIMER0_start(&timer0);
			TIMER0_delay_ms(to);
		}
		else if((enu_timer_state_flag == TIMER_FLAG_IS_FIRE) && (enu_blank_states == BLANK_IN_RESET))
		{
			enu_timer_state_flag = TIMER_FLAG_REST;
			enu_blank_states = BLANK_IN_TURN_ON;
		}
	}
	else if(seqCounter == FIVE_PRESS)
	{
		if((enu_blank_states == BLANK_IN_TURN_ON) && (enu_timer_state_flag == TIMER_FLAG_REST))
		{
			enu_blank_states = BLANK_IN_TURN_OFF;
			LED_turn_off(&led0);
			LED_turn_on(&led1);
			LED_turn_on(&led2);
			LED_turn_on(&led3);
			TIMER0_start(&timer0);
			TIMER0_delay_ms(from);
		}
		else if((enu_timer_state_flag == TIMER_FLAG_IS_FIRE) && (enu_blank_states == BLANK_IN_TURN_OFF))
		{
			enu_timer_state_flag = TIMER_FLAG_REST;
			enu_blank_states = BLANK_IN_RESET;
			LED_turn_off(&led1);
			LED_turn_off(&led2);
			LED_turn_off(&led3);
			TIMER0_start(&timer0);
			TIMER0_delay_ms(to);
		}
		else if((enu_timer_state_flag == TIMER_FLAG_IS_FIRE) && (enu_blank_states == BLANK_IN_RESET))
		{
			enu_timer_state_flag = TIMER_FLAG_REST;
			enu_blank_states = BLANK_IN_TURN_ON;
		}
	}
	else if(seqCounter == SIX_PRESS)
	{
		if((enu_blank_states == BLANK_IN_TURN_ON) && (enu_timer_state_flag == TIMER_FLAG_REST))
		{
			enu_blank_states = BLANK_IN_TURN_OFF;
			LED_turn_on(&led2);
			LED_turn_on(&led3);
			TIMER0_start(&timer0);
			TIMER0_delay_ms(from);
		}
		else if((enu_timer_state_flag == TIMER_FLAG_IS_FIRE) && (enu_blank_states == BLANK_IN_TURN_OFF))
		{
			enu_timer_state_flag = TIMER_FLAG_REST;
			enu_blank_states = BLANK_IN_RESET;
			LED_turn_off(&led2);
			LED_turn_off(&led3);
			TIMER0_start(&timer0);
			TIMER0_delay_ms(to);
		}
		else if((enu_timer_state_flag == TIMER_FLAG_IS_FIRE) && (enu_blank_states == BLANK_IN_RESET))
		{
			enu_timer_state_flag = TIMER_FLAG_REST;
			enu_blank_states = BLANK_IN_TURN_ON;
		}
	}
	else if(seqCounter == SEVEN_PRESS)
	{
		if((enu_blank_states == BLANK_IN_TURN_ON) && (enu_timer_state_flag == TIMER_FLAG_REST))
		{
			enu_blank_states = BLANK_IN_TURN_OFF;
			LED_turn_on(&led3);
			TIMER0_start(&timer0);
			TIMER0_delay_ms(from);
		}
		else if((enu_timer_state_flag == TIMER_FLAG_IS_FIRE) && (enu_blank_states == BLANK_IN_TURN_OFF))
		{
			enu_timer_state_flag = TIMER_FLAG_REST;
			enu_blank_states = BLANK_IN_RESET;
			LED_turn_off(&led3);
			TIMER0_start(&timer0);
			TIMER0_delay_ms(to);
		}
		else if((enu_timer_state_flag == TIMER_FLAG_IS_FIRE) && (enu_blank_states == BLANK_IN_RESET))
		{
			enu_timer_state_flag = TIMER_FLAG_REST;
			enu_blank_states = BLANK_IN_TURN_ON;
		}

	}
	else if(seqCounter == EIGHT_PRESS)
	{
		LED_turn_off(&led0);
		LED_turn_off(&led1);
		LED_turn_off(&led2);
		LED_turn_off(&led3);
	}
	else
	{
		/* Do Nothing */
	}
	
}


static void INT2_ISR_HANDELER(void)
{
	blankCounter++;
	if(blankCounter == 6)
	blankCounter = 1;
}

static void timer0_callback(void)
{
	enu_timer_state_flag = TIMER_FLAG_IS_FIRE;
}


static void seq_change(void)
{
	seqCounter++;
	if(seqCounter == 9)
	seqCounter = 0;
}
