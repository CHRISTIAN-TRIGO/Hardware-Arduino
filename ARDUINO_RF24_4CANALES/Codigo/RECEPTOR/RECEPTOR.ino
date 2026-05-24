/********** ING CHRISTIAN TRIGO ***************
controlador de cuatro puertos por RADIOFRECUENCIA***********
********RECEPTOR***************
*/
#include<RF24.h>-
RF24 radio(9,10);
const uint64_t canal = 0xE8E8F0F0E1LL;
int dato[4];//declara matriz de datos
#define LED1 2
#define LED2 3
#define LED3 4
#define LED4 5
#define MONITOR 8
void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(MONITOR, OUTPUT); 
  radio.begin();
  radio.openReadingPipe(1,canal); //determina direccion del nrf con recepcion de datos
  radio.startListening();

}
void loop()
{
  if(radio.available())
  {
    radio.read(dato,sizeof(dato));
    if(dato[0]==0) digitalWrite(LED1, !digitalRead(LED1));
    if(dato[1]==0) digitalWrite(LED2, !digitalRead(LED2));
    if(dato[2]==0) digitalWrite(LED3, !digitalRead(LED3));
    if(dato[3]==0) digitalWrite(LED4, !digitalRead(LED4));
    digitalWrite(MONITOR,1);
    delay(10);  
  }
  digitalWrite(MONITOR,0);
}
