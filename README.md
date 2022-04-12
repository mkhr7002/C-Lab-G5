# MTRX2700 Assignment 2

### Group5

<p>Name:<br>
<ol>
	<li>Marco Jara Blanco - SID</li>
	<li>Mary Khreich - 500505898</li>
  	<li>Jack Lunn - SID</li>
	<li>Zhanbo Zhu	   - 490035735</li>

### Exercise 1


**Modular Design**

<p>
This is partly a foundational model with the result of reading from serial being essential to exercise 2 and 3. The writing to serial module is also fairly foundational as it can also be used in exercise 2 and 3. Reading from serial is primarily conducted by interrupts after the ports have been initialised for read (a default of sorts as the bits required for writing to serial are set prior to doing so). Writing to serial is mostly contained into the ISR (after sending the first character) which then calls the writeSerial function.
</p>

**Instructions for User**

<p>

When the program runs, "Initalisation Successful" will be displayed to the terminal. A user may then type a command (of size < 50) and press enter when the command is done. If the command is invalid, "invalid command" will be displayed to the terminal. If the command is valid, the program will output "Request Accepted" and conduct the appropriate command in hardware. Whilst this is being done, the user may not type anything. Once the request has been completed, the program will output "Ready to receive new input" to the terminal. Anything that is inputted into the terminal during the time between "Request Accepted" and "Ready to receive new input" will not be acted upon, so a user may not input anything during this time.

</p>
  
  
**Discussion Points**

<p>

- The data is buffered using a global array which is continually overwritten with each completed input. The limits to this have to do with the buffer size of the array which limits how long an instruction can be. This limit can be increased by increasing the value of SERIAL_BUFFER in "functions.h".
- The time taken to service the interrupt is dependent on the time to perform the desired task. The actual time taken in terms of handling data to the point of conducting the command is extremely small (nearly negligible).
	
</p>

	

### Exercise 2


**Modular Design**
<p>
Design a method to receive information from user input. Trigger actions with received user input
First define the information to be output corresponding to the received information
Then determine the first character of the buffer after that output the result that should be output
When the end of output is detected, reset the register of SCI0CR2
</p>

**Instructions for User**
<p>
Output Invalid command when user input is not l or m
When user input is l, output LED, it means that the LED is being controlled
When user input is m output play music that means that music should be played
Every time a message is outputed, program will detect whether the output is completed
</p>


**Discussion Points**

<p>
	
 - Use more if statement to test
	
 - If the number is too big or the character is not a number
</p>

### Exercise 3

<p>  Exercise 3 has been separated into its own modular function within the processSerialPort() function. The function uses the rawData character input obtained by writing to the serial port, where each character represents either the length or pitch of a tune in alternating order. The function begins by calculating the number of clock cycles it will take to play the tune and sending an information message to the serial port. 

The length and tune of the song is created by implementing recursive delay functions. The tune delay creates different pitches by toggling the speaker on and off at different speeds. The time delay makes the tunes last for different lengths of time, dictated by the character.  Note that when there is a space in the character string, this is considered as a tune of 0 pitch and thus, created periods with silence. This has been implemented by disabling the speaker for the space character.
</p>
