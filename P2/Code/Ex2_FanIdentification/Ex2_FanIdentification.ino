// EMBEDDED AND REAL-TIME SYSTEMS - LABORATORY L2
// Alejandro Acosta, Ivan Barrachina and Victor Escribano
// Exercise 2: Characterizing the fan response

#define PIN_PWM      3     // Pin to send a trigger to the sensor
#define PIN_RPM      7     // Pin to read the F00 speed sensor output 
#define TOTAL_PULSES 4
#define PULSE_TIMO   25000
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
  static uint16_t pulse_val=0;              // Variable to store the received measure from the sensor
  static float meas_vel=0.0;                // Variable to store the calculated rpm from sensor value
  static uint8_t sample_counts=0;           // Define a variable to count on the main loop the need of changing setpoint to fan
  static uint8_t pulse_counts=0;            // Define variable to count pulses read so far on loop

  // Increase the counter of samples first
  sample_counts++;

  // Check if it is necessary to update pwm value to fan
  if (sample_counts==100)
  {
    if(pwm_val == 250){pwm_val=0;}
    else {pwm_val+=50;}
    sample_counts=0;
  }
  // Send the PWM control signal
  analogWrite(PIN_PWM, pwm_val);

  // Read the pulse width value from the speed sensor output and convert it
  while(pulse_counts!=TOTAL_PULSES)
  {
    pulse_val+=pulseIn(PIN_RPM,HIGH,PULSE_TIMO);
    pulse_counts++;
  }
  // Set the counter of pulses at 0 after the while loop
  pulse_counts=0;

  // Get the value in rpms from obtained sensor value
  if(pulse_val !=0)
  {
    meas_vel=(float)(60*1000000/(pulse_val*1.0)); pulse_val=0;
  }
  else {meas_vel=0;}
  
  // Print last values before changing anything
  Serial.print(pwm_val);Serial.print(",");Serial.println(meas_vel);

  // wait for 50 ms to have speed stabilized
  delay(50);                            
}
