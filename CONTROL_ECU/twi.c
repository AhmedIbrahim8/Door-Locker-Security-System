/*[FILE NAME]   : twi.C
 *[AUTHOR]      : AHMED IBRAHIM
 *[DATE CREATED]: OCT 22, 2021
 *[DESCRIPTION] : Header file for two wire interface (I2C)
 */
#include"twi.h"
#include"gpio.h"
#include<avr/io.h>
#include"common_macros.h"

void TWI_init(TWI_configType *Config_Ptr){
	/*Choosing a prescaler of 1*/
	TWSR = 0x00;
	/* AVR support up to 400 kHz Data Transfer Speed
	 * so, we have two speed mode which are :
	 *  --> normal mode (100)
	 *  --> fast mode   (400)
	 * */
	TWBR=((F_CPU/(Config_Ptr->mode))-16)/2;
	TWBR=2;
	/*fit the address given by the structure in the TWAR*/
	TWAR=((Config_Ptr->address)<<1);
	/*Enabling the two wire interface */
	TWCR = (1<<TWEN);
}


void TWI_start(){
	/* (1<<TWSTA) ---> To send the start bit, TWSTA must be 1
	 * (1<<TWEN)  ---> to save the enable bit value because we don't make an oring operation
	 * (1<<TWINT) ---> to clear the flag before sending the start bit to check for the next time
	 * */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	/*Polling till the start bit is sent*/
	while(BIT_IS_CLEAR(TWCR,TWINT));
}


void TWI_stop(){
	/* (1<<TWSTO) ---> To send the stop bit, TWSTO must be 1
	 * (1<<TWEN)  ---> to save the enable bit value because we don't make an oring operation
	 * (1<<TWINT) ---> to clear the flag before sending the start bit to check for the next time
	 * */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	/* Here, we don't need to make polling because i have just finished the communication so no need for
	 * the pooling. if we make pooling, it will be waste of time.
	 *
	 * */

}


void TWI_writeByte(uint8 data){
	/*Put the data we want to send in the two wire data register*/
	TWDR=data;
	/* (1<<TWEN)  ---> to save the enable bit value because we don't make an oring operation
	 * (1<<TWINT) ---> to clear the flag before sending the start bit to check for the next time
	 * */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/*Polling until the data is sent by checking on the flag*/
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readByteWithACK(){
	/* (1<<TWEN)  ---> to save the enable bit value because we don't make an oring operation
	 * (1<<TWINT) ---> to clear the flag before sending the start bit to check for the next time
	 * (1<<TWEA)  ---> to enable the ACK bit
	 * */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	/*Polling until the data is read by checking on the flag*/
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/*return the two wire data register value*/
	return TWDR;
}

uint8 TWI_readByteWithNACK(){
	/* (1<<TWEN)  ---> to save the enable bit value because we don't make an oring operation
	 * (1<<TWINT) ---> to clear the flag before sending the start bit to check for the next time
	 * */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/*Polling until the data is read by checking on the flag*/
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/*return the two wire data register value*/
	return TWDR;
}


uint8 TWI_getStatus(){
	/* Return the status of the last 5-bit in the TWSR register
	 * why masking of 0xF8 :
	 * (0xF8)----> 0B1111 1000
	 * 8----> For clearing the prescaler bits
	 * */
	return (TWSR & 0xF8);
}
