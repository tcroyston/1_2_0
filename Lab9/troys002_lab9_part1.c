/* Author: Thomas Royston
 * Partner(s) Name (if applicable):  
 * Lab Section: 22
 * Assignment: Lab #9  Exercise #1
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 *  Demo Link: https://www.youtube.com/watch?v=0XziOtKjTAU&ab_channel=ThomasRoyston
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

typedef struct task {
        int state;
        unsigned long period;
        unsigned long elapsedTime;
        int (*TickFct)(int);
} task;

const unsigned char tasksNum = 3;

const unsigned long tasksPeriodGCD = 1000;
const unsigned long periodBlinkLED = 1000;
const unsigned long periodThreeLEDs = 1000;
const unsigned long periodCombineLEDs = 1000;

task tasks[3];

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
        TCCR1B = 0x0B;
        OCR1A = 125;
        TIMSK1 = 0x02;
        TCNT1 = 0;
        _avr_timer_cntcurr = _avr_timer_M;
        SREG |= 0x80;
}


void TimerOff() {
        TCCR1B = 0x00;
}


void TimerISR() {
        unsigned char i;
  	for (i = 0; i < tasksNum; ++i) {
     		if ( tasks[i].elapsedTime >= tasks[i].period ) {
        		tasks[i].state = tasks[i].TickFct(tasks[i].state);
        		tasks[i].elapsedTime = 0;
     		}
     		tasks[i].elapsedTime += tasksPeriodGCD;
  	}
}


ISR(TIMER1_COMPA_vect) {
        _avr_timer_cntcurr--;
        if(_avr_timer_cntcurr == 0) {
                TimerISR();
                _avr_timer_cntcurr = _avr_timer_M;
        }
}


void TimerSet(unsigned long M) {
        _avr_timer_M = M;
        _avr_timer_cntcurr = _avr_timer_M;
}





unsigned char threeLEDs;
unsigned char blinkingLED;

enum BlinkingLEDStates { BL_Start, BL_Off, BL_On };
int BlinkingLEDSM(int state) {
  	switch(state) {
     		case BL_Start:
        		blinkingLED = 0;
        		state = BL_On;
        		break;
     		case BL_Off:
        		state = BL_On;
        		break;
		case BL_On:
			state = BL_Off;
			break;
     		default:
        		state = BL_Start;
			break;
   	}


	switch(state) {
		case BL_Start:
		case BL_Off:
			blinkingLED = 0x00;
			break;
     		case BL_On:
        		blinkingLED = 0x08;
        		break;
     		default:
        		break;
  	}


  	return state;
}





enum ThreeLEDsStates { TL_Start, TL_One, TL_Two, TL_Three };
int ThreeLEDsSM(int state) {
  	switch(state) {
		case TL_Start:
			threeLEDs = 0;
        		state = TL_One;
        		break;
     		case TL_One:
        		state = TL_Two;
        		break;
     		case TL_Two:
        		state = TL_Three;
        		break;
     		case TL_Three:
        		state = TL_One;
        		break;
     		default:
        		state = TL_Start;
			break;
   	}


  	switch(state) {
		case TL_Start:
			break;
     		case TL_One:
        		threeLEDs = 0x01;
        		break;
     		case TL_Two:
        		threeLEDs = 0x02;
        		break;
     		case TL_Three:
        		threeLEDs = 0x04;
        		break;
     		default:
        		break;
  	}


  	return state;
}





enum CombineLEDsStates { CL_Start, CL_On };
int CombineLEDsSM(int state) {
        switch(state) {
                case CL_Start:
                        PORTB = 0x00;
                        state = CL_On;
                        break;
                case CL_On:
                        state = CL_On;
                        break;
                default:
                        state = CL_Start;
                        break;
        }


        switch(state) {
                case CL_Start:
                        break;
                case CL_On:
                        PORTB = (blinkingLED | threeLEDs);
                        break;
                default:
                        break;
        }


        return state;
}

int main() {
	DDRA = 0x00; PORTA = 0xFF;
        DDRB = 0xFF; PORTB = 0x00;

  	unsigned char i=0;

  	tasks[i].state = BL_Start;
  	tasks[i].period = periodBlinkLED;
  	tasks[i].elapsedTime = tasks[i].period;
  	tasks[i].TickFct = &BlinkingLEDSM;
  	i++;


  	tasks[i].state = TL_Start;
  	tasks[i].period = periodThreeLEDs;
  	tasks[i].elapsedTime = tasks[i].period;
  	tasks[i].TickFct = &ThreeLEDsSM;
	i++;


        tasks[i].state = CL_Start;
        tasks[i].period = periodCombineLEDs;
        tasks[i].elapsedTime = tasks[i].period;
        tasks[i].TickFct = &CombineLEDsSM;

  	TimerSet(tasksPeriodGCD);
  	TimerOn();
  
	while(1){
	}

  	return 0;
}
