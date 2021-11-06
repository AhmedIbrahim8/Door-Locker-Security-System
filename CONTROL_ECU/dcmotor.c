/*[FILE NAME]   : dcmotor.c
 *[AUTHOR]      : AHMED IBRAHIM
 *[DATE CREATED]: OCT 11, 2021
 *[DESCRIPTION] : this file contain the source file of the DC motor
 */

#include"dcmotor.h"
#include"gpio.h"
#include"pwm.h"
#include"common_macros.h"

void DcMotor_Init(void){
	/*
	 * The below 2-lines will setup the direction of the 2-pins of the motor */
	GPIO_setupPinDirection(MOTOR_IN1_PORT_ID,MOTOR_IN1_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_IN2_PORT_ID,MOTOR_IN2_PIN_ID,PIN_OUTPUT);
	/*To stop the motor at the beginning the IN1 & IN2 must be zeros at the first*/
	GPIO_writePin(MOTOR_IN1_PORT_ID,MOTOR_IN1_PIN_ID,LOGIC_LOW);
	GPIO_writePin(MOTOR_IN2_PORT_ID,MOTOR_IN2_PIN_ID,LOGIC_LOW);
}

/*
 * why state>>MOTOR_IN1_PIN_ID and state>>MOTOR_IN2_PIN_ID ??
 * --> if state = MOTOR_CW so state is 1 which is 0000 0001
 *  |-->that's mean IN1 pin need logic 1 and IN2 pin need logic 0
 * --> if state = MOTOR_CWW so state is 2 which is 0000 0010
 *  |-->that's mean IN1 pin need logic 0 and IN2 pin need logic 1
 * */
void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	if(state == MOTOR_CW){
	GPIO_writePin(MOTOR_IN1_PORT_ID,MOTOR_IN1_PIN_ID,LOGIC_HIGH);
	GPIO_writePin(MOTOR_IN2_PORT_ID,MOTOR_IN2_PIN_ID,LOGIC_LOW);
	}
	else if(state == MOTOR_CCW){
	GPIO_writePin(MOTOR_IN1_PORT_ID,MOTOR_IN1_PIN_ID,LOGIC_LOW);
	GPIO_writePin(MOTOR_IN2_PORT_ID,MOTOR_IN2_PIN_ID,LOGIC_HIGH);
	}
	else{
	GPIO_writePin(MOTOR_IN1_PORT_ID,MOTOR_IN1_PIN_ID,LOGIC_LOW);
	GPIO_writePin(MOTOR_IN2_PORT_ID,MOTOR_IN2_PIN_ID,LOGIC_LOW);
	}
	PWM_Timer0_Start(speed);

}
