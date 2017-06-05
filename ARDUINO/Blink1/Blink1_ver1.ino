/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
  ZADATAK: promeni pin ili vreme; iskoristi tastere BTN1:4
 */
 
#define dump(v) Serial.println(v) 

#define LED_1 26
#define LED_NUM 8

// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize LED pins as output.
  for( int i=0; i<LED_NUM; i++)
  {
    pinMode(LED_1+i, OUTPUT);
    digitalWrite(LED_1+i, LOW);
  }
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);  
}

// the loop function runs over and over again forever
void loop() 
{
  static int lcnt = 0;             // Led Counter
 
  digitalWrite(LED_1+lcnt, LOW);    // prvo pogasi tekuci
  if( digitalRead(7) )
  {
    // Show 1: pali na desno
    if (lcnt == 0)
      lcnt = LED_NUM-1;
    else
      lcnt = lcnt - 1;  
  }
  else
  {
    // Show 2: pali na levo
    lcnt = (lcnt + 1) % LED_NUM;
  }
  digitalWrite(LED_1+lcnt, HIGH);    // upali skledeci LED

  delay(1000);
}
