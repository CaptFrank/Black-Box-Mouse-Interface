/* Arduino USB Mouse HID demo */

/* Author: Darran Hunt
 * Release into the public domain.
 */

 #define PIN_DIGI_1      5
 #define PIN_DIGI_2      6
 #define APIN_1          A7

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
  
    randomSeed(analogRead(0));
    
    mouseReport.x = (int8_t) 0;
    mouseReport.y = (int8_t) 0;
    mouseReport.buttons = (uint8_t) 0;
    
    Serial.begin(9600);
    delay(200);
}

/* Move the mouse in a clockwise square every 5 seconds */
void loop() 
{
    delay(100);
    
    mouseReport.x = random(100);
    mouseReport.y = random(100);
    mouseReport.buttons = random(8);
   
    Serial.write((uint8_t *)&mouseReport, 4); 
}
