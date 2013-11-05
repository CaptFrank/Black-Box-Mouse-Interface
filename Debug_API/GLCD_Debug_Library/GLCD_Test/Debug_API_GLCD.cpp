//
//  Debug_API_GLCD.cpp
//  GLCD_Debug_Library
//
//  Created by Francis Papineau on 2013-10-10.
//
//

#include "Debug_API_GLCD.h"

#define END_LINE    '\n'
#define DEBUG

// ---------------------------------------------------------------------------------------

// PRIVATE METHODS

// Sends a command to the remote screen
void debug_GLCD_GLK12232::_send_command(uint8_t* command, uint8_t size_of){
    
    // send to the bus.
    #ifdef DEBUG
    Serial.print("Sending Command: ");
    Serial.write(command, size_of);
    #endif
    this->serial_device->write(command, size_of);
}

// Reads a command from the lcd
void debug_GLCD_GLK12232::_read_command(void){
  
    while(this->serial_device->available() > 0){
        // read the incoming byte:
        byte incomingByte = this->serial_device->read();

        #ifdef DEBUG
        // say what you got:
        Serial.println(incomingByte, DEC);
        #endif
    }
    Serial.print("\n");
}

// ---------------------------------------------------------------------------------------

// PUBLIC METHODS

// Init the serial device handler.
debug_GLCD_GLK12232::debug_GLCD_GLK12232(){}

// Send configs.
void debug_GLCD_GLK12232::set_configs(HardwareSerial *serial_device, uint16_t baud, bool flow_control){
  
  
    // Init the variables.
    this->serial_device = serial_device;
    this->GLCD_Type.baud = baud;
    this->GLCD_Type.flow_control = flow_control;
    
    this->serial_device->begin(this->GLCD_Type.baud);
    
    // Set the baud,
    uint8_t command[3] = {254, 57, this->GLCD_Type.baud};
    _send_command(command, sizeof(command));
    
    // Check to see if we need to use flow control
    if(GLCD_Type.flow_control){
        uint8_t command[3] = {254, 58, 1};
        _send_command(command, sizeof(command));
    }
    else{
        uint8_t command[2] = {254, 59};
        _send_command(command, sizeof(command));
    }
}

// Moves cursor to home position.
void debug_GLCD_GLK12232::set_cursor_to_home_pos(void){
    
    uint8_t command[2] = {254, 72};
    _send_command(command, sizeof(command));
    
}

// Sets the cursor to the position described \
- [column] [row]
void debug_GLCD_GLK12232::set_cursor_to_pos(uint8_t column, uint8_t row){
    
    uint8_t command[4] = {254, 71, column, row};
    _send_command(command, sizeof(command));
    
}

// Sets the cursor to a specific pixel \
- [x] [y]
void debug_GLCD_GLK12232::set_cursor_to_pix(uint8_t x, uint8_t y){
 
    uint8_t command[4] = {254, 121, x, y};
    _send_command(command, sizeof(command));
}

// Toggles auto-scroll
void debug_GLCD_GLK12232::toggle_autoscroll(bool auto_scroll){
    
    if(auto_scroll){
        uint8_t command[2] = {254, 81};
        _send_command(command, sizeof(command));
    }else{
        uint8_t command[2] = {254, 82};
        _send_command(command, sizeof(command));
    }   
}

// Uploads a bitmap to the device
void debug_GLCD_GLK12232::upload_bitmap(uint8_t bitmap_id, uint16_t size, void* data){
    
    // NOT implemented
    
}

// Draws bitmap from memory
void debug_GLCD_GLK12232::draw_bitmap_from_mem(uint8_t bitmap_id, uint8_t x, uint8_t y){
    
    // NOT implemented
    
}

// This draws the bitmap directly
void debug_GLCD_GLK12232::draw_bitmap_directly(uint8_t x, uint8_t y, uint8_t width,
                                               uint8_t heigth, uint8_t data){
    
    // NOT implemented
}

// Sets teh drawing colour.
void debug_GLCD_GLK12232::set_drawing_colour(uint8_t colour){
    
    uint8_t command[3] = {254, 99, colour};
    _send_command(command, sizeof(command));
}

// Sets a pixel
void debug_GLCD_GLK12232::draw_pixel(uint8_t x, uint8_t y){
    
    uint8_t command[4] = {254, 112, x, y};
    _send_command(command, sizeof(command));
}

// Draws a line
void debug_GLCD_GLK12232::draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
    
    uint8_t command[6] = {254, 108, x1, y1, x2, y2};
    _send_command(command, sizeof(command));
}

// Draws a line from the x2, y2 defined above
void debug_GLCD_GLK12232::continue_line(uint8_t x, uint8_t y){
    
    uint8_t command[4] = {254, 101, x, y};
    _send_command(command, sizeof(command));
}

// Draws a rectangle
void debug_GLCD_GLK12232::draw_rectangle(uint8_t colour, uint8_t x1, uint8_t y1,
                                                uint8_t x2, uint8_t y2){
    
    uint8_t command[7] = {254, 114, colour, x1, y1, x2, y2};
    _send_command(command, sizeof(command));
}

// Draws a solid rectangle
void debug_GLCD_GLK12232::draw_solid_rectangle(uint8_t colour, uint8_t x1, uint8_t y1,
                                               uint8_t x2, uint8_t y2){
    
    uint8_t command[7] = {254, 120, colour, x1, y1, x2, y2};
    _send_command(command, sizeof(command));
}

// Initializes a bar graph
void debug_GLCD_GLK12232::init_bar_graph(uint8_t graph_id, uint8_t type, uint8_t x1,
                                                uint8_t y1, uint8_t x2, uint8_t y2){
    
    // NOT implemented
    
}

// Draws a bar graph
void debug_GLCD_GLK12232::draw_bar_graph(uint8_t graph_id, void* value){
    
    // NOT implemented
    
}

// Clears teh screen
void debug_GLCD_GLK12232::clear_screen(void){
    
    uint8_t command[2] = {254, 88};
    _send_command(command, sizeof(command));
}

// Turn On display
void debug_GLCD_GLK12232::toggle_display(bool display_on, uint8_t time){
    
    uint8_t command[4] = {0, 0, 0};
  
    if(display_on){
        uint8_t command[4] = {254, 66, time};
    }
    else{
        uint8_t command[3] = {254, 70};
    }
    _send_command(command, sizeof(command));
    
    display_on = ~display_on;
}

// Set brightness
void debug_GLCD_GLK12232::set_brightness(uint8_t brightness){
    
    uint8_t command[3] = {254, 153, brightness};
    _send_command(command, sizeof(command));
    
}

// This saves and sets teh brightness entered.
void debug_GLCD_GLK12232::set_save_brightness(uint8_t brightness){
    
    uint8_t command[3] = {254, 152, brightness};
    _send_command(command, sizeof(command));
}

// Sets the contrast ratio
void debug_GLCD_GLK12232::set_contrast(uint8_t contrast){
 
    uint8_t command[3] = {254, 80, contrast};
    _send_command(command, sizeof(command));
    
}

// This saves and sets teh contrast entered.
void debug_GLCD_GLK12232::set_save_contrast(uint8_t contrast){
    
    uint8_t command[3] = {254, 145, contrast};
    _send_command(command, sizeof(command));
    
}

/***
 
 NOTE: The filesystem/security portion of the user guide was not implemented
 due to the fact that it was not used in this project ocntext.
 
 ***/

// Read the firmware version
uint8_t* debug_GLCD_GLK12232::read_version(void){
    
    uint8_t command[2] = {254, 54};
    _send_command(command, sizeof(command));
    _read_command();
    
}

// Reads the module type.
uint8_t* debug_GLCD_GLK12232::read_module_type(void){
    
    uint8_t command[2] = {254, 55};
    _send_command(command, sizeof(command));
    _read_command(); 
}


