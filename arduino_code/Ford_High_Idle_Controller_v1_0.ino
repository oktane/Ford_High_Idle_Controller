// High Idle Auto Resume
// Version 1.0 12/2011
// droktane


const int  pto_ok_pin = 2;    // the pin that the pushpto is attached to
const int relay_pin = 6;       // the pin that the LED is attached to
// Variables will change:
int ptoState = 0;         // current state of the pto
int lastptoState = 0;     // previous state of the pto

void setup() {
  pinMode(pto_ok_pin, INPUT);
  pinMode(relay_pin, OUTPUT);
  Serial.begin(9600);
  delay(3000);
}


void loop() {
  // read the pushpto input pin:
  ptoState = digitalRead(pto_ok_pin);

  // compare the ptoState to its previous state
  if (ptoState != lastptoState) {
    // if the state has changed, increment the counter
    if (ptoState == LOW) {
      // if the current state is LOW then the PTO is ok
      // went from off to on:
      Serial.println("Sleeping...");
    } 
    else {
      // if the current state is High then the pto
      // went from on to off:
      Serial.println("PTO was interrupted. Restarting in 5 Seconds..."); 
    }
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastptoState = ptoState;

  
  // turns on the LED every four pto pushes by 
  // checking the modulo of the pto push counter.
  // the modulo function gives you the remainder of 
  // the division of two numbers:
  if (ptoState == HIGH) {
    digitalWrite(relay_pin, HIGH);
    Serial.println("PTO REQ to PCM disabled temporarily...");
    delay(1000); 
    digitalWrite(relay_pin, LOW);
    Serial.println("PTO REQ to PCM reenabled. High Idle should resume if able to.");
    delay(6000);
  } else {
   //digitalWrite(relay_pin, LOW);
   delay(1000);
  }    
}









