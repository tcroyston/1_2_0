/* Author: Thomas Royston
 * Partner(s) Name (if applicable):  
 * Lab Section: 022
 * Assignment: Lab #14  Exercise #1
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 *  Demo Link: https://www.youtube.com/watch?v=6DmPyMkF-ww&ab_channel=ThomasRoyston
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include “usart_ATMEGA1284.h”
#endif

typedef struct task{
        int state;
        unsigned long period;
        unsigned long elapsedTime;
        int(*tick_function)(int);
}

task;

task tasks[1];

const unsigned short taskNum=1;
const unsigned long taskPeriod=10;

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void TimeOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimeOff() {
	TCCR1B = 0x00;
}

void TimeISR() {
	unsigned char i;
	for(i = 0; i < taskNum; ++i){
		if(tasks[i].elapsedTime>=tasks[i].period){
			tasks[i].state=tasks[i].tick_function(tasks[i].state);
			tasks[i].elapsedTime = 0;
		}
		tasks[i].elapsedTime += taskPeriod;
	}
}

ISR(TIMER1_COMPA_vect)
{
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimeISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

enum Led_Follow{led};

int follow_tick(int state){
	static unsigned char temp = 0;
        switch(state){
                case led:
			if(USART_HasReceived(0)){
				temp=USART_Receive(0);			
				PORTA = temp;
			}
                        break;
                default:
			state = led;
                        break;
        }
        return state;
}

int main(void) {
	initUSART(0);
	DDRA=0xFF; PORTA=0x00;
	unsigned char i=0;

	tasks[i].state = led;
	tasks[i].period = 20;
	tasks[i].elapsedTime = 0;
	tasks[i].tick_function = &follow_tick;

	TimerSet(10);
	TimeOn();

    	while (1) {
    	}

    	return 1;
}
