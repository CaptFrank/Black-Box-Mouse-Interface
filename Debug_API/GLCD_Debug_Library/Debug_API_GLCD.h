//
//  Debug_API_GLCD.h
//  GLCD_Debug_Library
//
//  Created by Francis Papineau on 2013-10-10.
//
//

#ifndef GLCD_Debug_Library_Debug_API_GLCD_h
#define GLCD_Debug_Library_Debug_API_GLCD_h


class debug_GLCD_GLK12232 {

private:
    
    typedef struct {
    
        HardwareSerial*         serial_device;
        bool                    flow_control;
        bool                    auto_scroll;
        bool                    display_on;
        uint8_t                 brighness;
        uint8_t                 contrast;
        uint16_t                baud;
        
    } GLCD_serial_configs_t;
    
    // Defining a settings container.
    GLCD_serial_configs_t GLCD_Type;
    
    // Sends a command
    void _send_command(void* command, uint8_t size);

public:
    
    // Init the serial device handler.
    debug_GLCD_GLK12232(HardwareSerial* serial_device, uint16_t* baud, bool flow_control);
    
    // Send configs.
    void set_configs(void);
    
    // Moves cursor to home position.
    void set_cursor_to_home_pos(void);
    
    // Sets the cursor to the position described \
        - [column] [row]
    void set_cursor_to_pos(uint8_t* column, uint8_t* row);
    
    // Sets the cursor to a specific pixel \
        - [x] [y]
    void set_cursor_to_pix(uint8_t* x, uint8_t* y);
    
    // Sets the colour
    void set_colour(uint8_t* colour);
    
    // Toggles auto-scroll
    void toggle_autoscroll(bool* auto_scroll);
    
    // Uploads a bitmap to the device
    void upload_bitmap(uint8_t* bitmap_id, uint16_t* size, void* data);
    
    // Draws bitmap from memory
    void draw_bitmap_from_mem(uint8_t* bitmap_id, uint8_t* x, uint8_t* y);
    
    // This draws the bitmap directly
    void draw_bitmap_directly(uint8_t* x, uint8_t* y, uint8_t* width,
                                                uint8_t* heigth, uint8_t* data);
    
    // Sets a drwaing colour
    void set_drawing_colour(uint8_t* colour);
    
    // Sets a pixel
    void draw_pixel(uint8_t* x, uint8_t* y);
    
    // Draws a line
    void draw_line(uint8_t* x1, uint8_t* y1, uint8_t* x2, uint8_t* y2);
    
    // Draws a line from the x2, y2 defined above
    void continue_line(uint8_t* x, uint8_t* y);
    
    // Draws a rectangle
    void draw_rectangle(uint8_t* colour, uint8_t* x1, uint8_t* y1,
                                                uint8_t* x2, uint8_t* y2);
    
    // Draws a solid rectangle
    void draw_solid_rectangle(uint8_t* colour, uint8_t* x1, uint8_t* y1,
                                                uint8_t* x2, uint8_t* y2);
    
    // Initializes a bar graph
    void init_bar_graph(uint8_t* graph_id, uint8_t* type, uint8_t* x1,
                                                uint8_t* y1, uint8_t* x2, uint8_t* y2);
    
    // Draws a bar graph
    void draw_bar_graph(uint8_t* graph_id, void* value);
    
    // Clears teh screen
    void clear_screen(void);
    
    // Turn On display
    void toggle_display(bool* display_on, uint8_t time = 10);
    
    // Set brightness
    void set_brightness(uint8_t* brightness);
    
    // This saves and sets teh brightness entered.
    void set_save_brightness(uint8_t* brightness);
    
    // Sets the contrast ratio
    void set_contrast(uint8_t* contrast);
    
    // This saves and sets teh contrast entered.
    void set_save_contrast(uint8_t* contrast);
    
    /***
     
     NOTE: The filesystem/security portion of the user guide was not implemented
     due to the fact that it was not used in this project ocntext.
     
     ***/
    
    // Read the firmware version
    uint8_t* read_version(void);
    
    // Reads the module type.
    uint8_t* read_module_type(void);
    
};


#endif
