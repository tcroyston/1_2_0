/*	Author: troys002
 *  	Partner(s) Name: (none)
 *	Lab Section:22
 *	Assignment: Lab #4 Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
enum States{start,init ,  A2P, A2R, WP, A1P, A1R, lock}state;
#endif


void tick(){
	switch(state){//transitions
		case start:
			state = init;
			break;

		case init:
			if(PINA == 0x80){
				state = lock;
			}
			else if(PINA == 0x04){
				state = A2P;
			}
			else{
				state = init;
			}
			break;

		case lock:
			if(PINA == 0x00){
				state = init;
			}
			else{
				state = lock;
			}
			break;

		case A2P:
			if(PINA == 0x00){
				state = A2R;
			}
			else{
				state = A2P;
			}
			
			break;

		case A2R:
			if(PINA == 0x02){
				state = A1P;
			}
			else if(PINA == 0x00){
				state = A2R;
			}
			else{
				state = WP;
			}	
			break;
		case WP:
			if(PINA == 0x00){
				state = init;
			}
			else{
				state = WP;
			}
			break;

		case A1P:
			PORTB = 0x01;
			if(PINA == 0x00){
				state = A1R;
			}
			else if(PINA == 0x80){
				state = lock;
			}
			else{
				state = A1P;
			}
			
			break;

		case A1R:
			state = init;
			break;

		default:
			break;
	}

	switch(state){//actions
		default:
			break;

		case start:
			PORTB = 0x00;
			break;
		case init:
			break;
		case lock:
			PORTB = 0x00;
			break;

		case A2P:
			break;

		case A2R:
			break;
	
		case A1P:
			PORTB = 0x01;
			break;
		case A1R:
			break;
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	state = start;
 	while (1) {	
		tick();	
 	}
    return 1;
}
