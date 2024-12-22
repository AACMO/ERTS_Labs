// EMBEDDED AND REAL-TIME SYSTEMS - LABORATORY L5
// Alejandro Acosta, Ivan Barrachina and Victor Escribano
// Exercise 2: Characterizing the ball in tube system response

#define PIN_PWM         9     // Digital output pin to send the PWM signal to the fan
#define PIN_TRIGGER     12    // Digital I/O pin to send a trigger to the sensor
#define PIN_ECHO        11    // Digital I/O pin to receive the echo response from the sensor
#define SENSOR_CONST    58    // Constant that must be used to decode sensor data into cm from pulse width
#define MAX_DIST        30.0  // Distance from the lowest slot part in the tube wrt the ultrasonic sensor

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
  static float dist = 0.0;                  // Variable to store the distance decode from sensor in cm
  static float dist_error = 0.0;            // Variable to store the distance from the bottom part of the slot to the ball
  static uint8_t pwm_val=82;                // Variable to store the PWM value to be sent to the computer fan on the control loop
  static uint8_t sample_counts=0;           // Define a variable to count on the main loop the need of changing setpoint to fan
  static uint8_t decremental = 0;           // Variable to store whether it is necessary to make the decrements on PWM value

  // Increase the counter of samples first
  sample_counts++;

  // Check if it is necessary to update pwm value to fan
  if (sample_counts==200)
  {
    // Check PWM value within given interval
    if(pwm_val == 182){decremental = 1;}
    else if (pwm_val == 82) {decremental = 0;}
    else{}

    // Check if it is need to go up or down with PWM values
    if (decremental == 0){pwm_val+=10;}
    else {pwm_val-=10;}
    sample_counts=0;
  }

  // Send the PWM control signal
  analogWrite(PIN_PWM, pwm_val);
  
  // Send a trigger command to read ultrasonic sensor data 
  digitalWrite(PIN_TRIGGER, HIGH);             // Activate the trigger pulse
  delayMicroseconds(10);                       // wait for a 10 us
  digitalWrite(PIN_TRIGGER, LOW);              // Deactivate the trigger pulse 
  // Wait until we receive a response from ECHO pin
  resp_length = pulseIn(PIN_ECHO,HIGH);
  
  // Use the given formula to calculate the distance from obtained pulse width and plot it
  dist=(float)((1.0*resp_length)/SENSOR_CONST);
  // Compute the distance to the bottom of the slot
  dist_error = MAX_DIST - dist;
    
  // Print last values before changing anything
  Serial.print(pwm_val);Serial.print(";");Serial.println(dist_error);

  // wait for 50 ms to have speed stabilized
  delay(50);                            
}
