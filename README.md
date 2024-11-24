# ERTS_Labs 

This repository contains the code, videos, schematics, images, and the project related to the Master's course on Embedded and Real Time Systems (ERTS) offered at UPC-ETSEIB. The course explores the fundamental concepts and methodologies to be used in embedded real time systems to achieve applications and solutions running on the edge in real time. Additionally, the course also covers basics about C programming and microcontrollers and offers insights about how Arduino UNO platform works.

The repository includes implementations and solutions developed in Arduino sketches for the different proposed exercises along the laboratory sessions as well as the code for the development of the final course project. 

To execute the proposed code on Arduino platform, please download last version of Arduino IDE environment: [Download Last Arduino IDE version](https://www.arduino.cc/en/software)

To get purchased an Arduino UNO where to execute all the code implemented, please go to this Arduino webpage: [Buy Arduino Uno Rev3](https://store.arduino.cc/products/arduino-uno-rev3?queryID=undefined)

## Repository folder structure:

The repository has the basic structure as follows: 
```
  - 1 folder for each lab session: Where each folder has the structure presented on the tree coming with this point
      |
      |
      |__ __ Schematics: Contains the electric layout to the solution of each exercise and how it is interfacing Arduino UNO.
      |
      |
      |__ __ Images: Where some of them are proving how the solution is working.
      |
      |
      |__ __ Videos: Showing how the different solutions are working while the code is executed.
      |
      |
      |__ __ Code: Where it is placed all the code used for each exercise proposed on the lab session. It has a folder for each sketch where each sketch represents the solution of an exercise
      |
      |
      |__ __ Utils: Where it is placed additional files used on the practice development such as MATLAB files or Excel files.

  - Datasheet folder: Here it is stored all different datasheets for the different elements used during the laboratory sessions, including Arduino UNO documentation.
```
## Laboratory session 1: Introduction to Arduino 

This exercise is devoted to get familiarized with Arduino IDE platform to execute and create sketches as well as to get in touch with Arduino UNO. Then, a set of 4 exercises are proposed to start working with Arduino:

1. *Reading an ultrasonic distance sensor:* On this exercise is connected an ultrasonic sensor to Arduino UNO and, after set a request to sensor, it must be possible to read the pulse width received from the sensor via a digital input and convert into the sensed distance the sensor is perceiving. It has an optional approach to obtain this distance without using the Arduino function *pulseIn()*.

2. *Reading a linear temperature sensor:* Here Arduino UNO is connected to an LM35 linear temperature sensor from where its sensed temperature is received via an analog input and converted to temperature using formula from manufacturer.

3. *Reading a non-linear infrared distance sensor:* On the exercise Arduino UNO is connected to an infrared sensor with a characteristic curve that is non-linear. Then, 2 different methods are created to compute the equation to use to convert the voltage value given by the sensor to the equivalent distance and both are implemented on the code. The result of both methods does not differ so any method might be valid. The equations of the different curves used to convert the voltage to distance are on the Excel called "InterpData" placed inside the **Utils** folder.

4. *Controlling a computer fan with a PWM signal:* On the exercise Arduino UNO is connected to a computer fan on its control signal pin so that a PWM output from Arduino will steer the speed of the fan. The *analogWrite()* function is used to change the PWM control signal value sent to the computer fan. Additionally, there is an optional approach where it is also obtained the speed from the computer fan from its internal F00 codified as a pulse in micro-seconds.

## Laboratory session 2: Basic Control Strategies

This exercise is devoted to test some standard and well - known control strategies on Arduino Uno platform to control the computer fan. Then, a set of 5 exercises are proposed to check these controls and make a comparison between them:

1. *ON/OFF temperature control*
2. *Characterization of fan response*
3. *Feedforward control*
4. *Feedforward + feedback control*
5. *PID Control*

## Laboratory session 3: Programming the ATmega328P in C with Eclipse

This exercise is devoted to understanding the basics of programming the Arduino Uno microcontroller (ATmega328P) using a professional IDE and via direct C programming code that will access to the direct hardware and MCU registers without using any built - in function given by Arduino IDE. The session will be focused on programming different timers and interrupts to read sensors and actuate over a computer fan via a PWM signal directly steering the register that contains the value of PWM to be imposed on the computer fan.  

# Initial requirements: 

To complete this laboratory session, it will be necessary to first of all install all necessary programs and dependencies listed below: 

1. AVR toolchain. To get all necessary libraries to work with the ATmega328P microcontroller. It can be downloaded from [here](https://www.microchip.com/en-us/development-tools-tools-and-software/gcc-compilers-avr-and-arm.
arm). It is only necessary to download file and copy files inside **C:\Program Files**. 
2. GNU Make. It is necessary to install this GNU compiler for Windows systems from [here](http://gnuwin32.sourceforge.net/packages/make.htm). Finally, launch the installer and accept the default location to install it at **C:\Program Files (x86)\GNUWin32**.
3. AVR programmer. To be able to download/upload and manage the MCU memory. It can be downloaded AVRDUDE from [here](http://fab.cba.mit.edu/classes/863.16/doc/projects/ftsmin/avrdude-win-64bit.zip). Once it is downloaded, just unzip the file and copy all the content at location **C:\Program Files**.
4. Eclipse. The IDE that will be used to program the different code solutions along the session. It can be downloaded from [here](https://www.eclipse.org/). Alternative to eclipse can be to download extension called *Platformio* from Visual Studio Code if this environment is already installed on the computer.
5. AVR plugin (Non-necessary if used on step 4 Visual Studio Code). Once Eclipse is installed on the computer, it is necessary to include on Eclipe the following URL in the field *Work with* inside the dialog menu *Help > Install New Software*: http://avr-eclipse.sourceforge.net/updatesite.

Once all this requirements are fulfilled, it will be necessary to give to Eclipse the path to all installed external tools for the program on the menu dialog *Window -> Preferences* and once within that window go to option *AVR -> Paths*. Give at that menu the path to the already installed AVR toolchain, GNU and AVRDUDE.

# Proposed exercises:

A set of 2 simple exercises have been proposed to start working with a MCU such that ATmega328P and understand how basic units such as timers and interrupts work on this microcontroller: 

1. *Controlling a computer fan:*  This exercise attempt to send a PWM signal controlled by timer 0 on ATmega328P to a computer fan on the range between 30 Hz - 300 kHz. The proposed solution sends this PWM signal with a frequency of 7.8 kHz according to timer 0 set up and it is changing the value of the PWM duty cycle for the signal every 1s according to specifications by increasing the PWM duty cycle 15 units. Then, every 17s there is an overflow on the signal and it starts again by 0 PWM duty cycle.
 
 On this solution it is also used timer 1 to generate interrupts that triggers every 1s so that it can be changed the signal for the PWM duty cycle on every timer 1 interrupt and fulfil problem specifications. It cannot be used any of the built - in Arduino functions such that **_delay_ms()** for timing purposes.
 
 The results of such exercise code are found on the following image:
 
 ![Demonstration exercise 1](/P3/Images/Ex3_Test_P1_PWM.jpg)
 
 And a video with demo results can be found at repository [here](/P3/Videos/P3_Ex2_Demo.mp4)

2. *Reading the ultrasonic sensor:* The second exercise is devoted to control 