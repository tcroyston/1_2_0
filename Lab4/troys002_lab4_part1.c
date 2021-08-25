/*	Author: troys002
 *  	Partner(s) Name: (none)
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
enum States{Start, firstPress, firstRelease, secondPress, secondRelease}state;
unsigned char Button, tempB;
#endif


void tick(){
	switch(state){//transitions
		case Start:
			state = secondRelease;
			break;

		default:
			state = Start;
			break;

		case secondRelease:
			if(Button){
				state = firstPress;
			}
			else{
				state = secondRelease;
			}
			break;

		case firstPress:
			if(Button){
				state = firstPress;
			}
			else{
				state = firstRelease;
			}
			break;

		case firstRelease:
			if(Button){
				state = secondPress;
			}
			else{
				state = firstRelease;
			}
			break;

		case secondPress:
			if(Button){
				state = secondPress;
			}
			else{
				state = secondRelease;
			} 
			break;
	}

	switch(state){//actions
		default:
			break;

		case secondRelease:
			tempB = 0x01;
			break;

		case firstPress:
			tempB = 0x02;
			break;

		case firstRelease:
			tempB = 0x02;
			break;

		case secondPress:
			tempB = 0x01;
			break;
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	state = Start;

    while (1) {
	tempB = 0x00;
	Button = PINA & 0x01;
	tick();	
	PORTB = tempB;
    }
    return 1;
}
