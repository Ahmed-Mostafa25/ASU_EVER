#include <Servo.h>
/* Define the Pins of Servo and Push Button */
#define SERVO_MOTOR     8
#define PUSH_BUTTON     5

/* Initialize Servo */
Servo myservo;

/* Initialize some variables */
int servoAngle = 90;
int buttonState = HIGH;
int lastButtonState = HIGH;
int isPressed = 0;

/**********************************************************/
/**********************************************************/
/**********************************************************/
void setup() {
/* Initialize Serial Communication */
Serial.begin(9600);
/* Initialize Pin Direction */
pinMode(PUSH_BUTTON, INPUT_PULLUP);
myservo.attach(SERVO_MOTOR);
myservo.write(servoAngle);
}
/***********************************************************/
/***********************************************************/
/***********************************************************/
void loop() {

/*Read From Push Button Part*/
buttonState = digitalRead(PUSH_BUTTON);
if(buttonState == LOW && lastButtonState == HIGH){
  delay(20);
  isPressed = ~(isPressed);

}
  lastButtonState = buttonState;

/****************************/
  
/* Communication Part */  
if(Serial.available()){
  /* Read Angle Value for Servo from Second Arduino */
  servoAngle = Serial.read();  
  myservo.write(servoAngle);
}
/************************/
/* Write the Value of Button to Second Arduino */
  Serial.write(isPressed);
/* Servo control Part */

//myservo.write(servoAngle);
//delay(15);
/************************/
}
