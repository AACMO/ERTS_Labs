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

1. **Reading an ultrasonic distance sensor:** On this exercise is connected an ultrasonic sensor to Arduino UNO and, after set a request to sensor, it must be possible to read the pulse width received from the sensor.

2. **Reading a linear temperature sensor:** Here Arduino UNO is connected to an LM35 linear temperature sensor from where its sensed temperature is received.

3. **Reading a non-linear infrared distance sensor:** On the exercise Arduino UNO is connected to an infrared sensor with a characteristic curve that is non-linear. 

4. **Controlling a computer fan with a PWM signal:** On the exercise Arduino UNO is connected to a computer fan on its control signal pin so that a PWM output from Arduino.

Further details about this session resolution can be found at [Laboratory session 1 page](/P1/README.md/#laboratory-session-1-introduction-to-arduino).

## Laboratory session 2: Basic Control Strategies

This exercise is devoted to test some standard and well - known control strategies on Arduino Uno platform to control the computer fan. Then, a set of 5 exercises are proposed to check these controls and make a comparison between them:

1. **ON/OFF temperature control:** The computer fan is controlled depending on the temperature sensed by the *LM35* temperature sensor with to control temperature to be around 25 ºC constantly.
 
2. **Characterization of fan response:** On this exercise is aimed to determine the fan response against the PWM input signal given from the Arduino Uno controller through pin 3 (PD3). Therefore, it is willing to determine the input - output static and dynamic response of the computer fan when a PWM input signal is sent and it is read the fan speed in rpms for every PWM input signal placed.

3. **Feedforward control:** On this solution is proposed to control the computer fan speed directly using only a feedforward gain based on the equation found on previous exercise 2 with the static curve relating the PWM value to be placed to achieve the desired fan speed.
   
4. **Feedforward + feedback control:** The following proposed exercise is based on the previous workflow described on exercise 3, but now it is added to the control scheme also a feedback control with only proportional gain that attempts to correct the error between the speed setpoint and the actual speed sensed from F00 sensor.

5. **PID Control:** The last control algorithm proposed attempts to tackle the problems presented on exercise 3 and 4 by adding an integral and a derivative gain to the already proportional gain given. With this new scheme, this control action must be able to correct the constant steady state error on the previous approaches.

Further details about this session resolution can be found at [Laboratory session 2 page](/P2/README.md/#laboratory-session-2-basic-control-strategies).

## Laboratory session 3: Programming the ATmega328P in C with Eclipse

This exercise is devoted to understanding the basics of programming the Arduino Uno microcontroller (ATmega328P) using a professional IDE and via direct C programming code that will access to the direct hardware and MCU registers without using any built - in function given by Arduino IDE. Hence, there must be solved 2 exercises listed below:

1. **Controlling a computer fan:**  This exercise attempt to send a PWM signal controlled by timer 0 on ATmega328P to a computer fan on the range between 30 Hz - 300 kHz to steer its speed being increased each second by 15 PWM value steps.

2. **Reading the ultrasonic sensor:** The second exercise is devoted to control the fan with the same PWM signal as used on exercise 1 but this time the PWM duty cicle is not increased every second a fixed step. Instead, the PWM duty cycle is adjusted constantly proportional to the reading of the ultrasonic sensor that is read with ICU from timer 1 every 100 ms. 

Further details about this session resolution can be found at [Laboratory session 3 page](/P3/README.md/#laboratory-session-3-programming-the-atmega328p-in-c-with-eclipse).

## Laboratory session 4: Programming Arduino Uno with FreeRTOS

This exercise is focused on the programming of the Arduino Uno microcontroller using an OS with the scheduler to have more modular code split into tasks that can be easily exported to other MCUs. The tasks will be executed at defined time intervals using the well - known FreeRTOS framework and the session will explore two small examples to test some scheduling features and a final exercise where it must be programmed a control loop task with FreeRTOS to check its time correctness and the feasibility of such methodology for a critical periodic task that needs to be executed each defined time period to obtain good performance.

### Proposed examples:

This small exercises are introduced below: 

1. **Programming periodic tasks:** On this exercise it is programmed a simple task to blink a LED each 500 ms and another task to print on serial output the value of an analog read sensor. It must be explored how tasks will deal with priorities when some situations occur with the 2 programmed task. 

2. **Access to shared resources:** Here it is programmed a task in which there is a read to an analog input and a read to a digital input. Additionally, on each task it is send via serial output port the value of the read so both are accessing to the same shared resource as it is the serial port. Then, it must be explored how tasks deal with shared resources if it is not properly implemented the control of shared resource.

### Proposed exercise:

It is proposed to solve a control loop using any of the control strategies implemented in the [Laboratory session 2](#laboratory-session-2-basic-control-strategies) to steer the speed of the computer fan to selected setpoints. However, this control loop must have 3 tasks according to problem statement specifications to test the feasibility of programme everything with FreeRTOS after giving some priorities to each task. Along the exercise it will be checked the performance of the control strategy implemented as well as the temporal correctness of the control loop task to ensure it is executed every defined timing period (100ms) and that the computation time of the task is never exceeding that periodicity even in the worst case scenario. 

Further details about this session resolution can be found at [Laboratory session 4 page](/P4/README.md/#laboratory-session-4-programming-arduino-uno-with-freertos).

## Laboratory session 5: Programming the "Ball in Tube" system with Arduino IDE

This exercise is devoted to implement different control strategies using the **"Ball in Tube"** system platform. This platform is an experimental prototype where a ping-pong ball is inside a methacrylate tube with a fan on the bottom and an ultrasonic distance measurement sensor on top so that it is aimed to place the ping-pong ball always within a distance from the lowest part of a slot placed on the tube. Therefore, the different control strategies will be tried to control in the best manner the system dynamics so that the ball is placed on a given setpoint:

1. **ON/OFF distance control:** It is first obtained PWM range in which the ball is within the tube slot part and the distance measured on each case by the ultrasonic sensor. Next, the computer fan is controlled using an ON/OFF control approach depending on the distance sensed by the *HCSR04* ultrasonic sensor placed on top of the tube to be around 15 cm from the lowest part of the tube slot.
  
2. **Feedforward control:** On this exercise it is proposed first to characterize the input - output static and the dynamic responses for the system and then implement with the input - output static response obtained a feedforward control using any regression method (linear on this case) to approximate the input - output static gain and have an initial basic control approach valid for all the PWM range of values and distances within the tube slot.

3. **Feedforward control + feedback control:** The last control algorithm proposed attempts to tackle the problems presented on exercise 2 specially and to ensure a setpoint is tracked without zero steady state error. However, on this section it will be divided in 2 different steps, doing in the first one a simple P controller with a proportional action only and on a second step a PI controller with both the proportional and the integral control actions. Additionally, for the PI controller it will be assessed its robustness to reject constant disturbances by obstructing the lowest part of the tube slot. 

Further details about this session resolution can be found at [Laboratory session 5 page](/P5/README.md/#laboratory-session-5-programming-the-ball-in-tube-system-with-arduino-ide).

## Laboratory session 6: Programming the "Ball in Tube" system with MATLAB

This exercise is devoted to implement different control strategies using again the **"Ball in Tube"** system platform presented in [Laboratory session 5](#laboratory-session-5-programming-the-ball-in-tube-system-with-arduino-ide) but this time being programmed with model - based design techniques by using Simulink and MATLAB. This approach will ease the development and tuning of necessary parameters for every control strategy to be implemented because it allows to change online while the simulation is running those interesting parameters if properly prepared the system. The model - based design is more flexible and allows to the user to be focused on the system control design problem rather than also deal with programming issues that could arise during the coding solution. 

Then, this practical session will attempt to solve the same 3 control strategy problems with the same **"Ball in Tube"** system presented in [Laboratory session 5](#laboratory-session-5-programming-the-ball-in-tube-system-with-arduino-ide) and it will be assessed the results of each of them with MATLAB and compared with the initial results obtained with Arduino IDE and the C++ code implemented.

Further details about this session resolution can be found at [Laboratory session 6 page](/P6/README.md/#laboratory-session-6-programming-the-ball-in-tube-system-with-matlab).