/*[FILE NAME]   : buzzer.c
 *[AUTHOR]      : AHMED IBRAHIM
 *[DATE CREATED]: OCT 28, 2021
 *[DESCRIPTION] : Source file for buzzer sensor
 */
#ifndef BUZZER_H_
#define BUZZER_H_
#include"std_types.h"

/*To make the buzzer configurable, those two below lines are made*/
#define BUZZER_PORT_ID PORTC_ID
#define BUZZER_PIN_ID  PIN5_ID

/*
 * Description :
 * Function responsible for initializing the buzzer to make the pin an output pin
 */
void BUZZER_init();
/*
 * Description :
 * Function responsible for turn on the buzzer
 */
void BUZZER_on();
/*
 * Description :
 * Function responsible for turn off the buzzer
 */
void BUZZER_off();

#endif /* BUZZER_H_ */
