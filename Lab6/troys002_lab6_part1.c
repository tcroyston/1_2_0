/*	Author: Thomas Royston
 *  	Partner(s) Name: None
 *	Lab Section: 022
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *	Video: https://www.youtube.com/watch?v=3OAaepklXyo&ab_channel=ThomasRoyston
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>
#include "timer.h"

enum States { Start, S0, S1, S2} state;
unsigned char tmpB = 0x00;

void Tick() {
	switch(state) {
		case Start: state = S0; break;
		case S0: state = S1; break;
		case S1: state = S2; break;
		case S2: state = S0; break;
		default: state = Start; break;
	}
	switch(state) {
		case Start: break;
		case S0: tmpB = 0x01; PORTB = tmpB; break;
		case S1: tmpB = 0x02; PORTB = tmpB; break;
		case S2: tmpB = 0x04; PORTB = tmpB; break;
		default: break;
	}
}


int main(void)
{
	DDRB = 0xFF;
	PORTB = 0x00;
	TimerSet(1000);
	TimerOn();
    while (1) 
    {
		Tick();
		while(!TimerFlag);
		TimerFlag = 0;
    }
}
