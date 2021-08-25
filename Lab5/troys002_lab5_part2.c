/*	Author: Thomas Royston
 *  	Partner(s) Name: (None)
 *	Lab Section: 22
 *	Assignment: Lab #5  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	VIDEO: https://www.youtube.com/watch?v=zGrBwVQTuN4&ab_channel=ThomasRoyston
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
unsigned char cnt;
enum state {Start, begin, add , sub, reset, wait, wait1 } state;
void tick() {
	cnt =~PINA;
        switch(state ) {
        case Start:
                state = begin;
        break;


        case begin:
                if(cnt == 0x01 ) {
                state = add;
                }
                else  if(cnt == 0x02) {
                state = sub;
                }
                else if (cnt == 0x03) {
                state = reset;
                }
                else {
                state = begin;
                }
        break;


	case add:
                state = wait;
        break;


        case sub:
                state = wait1;
        break;


        case reset:
                state =  begin;
        break;


        case wait:
                if(cnt == 0x00) {
                        state = begin;
                }
                else if(cnt == 0x03 ) {
                        state = reset;
                }
                else if(cnt == 0x02) {
                        state = begin;
                }
                else{
                        state = wait;
		 }
        break;


        case wait1:
                if(cnt == 0x00 || cnt ==  0x01 ) {
                        state = begin;
                }
                else if(cnt == 0x03 ) {
                        state = reset;
                }
                else {
                        state = wait1;
                }
        break;


        default:
                state = begin;
        break;

        }
	switch(state) {
        case begin:
        break;
        case add:
                if( PINC < 9) {
                PORTC = PINC + 1;
                }
        break;
        case sub:
                if(PINC > 0 ) {
                PORTC = PINC - 1;
                }
        break;


        case reset:
                PORTC = 0x00;
        break;
         default:
        break;
        }
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;  PORTA = 0xFF;
    DDRC = 0xFF;  PORTC = 0x07;
    /* Insert your solution below */
    state = Start;
   // unsigned char button = 0x00;
   // unsigned char level = 0x00;
    while (1) {
	tick();
    }
    return 1;
}