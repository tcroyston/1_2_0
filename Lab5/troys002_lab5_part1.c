/*	Author:Thomas Royston
 *  	Partner(s) Name: (None)
 *	Lab Section: 22
 *	Assignment: Lab #5  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	VIDEO: https://www.youtube.com/watch?v=C964RkXuWRA&ab_channel=ThomasRoyston
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
   
        DDRA = 0x00; PORTA = 0xFF;
        DDRC = 0xFF; PORTC = 0x00;

        unsigned char tempA;
        unsigned char tempC;


        while (1) {
                tempA = ~PINA & 0x0F;
                tempC = 0x40;
                if((tempA >= 1) && (tempA <= 2)) {
                        tempC = 0x60;
                }

                if((tempA >= 3) && (tempA <= 4)) {
                        tempC = 0x70;
                }
                if((tempA >= 5) && (tempA <= 6)) {
                        tempC = 0x38;
                }

                if((tempA >= 7) && (tempA <= 9)) {
                        tempC = 0x3C;
                }

                if((tempA >= 10) && (tempA <= 12)) {
                        tempC = 0x3E;
                }

                if((tempA >= 13) && (tempA <= 15)) {
                        tempC = 0x3F;
                }

                PORTC = tempC;
        }
        return 1;
}     
