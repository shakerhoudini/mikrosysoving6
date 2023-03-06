#define F_CPU 4000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>

//since we want 20ms period, 1/0.020 -> 50hz
// 4000000/(2*4*50) -> 10000 -> 0x2710

#define TIMER 0x2710			// max value
uint16_t dutycycle = 0x0000;	// current value

#define ms1 0x01F4
#define ms2 0x03E8

bool updown = true;

void PWM_Init();

int main(void)
{
	//Pins WO0-W02 are on PORTD 0-2
	PORTD.DIRSET |= PIN2_bm | PIN1_bm | PIN0_bm; //Enable output on them
	
	PWM_Init();
	
	/* Replace with your application code */
	while (1)
	{
		if(updown){
			TCA0.SINGLE.CMP0BUF = ms2;
			_delay_ms(1000);
			updown = !updown;
		} else {
			TCA0.SINGLE.CMP0BUF = ms1;
			_delay_ms(1000);
			updown = !updown;
		}
		
	}
}

void PWM_Init(){
	PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc; //enable waveform for port d
	
	// Control Register|	Compare And Enable Flag |	Set Output mode to Dual Slope
	TCA0.SINGLE.CTRLB =		TCA_SINGLE_CMP0EN_bm	|	TCA_SINGLE_WGMODE_DSBOTTOM_gc;
	
	TCA0.SINGLE.PERBUF	= TIMER;
	TCA0.SINGLE.CMP0BUF = ms1;//Duty Cycle, Using one from previous oppg
	
	//Set Prescaler To 4								| enable Timer
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV4_gc		| TCA_SINGLE_ENABLE_bm;
}
