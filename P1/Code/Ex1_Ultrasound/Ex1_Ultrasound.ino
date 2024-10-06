// EMBEDDED AND REAL-TIME SYSTEMS - LABORATORY L1
// Alejandro Acosta and Ivan Barrachina
// Exercise 1: Reading an ultrasonic distance sensor (digital output, pulse of variable width)

// Constants definition
#define PIN_TRIGGER  3     // Digital I/O pin to send a trigger to the sensor
#define PIN_ECHO     4     // Digital I/O pin to receive the echo response from the sensor
#define SENSOR_CONST 58    // Constant that must be used to decode sensor data into cm from pulse width
// the setup function runs once when you press reset or power the board
void setup() {
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
  static unsigned long resp_length = 0;          // Variable to store the pulse width from the sensor
  static float dist = 0.0;                       // Variable to store the distance decode from sensor in cm
  // Send a trigger command to sensor
  digitalWrite(PIN_TRIGGER, HIGH);             // Activate the trigger pulse
  delayMicroseconds(10);                       // wait for a 10 us
  digitalWrite(PIN_TRIGGER, LOW);              // Deactivate the trigger pulse 
  // Wait until we receive a response from ECHO pin
  resp_length = pulseIn(PIN_ECHO,HIGH);
  // Use the given formula to calculate the distance from obtained pulse width and plot it
  dist=(float)((1.0*resp_length)/SENSOR_CONST);      
  Serial.print("pulse_length[us]:"); Serial.print(resp_length);Serial.print(",");Serial.print("distance [cm]:"); Serial.println(dist);
  delay(200);                                  // wait for 200 ms
}
