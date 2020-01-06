/*
 * timer1.c
 *
 *  Created on: Jan 5, 2020
 *      Author: mohamed salah
 */

#include "timer1.h"
/*
 * global variable to store the call back function address
 * */
static volatile void (*g_func) (void) = NULL;

/*
 * Description :function to set timer1 registers to the specified
 * 		the function must be given an address to a structure of type timer_config
 * */
void TIMER1_init(const timer_config * a_timer1_configuration){
		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1  = 0;
		/*
		 * clear bit 1,0 in TCCR1A and insert the bit 1,0 in masked timer1_mode
		 * clear bit 4,3 in TCCR1B and insert the bit 3,2 in masked timer1_mode after shifting left by 1
		 * set timer 1 mode of operation overflow or compare
		 * */
		TCCR1A = (TCCR1A & 0xFC) | (a_timer1_configuration -> timer1_mode & 0x03);
		TCCR1B = (TCCR1B & 0xE7) | ((a_timer1_configuration -> timer1_mode & 0x0C)<<1);
		/*
		 * set the prescaler
		 * */
		TCCR1B = (TCCR1B & 0xF8) | (a_timer1_configuration -> timer1_prescaler & 0x07);
		/*
		 * enable timer 1 interrupt
		 * */
		if(a_timer1_configuration -> timer1_mode == OVF){
			TIMSK &= 0xC3 ; /*clear the TICIE1	OCIE1A	OCIE1B	TOIE1 bits*/
			SET_BIT(TIMSK , TOIE1); /*interrupt when TCNT1 == 0xFFFF */
		}
		else if (a_timer1_configuration -> timer1_mode == COMP_A){
			TIMSK &= 0xC3 ; /* clear the TICIE1	OCIE1A	OCIE1B	TOIE1 bits */
			SET_BIT(TIMSK , OCIE1A); /* interrupt at TCNT1 == OCR1A */
		}
}
/*
 * Description : function to give the timer a function's address to call it
 * 		at interrupt
 * 		this function should takes void and return a void
 * */
void TIMER1_setCallback(void (*const a_func)(void)){
	g_func = a_func ;
}
/*
 * Description : function to change Timer's 1 pre-scaler value
 * input : 	a data of type prescaler
 * */
void TIMER1_changePreScaler(const prescaler a_prescaler){
	TCCR1B = (TCCR1B & 0xF8) | (a_prescaler & 0x07);
}
/*
 * Description : function to change the mode of timer 1 to
 * either overflow mode or compare mode
 * input : data of type mode
 * */
void TIMER1_changeMode(const mode a_mode){
	TCCR1A = (TCCR1A & 0xFC) |  (a_mode & 0x03);
	TCCR1B = (TCCR1B & 0xE7) | ((a_mode & 0x0C)<<1);
}
/*
 * Description : function to set the compare register value
 * input : 16 bit integer number 0 ~ 65535
 * */
void TIMER1_setCompareValue(const uint16 a_val){
	OCR1A = a_val;
}
/*
 * Description :function to disable timer1 module
 * */
void TIMER1_deInit(void){
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 0;
	TIMSK &= 0xC3 ; /*clear the TICIE1	OCIE1A	OCIE1B	TOIE1 bits*/
}

ISR(TIMER1_COMPA_vect){
	if (g_func == NULL){return;}
	(*g_func)();
}

ISR(TIMER1_OVF_vect){
	if (g_func == NULL){return;}
	(*g_func)();
}


