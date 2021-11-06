# Door-Locker-Security-System
# Project Description 
- This Project is implemented based on the layered architecture.
- Using ATmega16 Microcontroller with frequency 8Mhz.
- We have 2 Micro-Controllers:<br/>
   1- The First one is used for human interface (HMI ECU) <br/>
   2- The second one is used for controlling the whole system (CONTROL ECU) <br/>
- The HMI ECU will not make any decision in the system. It will run by the CONTROL ECU instructions
- Steps:<br/>
  1- The CONTROL ECU will send to the HMI ECU an instruction to set the password so, the user will set his password. The user will enters the password and confirmation of that   password. The two passwords must be the same to continue with the process. If the two password are not the same, the CONTROL ECU will send again to the HMI ECU to set the password and so on until the two passwords are the same.<br/>
  2- CONTROL ECU will save the password in the external EEPROM by using the Two Wire Interface Protocol(TWI) and at the same time, the HMI ECU will wait for the next instruction from the CONTROL ECU.<br/>
  3- The menu will be displayed in the LCD and asking the user either to open the door or to change the password like the picture below.<br/>
![1](https://user-images.githubusercontent.com/91912492/139955104-a5b5131f-c193-4ebe-a0f9-25ab4b417087.PNG)<br/>
  4- If the user enters any key else, the CONTROL ECU will display the menu again until the user choose the right key.<br/>
  5- Based on the user choice, the CONTROL ECU will ask the user to enter the password in order to open the door or change the password.<br/>
  6- If the password is right and choice was to open the door:<br/>
         a) door will move clock wise (opening) for 15 seconds.<br/>
         b) door will be hold (stop) for 3 seconds.<br/>
         c) door will move counter clock wise (closing) for 15 second.<br/>
     note: Every action in the system will be displayed on the LCD. If the door is opening, the LCD must display that state and son on...<br/>
  7- If the password is right and choice was to change the password:<br/>
         Step 1 will be repeated again.<br/>
  8- If the password is wrong for three times:<br/>
         a) The system will be locked.<br/>
         b) Buzzer will play.<br/>
         c) LCD will display this message "System is locked".<br/>
         d) All of that will happenen for 1 minute and after that the menu will display agin.<br/>
# Proteus 
![2](https://user-images.githubusercontent.com/91912492/139956677-ff5f7c31-a6dc-4b45-8f03-a56a6e015dee.PNG)<br/>

# Software Driver
- Full Implemented Timer Driver based on dynamic configuration and call back.<br/>
- UART Driver based on dynamic configuration.<br/>
- TWI Driver based on dynamic configuration.<br/>
- LCD Driver based on static configuration.<br/>
- BUZZER driver based on static configuration.<br/>
- DC MOTOR Driver(note that dc motor is run by PWM mode).<br/>
- DC MOTOR Driver(note that dc motor is run by PWM mode).<br/>
- External EEPROM Driver.<br/>
- GPIO driver.<br/>
- PWM Driver.<br/>
- KEYPAD Driver.<br/>
