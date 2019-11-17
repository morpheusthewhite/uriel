#define DEBUG 0

/*
 * pins used for controlling light color
 */
char redPin = 3;
char greenPin = 5;
char bluePin = 6;

/* 
 * pin used to turn on/off the light 
 */
char powerPin = 7;

/*
 * variables used to keep track of input changes from button
 */
char powerOutput = 1;
char lastPowerInput = 0;
char currentPowerInput;

/*
 * Pins for reading color inputs
 */
char redInputPin = A2;
char greenInputPin = A1;
char blueInputPin = A0;

/*
 * Variables to keep track of input 
 */
unsigned short redInput;
unsigned short greenInput;
unsigned short blueInput;

/*
 * Variables to keep track of output on rgb pins
 */
unsigned char redValue;
unsigned char greenValue;
unsigned char blueValue;

void setup() {
  // output color pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // input on on/off pin
  pinMode(powerPin, INPUT);

  // input color pins
  pinMode(redInputPin, INPUT);
  pinMode(greenInputPin, INPUT);
  pinMode(blueInputPin, INPUT);

  // start Serial communication for debugging
  if(DEBUG)
    Serial.begin(9600);
}

void loop() {
  currentPowerInput = digitalRead(powerPin);

  /*
   * change power state after releasing the button
   */
  if( currentPowerInput == 0 && lastPowerInput == 1)
    powerOutput = 1 - powerOutput;
 
  lastPowerInput = currentPowerInput;

  /*
   * read and output color after mapping them on a 0-255 scale
   */
  unsigned short redInput = analogRead(redInputPin);
  redValue = map(redInput, 0, 1023, 0, 255);
  unsigned short greenInput = analogRead(greenInputPin);
  greenValue = map(greenInput, 0, 1023, 0, 255);
  unsigned short blueInput = analogRead(blueInputPin);
  blueValue = map(blueInput, 0, 1023, 0, 255);
  
  analogWrite(redPin, redValue * powerOutput);
  analogWrite(greenPin, greenValue * powerOutput);
  analogWrite(bluePin, blueValue * powerOutput);

  if(DEBUG){
    Serial.print("Red: ");
    Serial.println(redInput);
    Serial.print("Blue: ");
    Serial.println(blueInput);
    Serial.print("Green: ");
    Serial.println(greenInput);
  }
}
