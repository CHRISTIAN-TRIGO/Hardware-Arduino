/**
   **********  ING.LUIS ENRIQUE DE LA TORRE VERA *********
   *  CENTRO DE SISTEMAS DE COMPUTO Y ELECTRONICA*********
*/
#include <a_rebote.h>
// Create two button instances on pins 2 & 3
a_rebote buttonOn(2);
/**
   PROGRAM INITIALIZATION
*/
void setup() {
  // Prepare serial interface
  Serial.begin(9600);
}

/**
   MAIN PROGRAM LOOP
*/
void loop() {
  // Check if "on" button is pressed
  if (buttonOn.al_presionar()) 
  {
      if(digitalRead(13)==LOW) digitalWrite(13, HIGH);
      else digitalWrite(13, LOW);
  }


}
