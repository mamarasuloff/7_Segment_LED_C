/*
 * 7_Segment_LED_C.cpp
 *
 * Created: 12.04.2022 11:08:35
 *  Author: Mamarasuloff
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/io.h>
#define F_CPU 6000000 
#include <util/delay.h>
#include "74HC595.h"

int Data[] = { 0xBD, 0x90, 0x3B, 0xBA, 0x96,	    // { '0', '1', '2', '3', '4', 
               0xAE, 0xAF, 0x98, 0xBF, 0xBE };	    //   '5', '6', '7', '8', '9' };
unsigned char Segments[2];
			  
int main(void) {
    DDRB = 0xFF;
    void F74HC595_Init(void);
    while(1) {
        //TODO:: Please write your application code
        for(int i = 0; i < 10; i++) {
	    for(int j = 0; j < 10; j++) {
		Segments[0] = Data[i];
		Segments[1] = Data[j];
		Indication(Segments, 2);
         	_delay_ms(100);
            }
	}
    }
	return 0;
}
