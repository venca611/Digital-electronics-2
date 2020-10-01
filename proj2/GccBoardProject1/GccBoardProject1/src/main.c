/***********************************************************************
 *	Projekt 2
 *	Knight Rider LEDs
 *
 *	@author Vaclav Pastusek (xpatu02)
 *	@date 1.10.2020
 *	@Github https://github.com/venca611/Digital-electronics-2
 *
 **********************************************************************/


#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay func
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions


/* Defines -----------------------------------------------------------*/
#define DELAY 150   // Delay in milliseconds
#define PAUSE 50	// Pause in milliseconds
#define BTN PD0     // Button
int LED[5] = {PB1, PB2, PB3, PB4, PB5}; //RED LEDs

/* Variables ---------------------------------------------------------*/

/* Function prototypes -----------------------------------------------*/
/**
 * @brief Blink with specific LED
 * 
 * @param  number of LED
 * @return void
 */
void blink(int);

/* Functions ---------------------------------------------------------*/
void blink(int number){
	PORTB ^= (1<<LED[number]);
	_delay_ms(DELAY); 
	PORTB ^= (1<<LED[number]);
	_delay_ms(PAUSE);
	return;
}


/**
 * Knight Rider LEDs
 */
int main(void)
{
	// PORTs setup (LEDs and Button)
	for(int i = 0; i < 5; i++){
		DDRB |= (1<<LED[i]);
		PORTB &= ~(1<<LED[i]);
	}
	DDRD &= ~(1<<BTN);
	PORTD |= (1<<BTN);
	
	/**
	 * main infinite loop
	 *
	 * when inc is 1 then increase i else decrease i
	 * if i is 4 then inc changes to 0
	 * if i is 0 then inc changes to 1 
	 */
	for(int i = 0, inc = 0;; inc? i++: i--){
		inc = i%4?inc:(inc+1)%2;
		// If Button is pressed, then LEDs are off.
		if(bit_is_set(PIND,BTN)){
			blink(i);
		}
	}
			
    return 0;
}

/* Interrupt routines ------------------------------------------------*/