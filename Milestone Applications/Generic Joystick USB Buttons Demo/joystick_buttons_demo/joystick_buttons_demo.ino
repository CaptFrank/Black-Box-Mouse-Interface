/* Arduino USB Joystick HID demo */

/* Author: Darran Hunt
 * Released into the public domain.
 */

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

uint8_t nullReport[5] = { 0, 0, 0, 0, 0 };

void setup(void);
void loop(void);


void setup() 
{
    
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

}
