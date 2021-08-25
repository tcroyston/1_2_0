/*	Author: troys002
 *  	Partner(s) Name: (none)
 *	Lab Section:22
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
enum States{Start, INIT,  standBy, increment, decrement, reset}state;
#endif


void tick(){
	switch(state){//transitions
		case Start:
			PORTC = 0x07;
			state = INIT;
			break;

		case INIT:
			if(PINA == 0x01){
				state = increment;
			}
			else if(PINA == 0x02){
				state = decrement;
			}
			else if(PINA == 0x03){
				state = reset;
			}
			else{
				state = INIT;
			}
			break;

		case standBy:
			if((PINA == 0x01) || (PINA == 0x02)){
				state = standBy;
			}
			else if(PINA == 0x03){
				state = reset;
			}
			else{
				state = INIT;
			}
			break;

		case reset:
			if((PINA == 0x01) || (PINA == 0x02)){
				state = reset;
			}
			else{
				state = INIT;
			}
			
			break;

		case increment:
			state = standBy;
		
			break;

		case decrement:
			state = standBy;
			
			break;
		default:
			break;
	}

	switch(state){//actions
		default:
			break;

		case Start:
			PORTC = 0x07;
			break;
		case INIT:
			break;
		case standBy:
			break;

		case reset:
			PORTC = 0x00;
			break;

		case increment:
			if(PORTC >= 0x09){
				PORTC = 0x09;
			}
			else{
				PORTC = PORTC + 0x01;
			}
			break;

		case decrement:
			if(PORTC <= 0x00){
				PORTC = 0x00;
			}
			else{
				PORTC = PORTC - 0x01;
			}
			break;
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x07;
    /* Insert your solution below */
	state = Start;
 	while (1) {	
		tick();	
 	}
    return 1;
}
