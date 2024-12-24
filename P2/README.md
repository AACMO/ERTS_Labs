# Laboratory session 2: Basic Control Strategies

On this exercise it will be explored in detail the testing of some standard and well - known control strategies on Arduino Uno platform to control a computer fan. Then, the set of 5 exercises proposed to be solved to check these controls and make a comparison between them are presented below:

## 1. ON/OFF temperature control:

The computer fan is controlled depending on the temperature sensed by the *LM35* temperature sensor with to control temperature to be around 25 ºC constantly. Then, an hysteresis control is programmed with 1ºC hysteresis step that contains just 2 basic states as follows: 

- **The computer fan is ON:** When temperature sensed by *LM35* is over 26 ºC (25 ºC + the hysteresis step). At this control state the PWM duty cycle signal sent to the fan is constantly set to a value of 200 through pin PD3 (Arduino Uno pin 3). This value of PWM is really high, so it seems to drive the fan almost at maximum speed and for this reason it can be understood as ON state for the fan. 

- **The computer fan is OFF:** When the temperature sensed by *LM35* is under 24 ºC (25 ºC + the hysteresis step). At this control state the PWM duty cycle signal sent to the fan is constantly set to a value of 25 through pin PD3 (Arduino Uno pin 3). This value of PWM is too small to activate the computer fan and for this reason it can be understood as OFF state for the fan. 

On this program sensor value is read through analog pin in Arduino Uno at pin 16 (pin PC2) and the conversion given on datasheet is done to convert the digital value obtained directly to temperature in degrees Celsius.

The Arduino plotter snapshot with results for this exercise is found below for the triggering of the OFF state and for the triggering of the ON state for the PWM fan with this control respectively. It can be seen that it appropriately reacts against temperature sensor reading from *LM35* and works as expected.

![Demonstration exercise 1 ON](/P2/Images/Ex1_tst1.jpg)
![Demonstration exercise 1 OFF](/P2/Images/Ex1_tst2.jpg)

The video demo with the results for this exercise can be found at repository [here](/P2/Videos/Ex1_ONOFF_Demo.MOV).
 
## 2. Characterization of fan response: 

On this exercise is aimed to determine the fan response against the PWM input signal given from the Arduino Uno controller through pin 3 (PD3). Therefore, it is willing to determine the input - output static and dynamic response of the computer fan when a PWM input signal is sent and it is read the fan speed in rpms for every PWM input signal placed. For that purpose, 5 steps are programmed where the PWM value is increased by a value of 50 units so that it reaches value 250 at the end of the last step. Therefore, to get the appropriate data it is waited between each step 5 seconds so that enough samples are gathered every 50 ms on each step with the defined PWM value and to allow the speed of the computer fan to be stabilized on each step appropriately.
  
Additionally, through pin 7 (pin PD7) it is obtained the measurement of the speed signal from the F00 sensor inside the computer fan and both the PWM value and the read speed signal from the computer fan sensor are output through serial monitor every 50 ms to gather all data and post - process it properly later on. All output serial monitor data has been captured on a *txt* file called *Ex2_Fan_Response.txt* stored in **Utils** folder. The results for the steps imposed to the computer fan are presented on the following image:

![Demonstration step response Ex2](/P2/Images/Ex2_test_sysidentification.jpg)

Where it can be seen from results that timings are appropriately adjusted and a step response is presented.

Finally, all data gathered is opened on an Excel and it is able to obtain the following results shown on the following snapshots for the temporal static and dynamic system  response respectively: 

![Static response fan](/P2/Images/Ex2_static.png)
![Dynamic response fan](/P2/Images/Ex2_temp_response.png)
    
And from given previous static response it has been possible to determine experimentally the static curve that relates the value of PWM to be input to the system to achieve a desired speed as follows: 

<p align="center">
    <img src="Utils/Equation_des_speed.jpg" alt="Image" />
</p>
    
All data from where all these previous results are obtained can be found at **Utils** folder inside the Excel sheet called *Data_FanResponse.xlsx* where serial monitor output data from Arduino is analyzed. Finally, the response time for the system is determined to be as the settling time, which in average it has been stablished to be $t_{ss}$ at 98\% equal to $t_{ss} =1.33s$.

## 3. Feedforward control: 

On this exercise is proposed to control the computer fan speed directly using only a feedforward gain based on the equation found on [System Identification section](#2-characterization-of-fan-response) with the static curve relating the PWM value to be placed to achieve the desired fan speed. Then, on this exercise it is send via pin 3 (PD3) a PWM value that is adapted depending on a setpoint speed that varies every 10 s on the control loop between  the 2000 and 3000 rpm values and it is read on each control loop (every 50 ms) the speed of the sensor via pin 7 (PD7) using the F00 sensor information from the computer fan.

The results of this simple solution can be found on the following snapshot from Arduino plotter that displays the setpoint speed against the read speed at each control loop, where it can be seen the response is quite satisfying, but the controller fails when reducing the steady state error since there is always a constant shift between the setpoint and the final speed value. 

![Demonstration fan speed Ex3](/P2/Images/Ex3_ff_test.jpg)

And also the video demo with the results for this exercise can be found at repository [here](/P2/Videos/Ex3_ff_control_Demo.MOV).
   
## 4. Feedforward + feedback control:

The following proposed exercise is based on the previous workflow described on [feedforward exercise](#3-feedforward-control), but now it is added to the control scheme also a feedback control with only proportional gain that attempts to correct the error between the speed setpoint and the actual speed sensed from F00 sensor. 
   
On this approach, the value of the **K** gain to use on the feedback control is set up experimentally by trial and error until a suitable value in terms of performance and stability is achieved.

The results of this proposed approach can be found on the following snapshot from Arduino plotter that displays the setpoint speed against the read speed at each control loop, where it can be seen that the results obtained are better than the ones obtained with only the feedforward control since it sometimes exceeds the setpoint with some overshoot instead of remaining always behind the reference with a constant steady state error.

![Demonstration fan speed Ex4](/P2/Images/Ex4_ff+fb_test2.jpg)

The video demo with the results for this solution can be found at repository [here](/P2/Videos/Ex4_ff_fb_control_Demo.MOV).

## 5. PID Control: 

The last control algorithm proposed attempts to tackle the problems presented on [feedforward exercise](#3-feedforward-control) and [feedforward+feedback exercise](#4-feedforward--feedback-control) by adding an integral and a derivative gain to the already proportional gain given. With this new scheme, this control action must be able to correct the constant steady state error on the previous approaches because there was no integral action to help correcting that. Apart from that, it is also removed the feedforward gain and it is only used the PID control to set up the control action.

Then, on this proposed scheme, every 50 ms it is assessed if the setpoint needs to be changed from 2000 to 3000 rpms or the other way arround, the fan speed received from F00 sensor on pin 7 (PD7) is computed and the new control action *u* is found from error between setpoint and actual speed sensor. Finally, at the end of the control loop the new control action is sent to the computer fan via pin 3 (PD3) with the PWM signal. 

The formula used to compute the discrete PID control action at each control loop is stated as follows: 

![PID formula](/P2/Images/PID_formula.jpg)

Finally the results of this method can be found on the following snapshot from Arduino plotter that displays the setpoint speed against the read speed at each control loop, where it can be seen this controller outperforms approaches presented in [feedforward exercise](#3-feedforward-control) and [feedforward+feedback exercise](#4-feedforward--feedback-control) because it allows to get a steady state error equal to 0 in average when reaching the end of the transient. 

![Demonstration PID control Ex5](/P2/Images/Ex5_PID_TEST_2.jpg)

The video demo with the results for this solution can be found at repository [here](/P2/Videos/Ex5_PID_control_Demo.MOV).