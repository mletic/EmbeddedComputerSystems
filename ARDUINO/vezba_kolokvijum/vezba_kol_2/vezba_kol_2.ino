 /*
  * Zadatak:
  * a) Napraviti funkciju task1() koja proverava stanje dugmadi 1-4 i ispisuje njihovo stanje na lampicama 26-29
  * b) Kreirati task task2() koji na svakih 5ms proverava i koriguje stanje lampica 26-29, u zavisnosti od stanja dugmadi koristeci funkciju task1() i broji koliko puta je pritisnuto dugme BTN1. 
  * Nakon svakog pritiska, ispisati stanje brojaca  na serijski monitor
  * c) Kreirati funkciju digitalWrite2 (port, bit, state) koja ispisuje vrednost na digitalnom izlazu, koristeci diretkan pristup registrima porta preko njihovih adresa
 */
 


int task2_id;
unsigned long task2_var;
int old_state_btn1, cnt;

#define bit2mask(bit) (1<<bit) 
enum gpio_ports { PORT_A=1, PORT_B, PORT_C, PORT_D, PORT_E, PORT_F, PORT_G };
unsigned int gpio_base_addr[PORT_G] = 
    {0xBF886000, 0xBF886040, 0xBF886080, 0xBF8860C0, 0xBF886100, 0xBF886140, 0xBF886180 };
enum gpio_regs { GPIO_REG=0, GPIO_CLR, GPIO_SET, GPIO_INV };  

int PIN_LED[4] = {26, 27, 28, 29};
int PIN_LED_PORT[4] = {PORT_E, PORT_E, PORT_E, PORT_E};
int PIN_LED_BIT[4] = {0, 1, 2, 3};
int PIN_BTN[4] = {4, 34, 36, 37};
 

void digitalWrite2(int port, int bit, bool val)
{
  // proveri broj porta i bita
  if( (port < PORT_B) || (port > PORT_G) || (bit > 15) )
    return;
  
  // namesti masku pozicionu  
  int bmask = bit2mask( bit );
  
  // namesti adrese
  volatile uint32_t *lat_addr = (uint32_t *)(gpio_base_addr[port - 1] + 0x20);

  //* Set the pin state
  if (val == LOW)
  {
      *(lat_addr + GPIO_CLR) = bmask;
  }
  else
  {
      *(lat_addr + GPIO_SET) = bmask;
  }
}

void task1() 
{
  int i;
  for(i=0; i<4; i++)
    if (digitalRead(PIN_BTN[i]))
      digitalWrite2(PORT_E, PIN_LED_BIT[i], HIGH);
    else
      digitalWrite2(PORT_E, PIN_LED_BIT[i], LOW);
}

void task2(int id, void * tptr) 
{
   task1();
   int new_state_btn1 = digitalRead(PIN_BTN[0]);
   if (old_state_btn1 == 0 && new_state_btn1 == 1){
      cnt++;
      Serial.print("CNT = ");
      Serial.println(cnt);
      old_state_btn1 = 1;
   } else if (old_state_btn1 == 1 && new_state_btn1 == 0){
      old_state_btn1 = 0;
   }
} 

void setup() 
{
   int i;
   Serial.begin(9600);
   for(i=0; i<4; i++)
      pinMode(PIN_LED[i], OUTPUT);
   old_state_btn1 = 0;
   cnt = 0;
   task2_id = createTask(task2, 5, TASK_ENABLE, &task2_var);
}
 
void loop() 
{

}

