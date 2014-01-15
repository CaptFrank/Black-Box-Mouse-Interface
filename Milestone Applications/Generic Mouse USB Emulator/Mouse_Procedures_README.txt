#########################################################################################
#
#	This is the first milestone that was reached in terms of modifying and proving that
#	the Arduino Mega ADK rev3 is able to act as a Generic USB device. 
#		
#	In particular, this is a readme on how the Arduino Mega ADK was programmed in order 
#	enumerate as a USB joystick, and how to run a simulation of a joystick on an
#	Arduino Mega ADK.
#
#	by: Francis Papineau
#########################################################################################

	Files needed:
	
		NOTE: The Joystick tester application that was used in a Mac OS X application
		called Joystick and Gamepad Tester available on sourceforge for free 
		(Open Source).
		
		Link: http://download.cnet.com/Joystick-and-Gamepad-Tester
							/3000-18490_4-48273.html
		
		###############################################################

		Arduino Mega ADK (Atmega2560) Arduino Sketch needed:
		
		File name: mouse_usb_demo.ino
		Link: http://hunt.net.nz/users/darran/
							weblog/15f92/attachments/f1534/big_joystick_demo.ino
							
		###############################################################

		Atmega8U2 firmware file needed:
		
		File name: ./CLASS_MOUSE1/Debug/CLASS_MOUSE1.hex
							
	Procedure:
	
		1) Flash the Arduino bootloader on the arduino (Atmega2560), using the AVR MKII and
		the Arduino Atmega2560 using the ISP programmer plug.
		
		2) Flash the firmware file using the arduino suite. 
		(File name: mouse_usb_demo.ino)
						
		3) Flash the Atmega8U2 using the AVR MKII and the ISP for the Atmega8U2.
		(File name:./CLASS_MOUSE1/Debug/CLASS_MOUSE1.hex)

		Command: avrdude -p atmega16u2 -F -P usb -c avrispmkii -U flash:w:CLASS_MOUSE1.hex -U lfuse:w:0xFF:m -U hfuse:w:0xD9:m -U efuse:w:0xF4:m -U lock:w:0x0F:m
		
		4) Unplug and plug back the arduino on the computer.
			- this allows for reenumeration and rebooting of the arduino.
		
		5) Test the application using the test application listed above.
		
		
		To customize:
		
			Open the cproject in atmel studio,
				- customize, 
				- Upload ../Arduino-usbserial.hex using
					- Command: avrdude -p atmega16u2 -F -P usb -c avrispmkii -U flash:w:Arduino-usbserial.hex -U lfuse:w:0xFF:m -U hfuse:w:0xD9:m -U efuse:w:0xF4:m -U lock:w:0x0F:m
				- Upload the new Arduino code using the Arduino suite
				- upload the customized firmware with AVR MKII ISP (Atmega16U2), 
		
		