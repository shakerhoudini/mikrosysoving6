#define F_CPU 4000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

int main(void)
{
	//setup
	
	PORTB.DIR = PIN3_bm;
	//using diode on PORTB so using pin3 as output
	
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
	//Interrupt Enablem, using overflow interrupt 
	
	TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm | TCA_SINGLE_CLKSEL_DIV256_gc;
	// Control Register | Enable Timer for PWM | Prescaler = F_CPU/TCA_SINGLE_CLKSEL_DIVx_gc
	
	TCA0.SINGLE.PERBUF =0x3D09;
	//Define Period of timer: Ttca0 = (F_CUP * Freq) / N
	//Assuming n = 256 since prescaler is set to 256,  4 000 000 * 1hz / 256 -> 3D09 in hex
	
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		;//nothing happens in while loop waiting for interrupts
    }
}

ISR(TCA0_OVF_vect){
	PORTB.OUTTGL = PIN3_bm;
	
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

