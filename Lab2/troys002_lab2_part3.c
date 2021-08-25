/*	Author: troys002
 * 	Partner(s) Name: NONE
 *	Lab Section: 22
 *	Assignment: Lab #2  Exercise #3
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
	DDRC = 0xFF; PORTC = 0x00;

	unsigned char tmpB = 0x00;
	unsigned char tmpA = 0x00;
	unsigned char tmpC = 0x00;
	unsigned char availcnt = 0x00;
	unsigned char i;   
 /* Insert your solution below */
    while (1) {
	availcnt = 0x00;	
	//Read input from PINA [3:0]
	tmpA = PINA & 0x0F;
		
	for(i = 0; i < 4; i++){
		if((tmpA & (0x01 << i)) !=0 ){
			availcnt++;
		}
	}
	
	tmpC = 4 -  availcnt;	
	
	if(PINA == 0x0F){
		tmpC =  0x80;
	}
	
	PORTC = tmpC;
	}

		
    return 1;
}

