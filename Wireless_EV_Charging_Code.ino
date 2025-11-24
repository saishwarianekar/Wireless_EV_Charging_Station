#include <LiquidCrystal.h>
const int trigPin  = 7;  // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int echoPin  = 6;  // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int relayPin = A5; // Arduino pin connected to Relay's pin
const int threshold = 50; // centimeters
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// variables will change:
float duration, distanceCm;
void setup() {
  Serial.begin (9600);        // initialize serial port
  pinMode(trigPin, OUTPUT);  // set arduino pin to output mode
  pinMode(echoPin, INPUT);   // set arduino pin to input mode
  pinMode(relayPin, OUTPUT); // set arduino pin to output mode

}

void loop() {
  lcd.begin(16, 2);
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Trigger the sensor by sending a 10µs HIGH pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echo pin, return the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in centimeters
  distanceCm = duration * 0.034 / 2; // Speed of sound is 0.034 cm/µs
  
  // Display the distance on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distanceCm);
  lcd.print(" cm    "); // Extra spaces to clear previous values
  
  // Control the relay based on the distance
  if (distanceCm < threshold) {
    digitalWrite(relayPin, HIGH); // Activate relay if distance is less than threshold
    lcd.setCursor(0, 0);
    lcd.print("Relay: ON");
    lcd.setCursor(0, 1);
    lcd.print("Charging ON");
  } else {
    digitalWrite(relayPin, LOW);  // Deactivate relay otherwise
    lcd.setCursor(0, 1);
    lcd.print("Relay: OFF");
    lcd.setCursor(0, 2);
    lcd.print("Charging OFF");
  }
  
  delay(500); // Wait for half a second before the next measurement
}
