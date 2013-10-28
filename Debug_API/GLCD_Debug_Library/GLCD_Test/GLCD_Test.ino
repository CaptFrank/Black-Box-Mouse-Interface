
#include <Arduino.h>

// Include the debug lcd api
#include "Debug_API_GLCD.h"

debug_GLCD_GLK12232 lcd;

void setup(){
 
  Serial1.begin(9600);
  lcd = new debug_GLCD_GLK12232(Serial1, 9600, false); 
}



void loop(){
  
  
  
}


