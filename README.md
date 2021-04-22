# NEC IR transmission protocol
## Transmitter
Transmitter generating a carrier frequency on PORTD5 (IR emitter):
* 30kHz  
* 36kHz  
* 38kHz  
* 40kHz  
* 56kHz  

One pulse length is 562.5 uS  
Logic zero is a pulse of 562.5 uS then one 562.5 uS space. total transmit: 1125 uS  
Logic one is a pulse of 562.5 uS then one 1687.5 uS space. total transmit: 2250 uS  

### Data
* Sends a 16 * pulse length (9 ms) burst.
* A space of 8 * pulse length (4.5 ms).
* 1 byte address (LSB)
* 1 byte inverted address (LSB)
* 1 byte data (LSB)
* 1 byte inverted data (LSB)
* one pulse length burst (562.5 uS) indicating end of transmit

## Receiver 
Receives data on PIND2 (TSOP48xx)  
Decodes the data, checks if data is valid and sends it to UART (38400 baud).  
Saves the data byte in array for later use.  
If CR received, sending array to UART and clearing it.  