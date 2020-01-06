
#include "keypad.h"

uint8 KEYPAD_pressPosition(void){
	uint8 col=0;	/*to loop through the rows and columns*/
	uint8 row=0;
	static uint8 flag = 0;
	while(1){
		for(row=0 ; row<KEYPAD_ROW ; row++){
			KEYPAD_PORT_DIR = (1<<row);	/*set the current row as output
										  and all other columns and rows to input*/
			KEYPAD_PORT = ~(1<<row);	/*connect the current row to ground
										  configure the internal PULLUP resistors*/
			for(col=0 ; col<KEYPAD_COL ; col++){
				if(BIT_IS_CLEAR(KEYPAD_PIN , (col+KEYPAD_ROW) )){
					return ((KEYPAD_COL * row) + col);
				}
			}
		}
	}
}

uint8 KEYPAD_keyRelaesed(void){
	uint8 col=0;	/*to loop through the rows and columns*/
	uint8 row=0;
	for(row=0 ; row<KEYPAD_ROW ; row++){
		KEYPAD_PORT_DIR = (1<<row);	/*set the current row as output
											  and all other columns and rows to input*/
		KEYPAD_PORT = ~(1<<row);	/*connect the current row to ground
											  configure the internal PULLUP resistors*/
		for(col=0 ; col<KEYPAD_COL ; col++){
			if(BIT_IS_CLEAR(KEYPAD_PIN , (col+KEYPAD_ROW) )){
				return 0;
			}
		}
	}
	return 1;
}


uint8 KEYPAD_getCharacter(void){
	uint8 character = KEYPAD_pressPosition();
	switch (character){
#if(KEYPAD_COL == 3)
	case 0:
		return ROW0_COL0;
		break;
	case 1:
		return ROW0_COL1;
		break;
	case 2:
		return ROW0_COL2;
		break;
	case 3:
		return ROW1_COL0;
		break;
	case 4:
		return ROW1_COL1;
		break;
	case 5:
		return ROW1_COL2;
		break;
	case 6:
		return ROW2_COL0;
		break;
	case 7:
		return ROW2_COL1;
		break;
	case 8:
		return ROW2_COL2;
		break;
	case 9:
		return ROW3_COL0;
		break;
	case 10:
		return ROW3_COL1;
		break;
	case 11:
		return ROW3_COL2;
		break;
	default :
		break;
	}
#elif(KEYPAD_COL == 4)
	case 0:
		return ROW0_COL0;
		break;
	case 1:
		return ROW0_COL1;
		break;
	case 2:
		return ROW0_COL2;
		break;
	case 3:
		return ROW0_COL3;
		break;
	case 4:
		return ROW1_COL0;
		break;
	case 5:
		return ROW1_COL1;
		break;
	case 6:
		return ROW1_COL2;
		break;
	case 7:
		return ROW1_COL3;
		break;
	case 8:
		return ROW2_COL0;
		break;
	case 9:
		return ROW2_COL1;
		break;
	case 10:
		return ROW2_COL2;
		break;
	case 11:
		return ROW2_COL3;
		break;
	case 12:
		return ROW3_COL0;
		break;
	case 13:
		return ROW3_COL1;
		break;
	case 14:
		return ROW3_COL2;
		break;
	case 15:
		return ROW3_COL3;
		break;
	default :
		break;
}
#endif

}
uint8 KEYPAD_getNumber(void){
	uint8 num = KEYPAD_getCharacter();
	if((num>='0')&&(num<='9')){
		return num-48;
	}
}
