
 /*
  * Blink 3
  Blink LED1 with a 200ms cycle (5Hz)
  Utlizing the Timer1 rather than delay functions.
  ZADATAK: upoznati rad timera. Koristi Timer2.
 */


extern "C" void __attribute__((interrupt(),nomips16)) TimerHandler(void);

int pin = 33;               // LED pin
float frequency = 0.2;      // Hz

//************************************************************************
void EnableTimer(void)
{
  // Timers 2/3 u 32-bitnoj konfiguraciji
  
  T2CON = T3CON = 0;                  // pocetni disable timers
  TMR2 = TMR3 = 0;                    // Obrisi Timer counter

  // konfiguracija Timera 2
  T2CON = TBCON_PS_256;               // izbor preskalera
  T2CONSET = TBCON_MODE32;            // 32-bitni nacin rada
    
  // podesavanje perioda brojanja
  int pr = (__PIC32_pbClk / 256) / frequency;
  PR2 = pr;
  //PR2 = pr & 0xFFFF;    //lsb
  //PR3 = pr >> 16;       // msb
  Serial.println(pr);
  //Serial.println(PR2, HEX);
  //Serial.println(PR3, HEX);
    
  // inicijalizacija prekida
  setIntVector(_TIMER_3_VECTOR, TimerHandler);
  clearIntFlag(_TIMER_3_IRQ);
  setIntPriority(_TIMER_3_VECTOR, _T3_IPL_IPC, _T3_SPL_IPC);
  setIntEnable(_TIMER_3_IRQ);  

  T2CONSET = TBCON_ON;      // pusti ga da broji
}

void disableTimer(void)
{
  clearIntEnable(_TIMER_3_IRQ);
  //T2CON = 0;
  T2CONCLR = TBCON_ON;      // zaustavi brojac
  clearIntVector(_TIMER_3_VECTOR);
}

//*  we need the extern C so that the interrupt handler names dont get mangled by C++
extern "C"
{
void __attribute__((interrupt(),nomips16)) TimerHandler(void)
{
  digitalWrite(pin, !digitalRead(pin));
  //Serial.println(digitalRead(pin));
 
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

// Bata
  pinMode(31, OUTPUT);
  attachInterrupt(1, myInterrupt, FALLING);   // Pin2(INT1)
  attachInterrupt(2, myInterrupt, FALLING);   // Pin7(INT2) 
  attachInterrupt(3, myInterrupt, FALLING);   // Pin8(INT3)
  attachInterrupt(4, myInterrupt, FALLING);   // Pin35(INT4)
}


void loop() 
{
  // put your main code here, to run repeatedly:
  //myInterrupt();
  delay(1000);
}
