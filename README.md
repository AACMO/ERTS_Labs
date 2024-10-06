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

![Ex1_UltraSound_Test.mp4](Videos/Ex1_UltraSound_Test.mp4)

1. *Reading a linear temperature sensor:* Here Arduino UNO is connected to an LM35 linear temperature sensor from where its sensed temperature is received via an analog input and converted to temperature using formula from manufacturer.

2. *Reading a non-linear infrared distance sensor:* On the exercise Arduino UNO is connected to an infrared sensor with a characteristic curve that is non-linear. Then, 2 different methods are created to compute the equation to use to convert the voltage value given by the sensor to the equivalent distance and both are implemented on the code. The result of both methods does not differ so any method might be valid. The equations of the different curves used to convert the voltage to distance are on the Excel called "InterpData" placed inside the **Utils** folder.

3. *Controlling a computer fan with a PWM signal:* On the exercise Arduino UNO is connected to a computer fan on its control signal pin so that a PWM output from Arduino will steer the speed of the fan. The *analogWrite()* function is used to change the PWM control signal value sent to the computer fan. Additionally, there is an optional approach where it is also obtained the speed from the computer fan from its internal F00 codified as a pulse in micro-seconds.
