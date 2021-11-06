/*[FILE NAME]   : eeprom.c
 *[AUTHOR]      : AHMED IBRAHIM
 *[DATE CREATED]: OCT 11, 2021
 *[DESCRIPTION] : this file contain the header file of the DC motor
 */
/*The External EEPROM is running with the two wire interface protocol that's why we include the twi.h*/
#include"twi.h"
#include"eeprom.h"


uint8 EEPROM_writeByte(uint16 address,uint8 data){
	/* First : we send the start bit
	 * */
	TWI_start();
	/*Check of sending the start bit*/
	if(TWI_getStatus() != TWI_START){
		return ERROR;
	}
	/* In the device address, we need to send the last 3-bits of the location which we want to write in
	 * EXAMPLE : if we want to write in location (110 0101 0011) we need to take the last 3-bit
	 *    address  0000 0110 0101 0011
	 * & (0x0700)  0000 0111 0000 0000
	 *            ---------------------
	 *             0000 0110 0000 0000
	 *then we need to make shift right with 7 to be like that :
	 * >>7         0000 0000 0000 1100
	 * now, we need to put the device address and the write contol bit
	 * device address is 0B1010 which is 0xA
	 *                      0000 0000 0000 1100
	 * so oring with (0xA0) 0000 0000 1010 0000
	 *                      -------------------
	 *                      0000 0000 1010 1100
	 * last we need to casting to only 1-bye so the result will be
	 *                                1010 1100
	 * */
	TWI_writeByte((uint8)((((address & 0x0700)>>7) | 0xA0 )));
	/*Check of sending the slave address and responded with ACK*/
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK){
		return ERROR;
	}
	/*sending the first 8-bits in the location address*/
	TWI_writeByte((uint8)(address));
	/*Check of sending the location address and responded with ACK*/
	if(TWI_getStatus() != TWI_MT_DATA_ACK){
		return ERROR;
	}
	/*sending the data in the location address*/
	TWI_writeByte(data);
	/*Check of sending the data and responded with ACK*/
	if(TWI_getStatus() != TWI_MT_DATA_ACK){
		return ERROR;
	}
	TWI_stop();
	/*return success operation */
	return SUCCESS;
}

uint8 EEPROM_readByte(uint16 address,uint8 *data){
	/* First : we send the start bit
	 * */
	TWI_start();
	/*Check of sending the start bit*/
	if(TWI_getStatus() != TWI_START){
		return ERROR;
	}
	/* In the device address, we need to send the last 3-bits of the location which we want to write in
	 * EXAMPLE : if we want to write in location (110 0101 0011) we need to take the last 3-bit
	 *    address  0000 0110 0101 0011
	 * & (0x0700)  0000 0111 0000 0000
	 *            ---------------------
	 *             0000 0110 0000 0000
	 *then we need to make shift right with 7 to be like that :
	 * >>7         0000 0000 0000 1100
	 * now, we need to put the device address and the write contol bit
	 * device address is 0B1010 which is 0xA
	 *                      0000 0000 0000 1100
	 * so oring with (0xA0) 0000 0000 1010 0000
	 *                      -------------------
	 *                      0000 0000 1010 1100
	 * last we need to casting to only 1-bye so the result will be
	 *                                1010 1100
	 * */
	TWI_writeByte((uint8)((((address & 0x0700)>>7) | 0xA0 )));
	/*Check of sending the slave address and responded with ACK*/
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK){
		return ERROR;
	}
	/*sending the first 8-bits in the location address*/
	TWI_writeByte((uint8)(address));
	/*Check of sending the location address and responded with ACK*/
	if(TWI_getStatus() != TWI_MT_DATA_ACK){
		return ERROR;
	}
	/*Sending the repeated start bit*/
	TWI_start();
	if(TWI_getStatus() != TWI_REPEATED_START){
		return ERROR;
	}
	/*Here, we need to send read control bit so we will make or operation with 1*/
	TWI_writeByte((uint8)((((address & 0x0700)>>7) | 0xA0 | 1 )));
	/*Check of sending the slave address and responded with ACK*/
	if(TWI_getStatus() != TWI_MT_SLA_R_ACK){
		return ERROR;
	}
	/*reading the byte*/
	*data=TWI_readByteWithNACK();
    if (TWI_getStatus() != TWI_MR_DATA_NACK){
        return ERROR;
       }
    TWI_stop();
	return SUCCESS;
}


uint8 EEPROM_writeArray(uint16 address,uint8 *data,uint8 length){
	uint8 i=0;
	/* First : we send the start bit
		 * */
	TWI_start();
	/*Check of sending the start bit*/
	if(TWI_getStatus() != TWI_START){
		return ERROR;
	}
	/* In the device address, we need to send the last 3-bits of the location which we want to write in
	 * EXAMPLE : if we want to write in location (110 0101 0011) we need to take the last 3-bit
	 *    address  0000 0110 0101 0011
	 * & (0x0700)  0000 0111 0000 0000
	 *            ---------------------
	 *             0000 0110 0000 0000
	 *then we need to make shift right with 7 to be like that :
	 * >>7         0000 0000 0000 1100
	 * now, we need to put the device address and the write contol bit
	 * device address is 0B1010 which is 0xA
	 *                      0000 0000 0000 1100
	 * so oring with (0xA0) 0000 0000 1010 0000
	 *                      -------------------
	 *                      0000 0000 1010 1100
	 * last we need to casting to only 1-bye so the result will be
	 *                                1010 1100
	 * */
	TWI_writeByte((uint8)((((address & 0x0700)>>7) | 0xA0 )));
	/*Check of sending the slave address and responded with ACK*/
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK){
		return ERROR;
	}
	/*sending the first 8-bits in the location address*/
	TWI_writeByte((uint8)(address));
	/*Check of sending the location address and responded with ACK*/
	if(TWI_getStatus() != TWI_MT_DATA_ACK){
		return ERROR;
	}
	/* For loop to the length of the array to write in the memmory
	 * */
	for(i=0;i<length;i++){
	/*sending the data in the location address*/
	TWI_writeByte(data[i]);
	/*Check of sending the data and responded with ACK*/
	if(TWI_getStatus() != TWI_MT_DATA_ACK){
		return ERROR;
	}

	}
	/*sending the stop bit*/
	TWI_stop();
	return SUCCESS;
}



uint8 EEPROM_readArray(uint16 address,uint8 *data,uint8 length){
	    uint8 i=0;
		/* First : we send the start bit
			 * */
		TWI_start();
		/*Check of sending the start bit*/
		if(TWI_getStatus() != TWI_START){
			return ERROR;
		}
		/* In the device address, we need to send the last 3-bits of the location which we want to write in
		 * EXAMPLE : if we want to write in location (110 0101 0011) we need to take the last 3-bit
		 *    address  0000 0110 0101 0011
		 * & (0x0700)  0000 0111 0000 0000
		 *            ---------------------
		 *             0000 0110 0000 0000
		 *then we need to make shift right with 7 to be like that :
		 * >>7         0000 0000 0000 1100
		 * now, we need to put the device address and the write contol bit
		 * device address is 0B1010 which is 0xA
		 *                      0000 0000 0000 1100
		 * so oring with (0xA0) 0000 0000 1010 0000
		 *                      -------------------
		 *                      0000 0000 1010 1100
		 * last we need to casting to only 1-bye so the result will be
		 *                                1010 1100
		 * */
		TWI_writeByte((uint8)((((address & 0x0700)>>7) | 0xA0 )));
		/*Check of sending the slave address and responded with ACK*/
		if(TWI_getStatus() != TWI_MT_SLA_W_ACK){
			return ERROR;
		}
		/*sending the first 8-bits in the location address*/
		TWI_writeByte((uint8)(address));
		if(TWI_getStatus() != TWI_MT_DATA_ACK){
			return ERROR;
		}
		/*sending another start bit to change the control bit from write to read because we want to read*/
		TWI_start();
		if(TWI_getStatus() != TWI_REPEATED_START){
			return ERROR;
		}
		/*Here, we need to send read control bit so we will make or operation with 1*/
		TWI_writeByte((uint8)((((address & 0x0700)>>7) | 0xA0 | 1 )));
		/*Check of sending the slave address and responded with ACK*/
		if(TWI_getStatus() != TWI_MT_SLA_R_ACK){
			return ERROR;
		}
		/* why looping till (length-1) ??
		 * --> we want to read an array so we need to respond to the slave with ACK in order to make the slave
		 *    sending the following byte so we make the looping like that
		 * */
		for(i=0;i<length-1;i++){

		data[i]=TWI_readByteWithACK();
		if (TWI_getStatus() != TWI_MR_DATA_ACK){
		      return ERROR;
		   }

		}
		/* The last element in the array so the master will not respond to the slave with the ACK because the whole array now is sent
		 * to the master so the master doesn't want data that's why the master will respond with ACK so, the slave will
		 * understand that the master didn't want data.
		 * */
		data[i]=TWI_readByteWithNACK();
		if (TWI_getStatus() != TWI_MR_DATA_NACK){
	      return ERROR;
		   }

		TWI_stop();
		return SUCCESS;
}
