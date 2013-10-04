/* Arduino USB Joystick HID demo */

/* Author: Darran Hunt
 * Released into the public domain.
 */

#undef DEBUG

#define NUM_BUTTONS	2
#define NUM_AXES	3	       // 8 axes, X, Y, Z, etc

#define PIN_1           5
#define PIN_2           6


struct joyReport_t {
    int8_t axis[NUM_AXES];
    uint8_t buttons; // 8 buttons per byte
} joyReport;

uint8_t nullReport[5] = { 0, 0, 0, 0, 0 };

void setup(void);
void loop(void);


void setup() 
{
    Serial.begin(115200);
    delay(200);
    
    pinMode(PIN_1, INPUT);
    pinMode(PIN_2, INPUT);
}

void loop() 
{
    joyReport.buttons |= digitalRead(PIN_1) << 1;
    joyReport.buttons |= digitalRead(PIN_2);

    Serial.write((uint8_t *)&joyReport, sizeof(joyReport_t));
    Serial.write((uint8_t *)&nullReport, 5);
    delay(100);
}
