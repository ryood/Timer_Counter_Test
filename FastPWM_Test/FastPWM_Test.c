/*
 * FastPWM_Test.c
 *
 * Created: 2015/04/21 12:52:41
 *  Author: gizmo
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define F_CPU	16000000UL
#include <util/delay.h>

/*
void timer1_init_FastPWM(uint16_t cycle, uint16_t duty)
{
	// Output Compare Register
	OCR1A = cycle;
	OCR1B = duty;

	// Initialize Counter
	TCNT1 = 0;
	
	// Fast PWM Mode, TOP = OCR1A
	TCCR1B |= (1 << WGM13) | (1 << WGM12);
	TCCR1A |= (1 << WGM11) | (1 << WGM10);

	
	// Compare Output OC1A, OC1B
	TCCR1A |= (0 << COM1A1) | (1 << COM1A0);
	TCCR1A |= (1 << COM1B1) | (0 << COM1B0);
	
	
	// Timer1 Start, Set No Prescaling
	TCCR1B |= (1 << CS10);
}
*/

void timer1_init_Freq_Phase_Correct_PWM(uint16_t cycle, uint16_t duty, uint16_t prescaler)
{
	// Output Compare Register
	OCR1A = cycle;
	OCR1B = duty;

	// Initialize Counter
	TCNT1 = 0;
	
	// Phase and Frequency Correct PWM Mode, TOP = OCR1A
	TCCR1B |= (1 << WGM13) | (0 << WGM12);
	TCCR1A |= (0 << WGM11) | (1 << WGM10);

	
	// Compare Output OC1A, OC1B
	TCCR1A |= (0 << COM1A1) | (1 << COM1A0);
	TCCR1A |= (1 << COM1B1) | (0 << COM1B0);
	
	switch (prescaler) {
	case 0:
		// stop timer
		break;
	case 1:
		TCCR1B |= (1 << CS10);
		break;
	case 8:
		TCCR1B |= (1 << CS11);
		break;
	case 64:
		TCCR1B |= (1 << CS11) | (1 << CS10);
		break;
	case 256:
		TCCR1B |= (1 << CS12);
		break;
	case 1024:
		TCCR1B |= (1 << CS12) | (1 << CS10);
		break;
	// defult: stop timer
	}
}

int main(void)
{
	DDRB  = 0xFF;  // PB1(OC1A) o—Í

	timer1_init_Freq_Phase_Correct_PWM(1024, 1, 1024);
	//timer1_init_FastPWM(3, 0);
	sei();
	
    while(1)
    {
        //PORTB ^= 0x06;
        //_delay_ms(50);
    }
}
