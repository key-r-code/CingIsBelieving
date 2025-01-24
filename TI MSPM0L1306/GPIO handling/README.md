## Notes

GPIO pins - General Purpose Input Ouput pins

Control individual pins on the microcontroller for digital input/output.

Digital signals can have only 2 states, HIGH (3.3V/5V) or LOW (0V/Ground).

GPIO pins can be:

    * Output - code control voltage 

        * Set HIGH - Pin outputs 3.3 V
        * Set LOW  - Pin outputs 0 V
    * Input - Pin reads external voltage
    
        * Reads HIGH when voltage is 3.3 V
        * Reads LOW when voltage is 0 V

*Pull-up/down resistors*

GPIO input pins not connected to anything picks up random noise, drifting unpredicatably between HIGH and LOW. This is where pull up/down resistors come in play. They provide a default, stable state. 

Pull-up resistor   -- Keeps pin at HIGH until actively pulled LOW

Pull-down resistor -- Keeps pin at LOW until actively pulled HIGH

