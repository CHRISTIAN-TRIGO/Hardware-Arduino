/*PROGRAMA CONTROLA 5 SALIDAS MEDIANTE UN MENÚ VISUALIZADO EN LA LCD 
*/
#include<LiquidCrystal.h>//CARGAR LA LIBRERIA DE LA LCD

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

//INICIALIZA LA CONFIGURACION DE PINES DE LA LCD CON EL ARDUINO
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//DEFINICION DE BOTONES Y LEDS
int btn_sel = 8;
int btn_control = 9;

int led1 = 10;
int led2 = 11;
int led3 = 12;
int led4 = 13;
int led5 = A0;

//PROTOTIPOS DE FUNCIONES
void c_led1();
void c_led2();
void c_led3();
void c_led4();
void c_led5();

void setup()
{
  lcd.begin(16, 2); // INICIA LA LCD

  //DEFINE LOS PINES COMO ENTRADAS Y SALIDAS
  pinMode(btn_sel, INPUT_PULLUP);//DECLARA EL BOTON COMO ENTRADA
  pinMode(btn_control, INPUT_PULLUP);//DECLARA EL BOTON COMO ENTRADA

  //DECLARA LOS PINES DE LED COMO SALIDA
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  lcd.setCursor(0, 0);//POSICIONA EL CURSOR DE LCD EN 0,0
  lcd.print("******MENU****");//IMPRIME "****MENU***"

  lcd.setCursor(0, 1);//POSICIONA EL CURSOR DE LCD EN 1,1
  lcd.print("PRESIONA SEL");//IMPRIME "PRESIONA SELECT"

  delay(500);//ESPERA 500 MILISEGUNDOS
}

void loop()
{
  if (digitalRead(btn_sel) == LOW) //TOMA DE DESICION AL PRESIONAR BOTON SELECCION
  {
    lcd.clear();//LIMPIA LA PANTALLA

    lcd.setCursor(0, 0); //POSICIONA EL CURSOR DE LA LCD EN 0,0
    lcd.print("***SELECT LED");//IMPRIME LA SELECCION LED

    lcd.setCursor(5, 1);//POSICIONA EL CURSOR DE LA LCD EN 0,0
    lcd.print("LED 1");//IMPRIME "LED1"

    delay(500);//ESPERA 500 MILISEGUNDOS

    c_led1();//MANDA LLAMR LA FUNCION C_LED1 (MENU LED 1)
  }
}

//***********INICIO DE MENU LED 1*************
void c_led1()
{
  while (1)
  {
    if (digitalRead(btn_sel) == LOW)//TOMA DE DESICION SI BOTON SELECCION FUE PRESIONADO
    {
      lcd.setCursor(5, 1);//POSICIONA EL CURSOR EN 10,1
      lcd.print("LED 2");//IMPRIME 2

      delay(300);//ESPERA 300 MILISEGUNDOS

      c_led2();//MANDA LLAMR LA FUNCION C_LED1 (MENU LED 1)
    }

    if (digitalRead(btn_control) == LOW)//TOMA DE DESICION SI BOTON CONTROL FUE PRESIONADO
    {
      if (digitalRead(led1) == LOW)//SI LED 1 FUE SELECCIONADO
      {
        digitalWrite(led1,HIGH);//ENCIENDE LED 1
      }
      else //SINO
      {
        digitalWrite(led1,LOW);//APAGA LED1
      }

      delay(300);//ESPERA 300 MILISEGUNDOS
    }
  }
}

//************** LED 2**************
void c_led2() //FUNCION C_LED2
{
  while (1)
  {
    if (digitalRead(btn_sel) == LOW)//SI BOTON SELECCION ES
    {
      lcd.setCursor(5, 1);//POSICIONA CURSOR EN 10,1
      lcd.print("LED 3");//IMPRIME 3

      delay(300);//ESPERA 300 MILISEGUNDOS

      c_led3();//LLAMA LA FUNCION LED 3
    }

    if (digitalRead(btn_control) == LOW) // SI BOTON CONTROL = 0
    {
      if (digitalRead(led2) == LOW)
      {
        digitalWrite(led2,HIGH); //ENCIENDE LED 2
      }
      else //SINO
      {
        digitalWrite(led2,LOW);//APAGA LED2
      }

      delay(300);//ESPERA 300 MILISEGUNDOS
    }
  }
}

//******** LED 3************
void c_led3() //DEFINE FUNCION C_LED3
{
  while (1)
  {
    if (digitalRead(btn_sel) == LOW)// SI BTN_SEL = 0
    {
      lcd.setCursor(5, 1);//POSICIONA EL CURSOR EN 10,1
      lcd.print("LED 4");//IMPRIME LED 4

      delay(300);//ESPERA 300 MILISEGUNDOS

      c_led4();//LLAMA LA FUNCION LED 4
    }

    if (digitalRead(btn_control) == LOW)//SI BOTON CONTROL = 0
    {
      if (digitalRead(led3) == LOW)
      {
        digitalWrite(led3,HIGH); //ENCIENDE LED 3
      }
      else // SI NO
      {
        digitalWrite(led3,LOW); //APAGA LED 3
      }

      delay(300);//ESPERA 300 MILISEGUNDOS
    }
  }
}

//********** LED4**********
void c_led4() //DEFINE FUNCION C_LED4
{
  while (1)
  {
    if (digitalRead(btn_sel) == LOW) //SI BTN_SEL = 0
    {
      lcd.setCursor(5, 1);//POSICIONA EL CURSOR EN 10,1
      lcd.print("LED 5");//IMPRIME 5

      delay(300);//ESPERA 300 MILISEGUNDOS

      c_led5();//LLAMA LA FUNCION LED 5
    }

    if (digitalRead(btn_control) == LOW) //SI BOTON CONTROL = 0
    {
      if (digitalRead(led4) == LOW)
      {
        digitalWrite(led4,HIGH); //ENCIENDE LED 4
      }
      else //SINO
      {
        digitalWrite(led4,LOW); //APAGA LED 4
      }

      delay(300);//ESPERA 300 MILISEGUNDOS
    }
  }
}

//********** LED 5**********
void c_led5()//DEFINE LA FUNCION C_LED5
{
  while (1)
  {
    if (digitalRead(btn_sel) == LOW) //SI BOTON SELECCION = 0
    {
      lcd.setCursor(5, 1);//POSICIONA EL CURSOR 10,1
      lcd.print("LED 1");//IMPRIME 1

      delay(300);//ESPERA 300 MILISEGUNDOS

      c_led1();//LLAMA FUNCION LED1
    }

    if (digitalRead(btn_control) == LOW) //SI BOTON CONTROL = 0 
    {
      if (digitalRead(led5) == LOW)
      {
        digitalWrite(led5,HIGH);//ENCIENDE LED 5
      }
      else//SINO
      {
        digitalWrite(led5,LOW);//APAGA LED 5
      }

      delay(300);//ESPERA 300 MILISEGUNDOS
    }
  }
}
