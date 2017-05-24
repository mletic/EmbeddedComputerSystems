 /*
  Blink Task 1 and 2
  Blink LED1 with a 500ms cycle (2Hz)
  Read SW1 and turn on/off LED2 in a 25ms cycle (40Hz)
  Utlizing the chipKIT task manager rather than delay functions.
  This example code is in the public domain.
  ZADATAK: Task3 pusta/stopira Task2 u skladu sa polozajem SW2 (pin 7)
 */
 
#define PIN_LED1 33
#define PIN_LED2 27
#define PIN_SW2   7
 
int blink1_id;
unsigned long blink1_var;

int blink2_id;

void blink_task1(int id, void * tptr) 
{
  digitalWrite(PIN_LED1, !digitalRead(PIN_LED1));   // Toggle pin state
}

void blink_task2(int id, void * tptr) 
{
  digitalWrite(PIN_LED2, !digitalRead(PIN_LED2));   // Toggle pin state

  setTaskPeriod(blink2_id, random(500) + 20);
}

void blink_task3(int id, void * tptr) 
{
  if(digitalRead(PIN_SW2) == HIGH && getTaskState(blink2_id) == TASK_DISABLE)
  {
    setTaskState(blink2_id, TASK_ENABLE);
  }
  else if(digitalRead(PIN_SW2) == LOW && getTaskState(blink2_id) == TASK_ENABLE)
  {
    setTaskState(blink2_id, TASK_DISABLE);
  }
}

void setup() 
{
   // initialize the digital pin as an output.
   pinMode(PIN_LED1, OUTPUT);
   pinMode(PIN_LED2, OUTPUT);

   randomSeed(analogRead(A0));
   
   //create blink tasks
   blink1_id = createTask(blink_task1, 500, TASK_ENABLE, &blink1_var);
   blink2_id = createTask(blink_task2, random(500) + 20, TASK_ENABLE, NULL);

   createTask(blink_task3, 10 , TASK_ENABLE, NULL);
}

unsigned long msButtonPress;
boolean pressed = false;
 
void loop() 
{
  if(digitalRead(37) == HIGH && pressed == false)
  {
    msButtonPress = millis();
    pressed = true;
  }
  else if(digitalRead(37) == LOW && pressed == true)
  {
    pressed = false;

    unsigned long t = millis();
    
    if(t - msButtonPress >= 2000)
    {
      executeSoftReset(RUN_SKETCH_ON_BOOT);
    }
  }
}

