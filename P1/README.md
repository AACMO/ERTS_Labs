# Laboratory session 1: Introduction to Arduino 

The exercises to be solved to fulfill the objective of getting started with Arduino IDE platform are solved below presenting several results for each of them. It must be considered that an Arduino UNO board is used all the time to perform all exercises.

## 1. Reading an ultrasonic distance sensor:

On this exercise is connected an ultrasonic sensor to Arduino UNO and, after set a request to sensor, it must be possible to read the pulse width received from the sensor via a digital input and convert into the sensed distance the sensor is perceiving. It has an optional approach to obtain this distance without using the Arduino function *pulseIn()*.

The Arduino plotter snapshot with results for this exercise is found below:

![Demonstration exercise 1](/P1/Images/Ex1_sensor_read.jpg)

The video demo with the results for this exercise can be found at repository [here](/P1/Videos/Ex1_UltraSound_Test2.mp4) and [here](/P1/Videos/Ex1_UltraSound_Test2.mp4). 

## 2. Reading a linear temperature sensor:

Here Arduino UNO is connected to an LM35 linear temperature sensor from where its sensed temperature is received via an analog input and converted to temperature using formula from manufacturer.

The Arduino plotter snapshot with results for this exercise is found below:

![Demonstration exercise 2](/P1/Images/Ex2_TempSensor_Read.jpg)

The video demo with the results for this exercise can be found at repository [here](/P1/Videos/Ex2_LM35_Test.MOV).

## 3. Reading a non-linear infrared distance sensor:

On the exercise Arduino UNO is connected to an infrared sensor with a characteristic curve that is non-linear. Then, 2 different methods are created to compute the equation to use to convert the voltage value given by the sensor to the equivalent distance and both are implemented on the code. The result of both methods does not differ so any method might be valid. The equations of the different curves used to convert the voltage to distance are on the Excel called *"InterpData"* placed inside the **Utils** folder.

The Arduino plotter snapshot with results for this exercise is found below:

![Demonstration exercise 3](/P1/Images/Ex3_Infrared_Read.jpg)

The video demo with the results for this exercise can be found at repository [here](/P1/Videos/Ex3_Infrared_Test.MOV).

# 4. Controlling a computer fan with a PWM signal: 

On the exercise Arduino UNO is connected to a computer fan on its control signal pin so that a PWM output from Arduino will steer the speed of the fan. The *analogWrite()* function is used to change the PWM control signal value sent to the computer fan. Additionally, there is an optional approach where it is also obtained the speed from the computer fan from its internal F00 codified as a pulse in micro-seconds.

The Arduino plotter snapshot with results for the basic exercise is found below:

![Demonstration exercise 4 basic](/P1/Images/Ex4_Fan_PWM.jpg)

And the results for the optional exercise are found on next image:

![Demonstration exercise 4 optional](/P1/Images/Ex4_Fan_Optional.jpg)

The video demo with the results for the basic exercise solution can be found at repository [here](/P1/Videos/Ex4_FanBasic_Test.MOV) and for the optional part it can be found [here](/P1/Videos/Ex4_FanOptional_Test.MOV)