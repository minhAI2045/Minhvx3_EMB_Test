# Minhvx3_EMB_Test
## Control PWM with buttons
### [SRS_01] Init PWM pulse with Frequency: 2KHz and Duty cycle: 50%
### [SRS_02] If button 1 is pressed, increase the duty cycle by 10%
### [SRS_03] If button 2 is pressed, decrease the duty cycle by 10%
### [SRS_04] The duty cycle is always: 0% <= duty cycle <= 100%
### [SRS_05] Show the result [duty cycle/10] by UART (use TeraTerm Software to check data)
### [SRS_06] If button 3 is pressed, switch the PWM frequency value to another one (2KHz <-> 4KHz)
### [SRS_07] Right after changing the frequency value, make sure that the duty cycle is always 50%
### [SRS_08] Send the duty cycle value via CAN message with ID 0xA0 (Classic CAN) every second
### [SRS_09] If S32K144 receive CAN message with ID: 0xC0 and Data = 0x01, Stop generating PWM
### [SRS_10] If S32K144 receive CAN message with ID: 0xD0 and Data = 0x01, do [SRS_01]
