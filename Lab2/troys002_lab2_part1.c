/*	Author: troys002
 * 	Partner(s) Name:  NONE
 *	Lab Section: 22
 *	Assignment: Lab #2  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB  = 0x00;
	
	unsigned char tmpB = 0x00;
	unsigned char tmpA = 0x00;
    /* Insert your solution below */
    while (1) {
	// Read Input from PINA
	tmpA = PINA & 0x03;
	
	// if PA) is 1, set PB1PB0 = 01, else = 10
	if(tmpA == 0x01){
		tmpB = (tmpB & 0xFC) | 0x01; //sets tmpB to bbbbbb01

	}
	else{
		tmpB = (tmpB & 0xFC) | 0x00;//sets tmpB to bbbbbb00
	}

	PORTB = tmpB;
	}
    return 1;
}

