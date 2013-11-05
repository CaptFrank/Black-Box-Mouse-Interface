//
//  Debug_API_GLCD.cpp
//  GLCD_Debug_Library
//
//  Created by Francis Papineau on 2013-10-10.
//
//

#include "Debug_API_GLCD.h"

// Defining a settings container.
GLCD_serial_configs_t GLCD_Type;

// ---------------------------------------------------------------------------------------

// PRIVATE METHODS

// Sends a command to the remote screen
void debug_GLCD_GLK12232::_send_command(void* command, uint8_t size){
    
    // send to the bus.
    this.GLCD_Type.serial_device->write((uint8_t*)&command, size)
}

// ---------------------------------------------------------------------------------------

// PUBLIC METHODS

// Init the serial device handler.
debug_GLCD_GLK12232::debug_GLCD_GLK12232(HardwareSerial* serial_device, uint16_t* baud, bool flow_control){
    
    // Init the variables.
    this.serial_device = serial_device;
    this.baud = &baud;
    this.flow_control = flow_control;
    
}

// Send configs.
void debug_GLCD_GLK12232::set_configs(void){
    
    // Set the baud,
    uint8_t command[3] = {0xfe, 0x39, this.GLCD_Type.baud};
    _send_command((void*)&command, sizeof(command));
    
    // Check to see if we need to use flow control
    if(flow_control){
        uint8_t command[3] = {0xfe, 0x3a, 0b01};
        _send_command((void*)&command, sizeof(command));
    }
    else{
        uint8_t command[2] = {0xfe, 0x3b};
        _send_command((void*)&command, sizeof(command));
    }
}

// Moves cursor to home position.
void debug_GLCD_GLK12232::set_cursor_to_home_pos(void){
    
    uint8_t command[2] = {0xfe, 0x48};
    _send_command((void*)&command, sizeof(command));
    
}

// Sets the cursor to the position described \
- [column] [row]
void debug_GLCD_GLK12232::set_cursor_to_pos(uint8_t* column, uint8_t* row){
    
    uint8_t command[2] = {0xfe, 0x47, &column, &row};
    _send_command((void*)&command, sizeof(command));
    
}

// Sets the cursor to a specific pixel \
- [x] [y]
void debug_GLCD_GLK12232::set_cursor_to_pix(uint8_t* x, uint8_t* y){
 
    uint8_t command[4] = {0xfe, 0x79, &x, &y};
    _send_command((void*)&command, sizeof(command));
}

// Toggles auto-scroll
void debug_GLCD_GLK12232::toggle_autoscroll(bool* auto_scroll){
    
    if(&auto_scroll){
        uint8_t command[2] = {0xfe, 0x51};
        _send_command((void*)&command, sizeof(command));
    }else{
        uint8_t command[2] = {0xfe, 0x52};
        _send_command((void*)&command, sizeof(command));
    }
    &auto_scroll = ~&auto_scroll;
    
}

// Uploads a bitmap to the device
void debug_GLCD_GLK12232::upload_bitmap(uint8_t* bitmap_id, uint16_t* size, void* data){
    
    // NOT implemented
    
}

// Draws bitmap from memory
void debug_GLCD_GLK12232::draw_bitmap_from_mem(uint8_t* bitmap_id, uint8_t* x, uint8_t* y){
    
    // NOT implemented
    
}

// This draws the bitmap directly
void debug_GLCD_GLK12232::draw_bitmap_directly(uint8_t* x, uint8_t* y, uint8_t* width,
                                               uint8_t* heigth, uint8_t* data){
    
    // NOT implemented
}

// Sets teh drawing colour.
void debug_GLCD_GLK12232::set_drawing_colour(uint8_t* colour){
    
    uint8_t command[3] = {0xfe, 0x63, &colour};
    _send_command((void*)&command, sizeof(command));
}

// Sets a pixel
void debug_GLCD_GLK12232::draw_pixel(uint8_t* x, uint8_t* y){
    
    uint8_t command[4] = {0xfe, 0x70, &x, &y};
    _send_command((void*)&command, sizeof(command));
}

// Draws a line
void debug_GLCD_GLK12232::draw_line(uint8_t* x1, uint8_t* y1, uint8_t* x2, uint8_t* y2){
    
    uint8_t command[6] = {0xfe, 0x6c, &x1, &y1, &x2, &y2};
    _send_command((void*)&command, sizeof(command));
}

// Draws a line from the x2, y2 defined above
void debug_GLCD_GLK12232::continue_line(uint8_t* x, uint8_t* y){
    
    uint8_t command[4] = {0xfe, 0x65, &x, &y};
    _send_command((void*)&command, sizeof(command));
}

// Draws a rectangle
void debug_GLCD_GLK12232::draw_rectangle(uint8_t* colour, uint8_t* x1, uint8_t* y1,
                                                uint8_t* x2, uint8_t* y2){
    
    uint8_t command[7] = {0xfe, 0x72, &colour, &x1, &y1, &x2, &y2};
    _send_command((void*)&command, sizeof(command));
}

// Draws a solid rectangle
void debug_GLCD_GLK12232::draw_solid_rectangle(uint8_t* colour, uint8_t* x1, uint8_t* y1,
                                               uint8_t* x2, uint8_t* y2){
    
    uint8_t command[7] = {0xfe, 0x78, &colour, &x1, &y1, &x2, &y2};
    _send_command((void*)&command, sizeof(command));
}

// Initializes a bar graph
void debug_GLCD_GLK12232::init_bar_graph(uint8_t* graph_id, uint8_t* type, uint8_t* x1,
                                                uint8_t* y1, uint8_t* x2, uint8_t* y2){
    
    uint8_t command[8] = {0xfe, 0x69, &graph_id, &type, &x1, &y1, &x2, &y2};
    _send_command((void*)&command, sizeof(command));
}

// Draws a bar graph
void debug_GLCD_GLK12232::draw_bar_graph(uint8_t* graph_id, void* value){
    
    uint8_t command[4] = {0xfe, 0x69, &graph_id, &(uint8_t*)(value)};
    _send_command((void*)&command, sizeof(command));
}

// Clears teh screen
void debug_GLCD_GLK12232::clear_screen(void){
    
    uint8_t command[2] = {0xfe, 0x58};
    _send_command((void*)&command, sizeof(command));
}

// Turn On display
void debug_GLCD_GLK12232::toggle_display(bool* display_on, uint8_t time){
    
    if(&display_on){
        uint8_t command[4] = {0xfe, 0x98, 0x42, time};
    }
    else{
        uint8_t command[3] = {0xfe, 0x98, 0x46};
    }
    _send_command((void*)&command, sizeof(command));
    
    &display = ~&display;
}

// Set brightness
void debug_GLCD_GLK12232::set_brightness(uint8_t* brightness){
    
    uint8_t command[3] = {0xfe, 0x99, &brightness};
    _send_command((void*)&command, sizeof(command));
    
}

// This saves and sets teh brightness entered.
void debug_GLCD_GLK12232::set_save_brightness(uint8_t* brightness){
    
    uint8_t command[3] = {0xfe, 0x98, &brightness};
    _send_command((void*)&command, sizeof(command));
}

// Sets the contrast ratio
void debug_GLCD_GLK12232::set_contrast(uint8_t* contrast){
 
    uint8_t command[3] = {0xfe, 0x50, &contrast};
    _send_command((void*)&command, sizeof(command));
    
}

// This saves and sets teh contrast entered.
void debug_GLCD_GLK12232::set_save_contrast(uint8_t* contrast){
    
    uint8_t command[3] = {0xfe, 0x91, &contrast};
    _send_command((void*)&command, sizeof(command));
    
}

/***
 
 NOTE: The filesystem/security portion of the user guide was not implemented
 due to the fact that it was not used in this project ocntext.
 
 ***/

// Read the firmware version
uint8_t* debug_GLCD_GLK12232::read_version(void){
    
    uint8_t command[2] = {0xfe, 0x36};
    _send_command((void*)&command, sizeof(command));
    
}

// Reads the module type.
uint8_t* debug_GLCD_GLK12232::read_module_type(void){
    
    uint8_t command[2] = {0xfe, 0x37};
    _send_command((void*)&command, sizeof(command));
    
}


