/* Author: Thomas Royston
 * Partner(s) Name (if applicable):  
 * Lab Section:
 * Assignment: Lab #12 Exercise #3
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 *  Demo Link: https://www.youtube.com/watch?v=uLXEVhxU8wQ&ab_channel=ThomasRoyston
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


typedef struct task{
        int state; 
        unsigned long period; 
        unsigned long elapsedTime; 
        int(*tick_FCT)(int); 
}
task; 

task tasks[1]; 

const unsigned short tasksNum = 1; 
const unsigned long tasksPeriod = 1; 

volatile unsigned char TimerFlag  =  0;  
unsigned long _avr_timer_M  =  1;  
unsigned long _avr_timer_cntcurr  =  0;  

void TimerSet(unsigned long M) {
	_avr_timer_M  =  M; 
	_avr_timer_cntcurr  =  _avr_timer_M; 
}

void timer_on() {
	TCCR1B =  0x0B; 	
	OCR1A =  125; 	
	TIMSK1 =  0x02;  
	TCNT1  =  0; 
	_avr_timer_cntcurr  =  _avr_timer_M; 	
	SREG | =  0x80; 
}

void timer_off() {
	TCCR1B =  0x00;  
}

void timer_ISR() {
	unsigned char i; 
	for(i  =  0; i<tasksNum; ++i){
		if(tasks[i].elapsedTime> = tasks[i].period){
			tasks[i].state = tasks[i].tick_FCT(tasks[i].state); 
			tasks[i].elapsedTime = 0; 
		}
		tasks[i].elapsedTime+ = tasksPeriod; 
	}
}

ISR(TIMER1_COMPA_vect)
{
	_avr_timer_cntcurr--; 
	if (_avr_timer_cntcurr  ==  0) { 	
		timer_ISR();  				
		_avr_timer_cntcurr  =  _avr_timer_M; 
	}
}

#define A0 (~PINA&0x01)
#define A1 ((~PINA>>1)&0x01)
#define A2 ((~PINA>>2)&0x01)
#define A3 ((~PINA>>3)&0x01)


enum Shift_States {start,initial}; 

int shift_tick(int state) {

	static unsigned char p; 	
	static unsigned char r;   	
	static unsigned char t = 0; 	
	
	static const unsigned char pat[3] = {0x3C,0x24,0x3C}; 
	static const unsigned char row[3] = {0xF7,0xFB,0xFD};  
	
	switch (state) {
		case start:
			state = initial; 
			break; 

		case initial:
			state = initial; 
			break; 

		default:
			break; 
	}

	switch (state) {
		case start:
                        break; 

                case initial:
			p = pat[t%3]; 
			r = row[t%3]; 
			t++; 
			break; 
              
		default:
			break; 
	}
	PORTC  =  p; 	
	PORTD  =  r; 
		
	return state; 
}


int main(void) {
	DDRA = 0x00; PORTA = 0xFF; 
	DDRC = 0xFF; PORTB = 0x00; 
	DDRD = 0xFF; PORTC = 0x00;
 
	unsigned char i  =  0; 

	tasks[i].state = start; 
	tasks[i].period = 1; 
	tasks[i].elapsedTime = 0; 
	tasks[i].tick_FCT = &shift_tick; 

	TimerSet(1); 
	timer_on(); 

	while (1) {
    	}
	return 1; 
}
