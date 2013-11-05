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
  
    mouseReport.x = (int8_t) 0;
    mouseReport.y = (int8_t) 0;
    mouseReport.buttons = (uint8_t) 0;
    
    pinMode(PIN_DIGI_1, INPUT);
    pinMode(PIN_DIGI_2, INPUT);
    
    Serial.begin(9600);
    
    // Making the ADC work faster... 16MHZ
    bitClear(ADCSRA,ADPS0) ;
    bitClear(ADCSRA,ADPS1) ;
    bitSet(ADCSRA,ADPS2) ;
    
    delay(200);
}

/* Move the mouse in a clockwise square every 5 seconds */
void loop() 
{
    delay(100);
    
    // read a button and map the input to the USB report.
    mouseReport.buttons |= digitalRead(PIN_DIGI_1) << 1;
    mouseReport.buttons |= digitalRead(PIN_DIGI_2);
   
   
    mouseReport.x = (int8_t) map(analogRead(APIN_1), 0, 1023, -100, 100);
    
    Serial.write((uint8_t *)&mouseReport, 4);
    //Serial.write((uint8_t *)&nullReport, 4);
    
    mouseReport.buttons = 0;
    
}
