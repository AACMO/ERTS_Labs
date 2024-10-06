// EMBEDDED AND REAL-TIME SYSTEMS - LABORATORY L1
// Alejandro Acosta and Ivan Barrachina
//Exercise 2: Reading an analog temperature sensor (analog output, linear)

// Constants definition
#define PIN_ADC      16    // Analog input pin to receive the sensor's output

// the setup function runs once when you press reset or power the board
void setup() {
  // Initialize serial output
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() 
{
  // Initialize auxiliary variables to store data from the sensor
  static uint16_t sensed_val=0;                // Variable to store the pulse width from the sensor
  static float temp_val=0.0;                   // Variable to store the distance decode from sensor in cm
  // Read the value from the sensor
  sensed_val=analogRead(PIN_ADC);
  // Convert to degrees from output voltage using the linear formula and plot it
  temp_val=(float)((5000.0*sensed_val)/(10*1023));
  Serial.print("sensed_val:"); Serial.print(sensed_val);Serial.print(",");Serial.print("Temperature[degC]:"); Serial.println(temp_val);
  delay(200);                                  // wait for 200 ms
}
