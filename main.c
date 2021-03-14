/*
 * interrupt service routine.c
 *
 * Created: 22-02-2021 16:58:27
 * Author : Tamanna Dave
 */ 

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>


volatile uint8_t tick_signal = 0;


ISR(TIMER1_COMPA_vect, ISR_BLOCK)
{
	tick_signal++;					
	
}

int main(void)
{
	
	DDRB |= (1<<PORTB5);			
	PORTB &= ~(1<<PORTB5);		
	

	TCCR1B |= (1 << WGM12);
	OCR1A = 25000;					
	TIMSK1 |= (1 << OCIE1A);	
	TCCR1B |= ((1 << CS10) | (1 << CS11));	
	
	
	sei();
	
	while(1){
		if(tick_signal){
			PORTB ^= (1 << PORTB5); 
			tick_signal = 0;
		}
	}
}
