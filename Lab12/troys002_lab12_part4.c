/* Author: Thomas Royston
 * Partner(s) Name (if applicable):  
 * Lab Section:
 * Assignment: Lab #12  Exercise #4
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 *
 *  Demo Link: https://www.youtube.com/watch?v=FyvEXS23DT4&ab_channel=ThomasRoyston
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

task tasks[2]; 

const unsigned short tasksNum = 2; 
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

unsigned char pat[3] = {0x3C,0x24,0x3C}; 
unsigned char row[3] = {0xF7,0xFB,0xFD}; 

enum Show{starts,show};
 
int Show_Tick(int state1){
	static unsigned char p; 
        static unsigned char r; 
        static unsigned char t = 0; 
        switch (state1) {
                case starts:
                        state1 = show; 
                        break; 

                case show:
                        state1 = show; 
                        break; 

		default:
			break; 
	}
	switch (state1) {
                case starts:
                        break;
 
                case show:
                        p = pat[t%3]; 
                        r = row[t%3]; 
                        t++; 
                        break; 

                default:
                        break; 

        }

        PORTC  =  p;      
        PORTD  =  r;   
            
        return state1; 
}


enum Shift_States {start,initial,up,down,left,right}; 
int shift_tick(int state) {

	switch (state) {
		case start:
			state = initial; 
			break; 

		case initial:
			if(A0 && (!A1) && (!A2) && (!A3)){
				state = up; 
				if(row[2]! = 0xFE){
					row[0] = (row[0]>>1)|0x80; 
					row[1] = (row[1]>>1)|0x80; 
					row[2] = (row[2]>>1)|0x80; 
				}
			}
			else if(A1 && (!A0) && (!A2) && (!A3)){
				state = down; 
				if(row[0]! = 0xEF){
                                        row[0] = (row[0]<<1)|0x01; 
                                        row[1] = (row[1]<<1)|0x01; 
                                        row[2] = (row[2]<<1)|0x01; 
                                }

			}
			else if(A2 && (!A0) && (!A1) && (!A3)){
                                state = left; 
				if(pat[0]! = 0xF0){
					pat[0] = pat[0]<<1; 
					pat[1] = pat[1]<<1; 
					pat[2] = pat[2]<<1; 
				}
			}
			else if(A3 && (!A0) && (!A1) && (!A2)){
                                state = right; 
				if(pat[2]! = 0x0F){
                                        pat[0] = pat[0]>>1; 
                                        pat[1] = pat[1]>>1; 
                                        pat[2] = pat[2]>>1; 
                                }
                        }

			else{
				state = initial; 
			}
			break; 

		case up:
			if(A0 && (!A1) && (!A2) && (!A3)){
				state = up; 
			}
			else if((!A0) && (!A1) && (!A2) && (!A3)){
				state = initial; 
			}
			break; 

		case down:
                        if(A1 && (!A0) && (!A2) && (!A3)){
                                state = down; 
                        }
                        else if((!A0) && (!A1) && (!A2) && (!A3)){
                                state = initial; 
                        }
                        break;
 
		case left:
                        if(A2 && (!A1) && (!A0) && (!A3)){
                                state = left; 
                        }
                        else if((!A0) && (!A1) && (!A2) && (!A3)){
                                state = initial; 
                        }
                        break; 

		case right:
                        if(A3 && (!A1) && (!A2) && (!A0)){
                                state = right; 
                        }
                        else if((!A0) && (!A1) && (!A2) && (!A3)){
                                state = initial; 
                        }
                        break; 

		default:
			break; 
	}
	switch (state) {
		case start:
                        break;
 
                case initial:
			break; 

		default:
			break; 
	}
	return state; 
}


int main(void) {
	DDRA = 0x00; PORTA = 0xFF; 
	DDRC = 0xFF; PORTB = 0x00; 
	DDRD = 0xFF; PORTC = 0x00; 

	unsigned char i  =  0; 

	tasks[i].state = starts; 
	tasks[i].period = 1; 
	tasks[i].elapsedTime = 0; 
	tasks[i].tick_FCT = &Show_Tick; 
	i++; 

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
