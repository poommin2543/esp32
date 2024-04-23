int buttonPin = 15;    // Pin for the push button
int ledPin = 18;      // Pin for the LED
int buttonState = 0;        // Current state of the button
int lastButtonState = 0;    // Previous state of the button

void setup() {
  pinMode(buttonPin, INPUT_PULLDOWN);  // Set the button pin as input 
  pinMode(ledPin, OUTPUT);   // Set the LED pin as output
}

void loop() {
  buttonState = digitalRead(buttonPin);     // Read the state of the button
  if (buttonState != lastButtonState) {     // If the button state has changed
    if (buttonState == HIGH) {               // If the button is pressed
      digitalWrite(ledPin, !digitalRead(ledPin));  // Toggle the LED state
    }
    delay(50);                              // Debounce delay
  }
  lastButtonState = buttonState;            // Save the current button state for next loop
}

