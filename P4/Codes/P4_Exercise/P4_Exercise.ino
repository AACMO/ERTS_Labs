// EMBEDDED AND REAL-TIME SYSTEMS - LABORATORY L4
// Alejandro Acosta, Ivan Barrachina and Victor Escribano
// Exercise : Implement a feedback loop to the computer fan with FreeRTOS

#include <Arduino_FreeRTOS.h>

// Start all definitions for necessary defines
#define PIN_PWM      3                      // Pin to send a trigger to the sensor
#define PIN_RPM      7                      // Pin to read the F00 speed sensor output 
#define TOTAL_PULSES 4                      // Define the total of pulses to be sensed from sensor to count the speed value
#define PULSE_TIMO   25000                  // Define the time to wait to have a pulse from sensor with a falling edge (25000 us) 
#define MAX_PWM_VAL  250                    // Maximum PWM value allowed to be sent to fan with PWM signal
#define MAX_UNS_LONG 4294967295             // Maximum value an unsigned long element can have in Arduino
#define MAX_TOTAL_READS 5                   // Maximum time it will attempt to read the sensor in case a reading is failing and some value was previously stored on pulse_val
#define TASK_1_PERIOD 10000                 // Time in ms defined for periodic execution of task 1
#define TASK_2_PERIOD 100                   // Time in ms defined for periodic execution of task 2
#define TASK_3_PERIOD 200                   // Time in ms defined for periodic execution of task 3

// Start all global variables definition related with task timing
unsigned long t1_1=0;                       // Variable to store the time at which task 1 execution starts on each loop
unsigned long t2_1=0;                       // Variable to store the time at which task 1 execution ends on each loop
unsigned long t1_2=0;                       // Variable to store the time at which task 2 execution starts on each loop
unsigned long t2_2=0;                       // Variable to store the time at which task 2 execution ends on each loop
unsigned long t1_3=0;                       // Variable to store the time at which task 3 execution starts on each loop
unsigned long t2_3=0;                       // Variable to store the time at which task 3 execution ends on each loop      
unsigned long t1_ant1=0;                    // Variable to store the time at which task 1 started last execution to use it on next loop
unsigned long t1_ant2=0;                    // Variable to store the time at which task 2 started last execution to use it on next loop
unsigned long t1_ant3=0;                    // Variable to store the time at which task 3 started last execution to use it on next loop
float t1_cycle=0;                           // Variable to store the cycle time for the execution of task 1 (measured time between executions)
float t2_cycle=0;                           // Variable to store the cycle time for the execution of task 2 (measured time between executions)
float t3_cycle=0;                           // Variable to store the cycle time for the execution of task 3 (measured time between executions)

// Start all global variables definition related with control 
uint16_t rpm_val=2000;                      // Variable to give rpm setpoint to the fan in term of rpms
float meas_vel=0.0;                         // Variable to store the calculated rpm from sensor value
float K=0.08;                               // Proportional constant for the PID controller
float Ti=1.8;                               // Integral constant for the PID controller
float Td=0.012;                             // Derivative constant for the PID controller
float Ts=0.1;                               // Sampling time for the PID controller and all control loop

// define the 3 tasks for the scheduler 
void TaskSetpointGenerator( void *pvParameters );
void TaskControlLoop( void *pvParameters );
void TaskSerialOutput( void *pvParameters );

// Define other functions necessary for the code
float PID_Update (float error, float error_ant[2], float control_ant);

//-------
// setup
//-------
void setup()
{

  // Set up the digital pin to read F00 sensor as digital input with pull-up enabled.
  pinMode(PIN_RPM,INPUT_PULLUP);
  // Initialize serial output
  Serial.begin(9600);

  // Now set all tasks to run independently.
  xTaskCreate(TaskSetpointGenerator,
              "SetpointGenerator", 
              128,
              NULL, 
              3, // Highest priority
              NULL 
              );

  xTaskCreate(TaskControlLoop,
             "ControlLoop", 
             128, // Stack size
             NULL, 
             2, // Medium Priority
             NULL 
             );

  xTaskCreate(TaskSerialOutput,
             "SerialOutput", 
             128, // Stack size
             NULL, 
             1, // Lowest Priority
             NULL 
             );

  // Now the Task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

//------
// loop
//------
void loop()
{
  // Empty. Things are done in Tasks.
}

//-------------------------------------
// first task: generating a RPM setpoint each 10 s
//-------------------------------------
void TaskSetpointGenerator( void *pvParameters __attribute__((unused)) )
{ 
  // Define variables related with periodic execution of the task
  TickType_t xLastWakeTime_Task1 = xTaskGetTickCount();
  const TickType_t TimeIncTask1 = TASK_1_PERIOD/portTICK_PERIOD_MS;
  
  // Start infinite loop for the task
  for (;;) 
  { 
    // Get the time at start of the task
    t1_1 = micros(); 
    
    // Change setpoint every time it is entered between 2000 and 3000 rpm
    if(rpm_val == 3000){rpm_val=2000;}
    else {rpm_val=3000;}

    // Get the time at the end of the task
    t2_1 = micros(); 
    // Compute elapsed time since last task execution and store the actual initial task 1 as the previous value
    t1_cycle = (t1_1-t1_ant1)/1000; t1_ant1 = t1_1;
    
    // Delay for 10 s for next change
    vTaskDelayUntil(&xLastWakeTime_Task1,TimeIncTask1); 
  }
}

//--------------------------------------
// second task: Execute the control loop with given setpoint and new speed value
//--------------------------------------
void TaskControlLoop( void *pvParameters __attribute__((unused)) )
{
  // Define all local task variables
  static uint8_t pwm_val=0;                 // Variable to store the pulse width to send to fan
  static uint8_t pulse_counts=0;            // Define variable to count pulses read so far on loop
  static uint8_t read_retries=0;            // Define variable to count the times a false read from sensor will be attempted to be read
  static unsigned long pulse_val=0;         // Variable to store the received measure from the sensor
  static float err_fb = 0.0;                // Variable to store the error for the feedback control
  static float cont_err[2];                 // Variable to store the previous control errors for PID control
  static float prev_cont;                   // Variable to store the previous control action for PID control
  static float u=0.0;                       // Variable to store the control action to be imposed as PWM signal value

  // Define variables related with periodic execution of the task
  TickType_t xLastWakeTime_Task2 = xTaskGetTickCount();
  const TickType_t TimeIncTask2 = TASK_2_PERIOD/portTICK_PERIOD_MS;
    
  // Start infinite loop for the task
  for (;;)
  {
    // Get the time at start of the task
    t1_2 = micros();
    
    // Read the pulse width value from the speed sensor output and convert it
    while(pulse_counts!=TOTAL_PULSES && read_retries != MAX_TOTAL_READS)
    {
      unsigned long pulse_got=0;
      
      // Wait for a read from rpm sensor from the fan
      pulse_got=pulseIn(PIN_RPM,HIGH,PULSE_TIMO);

      // A read has been done properly from sensor
      if (pulse_got != 0)
      { 
        // Check if still no other measure was assigned to this variable
        if (pulse_val == MAX_UNS_LONG)
        {
          // Set it to 0
          pulse_val=0;
        }
        // Add new value sensed
        pulse_val+=pulse_got;
        // Increase the number of counts done 
        pulse_counts++;
      }
      // No read has been received after timeout reached
      else 
      { 
        // Check if pulse val was still the maximum (no value assigned yet) because there is no movement
        if (pulse_val == MAX_UNS_LONG && meas_vel == 0.0)
        {
          // Increase the number of counts done, fan is not moving possibly
          pulse_counts++;
        }
        // Increase the counter for the retries
        else{read_retries++;}
      }
    }

    // Get the value in rpms from obtained sensor value
    if(pulse_val != MAX_UNS_LONG)
    {
      // Check if it has not reached the maximum number of readings before ending necessary counts
      if (read_retries != MAX_TOTAL_READS)
      {
        // Get measured value in RPMS properly
        meas_vel=(float)((60*1000000.0/pulse_val)); 
      }
      // Maximum reached, find the speed computing an average of only one pulse 
      else
      { 
        meas_vel=(float)((60*1000000.0/((4.0*pulse_val/pulse_counts))));
      }
      // Set the variable to get time of each pulse and the retries counter to 0 again
      pulse_val=MAX_UNS_LONG;
    }
    else {meas_vel=0;}

    // Set the counter of pulses and the retries at 0 after all computations
    pulse_counts=0;
    read_retries=0;

    // Compute actual error feedback based on last measurement and the actual setpoint
    err_fb = (rpm_val - meas_vel);

    // Compute the next pwm value based on rpm setpoint and computed curve
    u=PID_Update(err_fb,cont_err,prev_cont);
    // Check if u is within PWM signal bound afterwards
    if (u<0.0){u=0.0;}
    else if (u>MAX_PWM_VAL){u=MAX_PWM_VAL;}
    else if (isnan(u)){u=MAX_PWM_VAL/2.0;}
    else{}

    // Send the PWM control signal after converting to uint8_t
    pwm_val = (uint8_t)(u);
    analogWrite(PIN_PWM, pwm_val);

    // Update errors and last control action on the system before next loop
    cont_err[1] = cont_err[0];
    cont_err[0] = err_fb;
    prev_cont = u;
    
    // Get the time at the end of the task
    t2_2 = micros(); 
    // Compute elapsed time since last task execution and store the actual initial task 1 as the previous value
    t2_cycle = (t1_2-t1_ant2)/1000; t1_ant2 = t1_2;
    
    // Delay for 100 ms for next control loop
    vTaskDelayUntil(&xLastWakeTime_Task2,TimeIncTask2); 
  }
}

//-------------------------------------
// third task: output on serial monitor actual setpoint and measured speed
//-------------------------------------
void TaskSerialOutput( void *pvParameters __attribute__((unused)) )
{  
  // Define variables related with periodic execution of the task
  TickType_t xLastWakeTime_Task3 = xTaskGetTickCount();
  const TickType_t TimeIncTask3 = TASK_3_PERIOD/portTICK_PERIOD_MS;
  
  // Start infinite loop for the task
  for (;;)
  { 
    // Get time at the end of the task
    t1_3 = micros();
    
    // Change setpoint every time it is entered between 2000 and 3000 rpm
    Serial.print("rpm_setpoint:");Serial.print(rpm_val);Serial.print(",");Serial.print("meas_speed[rpm]:");Serial.println(meas_vel);  
    
    // Get the time at the end of the task
    t2_3 = micros(); 
    // Compute elapsed time since last task execution and store the actual initial task 1 as the previous value
    t3_cycle = (t1_3-t1_ant3)/1000; t1_ant3 = t1_3;
    
    // Print for data collection
    //Serial.print((float)(t2_1-t1_1)/1000);Serial.print(",");Serial.print((float)(t2_2-t1_2)/1000);Serial.print(",");Serial.print((float)(t2_3-t1_3)/1000);Serial.print(",");Serial.print(t1_cycle);Serial.print(",");Serial.print(t2_cycle);Serial.print(",");Serial.println(t3_cycle);
    
    // Delay for 200 ms for next serial output
    vTaskDelayUntil(&xLastWakeTime_Task3,TimeIncTask3); 
  }
}

// Start defining all additional functions necessary for the code
// Definition of the control gain to use on next loop
float PID_Update (float error, float error_ant[2], float control_ant)
{
  float a1,a2,a3,control;

  // Compute components for the control action values
  a1 = K*(1+Ts/Ti+Td/Ts);
  a2 = K*(-1-2*Td/Ts);
  a3 = K*Td/Ts;

  // Get the new control action based on components computed
  control = control_ant+a1*error+a2*error_ant[0]+a3*error_ant[1];
  
  // Give the control action after its computation
  return(control);
}
