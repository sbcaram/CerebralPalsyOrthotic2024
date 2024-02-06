
#include <SparkFun_ADS1015_Arduino_Library.h>
#include <Wire.h>
#include <Servo.h>

Servo thumbServo; 
Servo pointerServo; 
Servo middleServo; 
Servo ringServo; 
Servo pinkyServo; 
ADS1015 pinkySensor;
ADS1015 indexSensor;
ADS1015 thumbSensor;
uint16_t hand[6] = {0, 0, 0, 0, 0, 0};

int pos = 0;    // variable to store the servo position
String command;

void setup() {

  thumbServo.attach(5); 
  pointerServo.attach(9); 
  middleServo.attach(10); 
  ringServo.attach(2); 
  pinkyServo.attach(11); 

  thumbServo.write(pos);             
  pointerServo.write(pos);
  middleServo.write(pos);
  ringServo.write(pos);
  pinkyServo.write(pos);
  
  Wire.begin();
  //Serial.begin(115200);
  Serial.begin(9600);
  
  //Set up each sensor, change the addresses based on the location of each sensor
  if (pinkySensor.begin(ADS1015_ADDRESS_SCL) == false) {
     Serial.println("Pinky not found. Check wiring.");
     while (1);
  }
  if (indexSensor.begin(ADS1015_ADDRESS_GND) == false) {
     Serial.println("Index not found. Check wiring.");
     while (1);
  }  

   if (thumbSensor.begin(ADS1015_ADDRESS_VDD) == false) {
     Serial.println("Thumb not found. Check wiring.");
     while (1);
  }  
 
  pinkySensor.setGain(ADS1015_CONFIG_PGA_TWOTHIRDS); // Gain of 2/3 to works well with flex glove board voltage swings (default is gain of 2)
  indexSensor.setGain(ADS1015_CONFIG_PGA_TWOTHIRDS); // Gain of 2/3 to works well with flex glove board voltage swings (default is gain of 2)
  thumbSensor.setGain(ADS1015_CONFIG_PGA_TWOTHIRDS); // Gain of 2/3 to works well with flex glove board voltage swings (default is gain of 2)
}

void loop() {  
  uint16_t pinkyFinger;
  uint16_t ringFinger;
  uint16_t middleFinger;
  uint16_t pointerFinger;
  uint16_t thumb1;
  uint16_t thumb2;

  //   if(pinkyFinger > 917){
  //     pinkyServo.write(180);
  //   } else if(ringFinger > 920){
  //     ringServo.write(180);
  //   } else if(middleFinger > 908){
  //     middleServo.write(180);
  //   } else if(pointerFinger > 913){
  //     pointerServo.write(180);
  //   } else if(thumb1 > 1095){
  //     thumbServo.write(180);
  //   } else if(thumb2 > 1095){
  //     thumbServo.write(180);
  //   }

  //    if (Serial.available() == 0) {
  //     pinkyServo.write(90);
  //    }



  if(Serial.available()){
    command = Serial.readStringUntil('\n');

    if(command.equals("thumb")){
      thumbServo.write(180);
      Serial.println("You turned servo one 180°");
    } else if(command.equals("pointer")){
      pointerServo.write(180);
      Serial.println("You turned servo two 180°");
    } else if(command.equals("middle")){
      middleServo.write(180);
      Serial.println("You turned servo three 180°");
    } else if(command.equals("ring")){
      ringServo.write(180);
      Serial.println("You turned servo four 180°");
    } else if(command.equals("pinky")){
      pinkyServo.write(180);
      Serial.println("You turned servo five 180°");
    } else if(command.equals("reset")){
      thumbServo.write(pos);             
      pointerServo.write(pos);
      middleServo.write(pos);
      ringServo.write(pos);
      pinkyServo.write(pos);
      Serial.println("You just reset the servos");
    } else{
      Serial.println("Invalid command");
    }

    pinkyFinger = (pinkySensor.getAnalogData(0));
    Serial.print("pinky");
    Serial.print(": ");
    Serial.print(pinkyFinger);
    Serial.print(", "); 

    ringFinger = (pinkySensor.getAnalogData(1));
    Serial.print("ring");
    Serial.print(": ");
    Serial.print(ringFinger);
    Serial.print(", ");  

    middleFinger = (indexSensor.getAnalogData(0));
    Serial.print("middle");
    Serial.print(": ");
    Serial.print(middleFinger);
    Serial.print(", ");  

    pointerFinger = (indexSensor.getAnalogData(1));
    Serial.print("pointer");
    Serial.print(": ");
    Serial.print(pointerFinger);
    Serial.print(", "); 

    thumb1 = (thumbSensor.getAnalogData(0));
    Serial.print("thumb1");
    Serial.print(": ");
    Serial.print(thumb1);
    Serial.print(", ");   

    thumb2 = (thumbSensor.getAnalogData(1));
    Serial.print("thumb2");
    Serial.print(": ");
    Serial.print(thumb2);
    Serial.print(", ");   

      Serial.println();
  }
}
