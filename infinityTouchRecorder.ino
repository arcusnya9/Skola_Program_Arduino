// import the library (must be located in the Arduino/libraries directory)
#include <CapacitiveSensor.h>

// MAX_SIZE is the Array's maximum size
#define MAX_SIZE 50

// create an instance of the library
// pin 4 sends electrical energy
// pin 2 senses senses a change
CapacitiveSensor capSensor = CapacitiveSensor(4, 2);

// threshold will filter out alot of noise it's important because the array will be filled with tiny small noises that can't be heard.
// threshold for turning the piezo on
int threshold = 50;

// pin the PIEZO is connected to
const int piezoPin = 12;

long sensorValue = 0;
long sensorArray[MAX_SIZE] = {0};
int i = 0;

/*
*  RadioMachine Function takes an int as input and plays it on the Piezo
*/
void radioMachine(int arrVal)
{
    if (arrVal > threshold) {
      tone(piezoPin,arrVal);
    }
    // if it's lower than the threshold (NOISE).
    // don't play when threshold is under definded 50.
    else { 
        noTone(piezoPin); 
    }
}

void setup() {
  // open a serial connection
  Serial.begin(9600);
  // set the piezoPin as an output
  pinMode(piezoPin, OUTPUT);

}

/*
 * Main loop of the program that add sensor data and replays it indefinately.
 */
void loop() 
{
  // Add sensor data into SensorArray and store it and play it Live so you know what your recording.
  for(i=0; i <= MAX_SIZE; i++){
    sensorArray[i] = capSensor.capacitiveSensor(15);
    radioMachine(sensorArray[i]);
    delay(100);}
  // Playback some of the recorded input.
  for(i=0;i <= MAX_SIZE; i++){
    radioMachine(sensorArray[i]);
    delay(100);}
  delay(100);
}
