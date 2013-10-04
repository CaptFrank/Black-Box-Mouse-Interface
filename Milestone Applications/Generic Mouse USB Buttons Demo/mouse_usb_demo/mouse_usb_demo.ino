/* Arduino USB Mouse HID demo */

/* Author: Darran Hunt
 * Release into the public domain.
 */

 #define PIN_DIGI_1      5
 #define PIN_DIGI_2      6

struct {
    uint8_t buttons;
    int8_t x;
    int8_t y;
} mouseReport;

uint8_t nullReport[4] = { 0, 0, 0, 0 };

void setup();
void loop();

void setup() 
{
    Serial.begin(9600);
    delay(200);
}

/* Move the mouse in a clockwise square every 5 seconds */
void loop() 
{
    int ind;
    delay(5000);

    mouseReport.x = 0;

    mouseReport.x = -2;
    for (ind=0; ind<20; ind++) {
	Serial.write((uint8_t *)&mouseReport, 4);
	Serial.write((uint8_t *)&nullReport, 4);
    }

    mouseReport.x = 0;
    mouseReport.y = -2;
    for (ind=0; ind<20; ind++) {
	Serial.write((uint8_t *)&mouseReport, 4);
	Serial.write((uint8_t *)&nullReport, 4);
    }

    mouseReport.x = 2;
    mouseReport.y = 0;
    for (ind=0; ind<20; ind++) {
	Serial.write((uint8_t *)&mouseReport, 4);
	Serial.write((uint8_t *)&nullReport, 4);
    }

    mouseReport.x = 0;
    mouseReport.y = 2;
    for (ind=0; ind<20; ind++) {
	Serial.write((uint8_t *)&mouseReport, 4);
	Serial.write((uint8_t *)&nullReport, 4);
    }
    
    
    // read a button and map the input to the USB report.
    mouseReport.buttons |= digitalRead(PIN_DIGI_1) << 1;
    mouseReport.buttons |= digitalRead(PIN_DIGI_2);
    
}
