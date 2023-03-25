//#include <Servo.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

//Servo servo;
//int pos = 0; //Aktualna pozycja serwa 0-180
//int change = 1; //Co ile ma się zmieniać pozycja serwa?
const int motorPin1  = 2; // Pin  7 of L293
const int motorEn = 3;
const int motorPin2  = 4;  // Pin  2 of L293

const int SmotorPin1  = 5; // Pin  7 of L293
const int SmotorEn = 6;
const int SmotorPin2  = 7;  // Pin  2 of L293

const int receiverPin = 11;

const int buzzerPin = 12;
const int distIn = 8;
RH_ASK driver(2000, receiverPin, 10);
void setup()
{
    Serial.begin(9600);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
    pinMode(motorPin1, OUTPUT);
    pinMode(motorEn, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    
    pinMode(SmotorPin1, OUTPUT);
    pinMode(SmotorEn, OUTPUT);
    pinMode(SmotorPin2, OUTPUT);

    pinMode(buzzerPin, OUTPUT);
    pinMode(distIn, INPUT);
    //servo.attach(3);  //Serwomechanizm podłączony do pinu 3
}

uint8_t buf[9];
uint8_t buflen = sizeof(buf);
const int sensX = 50;
const int sensY = 50;

const int maxSensX = 512 - sensX;
const int minSensX = 512 + sensX;
const int maxSensY = 512 - sensY;
const int minSensY = 512 + sensY;

void loop()
{    
    if (digitalRead(distIn) == 0) {
      digitalWrite(buzzerPin, HIGH);
      } else {
        digitalWrite(buzzerPin, LOW);
        }
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      String msg = String((char *)buf).substring(0, 8);
      String xValStr = msg.substring(0, 4);
      String yValStr = msg.substring(4, 8);
      int xVal = xValStr.toInt();    
      int yVal = yValStr.toInt();
      //servo.write(map(xVal, 0, 1023, 0, 180));
      if (yVal > minSensY) {
          analogWrite(motorEn, map(yVal, minSensY, 1023, 0, 255));
          digitalWrite(motorPin1, HIGH);
          digitalWrite(motorPin2, LOW);
       } else if (yVal < maxSensY) {
          analogWrite(motorEn, map(yVal, maxSensY, 0, 0, 255));
          digitalWrite(motorPin1, LOW);
          digitalWrite(motorPin2, HIGH);
        } else {
          digitalWrite(motorEn, LOW);
        }

        if (xVal > minSensX) {
          analogWrite(SmotorEn, map(xVal, minSensX, 1023, 0, 255));
          digitalWrite(SmotorPin1, HIGH);
          digitalWrite(SmotorPin2, LOW);
       } else if (xVal < maxSensX) {
          analogWrite(SmotorEn, map(xVal, maxSensX, 0, 0, 255));
          digitalWrite(SmotorPin1, LOW);
          digitalWrite(SmotorPin2, HIGH);
        } else {
          digitalWrite(SmotorEn, LOW);
        }
    }
}
