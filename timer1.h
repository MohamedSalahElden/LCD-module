/*
 * timer1.h
 *
 *  Created on: Jan 5, 2020
 *      Author: mohamed salah
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#ifdef PWM_H_
#warning "PWM module uses timer1 to operate it will produce a runtime error operating these modules together "
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif
/*--------------------------include utility files------------------------------*/
#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

/*---------------------------------data definitions----------------------------*/
typedef enum {
	OVF ,
	COMP_A = 4
} mode;

typedef enum {
	CLK_OFF = 0,
	CLK_1 ,
	CLK_8 ,
	CLK_64 ,
	CLK_256 ,
	CLK_1024 ,
	EX_T1_FALLING ,
	EX_T1_RISING
}prescaler;

typedef struct {
	mode timer1_mode;
	prescaler timer1_prescaler;
}timer_config;

/*---------------------------------function prototypes--------------------------*/
/*
 * Description :function to set timer1 registers to the specified
 * 		the function must be given an address to a structure of type timer_config
 * */
void TIMER1_init(const timer_config * timer1_configuration);
/*
 * Description : function to give the timer a function's address to call it
 * 		at interrupt
 * 		this function should takes void and return a void
 * */
void TIMER1_setCallback(void (* const func)(void));
/*
 * Description : function to change Timer's 1 pre-scaler value
 * input : 	a data of type prescaler
 * */
void TIMER1_changePreScaler(const prescaler a_prescaler);
/*
 * Description : function to change the mode of timer 1 to
 * either overflow mode or compare mode
 * input : data of type mode
 * */
void TIMER1_changeMode(const mode a_mode);
/*
 * Description : function to set the compare register value
 * input : 16 bit integer number 0 ~ 65535
 * */
void TIMER1_setCompareValue(uint16 a_val);
/*
 * Description :function to disable timer1 module
 * */
void TIMER1_deInit(void);


#endif /* TIMER1_H_ */
