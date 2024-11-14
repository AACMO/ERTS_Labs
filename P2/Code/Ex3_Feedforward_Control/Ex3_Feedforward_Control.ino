// EMBEDDED AND REAL-TIME SYSTEMS - LABORATORY L2
// Alejandro Acosta, Ivan Barrachina and Victor Escribano
// Exercise 3: Controlling the computer fan with feedforward control

#define PIN_PWM      3                      // Pin to send a trigger to the sensor
#define PIN_RPM      7                      // Pin to read the F00 speed sensor output 
#define TOTAL_PULSES 4                      // Define the total of pulses to be sensed from sensor to count the speed value
#define PULSE_TIMO   25000                  // Define the time to wait to have a pulse from sensor with a falling edge (25000 us) 
#define MAX_PWM_VAL  250                    // Maximum PWM value allowed to be sent to fan with PWM signal
#define MAX_UNS_LONG 4294967295             // Maximum value an unsigned long element can have in Arduino
#define MAX_TOTAL_READS 5                   // Maximum time it will attempt to read the sensor in case a reading is failing and some value was previously stored on pulse_val

float a = 38.506;                           // Define the term that goes with PWM on the f curve between RPMs and PWM value (x is PWM)
float b = -27.236;                          // Define the independent term for the f curve  

// the setup function runs once when you press reset or power the board
void setup() 
{
  // Set up the digital pin to read F00 sensor as digital input with pull-up enabled.
  pinMode(PIN_RPM,INPUT_PULLUP);
  // Initialize serial output
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() 
{
  // Initializing auxiliary variables for PWM signal generation and speed measurement
  static uint8_t pwm_val=0;                 // Variable to store the pulse width from the sensor
  static uint16_t rpm_val=2000;             // Variable to give rpm setpoint to the fan in term of rpms
  static float meas_vel=0.0;                // Variable to store the calculated rpm from sensor value
  static uint8_t sample_counts=0;           // Define a variable to count on the main loop the need of changing setpoint to fan
  static uint8_t pulse_counts=0;            // Define variable to count pulses read so far on loop
  static uint8_t read_retries=0;            // Define variable to count the times a false read from sensor will be attempted to be read
  static unsigned long pulse_val=0;         // Variable to store the received measure from the sensor
  
  // Increase the counter of samples first
  sample_counts++;

  // Check if it is necessary to update pwm value to fan
  if (sample_counts==100)
  {
    if(rpm_val == 3000){rpm_val=2000;}
    else {rpm_val=3000;}
    sample_counts=0;
  }
  // Compute the next pwm value based on rpm setpoint and computed curve
  pwm_val = (uint8_t) (((rpm_val-b)/a));
  // Saturate the maximum PWM value if it exceeds the maximum allowed
  if (pwm_val>MAX_PWM_VAL){pwm_val=MAX_PWM_VAL;}

  // Send the PWM control signal
  analogWrite(PIN_PWM, pwm_val);

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
  
  // Print last values before changing anything
  Serial.print("rpm_setpoint:");Serial.print(rpm_val);Serial.print(",");Serial.print("meas_speed[rpm]:");Serial.println(meas_vel); 

  // wait for 100 ms to have speed stabilized
  delay(100);                             
}
