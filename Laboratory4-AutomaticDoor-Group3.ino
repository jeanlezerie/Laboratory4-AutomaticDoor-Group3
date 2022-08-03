#include <IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(32, 16, 2);

int redLED = 2; //LED Variable
int pirPin = 4; //PIR Sensor Variable
int pirVal; //value from sensor detection

int servoPin = 3; //Micro Servo Variable
Servo myServo;

int IRpin = 5; // IR Sensor Variable
IRrecv IR(IRpin);

int i = 180;
int degrees;

//millis variables
unsigned long fromStartms; //millis from start
unsigned long prevms; //millis previous read
unsigned long interval = 50;

bool power = false;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  
  pinMode(IRpin, INPUT);
  IR.enableIRIn();
  
  pinMode(redLED, OUTPUT);
  pinMode(pirPin, INPUT);
  
  pinMode(servoPin, OUTPUT);
  myServo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
IR_numControl();
  if (power)
  {
    pirVal = digitalRead(pirPin);
    if (pirVal == 1)
    {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("DOOR OPENED");
      digitalWrite(redLED, HIGH);
      IR_numControl();
      
      Serial.println(i); // Prints the current angle of the servo
      myServo.write(i);
       
    }
    else
    {
      digitalWrite(redLED, LOW);
      myServo.write(0);
      lcd.setCursor(2, 0);
      lcd.print("DOOR CLOSED");
      degrees = 0;
    }
  }
}
  void IR_numControl()
  {
    while (IR.decode())
    {
      fromStartms = millis();
      if (fromStartms - prevms >= interval)
      {
        prevms = fromStartms;
        //Serial.println(IR.decodedIRData.decodedRawData,HEX);
        if (IR.decodedIRData.decodedRawData == 0xFF00BF00)
        {
          power = !power; 
        }
        //For 10 degrees angle
        else if (IR.decodedIRData.decodedRawData == 0xF30CBF00)
        {
          Serial.println("0");
          i = 10;
        }
        //For 20 degrees angle
        else if (IR.decodedIRData.decodedRawData == 0xEF10BF00)
        {
          Serial.println("1");
          i = 20;
        }
        //For 40 degrees angle
        else if (IR.decodedIRData.decodedRawData == 0xEE11BF00)
        {
          Serial.println("2");
          i = 40;
        }
        //For 60 degrees angle
        else if (IR.decodedIRData.decodedRawData == 0xED12BF00)
        {
          Serial.println("3");
          i = 60;
        }
        //For 80 degrees angle
        else if (IR.decodedIRData.decodedRawData == 0xEB14BF00)
        {
          Serial.println("4");
          i = 80;
        }
        //For 100 degrees angle
        else if (IR.decodedIRData.decodedRawData == 0xEA15BF00)
        {
          Serial.println("5");
          i = 100;
        }
        //For 110 degrees angle
        else if (IR.decodedIRData.decodedRawData == 0xE916BF00)
        {
          Serial.println("6");
          i = 110;
        }
        //For 120 degrees angle 
        else if (IR.decodedIRData.decodedRawData == 0xE718BF00)
        {
          Serial.println("7");
          i = 120;
        }
        //For 140 degrees angle
        else if (IR.decodedIRData.decodedRawData == 0xE619BF00)
        {
          Serial.println("8");
          i = 140;
        }
        //For 160 degrees angle
        else if (IR.decodedIRData.decodedRawData == 0xE51ABF00)
        {
          Serial.println("9");
          i = 160;
        }
      }
      IR.resume();
    }
  }
}
