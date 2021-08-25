/*	Author: troys002
 *  	Partner(s) Name: (none)
 *	Lab Section: 22
 *	Assignment: Lab #4  Exercise #5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
enum States{start, init, lock, pound, check, standby, pause, unlock}state;

#endif
unsigned char array[3] = {0x01, 0x02, 0x01};
unsigned char i = 0;

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
				state = pound;
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

		case pound:
			if(PINA == 0x00){
				state = check;
			}
			else{
				state = pound;
			}
			
			break;

		case check:
			if(PINA == array[i] ){
				state = standby;
			}
			else if(i == 0x04){
				state = unlock;
			}
			else if(PINA == 0x08){
				state = lock;
			}
			else if(PINA = 0x00){
				state = check;
			}
			else if(PINA != array[i]){
				PORTB = 0x01;
                                state = pause;
                        }	
			break;
		case standby:
			if(PINA = 0x00){
				++i;
				state = check;
			}
			else{
				state = pause;
			}
			break;
		case pause:
			if(PINA = 0x00){
				state = check;
			}
			else{
				state = init;
			}
		case unlock:
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
			i = 0;
			PORTC = 0x01;
			break;
		case standby:
			PORTC = 0x04;
			PORTD = i;
		case lock:
			PORTB = 0x00;
			break;
		case unlock:
			if(PORTB == 0x01){
				PORTB = 0x00;
			}
			else{
				PORTB = 0x01;
			}
			break;
		case pound:
			PORTC = 0x02;
			PORTD = i;
			break;

		case check:
			PORTC = 0x03;
			PORTD = i;
			break;
	
		case pause:
			break;
		}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	state = start;
 	while (1) {	
		tick();	
 	}
    return 1;
}
