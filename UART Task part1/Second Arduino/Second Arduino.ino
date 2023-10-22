/* Define the Pins of LED and Potentiometer */
#define LED   11
#define POTENTIOMETER   A0

/* Initialze Some Variables */
int buttonIsPressed = 0;
int potValue;

/***********************************************************/
/***********************************************************/
/***********************************************************/
void setup() {
/* Initialize Serial Communication */
Serial.begin(9600);

/* Initialize Pin Direction */
pinMode(LED, OUTPUT);
pinMode(POTENTIOMETER, INPUT);
}
/***********************************************************/
/***********************************************************/
/***********************************************************/
void loop() {

/* Read value from potentiometer */
potValue = analogRead(POTENTIOMETER);

/* Communication Part */
if(Serial.available()>0){
/* Read value of button for LED */
  buttonIsPressed=Serial.read();
  /* Control LED */
digitalWrite(LED, buttonIsPressed);

}
/* Write Servo Angle */
potValue = map(potValue, 0, 1023, 0, 180);
Serial.write(potValue);



}
