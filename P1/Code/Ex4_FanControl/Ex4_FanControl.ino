// EMBEDDED AND REAL-TIME SYSTEMS - LABORATORY L1
// Alejandro Acosta and Ivan Barrachina
// Exercise 4: Controlling a computer fan (using a PWM signal)

// Constants definition
#define PIN_PWM      3     // Digital output pin to send the PWM signal to the fan

// the setup function runs once when you press reset or power the board
void setup() 
{
  // Initialize serial output
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() 
{
  static uint8_t pwm_val=10;                // Variable to store the pulse width to be sent to the sensor
  
  // Check if PWM value is within acceptable range
  if (pwm_val > 240) {pwm_val = 10;}        // Reset if it is out of range
  // Convert to PWM signal and print it
  analogWrite(PIN_PWM, pwm_val);
  Serial.print("PWM_setpoint:"); Serial.println(pwm_val);
  // Increase the pulse width for the PWM signal
  pwm_val+=10;
  delay(100);                               // wait for 100 ms
}
