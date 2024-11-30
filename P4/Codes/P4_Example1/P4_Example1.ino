//------------------------------------------------
// FreeRTOS example: programming 2 periodic tasks
//------------------------------------------------
#include <Arduino_FreeRTOS.h>

// define two tasks for Blink & AnalogRead
void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );

//-------
// setup
//-------
void setup() 
{
  // digital pin 13 (connected to built-in LED) as output
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW); // LED OFF initially

  // create first task
  xTaskCreate(TaskBlink, 
             "Blink", // name
             128, // stack size
             NULL,
             1, // Lower priority
             NULL );

  // create second task
  xTaskCreate(TaskAnalogRead, 
             "AnalogRead",
             128,
             NULL, 
             2, // Higher priority
             NULL );
  // now the task scheduler is automatically started
}

//------
// loop
//------
void loop()
{
// empty!
}

//--------------------------
// first task: LED blinking
//--------------------------
void TaskBlink(void *pvParameters)
{
  (void) pvParameters;

  // forever loop
  for (;;)
  {
    digitalWrite(13, HIGH); // LED ON
    Serial.println("Now LED is ON");
    vTaskDelay( 500 / portTICK_PERIOD_MS ); // wait for 0.5 seconds
    digitalWrite(13, LOW); // LED OFF
    Serial.println("Now LED is OFF");
    vTaskDelay( 500 / portTICK_PERIOD_MS ); // wait for 0.5 seconds
  }
}

//-------------------------
// second task: reading A0
//-------------------------
void TaskAnalogRead(void *pvParameters)
{
  (void) pvParameters;
  // initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  // forever loop
  for (;;)
  {
    int sensorValue = analogRead(A0); // read analog input A0
    Serial.println(sensorValue); // send through serial port
    //vTaskDelay(1); // one tick (smallest) delay
  }
}
