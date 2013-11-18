/* Arduino USB Joystick HID Buttons demo */

#include "ADXL335.h"

/**
 * This is the demonstration file... We use only the buttons.
 * This demo is simple, the digital input of a button array, 
 * is captured and mapped to a USB HID report, where it is then
 * sent to the computer as a joystick command. This is implemented
 * to show that it is easy to interface with the physical.
 */

#define NUM_AXES	3	       // 8 axes, X, Y, Z, etc

#define X_AXIS          A5
#define Y_AXIS          A4
#define Z_AXIS          A3

#define BUTTON_1        7
#define BUTTON_2        8
#define BUTTON_3        9

#define GND             A2
#define VCC             A0

#define AREF            3.3
#define AMIN            -100
#define AMAX            100

ADXL335 accel(X_AXIS, Y_AXIS, Z_AXIS, AREF);

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

// Function Definitions
void setup(void);
void loop(void);

// The setup loop
void setup()
{ 
    joyReport.x = 0;
    joyReport.y = 0;
    joyReport.z = 0;
    joyReport.buttons.buttons_byte = 0;
    
    
    pinMode(X_AXIS, INPUT);
    pinMode(Y_AXIS, INPUT);
    pinMode(Z_AXIS, INPUT);
    
    pinMode(BUTTON_1, INPUT);
    pinMode(BUTTON_2, INPUT);
    pinMode(BUTTON_3, INPUT);
    
    pinMode(GND, OUTPUT);
    pinMode(VCC, OUTPUT);
    
    digitalWrite(GND, LOW);
    digitalWrite(VCC, HIGH);
    
    analogReference(EXTERNAL);
    
    Serial.begin(115200);
    
    delay(200);
}

void loop() 
{
    delay(100);
    
    accel.update();

    joyReport.buttons.buttons_bits.button_1 = digitalRead(BUTTON_1);
    joyReport.buttons.buttons_bits.button_2 = digitalRead(BUTTON_2);
    joyReport.buttons.buttons_bits.button_3 = digitalRead(BUTTON_3);
    
    joyReport.x = (int8_t) (accel.getX()*100.0);
    joyReport.y = (int8_t) (accel.getY()*100.0);
    joyReport.z = (int8_t) (accel.getZ()*100.0);
    
//    Serial.print("x :");
//    Serial.println(joyReport.x);
//    Serial.print("y :");
//    Serial.println(joyReport.y);
//    Serial.print("z :");
//    Serial.println(joyReport.z);

    Serial.write((uint8_t *)&joyReport, sizeof(joyReport_t));
    joyReport.buttons.buttons_byte = 0;

}

