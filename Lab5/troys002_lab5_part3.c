/*	Author: Thomas Royston
 *  	Partner(s) Name: (None)
 *	Lab Section: 22
 *	Assignment: Lab #5  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 * 	VIDEO: https://www.youtube.com/watch?v=BsI3xFnT8Vo&ab_channel=ThomasRoyston
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, Display, Wait} state;
unsigned char sequence[] = { 33, 18, 12, 18 };
unsigned char i;

void Tick() {
	switch(state) {
		case Start:
			state = Display;
			i = 0;
			break;


		case Display:
			if((PINA & 0x01) == 0x00) {
				if(i < 3) { i++; }
				else { i = 0; }
				state = Wait;
			}
			else { state = Display; }
			break;


		case Wait:
			if((PINA & 0x01) == 0x01) { state = Display; }
			else { state = Wait; }
			break;


		default:
			state = Start;
			break;
	}
	switch(state) {
		case Start:
			break;


		case Display:


		case Wait:
			PORTC = sequence[i];
			break;


		default:
			break;
	}
}

int main(void) {

        DDRA = 0x00; PORTA = 0xFF;
        DDRC = 0xFF; PORTC = 0x00;

	state = Start;
        while (1) { Tick(); }
        return 1;
}     
