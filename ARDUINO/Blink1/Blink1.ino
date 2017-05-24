/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
  ZADATAK: promeni pin ili vreme; iskoristi SW1 i SW2 (naizmenicno)
 */
 
#define dump(v) Serial.println(v)

// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pin 33 as an output.
  pinMode(33, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);  
}

// the loop function runs over and over again forever
void loop() 
{ 
  int pin7;
  int pin2;

  pinCheck(&pin7, &pin2);
  
  if (pin2 && !pin7) { 
      kaUnutra();
                   
      while (pin2 && !pin7) {
        pinCheck(&pin7, &pin2);      
      }
  }
  else if (pin2 && pin7) {
      kaSpolja();           

      while (pin2 && pin7) {
        pinCheck(&pin7, &pin2);         
      }
  }
  else {
      ugaseno();
  }
}

void kaUnutra() {
    digitalWrite(33, HIGH);
    digitalWrite(26, HIGH);
    delay(333);             
    digitalWrite(33, LOW);
    digitalWrite(26, LOW);
    delay(333);

    digitalWrite(32, HIGH);
    digitalWrite(27, HIGH);
    delay(333);             
    digitalWrite(32, LOW);
    digitalWrite(27, LOW);
    delay(333); 

    digitalWrite(31, HIGH);
    digitalWrite(28, HIGH);
    delay(333);             
    digitalWrite(31, LOW);
    digitalWrite(28, LOW);
    delay(333); 

    digitalWrite(30, HIGH);
    digitalWrite(29, HIGH);
    delay(333); 
}

void kaSpolja() {
    digitalWrite(30, HIGH);
    digitalWrite(29, HIGH);
    delay(333);             
    digitalWrite(30, LOW);
    digitalWrite(29, LOW);
    delay(333);

    digitalWrite(31, HIGH);
    digitalWrite(28, HIGH);
    delay(333);             
    digitalWrite(31, LOW);
    digitalWrite(28, LOW);
    delay(333); 

    digitalWrite(32, HIGH);
    digitalWrite(27, HIGH);
    delay(333);             
    digitalWrite(32, LOW);
    digitalWrite(27, LOW);
    delay(333); 

    digitalWrite(33, HIGH);
    digitalWrite(26, HIGH);
    delay(333);
}

void ugaseno() {
    digitalWrite(33, LOW);
    digitalWrite(32, LOW);
    digitalWrite(31, LOW);
    digitalWrite(30, LOW);
    digitalWrite(29, LOW);
    digitalWrite(28, LOW);
    digitalWrite(27, LOW);
    digitalWrite(26, LOW);
}

void pinCheck(int *pin7, int *pin2) {
    *pin7 = digitalRead(7);
    *pin2 = digitalRead(2);
  
    dump(*pin7);
    dump(*pin2);
}

