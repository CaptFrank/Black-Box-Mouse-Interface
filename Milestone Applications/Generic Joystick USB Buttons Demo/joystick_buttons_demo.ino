/* Arduino USB Joystick HID Buttons demo */

/**
 * This is the demonstration file... We use only the buttons.
 * This demo is simple, the digital input of a button array, 
 * is captured and mapped to a USB HID report, where it is then
 * sent to the computer as a joystick command. This is implemented
 * to show that it is easy to interface with the physical.
 */

/**
 * This defines the number of buttons and the number of axis.
 */
#define BUTTON_1    5
#define BUTTON_2    6
#define NUM_AXES	3	       // 8 axes, X, Y, Z, etc

/**
 * This is the usb joystick structure that the USB PHY, 
 * will interpret.
 */
typedef struct joyReport_t {
    int16_t x;
    int16_t y;
    int16_t z;
    uint8_t button; // 8 buttons per byte
} joyReport_t;

joyReport_t joyReport;

// Function Definitions
void setup(void);
void loop(void);
void sendJoyReport(joyReport_t *report);


// The setup loop
void setup()
{

    pinMode(BUTTON_1, INPUT);
    pinMode(BUTTON_2, INPUT);
    
    // activate the serial lines
    Serial.begin(115200);
    delay(200);
    joyReport.x = 100;
    joyReport.y = 100;
    joyReport.z = 100;
}

// Send an HID report to the USB interface
void sendJoyReport(struct joyReport_t *report){
    Serial.write((uint8_t *)report, sizeof(joyReport_t));
}

/* Turn each button on in sequence 1 - 40, then off 1 - 40
 * add values to each axis each loop
 */
void loop() {
    
    int button1 = digitalRead(BUTTON_1);
    int button2 = digitalRead(BUTTON_2);
    
    joyReport.button = 0;
    
    if(button1){
        joyReport.button |= 0b1 << 1;
    }
    if(button2){
        joyReport.button |= 0b1;
    }
    
    // send the report
    sendJoyReport(&joyReport);
    delay(100);
}
