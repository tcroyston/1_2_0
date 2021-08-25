/*	Author: troys002
 * 	Partner(s) Name: NONE
 *	Lab Section: 22
 *	Assignment: Lab #2  Exercise #4
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
	DDRA = 0x00; PORTA = 0xFF; //INPUT A
	DDRB = 0x00; PORTB  = 0xFF; //INPUT B
	DDRC = 0x00; PORTC = 0xFF; //INPUT C
	DDRD = 0xFF; PORTD = 0x00; // OUTPUT D
    /* Insert your solution below */
	unsigned char tmpB = 0x00;
        unsigned char tmpA = 0x00;
        unsigned char tmpC = 0x00;

    while (1) {
	// Read Input from A B C
        unsigned char totalWeight = 0x00;
        unsigned char tmpD = 0x00;
	unsigned char heavierAC = 0x00;
	unsigned char lighterAC = 0x00;
	tmpA = PINA;
	tmpB = PINB;
	tmpC = PINC; 
	
	// add together weight
	totalWeight = tmpB + tmpA + tmpC;
	tmpD = totalWeight;

	if(tmpA >= tmpC){
		heavierAC = tmpA;
		lighterAC = tmpC;
	}
	else{
		heavierAC = tmpC;
		lighterAC = tmpA;
	}

	// if total weight is greater than 140kg set PD0 to 1
	if(totalWeight > 0x8C ){
		tmpD = tmpD | 0x01;

	}
	else{
		tmpD = tmpD & ~(0x01);
	}
	    
	    

	if((heavierAC  -  lighterAC) > 0x50 ){
		tmpD = tmpD | (0x01 << 1);

	}
	else{
		tmpD = tmpD & ~(0x01 << 1);
	}

	PORTD = tmpD;
	}
	
    return 1;
}

