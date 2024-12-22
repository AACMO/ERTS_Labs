// EMBEDDED AND REAL-TIME SYSTEMS - LABORATORY L5
// Alejandro Acosta, Ivan Barrachina and Victor Escribano
// Exercise 2: Feedforward control for the ball in tube system

#define PIN_PWM         9     // Digital output pin to send the PWM signal to the fan
#define PIN_TRIGGER     12    // Digital I/O pin to send a trigger to the sensor
#define PIN_ECHO        11    // Digital I/O pin to receive the echo response from the sensor
#define SENSOR_CONST    58    // Constant that must be used to decode sensor data into cm from pulse width
#define MAX_DIST        30.0  // Distance from the lowest slot part in the tube wrt the ultrasonic sensor
#define MAX_PWM_VAL     250   // Maximum PWM value allowed to be sent to fan with PWM signal

float a = 0.2678;             // Define the term that goes with PWM on the f curve between distance and PWM value (x is PWM)
float b = -19.218;            // Define the independent term for the f curve  

// the setup function runs once when you press reset or power the board
void setup() 
{
  // Digital pin initialization
  pinMode(PIN_TRIGGER, OUTPUT); // initialize digital pin PIN_TRIGGER as an output.
  pinMode(PIN_ECHO, INPUT);     // initialize digital pin PIN_ECHO as an input.
 
  // Initialize serial output
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() 
{
  // Initializing auxiliary variables for PWM signal generation and speed measurement
  static unsigned long resp_length = 0;     // Variable to store the pulse width from the sensor
  static float dist_val=15.0;               // Variable to give distance setpoint to the fan with respect to the bottom of the slot
  static float dist = 0.0;                  // Variable to store the distance decode from sensor in cm
  static float meas_dist = 0.0;             // Variable to store the distance from the bottom part of the slot to the ball
  static uint8_t pwm_val=82;                // Variable to store the pulse width from the sensor
  static uint8_t sample_counts=0;           // Define a variable to count on the main loop the need of changing setpoint to fan

  // Increase the counter of samples first
  sample_counts++;

  // Check if it is necessary to update pwm value to fan
  if (sample_counts==200)
  {
    if(dist_val == 20.0){dist_val=10.0;}
    else {dist_val=20.0;}
    sample_counts=0;
  }
  
  // Compute the next pwm value based on rpm setpoint and computed curve
  pwm_val = (uint8_t) (((dist_val-b)/a));
  // Saturate the maximum PWM value if it exceeds the maximum allowed
  if (pwm_val>MAX_PWM_VAL){pwm_val=MAX_PWM_VAL;}
  // Send the PWM control signal
  analogWrite(PIN_PWM, pwm_val);
  
  // Send a trigger command to sensor
  digitalWrite(PIN_TRIGGER, HIGH);          // Activate the trigger pulse
  delayMicroseconds(10);                    // wait for a 10 us
  digitalWrite(PIN_TRIGGER, LOW);           // Deactivate the trigger pulse 
  // Wait until we receive a response from ECHO pin
  resp_length = pulseIn(PIN_ECHO,HIGH);
  
  // Use the given formula to calculate the distance from obtained pulse width and plot it
  dist=(float)((1.0*resp_length)/SENSOR_CONST);
  // Compute the distance to the bottom of the slot
  meas_dist = MAX_DIST - dist;
    
  // Print last values before changing anything
  Serial.print("setpoint:");Serial.print(dist_val);Serial.print(",");Serial.print("dist_meas:");Serial.print(meas_dist);Serial.println(",");

  // wait for 50 ms to have speed stabilized
  delay(50);                            
}
