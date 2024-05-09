#include <SparkFun_ADS1015_Arduino_Library.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
String command;

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

void setup() {

  pwm.setPWM(0, 0, 0);           
  pwm.setPWM(1, 0, 0);
  pwm.setPWM(2, 0, 0);
  pwm.setPWM(3, 0, 0);
  pwm.setPWM(4, 0, 0);
  
  Wire.begin();
  Serial.begin(9600);

  Serial.println("Testing");
 
  pwm.begin();

  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
}

void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= SERVO_FREQ;   // Analog servos run at ~60 Hz updates
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert input seconds to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}

void loop() {  

  if(Serial.available()){
    command = Serial.readStringUntil('\n');

    if(command.equals("thumb")){
      pwm.setPWM(0, 0, SERVOMIN);
      delay(500);
      pwm.setPWM(0, 0, 0);
      Serial.println("You turned servo one");
    } else if(command.equals("pointer")){
      pwm.setPWM(1, 0, SERVOMIN);
      delay(500);
      pwm.setPWM(1, 0, 0);
      Serial.println("You turned servo two");
    } else if(command.equals("middle")){
      pwm.setPWM(2, 0, SERVOMIN);
      delay(500);
      pwm.setPWM(2, 0, 0);
      Serial.println("You turned servo three");
    } else if(command.equals("ring")){
      pwm.setPWM(3, 0, SERVOMIN);
      delay(500);
      pwm.setPWM(3, 0, 0);
      Serial.println("You turned servo four");
    } else if(command.equals("pinky")){
      pwm.setPWM(4, 0, SERVOMIN);
      delay(500);
      pwm.setPWM(4, 0, 0);
      Serial.println("You turned servo five");
    // } else if(command.equals("reset")){
    //   thumbServo.write(pos);             
    //   pointerServo.write(pos);
    //   middleServo.write(pos);
    //   ringServo.write(pos);
    //   pinkyServo.write(pos);
    //   Serial.println("You just reset the servos");
    } else{
      Serial.println("Invalid command");
    }

    Serial.println();
  }
}
