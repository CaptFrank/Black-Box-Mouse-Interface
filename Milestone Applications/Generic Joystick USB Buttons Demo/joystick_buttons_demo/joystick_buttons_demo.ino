/* Arduino USB Joystick HID Buttons demo */

/**
 * This is the demonstration file... We use only the buttons.
 * This demo is simple, the digital input of a button array, 
 * is captured and mapped to a USB HID report, where it is then
 * sent to the computer as a joystick command. This is implemented
 * to show that it is easy to interface with the physical.
 */

<<<<<<< HEAD
/**
 * These defines, define the sequential order of the button array.
 * These defines, define the port map for the buttons.
 */
#define FIRST_BUTTON_PIN   5
#define LAST_BUTTON_PIN    6

/**
 * This defines the number of buttons and the number of axis.
 */
#define NUM_BUTTONS	3
#define NUM_AXES	3	       // 8 axes, X, Y, Z, etc

/**
 * This is the usb joystick structure that the USB PHY, 
 * will interpret.
 */
typedef struct joyReport_t {
    int16_t axis[NUM_AXES];
    uint8_t button; // 8 buttons per byte
} joyReport_t;
=======
#define NUM_AXES	3	       // 8 axes, X, Y, Z, etc

#define PIN_1           5
#define PIN_2           6
#define APIN_1          A7


typedef struct joyReport_t {
    int8_t x;
    int8_t y;
    int8_t z;
    uint8_t buttons; // 8 buttons per byte
    uint8_t spacer;
} joyReport_t;

joyReport_t joyReport;
>>>>>>> c0af0e9eb28b412a31850c3c6dc6941ff65bc901

joyReport_t joyReport;

// Function Definitions
void setup(void);
void loop(void);
void sendJoyReport(joyReport_t *report);


// The setup loop
void setup()
{
<<<<<<< HEAD
    // activate the serial lines
    Serial.begin(115200);
    delay(200);
    
    // initialize the buttons and axis
    for (uint8_t ind=0; ind<8; ind++) {
        joyReport.axis[ind] = ind*1000;
    }
    for (uint8_t ind=0; ind<sizeof(joyReport.button); ind++) {
        joyReport.button[ind] = 0;
    }
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
    for(byte i = FIRST_BUTTON_PIN; i < LAST_BUTTON_PIN; i++){
        joystick.button[i - FIRST_BUTTON_PIN] = digitalRead(i);
    }
    
    // send the report
    sendJoyReport(&joyReport);
    delay(100);
=======
    
    joyReport.x = (int8_t)100;
    joyReport.y = (int8_t)100;
    joyReport.z = (int8_t)100;
    joyReport.buttons = 0;
    
    pinMode(PIN_1, INPUT);
    pinMode(PIN_2, INPUT);
    
    Serial.begin(115200);
    
    // Making the ADC work faster... 16MHZ
    bitClear(ADCSRA,ADPS0) ;
    bitClear(ADCSRA,ADPS1) ;
    bitSet(ADCSRA,ADPS2) ;
    
    delay(200);
}

void loop() 
{
    delay(200);
    joyReport.buttons |= digitalRead(PIN_1) << 1;
    joyReport.buttons |= digitalRead(PIN_2);
    
    joyReport.x = (int8_t) map(analogRead(APIN_1), 0, 1023, 0, 255);

    Serial.write((uint8_t *)&joyReport, sizeof(joyReport_t));
    joyReport.buttons = 0;

>>>>>>> c0af0e9eb28b412a31850c3c6dc6941ff65bc901
}
