#include <avr/io.h>
#include <avr/interrupt.h>

// Start all defines for the code
// ----------------------------------------------------------------------------------------------------//
#define MAX_PWM_VALUE 255                         // Maximum value for the PWM fan duty cycle on PWM signal
#define SENSOR_CONST  58.0                        // Constant that must be used to decode sensor data into cm from pulse width
#define TIMER1_FREQ   4.0                         // Constant defining the time in us between ticks for timer 1
#define MIN_DIST      2.0                         // Constant defining the minimum distance in cm for the sensor ultrasonic range (2 cm)
#define MAX_DIST    150.0                         // Constant defining the maximum distance in cm for the sensor ultrasonic range (1.5 m for the exercise)
#define ARDUINO_P       0                         // Variable to decide which is the IDE used for the programming and for the testing

// Define the ARDUINO_IDE macro only if it is used the Arduino for the programming task
#if ARDUINO_P
#define ARDUINO_IDE
#endif
// Include only the debugger library if the IDE used is not Arduino
#ifndef ARDUINO_IDE
#include <avr8-stub.h>
#endif

// Start all global variables definition for the code
// ----------------------------------------------------------------------------------------------------//
uint8_t meas_done = 0;                            // Flag to store when a new value of the PWM can be processed after a full cycling measurement is done
float sensed_dist = 0;                            // Variable to store the results of measured distance from the ultrasonic sensor

// Start set up function for the code
// ----------------------------------------------------------------------------------------------------//
// Make all necessary setup inside this function
void setup_init() 
{
  // Select interface used for debugging
  #ifdef ARDUINO_IDE
  // Initialize serial output
  Serial.begin(9600);
  #else
  // Allows debugging with visual studio code tools
  debug_init();
  #endif
  
  // Initialize pin PB0 as input for echo signal from sensor (Input Capture Unit 1 - ICP1)
  DDRB = 0b00000000;                              // Initialize pin PB0 as input
  // Initialize pin PD2 as output for trigger signal to sensor and PD6 as output for PWM signal to the fan 
  DDRD |= 0b01000100;                             // Initialize pin PD6 and PD2 as outputs
  PORTD &= 0xFB;                                  // Set output on pin PD6 and PD1 as inactive initially

  // Initialize counter timer 0 (TC0) for PWM signal generation
  /****************************************************************************************************
  * It is desired to have a PWM signal with a frequency within 30 - 300 kHz, which is the acceptable bandwidth 
  * for the fan. On this regard, due to the usage of the timer 0 for the signal generation in fast PWM mode, the 
  * frequency will be a value that can be reached properly just adjusting the prescaler for that clock signal. 
  * The formula to determine the frequency for PWM signal is as follows: 
  *                                              (fclk_I/O)
  *                                 f_signal = --------------
  *                                                N·256
  * Imposing a prescaler (N) as 8 and knowing that the frequency of the MCU (fclk_I/O) cannot be 
  * changed from 16 MHz, the frequency to be obtained with these prepared settings will be the next:
  *                                           16000000
  *                           f_signal = ------------------ -> f_signal = 7812.5 Hz -> 7.8 kHz
  *                                            8 · 256
  * Then, with this prescaler the frequency for the PWM signal on Fast PWM mode will be 7.8 kHz. Now the duty cycle
  * needs to be adjusted on each loop to increase the speed of the fan with this signal. With these values, each timer 
  * tick will be 0.5 us to make a total period of 0.5 us*256 ticks = 128 us/period. Therefore, to get an appropriate 
  * timing for the echo request to the ultrasonic sensor, the output compare register B for timer 0 will be used with a 
  * value of 22 to exceed the minimum request time of 10 us (22 ticks * 0.5 us/tick = 11 us).
  ****************************************************************************************************/
  TCCR0A = 0x03;                                    // Fast PWM mode selected for TC0 counter
  TCCR0A |= (1<<COM0A1);                            // Clear OC0A on compare Match and set OC0A at bottom again when timer overflows      
  TCCR0B |= (1<<CS01);                              // Set TC0 prescaler at value 8
  OCR0A = 0x00;                                     // Set initially output compare value A for the timer 0 OCR0 to 0.
  TIMSK0 |= (1<<TOIE0);                             // Set timer 0 overflow interrupt enabled

  // Initialize counter timer 1 (TC1) for counting time precisely
  /****************************************************************************************************
  * It is desired to have at least an overflow each 100 ms to change the PWM duty cycle depending on the sensor 
  * data readings. The CTC mode will be used, so it is necessary to set the prescaler properly and adjust the 
  * OCR value so that the timer overflow is done just when 100 ms elapsed since it started running. 
  * The formula to use is as follows:
  *                                         (fclk_I/O)
  *                            f_signal = --------------
  *                                         N·(1+OCRnx)
  * Where the value that will be reached by the counter is will be found by isolating OCRnx from previous
  * formula. The prescaler (N) will be selected as 64 and the frequency of the MCU (fclk_I/O) cannot be 
  * changed from 16 MHz. With all these set up, and considering that it is willing to obtain a T period of 1s 
  * for a timer overflow occurrence, it is obtained a value of OCRnx register as follows:
  *                                        16000000
  *                           OCRnx = ------------------ - 1 -> OCRnx = 24999
  *                                       64 · 1/0.1
  * Then, with this OCRnx value the period of the timer will be 100 ms. Hence, at each time the overflow occurs, the
  * ADC data will be checked and the duty can be changed as necessary. Note that for timer 1 the OCR maximum value 
  * will be 65535 because it is a 16-bit timer. Finally, it must be remarked that in CTC mode this timer will count 
  * until the value placed in OCR0A so it will reach up to 24999 doing 25000 ticks. This will mean that the time 
  * between ticks for this timer will be: 
  *                                                      100 ms
  *                            Timer1_Tick_Time [us] = ---------- = 0.004 ms/tick = 4 us/tick
  *                                                    25000 ticks
  * Then, each tick from Timer 1 with this configuration will impose a time of 4 us on the system. This must be considered
  * for the counts done using the timer ticks such as the ICU results or the requests to the ultrasonic sensor
  ****************************************************************************************************/
  TCCR1A = 0x00;                                    // CTC mode selected for TC1 counter
  TCCR1B |= ((1<<WGM12)| (1<<CS11) | (1<<CS10));    // Set TC1 prescaler to count at 64 and set up CTC mode with WGM12 bit set
  TCCR1B |= ((1<<ICNC1)| (1<<ICES1));               // Set the input capture unit as rising edge to detect the echo signal from sensor initially
  OCR1A = 0x61A7;                                   // Set maximum value for the timer to count at each loop with output compare match A
  OCR1B = 0x0003;                                   // Set the maximum value for the OCR1B to 3 counts (after the first 12 us it must have an interrupt). For the ultrasonic sensor request signal
  TIMSK1 |= ((1<<OCIE1B) | (1<<OCIE1A));            // Set timer 1 output compare match A and B interrupts enabled
  TIMSK1 |= (1<<ICIE1);                             // Set input capture unit interrupt enabled flag to get measurements from ultrasonic sensor

  // Enable interrupts in the system
  SREG |= 0x80;                                     // Global interrupt enable, to be able to trigger any interrupt on system 
}

// Start main function for the code
// ----------------------------------------------------------------------------------------------------//
int main() 
{
  // Call first the setup function
  setup_init();

  // Start infinite loop empty
  for(;;)
  {
  }
}

// Start definition of all ISR functions necessary for the code
// ----------------------------------------------------------------------------------------------------//
// To handle timer 0 overflow interrupt
ISR(TIMER0_OVF_vect)
{ 
  static uint8_t pwm_duty_cycle = 0;                            // Variable to store the actual duty cycle to impose on PWM on each loop

  // Only attempt to update OCR0A value if there is a measurement pending to be checked
  if (meas_done == 1)
  {
    // Set flag to 0 again
    meas_done = 0;
    
    // Limit the output depending on results given
    if (sensed_dist > MAX_DIST){sensed_dist=MAX_DIST;}
    else if (sensed_dist < MIN_DIST){sensed_dist=MIN_DIST;}
    else{}
  
    // Change PWM value depending on the sensed distance 
    pwm_duty_cycle = MAX_PWM_VALUE*((sensed_dist - MIN_DIST)/(MAX_DIST - MIN_DIST));
    // Assign the new value to the output compare match A register to increase duty cycle on next counting
    OCR0A = pwm_duty_cycle;
  }
  // Do nothing otherwise, protective else
  else{}
}

// To handle timer 1 output compare match A interrupt (each 100 ms)
ISR(TIMER1_COMPA_vect)
{  
  // Send a new request to the sensor by setting the pin PD2 as active
  PORTD |= 0x04;
  
  // Only send data via serial port if Arduino IDE is being used
  #ifdef ARDUINO_IDE
  static uint8_t print_count = 0;
  // Check if 500 ms since last print elapsed 
  if (print_count == 5)
  { 
    // Send via the serial port data about measurements and PWM duty cycle imposed each 500 ms
    Serial.print(sensed_dist);Serial.print(";");Serial.println(OCR0A); 
    // Set the flag again to 0
    print_count = 0;
  }
  // Otherwise, increase the counter
  else{print_count++;}
  #endif   
}

// To handle timer 1 output compare match B interrupt (each 12 ms)
ISR(TIMER1_COMPB_vect)
{  
  // Set output on pin PD2 as inactive again when the output compare match occurs
  PORTD &= 0xFB;                              
}

//To handle timer 1 output compare match B interrupt (each 8 us when enabled)
ISR(TIMER1_CAPT_vect)
{  
  static uint8_t trigger_raised = 0;                // Variable to store if the rising edge has been already detected on ICU
  static uint16_t timestamps[2] = {0,0};            // Variable to store the value on the ICR1 register when an edge is detected
  
  // Set the flag if it was equal to 0
  if (trigger_raised == 0)
  {
    trigger_raised = 1;                             // Set the flag for the rising edge detected
    timestamps[0] = ICR1;                           // Store the timer time for the rising edge detection
    TCCR1B &= 0xBF;                                 // Reset the ICES1 to get the new measurement on a falling edge (reset to 0)
  }
  // It is already 1, needs to be reset and the ICU must be also prepared for next rising edge
  else 
  {
    trigger_raised = 0;                             // Reset the flag to get a new rising edge detected
    timestamps[1] = ICR1;                           // Store the timer time for the falling edge detection
    TCCR1B |= (1<<ICES1);                           // Set the ICES1 to get the new measurement on a rising edge (set to 1)
    meas_done = 1;                                  // Set the flag that a full measurement cycle is done
    
    // Compute new sensed distance depending on values obtained from timestamps
    if (timestamps[0]<=timestamps[1])
    {
      sensed_dist = TIMER1_FREQ*(timestamps[1]-timestamps[0])/(SENSOR_CONST);
    }
    // An overflow occurred during measurements, compute the time properly and make conversion
    else
    {
      // Get the value over the maximum timing register value
      uint32_t diff_count = 0;
      diff_count = OCR1A+timestamps[1];
      // Now compute the sensed distance properly
      sensed_dist = TIMER1_FREQ*(diff_count-timestamps[0])/(SENSOR_CONST);
    }
    // Reset values on timestamps at the end
    timestamps[0]=0; timestamps[1] = 0;
  }
}
