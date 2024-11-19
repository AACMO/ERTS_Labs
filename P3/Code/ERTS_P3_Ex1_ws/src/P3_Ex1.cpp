#include <avr/io.h>
#include <avr/interrupt.h>

// Start all defines for the code
// ----------------------------------------------------------------------------------------------------//
#define PWM_STEP_INC   15                         // Increase on each loop for the PWM signal 15 units the duty cycle
#define MAX_PWM_VALUE 255                         // Maximum value for the PWM fan duty cycle on PWM signal
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
uint8_t pwm_duty_cycle = 0;                       // Variable to store the actual duty cycle to impose on PWM on each loop

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

  // Initialize both pins PD6 as output for PWM signal
  DDRD = 0b01000000;                              // Initialize pin PD6 as output on DDRD register

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
  * needs to be adjusted on each loop to increase the speed of the fan with this signal.
  ****************************************************************************************************/
  TCCR0A = 0x03;                                 // Fast PWM mode selected for TC0 counter
  TCCR0A |= (1<<COM0A1);                         // Clear OC0A on compare Match and set OC0A at bottom again when timer overflows      
  TCCR0B |= (1<<CS01);                           // Set TC0 prescaler at value 8
  OCR0A = 0x00;                                  // Set initially output compare value for the timer 0 OCR0 to 0.

  // Initialize counter timer 1 (TC1) for counting time precisely
  /****************************************************************************************************
  * It is desired to have at least an overflow each second to change the PWM duty cycle depending on this 
  * situation. The CTC mode will be used, so it is necessary to set the prescaler properly and adjust the 
  * OCR value so that the timer overflow is done just when 1s elapsed since it started running. 
  * The formula to use is as follows:
  *                                         (fclk_I/O)
  *                            f_signal = --------------
  *                                         N·(1+OCRnx)
  * Where the value that will be reached by the counter is will be found by isolating OCRnx from previous
  * formula. The prescaler (N) will be selected as 256 and the frequency of the MCU (fclk_I/O) cannot be 
  * changed from 16 MHz. With all these set up, and considering that it is willing to obtain a T period of 1s 
  * for a timer overflow occurrence, it is obtained a value of OCRnx register as follows:
  *                                        16000000
  *                           OCRnx = ------------------ - 1 -> OCRnx = 62499
  *                                        256 · 1
  * Then, with this OCRnx value the period of the timer will be 1 s. Hence, at each time the overflow occurs, the
  * duty cycle will be necessary to be increased. Note that for timer 1 the OCR maximum value will be 65535 because
  * it is a 16-bit timer. 
  ****************************************************************************************************/
  TCCR1A = 0x00;                                 // CTC mode selected for TC1 counter
  TCCR1B |= (1<<WGM12) | (1<<CS12);              // Set TC1 prescaler to count at 256 and set up CTC mode with WGM12 bit set
  OCR1A = 0xF423;                                // Set maximum value for the timer to count at each loop (62499)
  TIMSK1 |= (1<<OCIE1A);                         // Set timer 1 output compare match A interrupt enabled

  // Enable interrupts in the system
  SREG |= 0x80;                                  // Global interrupt enable, to be able to trigger any interrupt on system 
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
// To handle timer 1 output compare match A interrupt
ISR(TIMER1_COMPA_vect)
{   
  // Increase the PWM duty cycle on each overflow event
  static uint16_t pwm_counter = 0;
  pwm_counter += (uint8_t)PWM_STEP_INC;
  // Check if PWM duty cycle value to be assigned is already exceeding the maximum allowed value and reset the value if necessary
  if (pwm_counter > MAX_PWM_VALUE) {pwm_duty_cycle=0;pwm_counter=0;}
  // Otherwise, just assign to the PWM duty cycle variable the already counted one on this cycle.
  else{pwm_duty_cycle = (uint8_t)pwm_counter;}

  // Assign the new value to the output compare match A register to increase duty cycle on next counting
  OCR0A = pwm_duty_cycle;

  // Only send data via serial port if Arduino IDE is being used
  #ifdef ARDUINO_IDE
  // Send via the serial port data about measurements and PWM duty cycle imposed each 500 ms
  Serial.print("PWM_value:");Serial.println(pwm_duty_cycle); 
  #endif     
}