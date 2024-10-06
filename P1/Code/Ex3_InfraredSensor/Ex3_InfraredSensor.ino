// EMBEDDED AND REAL-TIME SYSTEMS - LABORATORY L1
// Alejandro Acosta and Ivan Barrachina
//Exercise 3: Reading an infrared distance sensor (analog output, non-linear)

// Constants definition
#define PIN_ADC      16    // Analog input pin to receive the sensor's output

// the setup function runs once when you press reset or power the board
void setup() 
{
  // Initialize serial output
  Serial.begin(9600);
}

// voltage_table function:
// Applying separated formulae to calculate the sensed distance depending on the sensed voltage interval
// The formula have been obtained from the specifications using linear and quadratic interpolations
float voltage_table(float sense_voltage)
{
  float dist=0.0;

  // Distance between 10 and 20 cm 
  if (sense_voltage > 1.25 && sense_voltage <= 2.25)
  {
    // Return with the formula for the distance on this case
    dist =(-10*sense_voltage+32.5);
  }
  // Distance between 20 and 40 cm 
  else if (sense_voltage <= 1.25 && sense_voltage > 0.75)
  {
    // Return with the formula for the distance on this case
    dist =76.19*(sense_voltage*sense_voltage)-(192.38*sense_voltage)+141.43;
  } 
  // Distance between 40 and 80 cm 
  else if (sense_voltage <= 0.75 && sense_voltage >= 0.45)
  {
    // Return with the formula for the distance on this case
    dist = 500.41*(sense_voltage*sense_voltage)-(720.44*sense_voltage)+299.4;
  }
  // Distance out of the threshold between 10-80, do nothing
  else{} 

  // Return the distance value updated
  return dist;
}

// voltage_interp function:
// Calculating the sensed distance from the sensed voltage applying an unique exponential formula
// This exponential formula was obtained experimentally from sensed voltages at determined distances
float voltage_interp(float sense_voltage)
{
  float dist=0.0;
  // If the sensed voltage is contained within the functioning limits compute the distance value
  if (sense_voltage < 2.25 && sense_voltage >= 0.45)
  {
    // Return the value using the formula interpolating all points
    dist = 27.497*(pow(sense_voltage,-1.225));
  }
  // Distance out of the threshold between 10-80, do nothing
  else {}

  // Return the distance value updated
  return dist;
}

// the loop function runs over and over again forever
void loop() 
{
  // Initialize auxiliary variables to store data from the sensor and calculated values
  static uint16_t sensed_val=0;                // Variable to store the pulse width from the sensor
  static float table_dist=0.0;                 // Variable to store the distance decoded from sensor in cm using voltage table function
  static float interp_dist=0.0;                // Variable to store the distance decoded from sensor in cm using interpolation function
  static float volt_val=0.0;                   // Variable to store the conversion from digital value received into a voltage value
  // Read the value from the sensor
  sensed_val=analogRead(PIN_ADC);
  // Convert to output voltage
  volt_val=(float)((5.0*sensed_val)/(1023));
  // Obtain distance in cm with both methods
  table_dist=voltage_table(volt_val);         // With voltage table function
  interp_dist=voltage_interp(volt_val);       // With interpolation function
  // Print the obtained values via serial port to compare
  Serial.print("sensed_val:"); Serial.print(sensed_val);Serial.print(",");Serial.print("table_dist[cm]:"); Serial.print(table_dist);Serial.print(",");Serial.print("interp_dist[cm]:"); Serial.println(interp_dist);
  delay(200);                                 // wait for 200 ms
}
