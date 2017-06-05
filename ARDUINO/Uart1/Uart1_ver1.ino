/*
  UART Demo 1
  Receive and send back character
*/

#define UON_MSK (1<<15)
volatile uint32_t *u1mode_reg = (uint32_t *) 0xBF806000;

#define URXEN_MSK 0x1000   // bit 12 (1 << 12)
#define UTXEN_MSK 0x0400   // bit 10 (1 << 10)
#define UTXBF_MSK 0x0200   // bit  9 (1 << 9)
#define URXDA_MSK 0x0001   // bit  0 (1 << 0)
volatile uint32_t *u1sta_reg  = (uint32_t *) 0xBF806010;

volatile uint32_t *u1tx_reg   = (uint32_t *) 0xBF806020;
volatile uint32_t *u1rx_reg   = (uint32_t *) 0xBF806030;
volatile uint32_t *u1brg_reg  = (uint32_t *) 0xBF806040;

// za podesavanje MODE i STA registara
enum gpio_regs { UART_REG=0, UART_CLR, UART_SET, UART_INV }; 

void uart_init( int baudRate )
{
  *u1mode_reg = 0;
  *u1sta_reg  = 0;
  // calculate actual BAUD generate value.
  *u1brg_reg = ((__PIC32_pbClk / 16 / baudRate) - 1);  
  *(u1sta_reg + UART_SET) = URXEN_MSK + UTXEN_MSK;  
  *(u1mode_reg + UART_SET) = UON_MSK; // enable UART module
}

bool uart_available( void )
{
  // da li je ista primljeno
  return *u1sta_reg & URXDA_MSK;
}

char uart_read( void )
{
  return *u1rx_reg;
}

void uart_send( char b )
{
  // sacekaj ako nema mesta u Tx bufferu
  while( (*u1sta_reg & UTXBF_MSK) == 1 );
  *u1tx_reg = b;
}

// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize serial communication at 9600 bits per second:
  //Serial.begin(9600);  
  uart_init( 9600 );
}

// the loop function runs over and over again forever
void loop() 
{
  // send data only when you receive data:
  //if (Serial.available() > 0) 
  if( uart_available() ) 
  {
    // read the incoming byte:
    //char inByte = Serial.read();
    char inByte = uart_read();
    // say what you got:
    uart_send(inByte);
  }
}
