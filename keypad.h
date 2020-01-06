/*
 * keypad.h
 *
 *  Created on: Dec 29, 2019
 *      Author: SALAH
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*--------------------------static configuration -------------*/
/* always connect the rows to the lower pins of the port
 * and the columne to the higher pins port
 * change the keypad number of rows and columns according to
 * the keypad connected
 * */
#define KEYPAD_ROW 4
#define KEYPAD_COL 4
/*
 * change the connected port to the 8 BIT port name of the uC
 * */
#define KEYPAD_PORT PORTA
#define KEYPAD_PORT_DIR DDRA
#define KEYPAD_PIN PINA
/*
 * change this to PULL_DOWN if you use pull down connection
 * */
#define BUTTON_CONNECTION PULL_UP
/*
 * comment this if you use external pull up resistors
 * */
#if (BUTTON_CONNECTION == PULL_UP)
#define USE_INTERNAL_PULLUP_RESISTOR
#endif
/*
 * change the character returned for every button
 * starting from up left (ROW0_COL0)
 * */
#define ROW0_COL0 '7'
#define ROW0_COL1 '8'
#define ROW0_COL2 '9'

#define ROW1_COL0 '4'
#define ROW1_COL1 '5'
#define ROW1_COL2 '6'

#define ROW2_COL0 '1'
#define ROW2_COL1 '2'
#define ROW2_COL2 '3'

#define ROW3_COL0 13
#define ROW3_COL1 '0'
#define ROW3_COL2 '='
/*
 * continue if the KEYPAD you have is 4*4
 * */
#if(KEYPAD_COL == 4)
#define ROW0_COL3 '/'
#define ROW1_COL3 '*'
#define ROW2_COL3 '-'
#define ROW3_COL3 '+'
#endif

/*------------------functions prototype ------------------------*/

uint8 KEYPAD_pressPosition(void);
uint8 KEYPAD_getCharacter(void);
uint8 KEYPAD_getNumber(void);
uint8 KEYPAD_keyRelaesed(void);


#endif /* KEYPAD_H_ */
