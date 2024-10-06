// EMBEDDED AND REAL-TIME SYSTEMS - LABORATORY L1
// Alejandro Acosta and Ivan Barrachina
// Exercise 4: Controlling a computer fan (using a PWM signal) - optional part

#define PIN_PWM      3     // Pin to send a trigger to the sensor
#define PIN_RPM      7     // Pin to read the F00 speed sensor output 

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
  static uint8_t pwm_val=10;                // Variable to store the pulse width from the sensor
  static uint16_t pulse_val=0;              // Variable to store the received measure from the sensor
  static float meas_vel=0.0;                // Variable to store the calculated rpm from sensor value
  static bool descend=false;                // Boolean which indicates if the PWM signal increases or decreases in amplitude
  // Print last values before changing anything
  Serial.print("sensed_val:"); Serial.print(pulse_val);Serial.print(",");Serial.print("PWM_setpoint:"); Serial.print(pwm_val);Serial.print(",");Serial.print("meas_speed[rpm]:"); Serial.println(meas_vel);
  // Check if PWM value is within acceptable range
  if (pwm_val == 240) {descend = true;}     // If it is at the higher limit, proceed to decrease it at next loop iteration
  if (pwm_val == 10) {descend = false;}     // If it is at the lower limit, proceed to increase it at next loop iteration
  // Read the pulse width value from the speed sensor output
  pulse_val=pulseIn(PIN_RPM,HIGH);
  // Get the value in rpms from obtained sensor value
  meas_vel=(float)(60*1000000/(pulse_val*4.0));
  // Send the PWM control signal
  analogWrite(PIN_PWM, pwm_val);
  // Increase or decrease the value for the PWM control signal
  if (descend == false) {pwm_val+=10;}
  else {pwm_val-=10;}
  delay(2000);                             // wait for 2 s to have speed stabilized
}
