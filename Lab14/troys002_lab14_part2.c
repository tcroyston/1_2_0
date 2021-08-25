/* Author: Thomas Royston
 * Partner(s) Name (if applicable):  
 * Lab Section: 022
 * Assignment: Lab #14  Exercise #2
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 *  Demo Link: https://www.youtube.com/watch?v=OqAtligdWlw&ab_channel=ThomasRoyston
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
task tasks[2];

const unsigned short taskNum = 2;
const unsigned long taskPeriod = 10;

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
	for(i=0;i<taskNum;++i){
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

#define B0 (PINB&0x01)
enum Led_Lead{init,lead};

int lead_tick(int state){
	static unsigned char x = 0;
	static unsigned char temp = 0;
	switch(state){
		case init:
			if(B0==1){
				state = lead;
			}
			else{
				state = init;
			}
			break;

		case lead:
			if(B0==1){
				state = lead;
				PORTC = 0x01;
			}
			else if(B0==0){
				state = init;
			}
			break;

		default:
			break;
	}
	switch(state){
		case init:
			PORTC = 0;
			break;

		case lead:
			if(USART_IsSendReady(1)){
				x =! x;
				PORTA = x;				
				USART_Send(x,1);
			}
			break;

		default:
			break;
	}
	return state;
}

enum Led_Follow{init_follow,follow};
int follow_tick(int state1){
	static unsigned char temp=0;
        switch(state1){
                case init_follow:
			if(B0==0){
				state1 = follow;
			}
			else{
				state1 = init_follow;
			}
			break;

		case follow:
			if(B0==0){
				state1 = follow;
			}
			else if(B0==1){
				state1 = init_follow;
			}
			break;

		default:
			break;
	}
	switch(state1){
		case init_follow:
			PORTC = 1;
			break;

		case follow:
			if(USART_HasReceived(0)){
				temp = USART_Receive(0);			
				PORTA = temp;
			}
		 	break;

                default:
                        break;
        }
        return state1;
}


int main(void) {
	initUSART(0);
	USART_Flush(0);
	initUSART(1);
	USART_Flush(1);

	DDRA=0xFF; PORTA=0x00;
	DDRB=0x00; PORTB=0xFF;
	DDRC=0xFF; PORTC=0x00;
	unsigned char i=0;

	tasks[i].state = init;
        tasks[i].period = 1000;
        tasks[i].elapsedTime = 0;
        tasks[i].tick_function =& lead_tick;
	i++;

	tasks[i].state = init_follow;
	tasks[i].period = 20;
	tasks[i].elapsedTime = 0;
	tasks[i].tick_function =& follow_tick;

	TimerSet(10);
	TimeOn();

    	while (1) {
    	}
    	return 1;
}
