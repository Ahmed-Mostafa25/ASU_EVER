#include <SPI.h>
#include <mcp2515.h>

/* Define the Pins of LED and Potentiometer */
#define LED   11
#define POTENTIOMETER   A0

/* Initialze Some Variables */
int buttonIsPressed = 0;
int potValue;

/* Build CAN Message */
struct can_frame canMsg;
struct can_frame canMsg2;
MCP2515 mcp2515(10);

void setup() {
/* Initialize SPI and UART Communication */
Serial.begin(9600);
SPI.begin();

/* Initialize Pin Direction */
pinMode(LED, OUTPUT);
pinMode(POTENTIOMETER, INPUT);

/* Initialize CAN Communication */
mcp2515.reset();
mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
mcp2515.setNormalMode();

canMsg.can_id = 0x036;
canMsg.can_dlc = 8;
}

void loop() {
/* Read value from potentiometer */
potValue = analogRead(POTENTIOMETER);
potValue = map(potValue, 0, 1023, 0, 180);

/* Create CAN Message to send */
canMsg2.can_id = 0x037;    // CAN ID as 0x037
canMsg2.can_dlc = 8;       // CAN data length as 8
canMsg2.data[0] = potValue; // Send Servo angle
canMsg2.data[1] = 0x00;
canMsg2.data[2] = 0x00;
canMsg2.data[3] = 0x00;
canMsg2.data[4] = 0x00;
canMsg2.data[5] = 0x00;
canMsg2.data[6] = 0x00;
canMsg2.data[7] = 0x00;

/* Send Message of servo angle */
mcp2515.sendMessage(&canMsg2);

/* Recieve Message of push button for LED */
if(mcp2515.readMessage(&canMsg)==MCP2515::ERROR_OK){
  if(canMsg.can_id == 0x036){
    buttonIsPressed = canMsg.data[0];
    digitalWrite(LED, buttonIsPressed); 
}
}
}
