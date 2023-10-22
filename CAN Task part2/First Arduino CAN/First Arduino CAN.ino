#include <SPI.h>
#include <mcp2515.h>
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

/* Build CAN Message */
struct can_frame canMsg;
struct can_frame canMsg2;
MCP2515 mcp2515(10); 
/**********************************************************/
/**********************************************************/
/**********************************************************/
void setup() {
/* Initialize SPI and UART Communication */  
Serial.begin(9600);
SPI.begin();

/* Initialize Pin Direction */
pinMode(PUSH_BUTTON, INPUT_PULLUP);
myservo.attach(SERVO_MOTOR);

/* Initialize CAN Communication */
mcp2515.reset();
mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
mcp2515.setNormalMode();
canMsg2.can_id = 0x037;
canMsg2.can_dlc = 8;
}
/**********************************************************/
/**********************************************************/
/**********************************************************/
void loop() {
/*Read From Push Button Part*/
buttonState = digitalRead(PUSH_BUTTON);
if(buttonState == LOW && lastButtonState == HIGH){
  delay(20);
  isPressed = ~(isPressed);

}
  lastButtonState = buttonState;

/****************************/

/* Create CAN Message to send */
canMsg.can_id = 0x036;     // CAN ID as 0x036
canMsg.can_dlc = 8;        // CAN data length as 8
canMsg.data[0] = isPressed; // Send State of Push Button
canMsg.data[1] = 0x00;
canMsg.data[2] = 0x00;
canMsg.data[3] = 0x00;
canMsg.data[4] = 0x00;
canMsg.data[5] = 0x00;
canMsg.data[6] = 0x00;
canMsg.data[7] = 0x00;

/* Send Message of push button state */
mcp2515.sendMessage(&canMsg);

/* Recieve Message of potentiometer for servo angle */
if(mcp2515.readMessage(&canMsg2)==MCP2515::ERROR_OK){
  if(canMsg2.can_id == 0x037){
    servoAngle = canMsg2.data[0];
    myservo.write(servoAngle);
  }    
}
}
