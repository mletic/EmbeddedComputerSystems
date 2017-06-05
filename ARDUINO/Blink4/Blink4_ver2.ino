/*
  Blink 4
  Turns on/off LED according to SW position.
  Reveals logic behind Arduino digitalRead function
  Napisi svoju digitalWrite funkciju
 */

#define dump(v) Serial.print(v)

//************************************************************************
int digitalRead1(uint8_t pin)
{
  volatile p32_ioport *iop;
  uint8_t  port;
  uint16_t bit;
  int      highLow;

  /* Check if pin number is in valid range.
  */
  if (pin >= NUM_DIGITAL_PINS_EXTENDED)
  {
    return 0;
  }

  //* Get the port number for this pin.
  if ((port = digitalPinToPort(pin)) == NOT_A_PIN)
  {
    return LOW;
  }

  //* Obtain pointer to the registers for this io port.
  iop = (p32_ioport *)portRegisters(port);

  //* Obtain bit mask for the specific bit for this pin.
  bit = digitalPinToBitMask(pin);

  dump("PORT=");dump(port); dump(" BIT=");dump(bit);
  dump(" DATA=");dump(iop->port.reg);
  dump("\n");

  //* Get the pin state.
  if ((iop->port.reg & bit) != 0) 
  {
    highLow = HIGH;
  }
  else
  {
    highLow = LOW;
  }

  return(highLow);
}


// the setup function runs once when you press reset or power the board
void setup() 
{
  Serial.begin(9600);
  // initialize digital pin 27 as an output.

  pinModeOutput(27);

}

void pinModeOutput(uint8_t pin)
{
  volatile p32_ioport *iop;
  uint8_t  port;
  uint16_t bit;

  /* Check if pin number is in valid range.
  */
  if (pin >= NUM_DIGITAL_PINS_EXTENDED)
  {
    return;
  }

  //* Get the port number for this pin.
  if ((port = digitalPinToPort(pin)) == NOT_A_PIN)
  {
    return;
  }

  //* Obtain pointer to the registers for this io port.
  iop = (p32_ioport *)portRegisters(port);

  //* Obtain bit mask for the specific bit for this pin.
  bit = digitalPinToBitMask(pin);

  //dump("PORT=");dump(port); dump(" BIT=");dump(bit);
  //dump(" DATA=");dump(iop->tris.reg);
  //dump("\n");
  
  /*
   * TRIS registar se koristi za upravljanje i citanje pravca GPIO pina, 1 za input, 0 za output. Bit maska pina se moze dobiti sa digitalPinToBitMask(pin)
   */
  
  bit = ~bit;
  iop->tris.reg = iop->tris.reg & bit;

  return;
}

void digitalWrite1(uint8_t pin, int state)
{
  //digitalWrite(pin, state);
  volatile p32_ioport *iop;
  uint8_t  port;
  uint16_t bit;

  /* Check if pin number is in valid range.
  */
  if (pin >= NUM_DIGITAL_PINS_EXTENDED)
  {
    return;
  }

  //* Get the port number for this pin.
  if ((port = digitalPinToPort(pin)) == NOT_A_PIN)
  {
    return;
  }

  //* Obtain pointer to the registers for this io port.
  iop = (p32_ioport *)portRegisters(port);

  //* Obtain bit mask for the specific bit for this pin.
  bit = digitalPinToBitMask(pin);

  dump("PORT=");dump(port); dump(" BIT=");dump(bit);
  dump(" DATA=");dump(iop->port.reg);
  dump("\n");

  //* Set the pin state.

   /*
   * PORT registar se koristi za upravljanje i citanje stanja GPIO pina, 1 za HIGH, 0 za LOW. Bit maska pina se moze dobiti sa digitalPinToBitMask(pin)
   */
  
  if(state == HIGH)
  {
    iop->port.reg = iop->port.reg | bit;
  }
  else
  {
    bit = ~bit;
    iop->port.reg = iop->port.reg & bit;
  }
  return;
}

// the loop function runs over and over again forever
void loop() 
{
  //delay(2000);
  
  if( digitalRead1(7) )
    digitalWrite1(27, HIGH);
  else
    digitalWrite1(27, LOW);
}
