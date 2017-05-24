
 /*
  * Blink 3
  Blink LED1 with a 200ms cycle (5Hz)
  Utlizing the Timer1 rather than delay functions.
  ZADATAK: upoznati rad timera. Sta nije u redu? Preci na Timer2.
 */


extern "C" void __attribute__((interrupt(),nomips16)) Timer3Handler(void);

int pin = 33;           // LED pin
int frequency = 5;      

//************************************************************************
void EnableTimer(void)
{
  T3CON = 0;
  T2CON = 0;                             // izbor preskalera
  TMR2 = 0;
  TMR3 = 0;
  
  T2CONSET = 0x0038;
  T2CONSET = TBCON_PS_256;
  
                                           // Obrisi Timer1 counter
  PR2 = ((__PIC32_pbClk) / 256 * frequency);
  Serial.println(PR2);
  
  // inicijalizacija prekida
  setIntVector(_TIMER_3_VECTOR, Timer3Handler);
  clearIntFlag(_TIMER_3_IRQ);
  setIntPriority(_TIMER_3_VECTOR, _T3_IPL_IPC, _T3_SPL_IPC);
  setIntEnable(_TIMER_3_IRQ);  

  T2CONSET = 0x8000;      // pusti ga da broji
}

void disableTimer(void)
{
  clearIntEnable(_TIMER_3_IRQ);
  T2CON = 0;
  T2CONCLR = TBCON_ON;      // zaustavi brojac
  clearIntVector(_TIMER_3_VECTOR);
}

//*  we need the extern C so that the interrupt handler names dont get mangled by C++
extern "C"
{
void __attribute__((interrupt(),nomips16)) Timer3Handler(void)
{
  digitalWrite(pin, !digitalRead(pin));

  // clear the interrupt flag
  clearIntFlag(_TIMER_3_IRQ);
}
};  //* extern "C"


void myInterrupt() 
{
    static boolean state = false;
    state = !state;
    digitalWrite(31, state);
    Serial.println(state);
}

void setup() 
{
  // put your setup code here, to run once:

  Serial.begin(9600);

  // Ensure that the pin is a digital output
  pinMode(pin, OUTPUT);
  
  // Init the timer.
  EnableTimer();
}


void loop() 
{
  // put your main code here, to run repeatedly:

}
