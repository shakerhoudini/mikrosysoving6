#define F_CPU 4000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>

//Variables

#define TIMER 0x01AB            // max value
uint16_t dutycycle = 0x0000;	// current value
bool updown = true;

//Function initialization
void PWM_Init();

int main(void)
{
	//Pins WO0-W02 are on PORTD 0-2
	PORTD.DIRSET |= PIN2_bm | PIN1_bm | PIN0_bm; //Enable output on them
	PWM_Init();
	
    while (1) 
    {
		if(updown){
			dutycycle++;
			if(dutycycle == TIMER){
				updown = false;
			}
		} else {
			dutycycle--;
			if(dutycycle == 0x0000){
				updown = true;
			}
		}
		
		_delay_ms(5);
    }
}

void PWM_Init(){
	PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc; //enable waveform for port d
	
	// Control Register|	Compare And Enable Flag |	Set Output mode to Dual Slope 
	TCA0.SINGLE.CTRLB =		TCA_SINGLE_CMP0EN_bm	|	TCA_SINGLE_WGMODE_DSBOTTOM_gc;
	
	TCA0.SINGLE.PERBUF	= TIMER;
	TCA0.SINGLE.CMP0BUF = TIMER/2;//Duty Cycle, Using one from previous task
	
	//Set Prescaler To 256 So values from oppg1 work	| enable Timer
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV4_gc		| TCA_SINGLE_ENABLE_bm;
}
