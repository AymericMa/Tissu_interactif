#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 74 

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

void setup() { 
  Serial.begin(9600);
  Serial.println("resetting");
  LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
  LEDS.setBrightness(86);
  pinMode(LED_BUILTIN,OUTPUT);
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

void loop() { 
  static uint8_t hue = 0;

  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n'){
        
        Serial.print("String complet : \n");
        Serial.print(inputString);
        Serial.print("\n");
        stringComplete = true;
        
      }
    else{
      inputString += inChar;
      Serial.print(inChar);
      Serial.print('\n');
      }
     
  }

  if (stringComplete) {
    
    // clear the string:

    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }

  if (inputString == "HELLO" and stringComplete == true){

    // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(5);
  }
  

  // Now go in the other direction.  
  for(int i = (NUM_LEDS)-1; i >= 0; i--) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(5);

    
  }

    inputString = "";
    stringComplete = false;
  }

  if (inputString == "HELLA" && stringComplete == true){
    
       // Move a single white led 
   for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
      // Turn our current led on to white, then show the leds
      leds[whiteLed] = CRGB::White;

      // Show the leds (only one of which is set to white, from above)
      FastLED.show();

      // Wait a little bit
      delay(40);

      // Turn our current led back to black for the next loop around
      leds[whiteLed] = CRGB::Black;
   }
   
   inputString = "";
   stringComplete = false;
    
    }
  

  
}

  void serialEvent() {
  
}
