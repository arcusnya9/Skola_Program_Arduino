void setup() {
  //start serial communication
  Serial.begin(9600);
}

/*
* This Is a password app 
* Where you type a password and if your correct you get a secret reward and if you fail you get an alarm
* It's based on project 7.
* Button Closest to the piezo Is enter. Next one is 3,2,1
*/

void playTone(int key)
{
  // If key is not false play the tune of success.
  if(!key)
    tone(8, 333);
  else
    tone(8, 122);

  //delay(1000);
}

void loop() {
  // Secret user password
  int password[] = {3,3,3,3};
  int UserPass[] = {0,0,0,0};
  int k = 0;
  int authenticated = 1;

  // create a local variable to hold the input on pin A0
  int passCode = analogRead(A0);

  while(k <= 4)
  {
      // Checks if the password is the same as UserPass If so it will print SUCCESS else FAIL
    if(k == 4) { 
      if(password[0] == UserPass[0] && password[1] == UserPass[1] && password[2] == UserPass[2] && password[3] == UserPass[3] ) { 
            Serial.println("SUCCESS");
            playTone(authenticated);
        } else { 
            Serial.println("FAIL");
            playTone(0); 
        }
    }
  
    if (passCode == 1023){ // Puts 4 in the array at index k
        UserPass[k] = 4;
        //Serial.println(UserPass[k]);
    } else if (passCode >= 990 && passCode <= 1010) { // Puts 3 in the array at index k
        UserPass[k] = 3;
        //Serial.println(UserPass[k]);
    } else if (passCode >= 505 && passCode <= 515) { // Puts 2 in the array at index k
        UserPass[k] = 2;
        //Serial.println(UserPass[k]);
    } else if (passCode >= 5 && passCode <= 10) { // Puts 1 in the array at index k
        UserPass[k] = 1;
        //Serial.println(UserPass[k]);
    } 
    k++;
    delay(500);
  }
}
