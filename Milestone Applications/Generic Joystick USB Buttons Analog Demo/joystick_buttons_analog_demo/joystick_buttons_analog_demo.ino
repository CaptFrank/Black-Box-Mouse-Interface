/* Arduino USB Joystick HID demo */

/* Author: Darran Hunt
 * Released into the public domain.
 */

#define NUM_AXES	3	       // 8 axes, X, Y, Z, etc

#define X_AXIS          1
#define Y_AXIS          0
#define BUTTON_A        5
#define BUTTON_B        3
#define BUTTON_C        4

#define NUM_INPUTS      5

typedef struct joyReport_t {
    int8_t x;
    int8_t y;
    int8_t z;
    union {
      struct{
        byte button_1 : 1;
        byte button_2 : 1;
        byte button_3 : 1;
        byte button_4 : 1;
        byte button_5 : 1;
        byte button_6 : 1;
        byte button_7 : 1;
        byte button_8 : 1;
      }buttons_bits;
      uint8_t buttons_byte;
    }buttons; // 8 buttons per byte
    uint8_t spacer;
} joyReport_t;

joyReport_t joyReport;

void setup(void);
void loop(void);

void setup() 
{
    
    joyReport.x = 0;
    joyReport.y = 0;
    joyReport.buttons.buttons_byte = 0;
 
    pinMode(X_AXIS, INPUT);
    pinMode(Y_AXIS, INPUT);
    pinMode(BUTTON_A, INPUT);
    pinMode(BUTTON_B, INPUT);
    pinMode(BUTTON_C, INPUT);

    Serial.begin(115200);
    
}

void loop() 
{
    delay(100);
    
    if(digitalRead(BUTTON_A) == HIGH){
      joyReport.buttons.buttons_bits.button_1 &= 0;
    } else {
      joyReport.buttons.buttons_bits.button_1 |= 1;
    }
    
    if(digitalRead(BUTTON_B) == HIGH){
      joyReport.buttons.buttons_bits.button_2 &= 0;
    } else {
      joyReport.buttons.buttons_bits.button_2 |= 1;
    }
    
    if(digitalRead(BUTTON_C) == HIGH){
      joyReport.buttons.buttons_bits.button_3 &= 0;
    } else {
      joyReport.buttons.buttons_bits.button_3 |= 1;
    }
    
    joyReport.x = (int8_t) map(analogRead(X_AXIS), 0, 1023, -100, 100);
    joyReport.y = (int8_t) map(analogRead(Y_AXIS), 0, 1023, -100, 100);

    Serial.write((uint8_t *)&joyReport, sizeof(joyReport_t));
    joyReport.buttons.buttons_byte = 0;

}
