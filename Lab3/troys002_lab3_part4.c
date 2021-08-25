/*	Author: troys002
 *  	Partner(s) Name: NONE
 *	Lab Section: 22
 *	Assignment: Lab #3  Exercise #4
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
    
	//Inputs
	DDRA = 0x00; PORTA = 0xFF;
	//Output
	DDRC = 0xFF; PORTC = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
   
	unsigned char tempB = 0x00;
	unsigned char tempC = 0x00;
	//unsigned char tempB = 0x00;

    while (1) {
	tempC = 0x00;
	tempB = 0x00;
	tempC =(( PINA & 0x0F ) << 4);
	tempB =((PINA & 0xF0) >> 4);
	
	PORTC = tempC;
	PORTB = tempB;
	
    }
    return 1;
}
