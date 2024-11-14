// EMBEDDED AND REAL-TIME SYSTEMS - LABORATORY L2
// Alejandro Acosta and Ivan Barrachina
//Exercise 1: Controlling the computer fan with an ON-OFF control strategy

// Constants definition
#define PIN_ADC         16    // Analog input pin to receive the sensor's output
#define PIN_PWM         3     // Digital output pin to send the PWM signal to the fan
#define OFF_MODE        0
#define ON_MODE         200
#define MAX_TEMP        25.0
#define HYSTERESYS_STEP 1.0

// the setup function runs once when you press reset or power the board
void setup() 
{
  // Initialize serial output
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() 
{
  // Initialize auxiliary variables to store data from the sensor
  static uint16_t sensed_val=0;                // Variable to store the pulse width from the sensor
  static float temp_val=0.0;                   // Variable to store the distance decode from sensor in cm
  static uint8_t pwm_val=OFF_MODE;

  // Read the value from the sensor
  sensed_val=analogRead(PIN_ADC);
  // Convert to degrees from output voltage using the linear formula and plot it
  temp_val=(float)((5000.0*sensed_val)/(10*1023));
  // Check if room temperature exceeds maximum allowed value
  if (temp_val >= (MAX_TEMP+HYSTERESYS_STEP)) {pwm_val=ON_MODE;}
  // Stop the control action if room temperature is below minimum temperature
  else if(temp_val < (MAX_TEMP-HYSTERESYS_STEP)){pwm_val=OFF_MODE;}
  // Do nothing
  else{}
  // Send the control command to the fan depending on temperature sensed
  analogWrite(PIN_PWM, pwm_val);
  // Print obtained values on the loop
  Serial.print("Temperature[degC]:"); Serial.print(temp_val);Serial.print(","); Serial.print("control_action:"); Serial.println(pwm_val/10);
  delay(200);                                  // wait for 200 ms
}
