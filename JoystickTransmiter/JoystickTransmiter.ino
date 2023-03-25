#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
//Transmiter code for arduino nano
RH_ASK driver(2000, 11, 2); //Data transmiter through pin D2
void setup()
{
    pinMode(A4, OUTPUT); // GND for joystick
    pinMode(A5, OUTPUT); // VCC for joystick
    pinMode(6, INPUT); // SW joystick
    digitalWrite(A4, LOW);
    digitalWrite(A5, HIGH);
    
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}
int analogXValue = 0;    // variable to hold the analog value
int analogYValue = 0;

String numTstr(int num)
{
  if (num < 10) {
    return String("000") + String(num);
  } else if (num < 100) {
    return String("00") + String(num);
  } else if (num < 1000) {
    return String("0") + String(num);
  } else {
    return String(num);  
  }  
}


void loop()
{
    analogXValue = analogRead(1);
    analogYValue = analogRead(2);
    String msgStr = numTstr(analogXValue) + numTstr(analogYValue);
    char msg[9];
    msgStr.toCharArray(msg, sizeof(msg));
    Serial.println(msg);
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(100);
}
