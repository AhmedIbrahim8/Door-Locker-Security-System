/*[FILE NAME]   : buzzer.h
 *[AUTHOR]      : AHMED IBRAHIM
 *[DATE CREATED]: OCT 28, 2021
 *[DESCRIPTION] : Header file for buzzer sensor
 */

#include "buzzer.h"

#include"gpio.h"


void BUZZER_init(){
	/*Making the buzzer pin an output pin*/
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
}

void BUZZER_on(){
	/*Write a logic 1 (5v) in the buzzer pin to turn on the buzzer*/
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);
}

void BUZZER_off(){
	/*Write a logic 0 (0v) in the buzzer pin to turn off the buzzer*/
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}
