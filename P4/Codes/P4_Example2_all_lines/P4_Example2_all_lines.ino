//-----------------------------------------------
// FreeRTOS example: accessing a shared resource
//-----------------------------------------------
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
SemaphoreHandle_t xSerialSemaphore;

// define two Tasks for DigitalRead & AnalogRead
void TaskDigitalRead( void *pvParameters );
void TaskAnalogRead( void *pvParameters );

//-------
// setup
//-------
void setup()
{
  Serial.begin(9600);

  if ( xSerialSemaphore == NULL ) // Check to confirm that the Serial Semaphore has not already been created.
  {
    xSerialSemaphore = xSemaphoreCreateMutex(); // Create a mutex semaphore we will use to manage the Serial Port
    if ( ( xSerialSemaphore ) != NULL )
    xSemaphoreGive( ( xSerialSemaphore ) ); // Make the Serial Port available for use, by "Giving" the Semaphore.
  }

  // Now set up two Tasks to run independently.
  xTaskCreate(TaskDigitalRead,
              "DigitalRead", 
              128,
              NULL, 
              1, // Priority
              NULL 
              );
  xTaskCreate(TaskAnalogRead,
             "AnalogRead", 
             128, // Stack size
             NULL, 
             1, // Priority
             NULL 
             );
  // Now the Task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

//------
// loop
//------
void loop()
{
  // Empty. Things are done in Tasks.
}

//-------------------------------------
// first task: reading a digital input
//-------------------------------------
void TaskDigitalRead( void *pvParameters __attribute__((unused)) )
{
  uint8_t pushButton = 2;
  pinMode(pushButton, INPUT);
  for (;;) // A Task shall never return or exit.
  {
    // read the input pin:
    int buttonState = digitalRead(pushButton);
    // See if we can obtain or "Take" the Serial Semaphore.
    //if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    //{
      // We were able to obtain or "Take" the semaphore and can now access the shared resource.
      Serial.println("TaskDigitalRead ");
      Serial.println(buttonState);
      //xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    //}
    vTaskDelay(1); // one tick delay (15ms) in between reads for stability
  }
}
//--------------------------------------
// second task: reading an analog input
//--------------------------------------
void TaskAnalogRead( void *pvParameters __attribute__((unused)) )
{
  for (;;)
  {
    int sensorValue = analogRead(A0);
    // See if we can obtain or "Take" the Serial Semaphore.
    //if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    //{
      // We were able to obtain or "Take" the semaphore and can now access the shared resource.
      Serial.println("TaskAnalogRead ");
      Serial.println(sensorValue);
      //xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    //}
    vTaskDelay(1); // one tick delay (15ms) in between reads for stability
  }
}
