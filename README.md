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

     The Arduino plotter snapshot with results for this exercise is found below:

     ![Demonstration exercise 1](/P1/Images/Ex1_sensor_read.jpg)

     The video demo with the results for this exercise can be found at repository [here](/P1/Videos/Ex1_UltraSound_Test2.mp4) and [here](/P1/Videos/Ex1_UltraSound_Test2.mp4). 

2. *Reading a linear temperature sensor:* Here Arduino UNO is connected to an LM35 linear temperature sensor from where its sensed temperature is received via an analog input and converted to temperature using formula from manufacturer.

     The Arduino plotter snapshot with results for this exercise is found below:

     ![Demonstration exercise 2](/P1/Images/Ex2_TempSensor_Read.jpg)

     The video demo with the results for this exercise can be found at repository [here](/P1/Videos/Ex2_LM35_Test.MOV).

3. *Reading a non-linear infrared distance sensor:* On the exercise Arduino UNO is connected to an infrared sensor with a characteristic curve that is non-linear. Then, 2 different methods are created to compute the equation to use to convert the voltage value given by the sensor to the equivalent distance and both are implemented on the code. The result of both methods does not differ so any method might be valid. The equations of the different curves used to convert the voltage to distance are on the Excel called *"InterpData"* placed inside the **Utils** folder.

     The Arduino plotter snapshot with results for this exercise is found below:

     ![Demonstration exercise 3](/P1/Images/Ex3_Infrared_Read.jpg)

     The video demo with the results for this exercise can be found at repository [here](/P1/Videos/Ex3_Infrared_Test.MOV).

4. *Controlling a computer fan with a PWM signal:* On the exercise Arduino UNO is connected to a computer fan on its control signal pin so that a PWM output from Arduino will steer the speed of the fan. The *analogWrite()* function is used to change the PWM control signal value sent to the computer fan. Additionally, there is an optional approach where it is also obtained the speed from the computer fan from its internal F00 codified as a pulse in micro-seconds.

     The Arduino plotter snapshot with results for the basic exercise is found below:

     ![Demonstration exercise 4 basic](/P1/Images/Ex4_Fan_PWM.jpg)

     And the results for the optional exercise are found on next image:

     ![Demonstration exercise 4 optional](/P1/Images/Ex4_Fan_Optional.jpg)

     The video demo with the results for the basic exercise solution can be found at repository [here](/P1/Videos/Ex4_FanBasic_Test.MOV) and for the optional part it can be found [here](/P1/Videos/Ex4_FanOptional_Test.MOV)

## Laboratory session 2: Basic Control Strategies

This exercise is devoted to test some standard and well - known control strategies on Arduino Uno platform to control the computer fan. Then, a set of 5 exercises are proposed to check these controls and make a comparison between them:

1. *ON/OFF temperature control:* The computer fan is controlled depending on the temperature sensed by the *LM35* temperature sensor with to control temperature to be around 25 ºC constantly. Then, an hysteresis control is programmed with 1ºC hysteresis step that contains just 2 basic states as follows: 
    - **The computer fan is ON:** When temperature sensed by *LM35* is over 26 ºC (25 ºC + the hysteresis step). At this control state the PWM duty cycle signal sent to the fan is constantly set to a value of 200 through pin PD3 (Arduino Uno pin 3). This value of PWM is really high, so it seems to drive the fan almost at maximum speed and for this reason it can be understood as ON state for the fan. 
    - **The computer fan is OFF:** When the temperature sensed by *LM35* is under 24 ºC (25 ºC + the hysteresis step). At this control state the PWM duty cycle signal sent to the fan is constantly set to a value of 25 through pin PD3 (Arduino Uno pin 3). This value of PWM is too small to activate the computer fan and for this reason it can be understood as OFF state for the fan. 

    On this program sensor value is read through analog pin in Arduino Uno at pin 16 (pin PC2) and the conversion given on datasheet is done to convert the digital value obtained directly to temperature in degrees Celsius.

    The Arduino plotter snapshot with results for this exercise is found below for the triggering of the OFF state and for the triggering of the ON state for the PWM fan with this control respectively. It can be seen that it appropriately reacts against temperature sensor reading from *LM35* and works as expected.

    ![Demonstration exercise 1 ON](/P2/Images/Ex1_tst1.jpg)
    ![Demonstration exercise 1 OFF](/P2/Images/Ex1_tst2.jpg)

    The video demo with the results for this exercise can be found at repository [here](/P2/Videos/Ex1_ONOFF_Demo.MOV).
 
2. *Characterization of fan response:* On this exercise is aimed to determine the fan response against the PWM input signal given from the Arduino Uno controller through pin 3 (PD3). Therefore, it is willing to determine the input - output static and dynamic response of the computer fan when a PWM input signal is sent and it is read the fan speed in rpms for every PWM input signal placed. For that purpose, 5 steps are programmed where the PWM value is increased by a value of 50 units so that it reaches value 250 at the end of the last step. Therefore, to get the appropriate data it is waited between each step 5 seconds so that enough samples are gathered every 50 ms on each step with the defined PWM value and to allow the speed of the computer fan to be stabilized on each step appropriately.
  
    Additionally, through pin 7 (pin PD7) it is obtained the measurement of the speed signal from the F00 sensor inside the computer fan and both the PWM value and the read speed signal from the computer fan sensor are output through serial monitor every 50 ms to gather all data and post - process it properly later on. All output serial monitor data has been captured on a *txt* file called *Ex2_Fan_Response.txt* stored in **Utils** folder. The results for the steps imposed to the computer fan are presented on the following image:

    ![Demonstration step response Ex2](/P2/Images/Ex2_test_sysidentification.jpg)

    Where it can be seen from results that timings are appropriately adjusted and a step response is presented.

    Finally, all data gathered is opened on an Excel and it is able to obtain the following results shown on the following snapshots for the temporal static and dynamic system  response respectively: 

    ![Static response fan](/P2/Images/Ex2_static.png)
    ![Dynamic response fan](/P2/Images/Ex2_temp_response.png)
    
    And from given previous static response it has been possible to determine experimentally the static curve that relates the value of PWM to be input to the system to achieve a desired speed as follows: 

    <p align="center">
      <img src="P2/Utils/Equation_des_speed.jpg" alt="Image" />
    </p>

    All data from where all these previous results are obtained can be found at **Utils** folder inside the Excel sheet called *Data_FanResponse.xlsx* where serial monitor output data from Arduino is analyzed. Finally, the response time for the system is determined to be as the settling time, which in average it has been stablished to be $t_{ss}@98\% = 1.33s$

3. *Feedforward control:*
4. *Feedforward + feedback control*
5. *PID Control*

## Laboratory session 3: Programming the ATmega328P in C with Eclipse

This exercise is devoted to understanding the basics of programming the Arduino Uno microcontroller (ATmega328P) using a professional IDE and via direct C programming code that will access to the direct hardware and MCU registers without using any built - in function given by Arduino IDE. The session will be focused on programming different timers and interrupts to read sensors and actuate over a computer fan via a PWM signal directly steering the register that contains the value of PWM to be imposed on the computer fan.  

### Initial requirements: 

To complete this laboratory session, it will be necessary to first of all install all necessary programs and dependencies listed below: 

1. AVR toolchain. To get all necessary libraries to work with the ATmega328P microcontroller. It can be downloaded from [here](https://www.microchip.com/en-us/development-tools-tools-and-software/gcc-compilers-avr-and-arm). It is only necessary to download file and copy files inside **C:\Program Files**. 
2. GNU Make. It is necessary to install this GNU compiler for Windows systems from [here](http://gnuwin32.sourceforge.net/packages/make.htm). Finally, launch the installer and accept the default location to install it at **C:\Program Files (x86)\GNUWin32**.
3. AVR programmer. To be able to download/upload and manage the MCU memory. It can be downloaded AVRDUDE from [here](http://fab.cba.mit.edu/classes/863.16/doc/projects/ftsmin/avrdude-win-64bit.zip). Once it is downloaded, just unzip the file and copy all the content at location **C:\Program Files**.
4. Eclipse. The IDE that will be used to program the different code solutions along the session. It can be downloaded from [here](https://www.eclipse.org/). Alternative to eclipse can be to download extension called *Platformio* from Visual Studio Code if this environment is already installed on the computer.
5. AVR plugin (Non-necessary if used on step 4 Visual Studio Code). Once Eclipse is installed on the computer, it is necessary to include on Eclipe the following URL in the field *Work with* inside the dialog menu *Help > Install New Software*: http://avr-eclipse.sourceforge.net/updatesite.

Once all this requirements are fulfilled, it will be necessary to give to Eclipse the path to all installed external tools for the program on the menu dialog *Window -> Preferences* and once within that window go to option *AVR -> Paths*. Give at that menu the path to the already installed AVR toolchain, GNU and AVRDUDE.

### Proposed exercises:

A set of 2 simple exercises have been proposed to start working with a MCU such that ATmega328P and understand how basic units such as timers and interrupts work on this microcontroller: 

1. *Controlling a computer fan:*  This exercise attempt to send a PWM signal controlled by timer 0 on ATmega328P to a computer fan on the range between 30 Hz - 300 kHz. The proposed solution sends this PWM signal with a frequency of 7.8 kHz according to timer 0 set up and it is changing the value of the PWM duty cycle for the signal every 1s according to specifications by increasing the PWM duty cycle 15 units. Then, every 17s there is an overflow on the signal and it starts again by 0 PWM duty cycle.
 
      On this solution it is also used timer 1 to generate interrupts that triggers every 1s so that it can be changed the signal for the PWM duty cycle on every timer 1 interrupt and fulfil problem specifications. It cannot be used any of the built - in Arduino functions such that **_delay_ms()** for timing purposes.
 
      The results of such exercise code are found on the following image:
 
      ![Demonstration exercise 1](/P3/Images/Ex3_Test_P1_PWM.jpg)
 
      And a video with demo results can be found at repository [here](/P3/Videos/P3_Ex1_Demo.MOV)

2. *Reading the ultrasonic sensor:* The second exercise is devoted to control the fan with the same PWM signal as used on exercise 1 but this time the PWM duty cicle is not increased every second a fixed step. Instead, the PWM duty cycle is adjusted constantly proportional to the reading of the ultrasonic sensor that is read with ICU from timer 1 every 100 ms. 

      Moreover, the used ultrasonic sensor as described in Laboratory Session 1 works on the range from 2 cm to 400 cm. However, for this session it has been restricted the maximum distance to 150 cm so that if the sensor reading reaches this maximum distance the duty cycle for the PWM signal will be the maximum value (255). Hence the equation to set the PWM signal value according to measured sensor distance is as follows: 
      
      <p align="center">
        <img src="P3/Utils/Equation_duty_cycle.jpg" alt="Image" />
      </p>
      
      Where variable *timer_tick_period* is a constant of 4 $\mu s$ that depends on timer 1 configuration and defines the time between 2 consecutive ticks for that timer, the *diff_between_pulses* is the difference in timer ticks between the raising and falling edge of the ECHO signal from the sensor and *SENSOR_CONST* is the constant of 58 $\mu s$/cm defined in sensor datasheet for conversions. 

      Next for the completion of this exercise, there are 3 interrupts enabled for timer 1 as follows: 
      - **Output Compare Match A interrupt:** triggers every every 100 ms to start a new sensor ultrasonic sensor reading by setting TRIG pin on ultrasonic sensor to 1.
      -  **Output Compare Match B interrupt:** Triggered 12 $\mu s$ after the Output Compare Match A has been triggered to reset TRIG pin on ultrasonic sensor to 0.
      -  **Input Capture Unit interrupt:** To capture initially a raising edge on ECHO pin from ultrasonic sensor and then the falling edge of that pin so that it can be obtained the whole pulse duration that is proportional to distance from sensor to the obstacle. 
      
      For timer 0 there is no interrupt configured on this exercise since it is just used to generate the PWM signal according to measured distance from sensor.

      The results of such exercise code are found on the following image, where it can be seen that the PWM signal increases proportional to the measured distance from the sensor according to specifications (blue the measured distance, red the PWM value send to fan)
 
      ![Demonstration exercise 2](/P3/Images/Ex3_Test_P2_sensor.jpg)

      And a video with demo results can be found at repository [here](/P3/Videos/P3_Ex2_Demo.mp4)