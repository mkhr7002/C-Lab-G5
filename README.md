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

<p> 123
</p>
	
<p>
123
</p>

**Instructions for User**

<p>
123
</p>
  
  
**Discussion Points**

<p>
123
</p>

	

### Exercise 2


**Modular Design**
<p>123</p>

**Instructions for User**
<p>123 </p>


**Discussion Points**

<p>
123
</p>

### Exercise 3

<p>  Exercise 3 has been separated into its own modular function within the processSerialPort() function. The function uses the rawData character input obtained by writing to the serial port, where each character represents either the length or pitch of a tune in alternating order. The function begins by calculating the number of clock cycles it will take to play the tune and sending an information message to the serial port. 

The length and tune of the song is created by implementing recursive delay functions. The tune delay creates different pitches by toggling the speaker on and off at different speeds. The time delay makes the tunes last for different lengths of time, dictated by the character.  Note that when there is a space in the character string, this is considered as a tune of 0 pitch and thus, created periods with silence. This has been implemented by disabling the speaker for the space character.
</p>
