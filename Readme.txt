MEB SPI FLASH Demo
------------------

This demo is intended to display the onboard Audio Codec (WM8731) feature of the Multimedia Expansion Board. In this demo the usage is demonstrated along with the graphics library to display the Menu and the audio driver that reads a wav audio, stored as an array in the internal Flash.


*************************
1. Demo requirements
*************************

This demo requires the following Hardware

- Multimedia Expansion Board (DM320005)
- One of the following Starter Kits: 
   • PIC32MX USB Starter Kit II (DM320003-2) 
   • PIC32MX Ethernet Starter Kit (DM320004)


Note: This demo does not work with the PIC32MX General Purpose Starter Kit i.e. PIC32MX Starter Kit (DM320001).


*************************
2. Running the Demo:
*************************

To run the demo, 

1. Load the demo code into MPLAB by double clicking the desired *.mcp project file.

2. Plug-in the Starter Kit to MEB board. .

3. Connect the mini-B debugger port on-board the starter board to an USB port on the development computer using the USB cable provided in the kit.

4. Choose the PIC32 Starter Kit debugger tool in MPLAB IDE by selecting Debugger>Select Tool and then click on PIC32 Starter Kit. 

5. Build the project by selecting Project->Build All.

6. Download the code into the evaluation board microcontroller by selecting Debugger>Programming>Program All Memories.

7. Run the demo code by selecting Debugger>Run.

8. The Screen pops up with the Play button, Stop button, and a progress bar.

9. Press the Play button to begin. The progress bar updates with respect to the amount of audio data played.

10. The process repeats. 

11. To stop playing the audio, press the Stop button.

12. Repeat the step 9 to continue with the demo.



