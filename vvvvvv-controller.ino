// radial = 20 A6

#include <Bounce2.h>

#ifndef __MKL26Z64__ // Using Teensy LC
#error Make sure you have a Teensy LC board, then select the proper board type in tools: Tools > Board > Teensy LC
#endif

// Setting pin positions as variables
const int kButtonPin = 5;
const int kRadial = A6;
const int kTouch = 0;

// Creating variables to hold value
int spinPos;
int isTouch;

const double kButtonInterval = 10;

Bounce btn = Bounce();

void setup() {
  // Set the pin for the Bounce, and pull the signal up.
  // If the signal is PULLUP by default, 'falling' is pressed.
  btn.attach(kButtonPin, INPUT_PULLUP);
  
  // Set the interval for the pin
  btn.interval(kButtonInterval);
  
  delay(500);

  pinMode(kTouch, INPUT_PULLUP);
}

void loop() {
  // This let's the Bounce update it's status. 
   btn.update();
   // This will activate once each time the button is pressed.
   // In other words, when the signal 'falls'.
   if ( btn.fell() ) {
    Keyboard.press(KEY_SPACE);
   }
  
   // This will activate once each time the button is released.
   // In other words, when the signal 'rises'.
   if ( btn.rose() ) {
    Keyboard.release(KEY_SPACE);
  }

  spinPos = analogRead(kRadial);
  spinPos = map(spinPos, 0, 1023, 0, 100);

  isTouch = touchRead(kTouch);
  if(isTouch > 4500){
    if(spinPos > 70 ){
      Keyboard.press(KEY_RIGHT);
    } else {
      Keyboard.press(KEY_LEFT);
    }
  } else {
    Keyboard.release(KEY_LEFT);
    Keyboard.release(KEY_RIGHT);
  }
  
    Serial.print("radial is: ");
    Serial.println(spinPos);
}
