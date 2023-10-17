// Import library/header files for ezButton so that we can use it later in the program.
#include <ezButton.h>


// Program is a modification of project 8 digital hourglass and has now become a 60 second stopwatch with an added green
// LED that blinks to user specification and instead of the tilt switch a real switch has been added
// that starts counting when the button is pressed and held for 50ms with the help of the ezButton Library.
// red led lights will also blink red while it's counting to 10 and when it has reached 10 it becomes non blinking and just
// becomes red until the end when the green LED will blink.

// named constant for the switch pin
const int switchPin = 13;

unsigned long previousTime = 0;  // store the last time an LED was updated
int switchState = 0;             // the current switch state
int prevSwitchState = 0;         // the previous switch state
int led = 2;                     // a variable to refer to the LEDs

// Constant names for red or green LEDs that are used for
// Either blinking or turning off green or red lights. 
const int red = 2;
const int green = 8;

// ezButton to control the start of the program is now for pin 13 on the arduino.
ezButton button(13); 

// 60000 = 1 minute in milliseconds
long interval = 10000;  // interval at which to light the next LED

/*
  BlinkLights takes 3 input parameters:
  int timeDelay --- is the amount of time one wants to delay each blink with.
  int blinks --- is the amount of times you want to blink. you might want to blink 4 times each 250 ms.
  int whatLight --- Specifies what light you want to start or stop.
*/
void blinkLights(int timeDelay, int blinks, int whatLight)
{

  if(whatLight == green) {
    // Turn off all the red lights.
    for(int j = 2; j <= 7; j++)
    {
        digitalWrite(j, LOW);
    }
  }

  /*
  * It's here where the blinking occurs.
  * TimeDelay is in MS
  */
  for(int i = 0; i != blinks; i++) {
      digitalWrite(whatLight, HIGH);
      delay(timeDelay);
      digitalWrite(whatLight, LOW);
      delay(timeDelay);}
}

void setup() 
{
  // set the LED pins as outputs
  for (int x = 2; x <= 8; x++) {
    pinMode(x, OUTPUT);
  }

  // set the on/off button as input
  pinMode(switchPin, INPUT);

  // set debounce time to 50 milliseconds.
  // So there's no accidental pressing of the button.
  button.setDebounceTime(50); 

  // Has to store currentTime here as well else it thinks that an interval has already gone so one LED will be turned on.
  // store the time since the Arduino started running in a variable
  unsigned long currentTime = millis();

  while (!button.isPressed())
    button.loop(); 
}

void loop() 
{
    // store the time since the Arduino started running in a variable
    unsigned long currentTime = millis();
    digitalWrite(led, LOW);

    // turn of green light incase it's still on. It should only be blinking inside blinkLights()
    digitalWrite(8, LOW);

    // Call blinkLights to blink once to tell the user that counting has begun.
    blinkLights(25,3,led);
    
    // compare the current time to the previous time an LED turned on
    // if it is greater than your interval, run the if statement
    if (currentTime - previousTime > interval) 
    {
      // save the current time as the last time you changed an LED
      previousTime = currentTime;

      // once 10 seconds has gone turn the LED on.
      digitalWrite(led, HIGH);

      // increment the led variable
      // in 10 the next LED will light up
      led++;

      // led starts at 2 and is incremented every 10 seconds.
      if (led == 8) {
        blinkLights(250,10,green);
      }
        
    } 
    
    // read the switch value
    switchState = digitalRead(switchPin);

    // if the switch has changed
    if (switchState != prevSwitchState) 
    {
      // turn all the LEDs low
      for (int x = 2; x < 8; x++) {
        digitalWrite(x, LOW);
      }

      // reset the LED variable to the first one
      led = 2;

      //reset the timer
      previousTime = currentTime;
    }

    // set the previous switch state to the current state
    prevSwitchState = switchState;

}
