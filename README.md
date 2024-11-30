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

    All data from where all these previous results are obtained can be found at **Utils** folder inside the Excel sheet called *Data_FanResponse.xlsx* where serial monitor output data from Arduino is analyzed. Finally, the response time for the system is determined to be as the settling time, which in average it has been stablished to be $t_{ss}$ at 98\% equal to $t_{ss} =1.33s$.

3. *Feedforward control:* On this exercise is proposed to control the computer fan speed directly using only a feedforward gain based on the equation found on previous exercise with the static curve relating the PWM value to be placed to achieve the desired fan speed. Then, on this exercise it is send via pin 3 (PD3) a PWM value that is adapted depending on a setpoint speed that varies every 10 s on the control loop between  the 2000 and 3000 rpm values and it is read on each control loop (every 50 ms) the speed of the sensor via pin 7 (PD7) using the F00 sensor information from the computer fan. 

    The results of this simple exercise can be found on the following snapshot from Arduino plotter that displays the setpoint speed against the read speed at each control loop, where it can be seen the response is quite satisfying, but the controller fails when reducing the steady state error since there is always a constant shift between the setpoint and the final speed value. 

    ![Demonstration fan speed Ex3](/P2/Images/Ex3_ff_test.jpg)

    And also the video demo with the results for this exercise can be found at repository [here](/P2/Videos/Ex3_ff_control_Demo.MOV).
   
4. *Feedforward + feedback control:* The following proposed exercise is based on the previous workflow described on exercise 3, but now it is added to the control scheme also a feedback control with only proportional gain that attempts to correct the error between the speed setpoint and the actual speed sensed from F00 sensor. 
   
    On this approach, the value of the **K** gain to use on the feedback control is set up experimentally by trial and error until a suitable value in terms of performance and stability is achieved.

    The results of this exercise can be found on the following snapshot from Arduino plotter that displays the setpoint speed against the read speed at each control loop, where it can be seen that the results obtained are better than the ones obtained with only the feedforward control since it sometimes exceeds the setpoint with some overshoot instead of remaining always behind the reference with a constant steady state error.

    ![Demonstration fan speed Ex4](/P2/Images/Ex4_ff+fb_test2.jpg)

    The video demo with the results for this exercise can be found at repository [here](/P2/Videos/Ex4_ff_fb_control_Demo.MOV).

5. *PID Control:* The last control algorithm proposed attempts to tackle the problems presented on exercise 3 and 4 by adding an integral and a derivative gain to the already proportional gain given. With this new scheme, this control action must be able to correct the constant steady state error on the previous approaches because there was no integral action to help correcting that. Apart from that, it is also removed the feedforward gain and it is only used the PID control to set up the control action.

    Then, on this proposed scheme, every 50 ms it is assessed if the setpoint needs to be changed from 2000 to 3000 rpms or the other way arround, the fan speed received from F00 sensor on pin 7 (PD7) is computed and the new control action *u* is found from error between setpoint and actual speed sensor. Finally, at the end of the control loop the new control action is sent to the computer fan via pin 3 (PD3) with the PWM signal. 

    The formula used to compute the discrete PID control action at each control loop is stated as follows: 

    ![PID formula](/P2/Images/PID_formula.jpg)

    Finally the results of this exercise can be found on the following snapshot from Arduino plotter that displays the setpoint speed against the read speed at each control loop, where it can be seen this controller outperforms approaches presented in exercises 3 and 4 because it allows to get a steady state error equal to 0 in average when reaching the end of the transient. 

    ![Demonstration PID control Ex5](/P2/Images/Ex5_PID_TEST_2.jpg)

    The video demo with the results for this exercise can be found at repository [here](/P2/Videos/Ex5_PID_control_Demo.MOV).

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

## Laboratory session 4: Programming Arduino Uno with FreeRTOS

This exercise is devoted to understanding the basics of programming the Arduino Uno microcontroller (ATmega328P) using a OS with its scheduler to split the code into modular tasks that can be executed at predetermined time intervals (or cycle times). This will lead to more modularity and portability for the code since this framework can be used on several architecture (called ports) that can use the same scheduler so it is not necessary to set up hardware registers on each device where this code will be used. On this case, it will be programmed using the well - known FreeRTOS framework and the session will be focused on testing small exercises to check the functionalities of this scheduler and how it deals with priorities and the situations in which resources are shared between the tasks. Finally, it will be necessary to solve a small exercise to programme a control loop over the computer fan speed with FreeRTOS.

### Initial requirements: 

It will be necessary to install FreeRTOS as a library into Arduino IDE. Then the session will be completed using all Arduino IDE environment but adding this feature regarding the FreeRTOS scheduler. To install follow these steps: 

- 1. Open Arduino IDE.
- 2. Go to menu ***"sketch ->Include Library->Manage Libraries..."***
- 3. Once inside the Library Manager, select *"Type"* as **Contributed** and *"Topic"* as **Timing** and then write **FreeRTOS** on the search bar.
- 4. Select the *FreeRTOS by Richard Barry* library from the options given and install it.
- 5. Once installed, on the sketch you want to use it just make an include as *#include <Arduino_FreeRTOS.h>*.

### Proposed examples:

First of all 2 small testing exercises with some questions are proposed to get started with FreeRTOS and get a better understanding about how it deals with tasks, timing, prioritization and resources. This small exercises are explained below: 

1. *Programming periodic tasks:* On this exercise it is programmed a simple task to blink a LED each 500 ms and another task to print on serial output the value of an analog read sensor. The exercise is initially prepared so that blinking task has more priority than serial output task and the output of the programme when executed can be seen below:

    ![Demonstration exercise 1](/P4/Images/P4_Example_1_nomod.jpg)

    Where it can be seen that both the blinking LED and the analog read shows some output and they are executed concurrently (one after the other) without conflicts. However, the exercise asked then to swap priorities and remove the delay on execution for task with serial output printing. These changes yield to a situation in which task for blinking LEDs is never executed since it has low priority and the serial output printing task do not have any delay so it is always ready to be executed after it is ended. 

    The video with demo results after doing these changes can be found at repository [here](/P4/Videos/P4_Exercise1_Demo_mod.mp4)

2. *Access to shared resources:* Here it is programmed a task in which there is a read to an analog input and a read to a digital input. Additionally, on each task it is send via serial output port the value of the read so both are accessing to the same shared resource as it is the serial port. Then, the initial approach considers this situation and contains a semaphore to avoid both task to access serial output at the same time and get a crash on the results and making one task wait when accessing to the serial output port until the first task finished working with it. The results of this initial situation are shown on the next image: 

    ![Demonstration exercise 2](/P4/Images/P4_Example_2_nomod.jpg)

    Where it can be seen that all works as expected and output is properly set for each task. However, the following changes are executed over this initial programme:

    - **Remove the line calling "xSemaphoreGive" inside one of the 2 tasks:** On this case, it has been removed the line on the task performing the digital read sensor. The result of this is that it is only executed one time the task for the digital read and no other task can be performed after that (not even the digital read task) because the semaphor has been taken by someone and never released after ending the first digital read task loop. Then, any task attempting to get the semaphore status will check that it is busy forever and all will be blocked without possibility to be executed. The results of these explanations can be shown at the following image presented: 

    ![Demonstration exercise 2-1](/P4/Images/P4_Example_2_mod_give_digitalread.jpg)

    - **Remove all lines regarding MUTEX in both tasks:** On this situation, both tasks will attempt to access to the same resource leading to a crash and non-desired outputs on serial port reads because both tasks will attempt to write on serial output and the outputs of each function there will be mixed. Therefore, on this case both tasks can be executed constantly and they are not blocked but the outputs are not as depicted in the initial programme code where everything was clear and separated by task. These results can be shown on the next image: 

    ![Demonstration exercise 2-2](/P4/Images/P4_Example_2_mod_all_smphr_lines.jpg)

    Where it can be seen that the output on terminal received from Arduino is unpredictable and changes constantly showing on each line random combinations of the serial output given by each task. Then, it is clear both tasks are trying to write information into the same resource and the problem appear.

### Proposed exercises:

Last, it is proposed the exercise in which it is necessary to programme a control loop for the computer fan speed using 3 different tasks to achieve this with different timings, but the priorities will be defined by the engineer programming the solution. The three tasks that are created as problem specifications are shown below: 

- **TaskSetpointGenerator:** This task will be executed each 10 s to change the setpoint of the control loop between 2000 and 3000 rpm constantly. It will have maximum priority (3) so that it will be executed when it is necessary above the other tasks to change the setpoint for next control loops.
  
- **TaskControlLoop:** This task will be executed each 100 ms to read the computer fan sensor F00 speed via pin 7 (PD7) and then compute the next control action (PWM duty cycle value) to send it via pin 3 (PD3) to the fan to control its speed based on the difference between the actual fan speed and the imposed setpoint. The controller selected to do this task is the one obtained in previous exercise 2 with the PID approach and all parameters tunned on that exercise will be used here to ensure the same performance is obtained on the control on this exercise. This task will have priority 2, so it will have less priority than first task presented, but it will have more priority than task 3 that is shown below

- **TaskSerialOutput:** This task will send via serial output each 200 ms the values of RPM sensed from computer fan F00 sensor and the actual setpoint for the fan speed. On this manner, it can be visualized the results for the control loop on the Arduino serial plotter. Additionally, this task will have the least priority (1), being the last to be executed when more than one task is in ready state for the scheduler.

The results of programming this architecture with these tasks and these priorities is shown on the following snapshot from Arduino plotter, where it is clear to check that control loop is performing as results presented in the PID control exercise for laboratory session 2. Therefore, it is clear it has been possible to obtain a modular code structure using the FreeRTOS scheduler that allows to respect the timings imposed and executes the tasks within given time constraints because the parameters for control loop are prepared for a sampling time of 100 ms and the performance in discrete - time is the same as in laboratory session 2.

![Demonstration exercise](/P4/Images/P4_Exercise_FreeRTOS_test.jpg)

And also the video demos with the results for this exercise can be found at repository [here](/P4/Videos/P4_Ex_Demo1.mp4) and [here](/P4/Videos/P4_Ex_Demo_2.mp4).

Finally, as additional request, it is necessary to ensure temporal correctness of the task where the control loop is performed (**TaskControlLoop**) to ensure it is executed each 100 ms because it is the most critical task here. 

For this reason, it has been used in all tasks the function *vTaskDelayUntil()* from FreeRTOS library to be sure each task is called after the defined number of ms on this function arguments instead of wait the defined number of ms from the moment the last function call is finished. The first approach will ensure (if the task computing time is less than the defined task cycle time) the time between task executions will be always the task cycle time defined meanwhile the latter will wait the defined task cycle time after the function call is finished, leading to unpredictable cycle time for the task and time between task executions because it will depend on the computing time for each function call. Then, the approach using function *vTaskDelayUntil()* is way more precise and suits better for the criticism of control loop task that is expected to be called each exactly 100 ms, but it is necessary to ensure the task 2 computing time is never exceeding the giving cycle time period (100 ms). Next, in Arduino it has been programmed with *micros()* function some variables to gather times when each task start and when each task ends and in task **TaskSerialOutput** it has been added to serial output these timing values for each loop so that they can be copied on a *.txt* file that can be processed into Excel to get statistical data for the computing time of control loop task. 

The conducted experiment is presented below:

- **Prepare output data for processing:**: It is added to serial output in Arduino a line that includes the following fields separated by ";" on the output: task 1 computing time, task 2 computing time, task 3 computing time, task 1 cycle time, task 2 cycle time and task 3 cycle time. This will be the study variables later on. 
- **Get data with Arduino during 5 minutes:** Ensures enough cycle times are executed and the worst cases scenario can be obtained. It is also obtained the data for fan speed and setpoint on the output as expected.
- **Store all data on *.txt* file:** This can be found inside folder **Utils** with name *Temporal_correctness_data_raw.txt* after removing all results obtained for rpm fan speed and setpoints on the otuput.
- **Process data to be exported to Excel:** The original file with all data is modified to be exported to Excel properly. This file is also inside folder **Utils** with name *Temporal_correctness_data.txt* and this is the one to insert into Excel to process data. Here decimal points has been substituted by commas and the separator between variables is changed from ";" to tabulator spaces.
- **Generation of Excel file:** Data is inserted here, computed the mean, standard deviation and interval of confidence for each study variable. Next it is found the histogram and the normal distribution for control loop task (**TaskControlLoop**) to obtain the appropriate results. This file is stored in folder **Utils** with name *Temporal_correctness_data.xlsx*. 

Then, from experiment done the following statistical results are shown for task 2 (control loop task) computing time and task cycle time:

| **Statistical feature**     | **Value - Computing time task 2** | **Value - Cycle time task 2** |
|-----------------------------|-----------------------------------|-------------------------------|
| Max value [ms]              | 86.850                            | 105.000                       |
| Min value [ms]              | 11.650                            | 95.000                        |
| Mean [ms]                   | 51.089                            | 99.009                        |
| Standard deviation          | 12.955                            | 0.319                         |
| Confidence interval (at 95%)| $51.089 \pm 0.4867$               | $99.009 \pm 0.012$            |


And these statistical results are also highlighted on the following plotted results where it can be examined in more detail how the computing times for task 2 are distributed for the experiment done.

![Demonstration exercise task2 temp correctness dist](/P4/Images/P4_Exercise_temp_correctness_dist.jpg)
![Demonstration exercise task2 temp correctness hist](/P4/Images/P4_Exercise_temp_correctness_hist.jpg)

Then, it is clear that the temporal correctness is ensured with precision and that task 2 will be executed without any problem at the specified cycle time. The deviation to 105 ms in some occasions as shown in the maximum value for the cycle time of task 2 might be caused by some timing inaccuracies with ticks on FreeRTOS because there is also some deviations to 95 ms in some occasions (shown by minimum value), but it has not been explored in depth. 