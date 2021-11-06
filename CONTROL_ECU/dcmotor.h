/*[FILE NAME]   : dcmotor.h
 *[AUTHOR]      : AHMED IBRAHIM
 *[DATE CREATED]: OCT 11, 2021
 *[DESCRIPTION] : this file contain the header file of the DC motor
 */


#ifndef DCMOTOR_H_
#define DCMOTOR_H_
#include"std_types.h"
/*To make the driver configurable we will make the 4 #s belows*/
#define MOTOR_IN1_PORT_ID PORTC_ID
#define MOTOR_IN1_PIN_ID  PIN6_ID

#define MOTOR_IN2_PORT_ID PORTC_ID
#define MOTOR_IN2_PIN_ID  PIN7_ID

/*
 * Description :
 *   1- MOTOR_OFF is equivalent to 0
 *   2- MOTOR_CW is equivalent to 1 so the IN1 = 1 , IN2 = 0
 *   3- MOTOR_CCW is equivalent to 2 so the IN1 = 0 , IN2 = 1
 *   */
typedef enum{
	MOTOR_OFF,MOTOR_CW,MOTOR_CCW
}DcMotor_State;


void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);


#endif /* DCMOTOR_H_ */
