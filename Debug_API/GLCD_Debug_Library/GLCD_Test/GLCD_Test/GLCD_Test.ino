
#include "Debug_API_GLCD.h"

debug_GLCD_GLK12232 debug_lcd;

void setup(){
  
 debug_lcd.set_configs(&Serial1, 9600, false);
}

void loop(){
  
  Serial1.write(0xfe);
  Serial1.write(0x39);
  Serial1.print(9600, HEX);
  Serial1.write(0xfe);
  Serial1.write(0x58);
  debug_lcd.clear_screen();
  debug_lcd.set_cursor_to_home_pos();
  
}
