/********** ING CHRISTIAN TRIGO ***************
controlador de cuatro puertos por RADIOFRECUENCIA***********
********TRANSMISOR***************
 */
#include <RF24.h>
RF24 radio(9,10); //9 CE Y 10 CSN
#include <a_rebote.h>
//define y crea pines
a_rebote BOTON1(2);
a_rebote BOTON2(3);
a_rebote BOTON3(4);
a_rebote BOTON4(5);
//DEFINE LA VARIABLE PARA LOS DATOS
int dato[4]; //matriz para envio de datos
const uint64_t canal = 0xE8E8F0F0E1LL;
void setup(void)
{
  radio.begin();
  radio.openWritingPipe(canal);
}

void loop()
{
  //envia datos
  if(BOTON1.al_presionar()) dato[0]=0; //elimina el rebote
  else dato[0] =1;
  if(BOTON2.al_presionar()) dato[1]=0; //elimina el rebote      
  else dato[1]=1;
  if(BOTON3.al_presionar()) dato[2]=0; //elimina el rebote
  else dato[2]=1;
  if(BOTON4.al_presionar()) dato[3]=0; //elimina el rebote      
  else dato[3]=1;
  radio.write(dato, sizeof(dato));
  delay(10);    
}
