/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 33; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

#define PWM_BIT_TIME 6
#define PWM_PERIOD (PWM_BIT_TIME * 1024)

void setup() 
{
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(analogOutPin, OUTPUT);
}

void loop() 
{
  static int loop_cnt = 0;

  if( !(loop_cnt % 500) )
  {
    // ucitaj A0 i odredi novu PWM vrednost
    sensorValue = analogRead(analogInPin);
    outputValue = map(sensorValue, 0, 1023, 0, PWM_PERIOD);
    // print the results to the serial monitor:
    Serial.print("sensor = ");
    Serial.print(sensorValue);
    Serial.print("\t output = ");
    Serial.println(outputValue);
  }

  if( loop_cnt < outputValue)
    digitalWrite(analogOutPin, HIGH);
  else
    digitalWrite(analogOutPin, LOW);

  delay(PWM_BIT_TIME);
  loop_cnt = (loop_cnt + PWM_BIT_TIME) % PWM_PERIOD;

}
