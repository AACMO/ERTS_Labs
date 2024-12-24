# Laboratory session 6: Programming the "Ball in Tube" system with MATLAB

This exercise is devoted to implement different control strategies using again the **"Ball in Tube"** system platform presented in [Laboratory session 5](/P5/README.md/#laboratory-session-5-programming-the-ball-in-tube-system-with-arduino-ide) but this time being programmed with model - based design techniques by using Simulink and MATLAB. This approach will ease the development and tuning of necessary parameters for every control strategy to be implemented because it allows to change online while the simulation is running those interesting parameters if properly prepared the system. 

Therefore, this model - based design approach is more flexible and focused on ease the tuning of parameters meanwhile reducing the overhead for the user when programming and implementing control strategies because the user does not need to know how to programme complex algorithms at all. The model - based design embed most of the programming task for the user on the blocks configuration so that it is only necessary to really design or create code for small custom tasks that are related with the particular solution created. Additionally, users can be focused more on the core of the control task and to understand what is wrong on the designed control to be improved since the hard part of programming task is dealt inside blocks configuration. Thus, the advantages of the Simulink modelling with blocks is clear, but it will need an extra effort to translate all created C++ code into blocks to obtain the same performances as previously obtained in [laboratory session 5](/P5/README.md/#laboratory-session-5-programming-the-ball-in-tube-system-with-arduino-ide). 

Hence, this exercise will attempt to replicate all controls done in [previous session](/P5/README.md/#laboratory-session-5-programming-the-ball-in-tube-system-with-arduino-ide) for the **"Ball in Tube"** system but now using this other approach to ensure it can be obtained the same results with this higher level programming language that is more user friendly. Finally, it must be noted that all pin configurations used on this session will be exactly the same as explained on [previous session](/P5/README.md/#laboratory-session-5-programming-the-ball-in-tube-system-with-arduino-ide) since the setup is the same, but the blocks in MATLAB will embed the pins configuration instead of being on the code.

## Initial requirements:

To complete this session, it will be necessary to first of all install all necessary programs and dependencies listed below: 

1. **MATLAB**. To get the framework where it will be all programed. If linked to an educational institution, you can download the program and check if you can have a student license from [here](https://login.mathworks.com/embedded-login/signin.html?cid=wdnl&uri=https%3A%2F%2Fes.mathworks.com%2Fdownloads%2F). It is only necessary to download file and click on the executable.
   
2. **MATLAB Support Package for Arduino**. This package allows you to program scripts directly in MATLAB that can be compiled and loaded on the Arduino target as it is done with Arduino IDE. It contains several functions that are specific for Arduino boards. Then, once MATLAB is installed, you will need to install this from the menu option *ADD-ONS->Get hardware support package* and look there for this package to be downloaded and installed
   
3. **Simulink Support Package for Arduino**. This package allows to program and create Simulink models using the built - in blocks from Arduino library that helps you setting up hardware and software configurations for the Arduino target to be programmed. Follow the same instructions as per the installation of the **MATLAB Support Package for Arduino** and download and install this Add-On from MATLAB menus. 

Once all this requirements are fulfilled, it will be necessary to reboot your computer before starting MATLAB with all complements added. 

## Proposed exercises:

A set of 3 exercises using the same 3 different control strategies as proposed in [laboratory session 5](/P5/README.md/#laboratory-session-5-programming-the-ball-in-tube-system-with-arduino-ide) will be solved here:

### 1. ON/OFF distance control:

Under the same assumptions as in previous [laboratory 5 session - ON/OFF Control exercise](/P5/README.md/#1-onoff-distance-control), it is first obtained PWM range in which the ball is within the tube slot part and the distance measured on each case by the ultrasonic sensor. The model created in Simulink for this part of the exercise is shown below.

![Model step 1-2 Ex1 P6](/P6/Images/Ex1_step1_2_sim_block.jpg)

Where the MATLAB function block called ***Sensor signal conditioner*** is implementing the translation of the ultrasonic sensor raw data distance measurement from the built-in Arduino block called ***Ultrasonic sensor output*** from meters to centimeters and it is also changed from the ultrasonic reference frame to the lowest tube slot part which is 30 cm from the ultrasonic sensor.

Next, the computer fan is controlled depending on the distance sensed by the *HCSR04* ultrasonic sensor placed on top of the tube to the distance of tha ball to the lowest part of the tube slot to be around 15 cm constantly. Then, an hysteresis control is programmed with 2 cm hysteresis step that contains just 2 basic states as explained in [laboratory 5 session - ON/OFF Control exercise](/P5/README.md/#1-onoff-distance-control). The model used to perform the last step of this exercise where the model is deployed is shown on next image

![Model step 3 Ex1 P6](/P6/Images/Ex1_step3_sim_block.jpg)

And the model results when running simulations over Arduino Uno target are presented on next image:

![Demonstration exercise 1](/P6/Images/P6_Ex1_ON_OFF_Demo.jpg)

Where from given results it is clear the system is able to behave as it was expected, shifting all the time between the ON and OFF states and with the distance measured for the ultrasonic sensor to be all the time around the setpoint of 15 cm given. However, despite being all the time shifting between states and changing the value of the distance sensor measurement, the dynamics is stable and the same performance as the one obtained in [laboratory 5 session - ON/OFF Control exercise](/P5/README.md/#1-onoff-distance-control) being programmed with C++ code in Arduino IDE is shown. 

The video demo with the results for this exercise can be found at repository [here](/P6/Videos/Ex1_ONOFF_Control_Demo.mp4).

### 2. Feedforward control:  

The first 2 steps to identify the system dynamics and the input - output static response are not done on this session because it is a assumed to be the same as presented in [laboratory 5 session - Feedforward Control exercise](/P5/README.md/#2-feedforward-control) because the system is the same and the tests to be done will replicate the same results. Then, the same lineal regression curve for the input - output static gain will be used on this exercise as the one obtained on previous session with the following equation: 

<p align="center">
    <img src="../P5/Utils/dist_equation.jpg" alt="Image" />
</p>

And then the following Simulink model is implemented to carry out the simulations with the 2 setpoint scenarios given on [laboratory 5 session - Feedforward Control exercise](/P5/README.md/#2-feedforward-control). 

![Model Ex2 P6](/P6/Images/Ex2_sim_block.jpg)

Where the MATLAB function called ***Feedforward_controller*** implements the linear regression given a setpoint to yield the PWM_Signal that must be sent to the system at any time to obtain the desired position of the ball. 

Then, testing this approach using the model implemented, it is obtained the following results presented in next images for both setpoints.

![Model Ex2 P6 results sp2010](/P6/Images/P6_Ex2_FeedForward_Demo_20_10.jpg)
![Model Ex2 P6 results sp2515](/P6/Images/P6_Ex2_FeedForward_Demo_25_15.jpg)

Where it can be seen the model sends PWM signals that are able to move the ball almost to the desired positions depending on the setpoints given, but there is some constant steady state error that cannot be fixed with this approach. Moreover, the errors are bigger when applying decremental PWM steps due to the fact of using only the lineal regression for the incremental steps, so the dynamics induced by the gravity when reducing the PWM value is not considered and thus the error is bigger going down with the ball. Then, the results obtained with this approach are the same as presented on [laboratory 5 session - Feedforward Control exercise](/P5/README.md/#2-feedforward-control).

Hence, from presented results, it is clear the need for another approach such as a P control or PI control to tackle the issues related with the constant steady state error. Nevertheless, the results for the feedforward control test can be seen at the video [here](/p6/Videos/Ex2_ff_control_sp2515_Demo.mp4) for the case of the setpoint between 25 and 15 cm.

### 3. Feedforward control + feedback control:

This is again proposed to tackle the problems presented on [Feedforward control section](#2-feedforward-control) specially and to ensure a setpoint is tracked without zero steady state error. However, on this section it will be used a discrete - time controller for the P and PI proposed using a Simulink block that contains all necessary setup for the PID controller. Again, despite the ease of the tuning with this model - based approach, it will not be used the derivative control action in any of the controllers. Additionally, the section is divided again in 2 steps modelling initially a simple P controller and next a PI controller. Note that, on this case, both gains must be tuned on each step because it is used a discrete - time controller instead of the continuous time used on [Laboratory session 5 - Feedforward control + feedback control exercise](/P5/README.md/#3-feedforward-control--feedback-control) and the control loop is executed each 100 ms on this case instead of every 50 ms as on [Laboratory session 5](/P5/README.md/#laboratory-session-5-programming-the-ball-in-tube-system-with-arduino-ide).

On this section it will be divided in 2 different steps, doing in the first one a simple P controller with a proportional action only and on a second step a PI controller with both the proportional and the integral control actions. On this manner, it can be both assessed and compared to ensure if it is necessary add at least an integral control action to reduce the error to 0 and its effect. The PID controller will not be designed since the trade - off between tuning effort and the performance improvement is really significant for the benefits it will have.

Consequently,the two setpoint scenarios given in [previous exercise](#2-feedforward-control) with the feedforward are tested with the 2 steps defined as follows.

#### P control: 

A simple proportional control gain has been tuned to add to the control action a factor that depends on the error between the actual sensor reading and the distance setpoint for the ping-pong ball. Thus, the new control action as a PWM value includes a continuous time P controller with the following equation: 

$$u[PWM]=feedforward_{action}+P_{action}(e(z))=0.2678\cdot PWM\_{Value}-19.128 + K_p\cdot e(z)$$

Where the gain $K_p$ must be tuned experimentally for the best performance and the variable $e(z)$ on the control action stands for the error between the actual distance setpoint and the ultrasonic sensor measured distance both with respect to the lowest part of the tube slot. 

Next, taking into consideration all these requirements, the model presented in the [feedforward exercise](#2-feedforward-control) is increased adding the PID control block and the error between actual setpoint and distance measurement for PID control.

![Model Ex3-P6 only P](/P6/Images/Ex3_sim_block_onlyP.jpg)

Hence, after tuning the $K_p$ parameter experimentally, leaving $K_i=0$ all the time and with a sample time of 100ms for the control loop, it is obtained an optimal $K_p=1.0$ for the proportional controller. Therefore, with this controller and control action shown, the presented results on the next image with respect to the setpoint between 25 - 15 cm to show the obtained control with this new feedforward and state feedback control approach.
      
![Demonstration ball distance Ex3-P6 setpoint 1](/P6/Images/P6_Ex3_FeedForward_PID_Ponly_20_10.jpg)
![Demonstration ball distance Ex3-P6 setpoint 2](/P6/Images/P6_Ex3_FeedForward_PID_Ponly_25_15.jpg)

From results it can be noted there is still some steady state error when applying decremental PWM values on the system meanwhile the system dynamics for the highest setpoint is adjusted properly with a small steady state error that in some cases is almost 0. This situation is due to the fact that the feedforward control has been created using only the input - output static response on the system when applying incremental PWM values, so that the gravity effect occurring on the decremental PWM values is not being into consideration obtaining errors on the output response. Hence, the same results as presented on [Laboratory 5 session - Feeforward + feedback control with P controller](/P5/README.md/#p-control) are obtained with this new methodology approach.

For this reason, the PI controller will be necessary to correct this permanent error on the steady state with the integral control effort.

Finally, the video demo with the results for this exercise can be found at repository [here](/P6/Videos/Ex3_ff_P_control_Demo.mp4) for the P control demonstration with model - based design using Simulink.

#### PI control: 

A controller using a proportional and integral control action must be tuned to add to the initial control the capability to track any given setpoint and converge to 0 steady state error if enough time is given to the system using the same discrete - time controller shown in the P control with a sampling time of 100ms, but this time it will be tuned online the parameters $K_p$ and $K_i$ for this control action. This controller must be also able to correct at least the error induced by constant disturbances such as the obstruction with the hand of the lowest part of the tube slot behind the ping-pong ball. Thus, all this situations will be checked on this section considering the new control action as a PWM value that includes both a continuous time PI controller and a feedforward gain with the following equation:

$$u[PWM]=feedforward_{action}+PI_{action}(e(z))=0.2678\cdot PWM\_{Value}-19.128 + (K_p+K_i\cdot T_s \frac{1}{z-1})e(z) $$

Where again the gains $K_p$ and $K_i$ must be tuned experimentally for the best performance and the variable $e(z)$ on the control action stands for the error between the actual distance setpoint and the ultrasonic sensor measured distance both with respect to the lowest part of the tube slot. Moreover, to replicate the same behavior as designed on the code for the accumulated error in the integral action effort, to avoid accumulating big errors the Integrator saturation will be saturated on the upper and lower bounds considering the maximum distance for the tube slot on the system (30 cm from the ultrasonic sensor) as follows:

- Upper bound for **Integrator saturation**:  Integrator saturation $\leq5\cdot$ MAX_DIST
- Lower bound for **Integrator saturation**:  Integrator saturation $\geq-3\cdot$ MAX_DIST

With MAX_DIST = 30 cm, which is the maximum distance between the ultrasonic sensor and the ping-pong ball to be within the tube slot. Note that the limits are in accordance with the ones programmed on [Laboratory 5 session PI control](/P5/README.md/#pi-control) section. Finally, these settings can be changed inside the PID control block added in the ***Saturation*** setting after ticking the **Limit Output** inside the *Integrator Saturation* option. 

Hence, after tuning the $K_p$ and $K_i$ parameters experimentally and with a sample time of 100ms for the control loop, it is obtained an optimal $K_p=1.0$ and $K_i=0.8$ for the PI controller proposed. The resulting Simulink model after tuning parameters is shown below on next image.

![Model Ex3-2 P6](/P6/Images/Ex3_sim_block_PI.jpg)

Consequently, with this controller and control action used, the presented results on the next images with respect to the both setpoint scenarios between 20 - 10 and between 25 - 15 cm to show the obtained control with this new feedforward and state feedback control approach using a PI action.

![Demonstration ball distance Ex3-PI setpoint 1](/P6/Images/P6_Ex3_FeedForward_PID_20_10_nodist.jpg)
![Demonstration ball distance Ex3-PI setpoint 2](/P6/Images/P6_Ex3_FeedForward_PID_25_15_nodist.jpg)

From results it is clear now the system is able to track any given setpoint with zero steady state error in both given setpoint scenarios, despite having some noise on the ultrasonic sensor distance measurement. Then, the same results are obtained as in [Laboratory 5 session PI control](/P5/README.md/#pi-control) section since it is able to track any given setpoint in any of the two given situations as shown on previous images. The steady state error from previous controls is reduced to 0 with this approach after the tuning of the P and I parameters without being too much reactive against sensor's noise.

Last, it is also checked the performance of the PI controller when the lowest part of the tube is obstructed with the hand, adding some disturbance on the system in both scenarios and in both setpoints for each scenarios. The results presented on the following images yield that the controller designed is also able converge to 0 steady state error if enough time is given with the same reference despite adding constant disturbances as the ones commented. Thus, the control is robust against this type of disturbances added as expected, having really similar results in both scenarions as the ones obtained in proposed [Laboratory 5 session PI controller](/P5/README.md/#pi-control) section.

![Demonstration ball distance Ex3-2 P6 PI_dist setpoint 1](/P6/Images/P6_Ex3_FeedForward_PID_20_10_dist.jpg)
![Demonstration ball distance Ex3-2 P6 PI_dist setpoint 2](/P6/Images/P6_Ex3_FeedForward_PID_25_15_dist.jpg)

The video demo with the results for this exercise can be found at repository [here](/P6/Videos/Ex3_ff_PI_control_Demo.mp4) for the PI demonstration with without disturbances for only a given setpoint, since it has been demonstrated it is valid for both scenarios.