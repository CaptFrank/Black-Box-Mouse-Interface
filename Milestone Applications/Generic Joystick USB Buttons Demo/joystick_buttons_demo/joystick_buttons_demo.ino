/* Arduino USB Joystick HID Buttons demo */

/**
 * This is the demonstration file... We use only the buttons.
 * This demo is simple, the digital input of a button array, 
 * is captured and mapped to a USB HID report, where it is then
 * sent to the computer as a joystick command. This is implemented
 * to show that it is easy to interface with the physical.
 */

/**
 * These defines, define the sequential order of the button array.
 * These defines, define the port map for the buttons.
 */
 #define PIN_DIGI_1      5
 #define PIN_DIGI_2      6
 
/**
 * This defines the number of buttons and the number of axis.
 */
#define NUM_AXES	3	       // 8 axes, X, Y, Z, etc

/**
 * This is the usb joystick structure that the USB PHY, 
 * will interpret.
 */
typedef struct joyReport_t {
    int8_t x;
    int8_t y;
    int8_t z;
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
  
    
    // activate the serial lines
    Serial.begin(115200);
    delay(200);
    
    pinMode(PIN_DIGI_1, INPUT);
    pinMode(PIN_DIGI_2, INPUT);
    // initialize the buttons and axis

    joyReport.x = (int) 0;
    joyReport.y = (int) 0;
    joyReport.z = (int) 0;

    joyReport.button = 0;
}

// Send an HID report to the USB interface
void sendJoyReport(struct joyReport_t *report){
    Serial.write((uint8_t *)report, sizeof(joyReport_t));
}

/* Turn each button on in sequence 1 - 40, then off 1 - 40
 * add values to each axis each loop
 */
void loop() {
    // read a button and map the input to the USB report.
    
    int digi_1 = digitalRead(PIN_DIGI_1);
    delay(10);
    int digi_2 = digitalRead(PIN_DIGI_2);
    delay(10);
    
    joyReport.button = 0;
    
    if(digi_1 == 1){
      joyReport.button |= 1 << 1;
    }if(digi_2 == 1){
      joyReport.button |= 1 ;
    }
//    Serial.println(joyReport.button);
    
    // send the report
    sendJoyReport(&joyReport);
    delay(100);
}
