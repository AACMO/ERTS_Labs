# Laboratory session 3: Programming the ATmega328P in C with Eclipse

This exercise is devoted to understanding the basics of programming the Arduino Uno microcontroller (ATmega328P) using a professional IDE and via direct C programming code that will access to the direct hardware and MCU registers without using any built - in function given by Arduino IDE. The session will be focused on programming different timers and interrupts to read sensors and actuate over a computer fan via a PWM signal directly steering the register that contains the value of PWM to be imposed on the computer fan.  

## Initial requirements: 

To complete this laboratory session, it will be necessary to first of all install all necessary programs and dependencies listed below: 

1. AVR toolchain. To get all necessary libraries to work with the ATmega328P microcontroller. It can be downloaded from [here](https://www.microchip.com/en-us/development-tools-tools-and-software/gcc-compilers-avr-and-arm). It is only necessary to download file and copy files inside **C:\Program Files**. 
2. GNU Make. It is necessary to install this GNU compiler for Windows systems from [here](http://gnuwin32.sourceforge.net/packages/make.htm). Finally, launch the installer and accept the default location to install it at **C:\Program Files (x86)\GNUWin32**.
3. AVR programmer. To be able to download/upload and manage the MCU memory. It can be downloaded AVRDUDE from [here](http://fab.cba.mit.edu/classes/863.16/doc/projects/ftsmin/avrdude-win-64bit.zip). Once it is downloaded, just unzip the file and copy all the content at location **C:\Program Files**.
4. Eclipse. The IDE that will be used to program the different code solutions along the session. It can be downloaded from [here](https://www.eclipse.org/). Alternative to eclipse can be to download extension called *Platformio* from Visual Studio Code if this environment is already installed on the computer.
5. AVR plugin (Non-necessary if used on step 4 Visual Studio Code). Once Eclipse is installed on the computer, it is necessary to include on Eclipe the following URL in the field *Work with* inside the dialog menu *Help > Install New Software*: http://avr-eclipse.sourceforge.net/updatesite.

Once all this requirements are fulfilled, it will be necessary to give to Eclipse the path to all installed external tools for the program on the menu dialog *Window -> Preferences* and once within that window go to option *AVR -> Paths*. Give at that menu the path to the already installed AVR toolchain, GNU and AVRDUDE.

## Proposed exercises:

A set of 2 simple exercises have been proposed to start working with a MCU such that ATmega328P and understand how basic units such as timers and interrupts work on this microcontroller: 

### 1. Controlling a computer fan:

This exercise attempt to send a PWM signal controlled by timer 0 on ATmega328P to a computer fan on the range between 30 Hz - 300 kHz. The proposed solution sends this PWM signal with a frequency of 7.8 kHz according to timer 0 set up and it is changing the value of the PWM duty cycle for the signal every 1s according to specifications by increasing the PWM duty cycle 15 units. Then, every 17s there is an overflow on the signal and it starts again by 0 PWM duty cycle.
 
On this solution it is also used timer 1 to generate interrupts that triggers every 1s so that it can be changed the signal for the PWM duty cycle on every timer 1 interrupt and fulfil problem specifications. It cannot be used any of the built - in Arduino functions such that **_delay_ms()** for timing purposes.
 
The results of such exercise code are found on the following image:
 
![Demonstration exercise 1](/P3/Images/Ex3_Test_P1_PWM.jpg)
 
And a video with demo results can be found at repository [here](/P3/Videos/P3_Ex1_Demo.MOV)

### 2. Reading the ultrasonic sensor:

The second exercise is devoted to control the fan with the same PWM signal as used on [exercise 1](#1-controlling-a-computer-fan) but this time the PWM duty cicle is not increased every second a fixed step. Instead, the PWM duty cycle is adjusted constantly proportional to the reading of the ultrasonic sensor that is read with ICU from timer 1 every 100 ms. 

Moreover, the used ultrasonic sensor as described in Laboratory Session 1 works on the range from 2 cm to 400 cm. However, for this session it has been restricted the maximum distance to 150 cm so that if the sensor reading reaches this maximum distance the duty cycle for the PWM signal will be the maximum value (255). Hence the equation to set the PWM signal value according to measured sensor distance is as follows: 
      
<p align="center">
    <img src="Utils/Equation_duty_cycle.jpg" alt="Image" />
</p>
      
Where variable *timer_tick_period* is a constant of 4 $\mu s$ that depends on timer 1 configuration and defines the time between 2 consecutive ticks for that timer, the *diff_between_pulses* is the difference in timer ticks between the raising and falling edge of the ECHO signal from the sensor and *SENSOR_CONST* is the constant of 58 $\mu s$/cm defined in sensor datasheet for conversions. 

Next for the completion of this exercise, there are 3 interrupts enabled for timer 1 as follows: 
- **Output Compare Match A interrupt:** triggers every every 100 ms to start a new sensor ultrasonic sensor reading by setting TRIG pin on ultrasonic sensor to 1.
-  **Output Compare Match B interrupt:** Triggered 12 $\mu s$ after the Output Compare Match A has been triggered to reset TRIG pin on ultrasonic sensor to 0.
-  **Input Capture Unit interrupt:** To capture initially a raising edge on ECHO pin from ultrasonic sensor and then the falling edge of that pin so that it can be obtained the whole pulse duration that is proportional to distance from sensor to the obstacle. 
      
For timer 0 there is no interrupt configured on this approach since it is just used to generate the PWM signal according to measured distance from sensor.

The results of such solution code are found on the following image, where it can be seen that the PWM signal increases proportional to the measured distance from the sensor according to specifications (blue the measured distance, red the PWM value send to fan)
 
![Demonstration exercise 2](/P3/Images/Ex3_Test_P2_sensor.jpg)

And a video with demo results can be found at repository [here](/P3/Videos/P3_Ex2_Demo.mp4)