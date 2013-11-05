
#include "Debug_API_GLCD.h"

debug_GLCD_GLK12232 debug_lcd;

void setup(){
 
 Serial.begin(9600);
 debug_lcd.set_configs(&Serial1, 19200, false);
}

void loop(){

  Serial.println("Setup Autoscroll = true");
  debug_lcd.toggle_autoscroll(true);
  
  Serial.println("Clearing Screen");
  debug_lcd.clear_screen();
  
  Serial.println("Setting cursor to home");
  debug_lcd.set_cursor_to_home_pos();
  
  Serial.println("Reading Version");
  debug_lcd.read_version();
  
  Serial.println("Reading Module");
  debug_lcd.read_module_type();
  
  debug_lcd.serial_device->print("Hello World\n");
  debug_lcd.serial_device->print("THIS IS A TUT\n");
  debug_lcd.serial_device->print("OF THE LCD SCREEN");
  
  // Loop for ever
  while(1);
  
}
