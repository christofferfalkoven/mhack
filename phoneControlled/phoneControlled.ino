/****
 * PIN DEFINITIONS
 */
//First motor
#define IN11 5
#define IN12 6
#define IN13 7
#define IN14 8
//Second motor
#define IN21 9
#define IN22 10
#define IN23 11
#define IN24 12
//input from phone
#define P_SIG 0

//Signal length definitions, from phone (should ideally be 90, 180, 270, 360, 450 but, you know..., noise)
#define SIG_LEFT 100
#define SIG_RIGHT 190
#define SIG_FORWARD 280
#define SIG_BACKWARD 370
#define SIG_SERVO 460
#define SIG_WHITE_LED 550
#define SIG_RED_LED 640
#define SIG_GREEN_LED 730
#define SIG_BLUE_LED 820
#define SIG_LOWER_BR 910
#define SIG_INCR_BR 1000

#define TURN_SCALE 512

//Servo motor
#include <Servo.h>
 
Servo servo1;  // create servo object to control a servo

//Stepper motor phases, table magic
const int phases1[] = {0, 0, 0, 0, 0, 1, 1, 1};
const int phases2[] = {0, 0, 0, 1, 1, 1, 0, 0};
const int phases3[] = {0, 1, 1, 1, 0, 0, 0, 0};
const int phases4[] = {1, 1, 0, 0, 0, 0, 0, 1};

//A convenient way to switch between motors
const int outputs[][4] = {{IN11, IN12, IN13, IN14}, //first motor, index 0
                          {IN21, IN22, IN23, IN24} //second motor, index 1
                         };

//The servos used are not configured properly for some reason.
//It is possible to get around that by offsetting
const int sketchyServoOffset = 8;

int inputSignal = 0;
//Initialize the phase of both motors as 0
int Phase[] = {0, 0};
int Speed = 100; //MUST BE 1 - 100
unsigned long startTime = 0;
int counter = 0;
// servo position
int servoPos = 90;
int current_red = 0;
int current_blue = 0;
int current_green = 0;

int redPin= 2;
int greenPin = 3;
int bluePin = 4;

void setup() {
  //First motor
  pinMode(IN11, OUTPUT);
  pinMode(IN12, OUTPUT);
  pinMode(IN13, OUTPUT);
  pinMode(IN14, OUTPUT);
  //Second motor
  pinMode(IN21, OUTPUT);
  pinMode(IN22, OUTPUT);
  pinMode(IN23, OUTPUT);
  pinMode(IN24, OUTPUT);
  pinMode(P_SIG, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin,OUTPUT);

  servo1.attach(2);  // attaches the servo on pin 2 to the servo object
  
  Serial.begin(57600);
  Serial.println("intitalized");
}

void loop() {
  startTime = millis();
  counter = 0;
  inputSignal = analogRead(P_SIG);   // read the input pin
  if (inputSignal > 10) {
    counter = 1;
    while(millis() < startTime + 200) {
      if (analogRead(P_SIG) > 10) {
        counter += 1;
      }
    }
  }
  if (counter > 50) {
    if (counter < SIG_LEFT) {
      top_left();
    }
    else if (counter < SIG_RIGHT) {
     top_right(); 
    }
    else if (counter < SIG_FORWARD) {
      bottom_left();
    }
    else if (counter < SIG_BACKWARD) {
      bottom_right();
    }
    else if (counter < SIG_SERVO) {
      // goes from 0 degrees to 180 degrees in steps of 1 degree
      for(servoPos = 90; servoPos < 180; servoPos += 1) {
        servo1.write(servoPos + sketchyServoOffset);  // tell servo to go to position in variable 'pos'
        delay(15);               // waits 15ms for the servo to reach the position
      }
      // goes back, from 180 degrees to 0
      for(servoPos = 180; servoPos > 0; servoPos -= 1) {
        servo1.write(servoPos + sketchyServoOffset);  // tell servo to go to position in variable 'pos'
        delay(15);
      }
      // then back to starting position
      for(servoPos = 0; servoPos < 90; servoPos += 1) {
        servo1.write(servoPos + sketchyServoOffset);  // tell servo to go to position in variable 'pos'
        delay(15);
      }
    }
    else if (counter < SIG_WHITE_LED){
        if (current_red>=155 && current_green >=155 && current_blue>=155){
          current_red = 0;
          current_green = 0;
          current_blue = 0;
        }
        else {
          current_red = 255;
          current_green = 255;
          current_blue = 255;
        }
        setColor(current_red,current_green,current_blue);
    }
    else if (counter < SIG_RED_LED){
        if (current_red>=155 && current_green <155 && current_blue<155){
          current_red = 0;
          current_green = 0;
          current_blue = 0;
        }
        else {
          current_red = 255;
          current_green = 0;
          current_blue = 0;
        }
        setColor(current_red,current_green,current_blue);
    }
    else if (counter < SIG_GREEN_LED){
        if (current_red<155 && current_green>=155 && current_blue<155){
          current_red = 0;
          current_green = 0;
          current_blue = 0;
        }
        else {
          current_red = 0;
          current_green = 255;
          current_blue = 0;
        }
        setColor(current_red,current_green,current_blue);
    }
    else if (counter < SIG_BLUE_LED){
        if (current_red<155 && current_green<155 && current_blue>=155){
          current_red = 0;
          current_green = 0;
          current_blue = 0;
        }
        else {
          current_red = 0;
          current_green = 0;
          current_blue = 255;
        }
        setColor(current_red,current_green,current_blue);
    }
    else if (counter < SIG_LOWER_BR){
        if (current_red<=255 && current_red >=180){
          current_red -= 25; 
        }
        if (current_green<=255 && current_green >=180){
          current_green -= 25; 
        }
        if (current_blue<=255 && current_blue >=180){
          current_blue -= 25;
        }
        setColor(current_red,current_green,current_blue);
    }
    else if (counter < SIG_INCR_BR){
        if (current_red<=230 && current_red >=155){
          current_red += 25; 
        }
        if (current_green<=230 && current_green >=155){
          current_green += 25; 
        }
        if (current_blue<=230 && current_blue >=155){
          current_blue += 25; 
        }
        setColor(current_red,current_green,current_blue);
    }
  }
}


void top_left() {
  for (int i = 0; i < TURN_SCALE; i += 1) {
    stepper(1, 0);
  }
  Serial.println("left");
}

void top_right() {
  for (int i = 0; i < TURN_SCALE; i += 1) {
    stepper(-1, 0);
  }
  Serial.println("right");
}

void bottom_left() {
  for (int i = 0; i < TURN_SCALE; i += 1) {
    stepper(1, 1);
  }
  Serial.println("forward");
}

void bottom_right() {
  for (int i = 0; i < TURN_SCALE; i += 1) {
    stepper(-1, 1);
  }
  Serial.println("backward");
}

void stepper(int count, int motor) {
  int rotationDirection = count < 1 ? -1 : 1;
  count *= rotationDirection;
  for (int x = 0; x < count; x++) {
    digitalWrite(outputs[motor][0], phases1[Phase[motor]]);
    digitalWrite(outputs[motor][1], phases2[Phase[motor]]);
    digitalWrite(outputs[motor][2], phases3[Phase[motor]]);
    digitalWrite(outputs[motor][3], phases4[Phase[motor]]);
    IncrementPhase(rotationDirection, motor);
    delay(100/Speed);
  }
}

void IncrementPhase(int rotationDirection, int motor) {
  Phase[motor] += 8;
  Phase[motor] += rotationDirection;
  Phase[motor] %= 8;
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, 255-redValue);
  analogWrite(greenPin, 255-greenValue);
  analogWrite(bluePin, 255-blueValue);
}
