/* Arduino USB Joystick HID Buttons demo */

/**
 * This is the demonstration file... We use only the buttons.
 * This demo is simple, the digital input of a button array, 
 * is captured and mapped to a USB HID report, where it is then
 * sent to the computer as a joystick command. This is implemented
 * to show that it is easy to interface with the physical.
 */

#define NUM_AXES	3	       // 8 axes, X, Y, Z, etc

#define X_AXIS          0
#define Y_AXIS          1
#define Z_AXIS          2

#define BUTTON_1        2
#define BUTTON_2        3
#define BUTTON_3        4

#define GND             3
#define VCC             4
#define V3              5

#define SAMPLE_SIZE     5

#define MINVAL          265
#define MAXVAL          402

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
    pinMode(V3, OUTPUT);
    
    analogWrite(GND, 0);
    analogWrite(VCC, 255);
    analogWrite(V3, 255);
    
    Serial.begin(115200);
    
    delay(200);
}

void loop() 
{
    delay(100);

    if(digitalRead(BUTTON_1) == HIGH){
      joyReport.buttons.buttons_bits.button_1 &= 0;
    } else {
      joyReport.buttons.buttons_bits.button_1 |= 1;
    }
    
    if(digitalRead(BUTTON_2) == HIGH){
      joyReport.buttons.buttons_bits.button_2 &= 0;
    } else {
      joyReport.buttons.buttons_bits.button_2 |= 1;
    }
    
    if(digitalRead(BUTTON_3) == HIGH){
      joyReport.buttons.buttons_bits.button_3 &= 0;
    } else {
      joyReport.buttons.buttons_bits.button_3 |= 1;
    }
    
    joyReport.x = (int8_t) map(ReadAxis(X_AXIS), MINVAL, MAXVAL, -100, 100);
    joyReport.y = (int8_t) map(ReadAxis(Y_AXIS), MINVAL, MAXVAL, -100, 100);
    joyReport.z = (int8_t) map(ReadAxis(Z_AXIS), MINVAL, MAXVAL, -100, 100);

    Serial.write((uint8_t *)&joyReport, sizeof(joyReport_t));
    joyReport.buttons.buttons_byte = 0;

}

//
// Read "sampleSize" samples and report the average
//
int ReadAxis(int axisPin)
{
  long reading = 0;
  analogRead(axisPin);
  delay(1);
  for (int i = 0; i < SAMPLE_SIZE; i++)
  {
    reading += analogRead(axisPin);
  }
  return reading/SAMPLE_SIZE;
}
