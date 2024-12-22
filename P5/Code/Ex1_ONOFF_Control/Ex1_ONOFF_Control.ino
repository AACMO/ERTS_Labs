// EMBEDDED AND REAL-TIME SYSTEMS - LABORATORY L5
// Alejandro Acosta, Ivan Barrachina and Victor Escribano
// Exercise 1: Controlling the ball in tube with an ON-OFF control strategy

// Constants definition
#define PIN_PWM         9     // Digital output pin to send the PWM signal to the fan
#define PIN_TRIGGER     12    // Digital I/O pin to send a trigger to the sensor
#define PIN_ECHO        11    // Digital I/O pin to receive the echo response from the sensor
#define SENSOR_CONST    58    // Constant that must be used to decode sensor data into cm from pulse width
#define OFF_MODE        115   // PWM value to impose on the ON/OFF control when it is on the OFF state (ball at 17 cm or more from lowest slot part)
#define ON_MODE         140   // PWM value to imoposed on the ON/OFF control when it is on the ON state (ball at 13 cm or more from the lowest slot part)
#define SETPOINT_DIST   15.0  // Setpoint for the ON/OFF control indicating the distance wrt lowest slot part that must be maintained
#define MAX_DIST        30.0  // Distance from the lowest slot part in the tube wrt the ultrasonic sensor
#define HYSTERESYS_STEP 2.0   // Maximum distance in cm the ball can move from the setpoint before activating the ON/OFF control

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
  // Initialize auxiliary variables to store data from the sensor
  static unsigned long resp_length = 0;        // Variable to store the pulse width from the sensor
  static float dist = 0.0;                     // Variable to store the distance decode from sensor in cm
  static float dist_error = 0.0;               // Variable to store the distance from the bottom part of the slot to the ball
  static uint8_t pwm_val=OFF_MODE;             // Variable to store the PWM value to be sent to the computer fan during the control loop

  // Send a trigger command to sensor
  digitalWrite(PIN_TRIGGER, HIGH);             // Activate the trigger pulse
  delayMicroseconds(10);                       // wait for a 10 us
  digitalWrite(PIN_TRIGGER, LOW);              // Deactivate the trigger pulse 
  // Wait until we receive a response from ECHO pin
  resp_length = pulseIn(PIN_ECHO,HIGH);
  // Use the given formula to calculate the distance from obtained pulse width and plot it
  dist=(float)((1.0*resp_length)/SENSOR_CONST);
  // Compute the distance to the bottom of the slot
  dist_error = MAX_DIST - dist;
  // Set the OFF mode if it is over the given setpoint
  if (dist_error >= (SETPOINT_DIST + HYSTERESYS_STEP))
  {pwm_val=OFF_MODE;}
  // Set the ON mode if it is below the given setpoint
  else if (dist_error <= (SETPOINT_DIST - HYSTERESYS_STEP))
  {pwm_val=ON_MODE;}
  // Do nothing otherwise
  else{}
  // Send the control command to the fan depending on temperature sensed
  analogWrite(PIN_PWM, pwm_val);
  // Print obtained values on the loop
  Serial.print("distance[cm]:"); Serial.print(dist_error);Serial.print(",");Serial.print("PWM_value:");Serial.println(pwm_val);
  // wait for 200 ms
  delay(200);                                 
}
