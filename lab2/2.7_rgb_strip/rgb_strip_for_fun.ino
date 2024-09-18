#include <Adafruit_NeoPixel.h> // Include the Adafruit NeoPixel library

#define LED_PIN 14 // NeoPixel LED strip
#define NUM_LEDS 8 // Number of LEDs

#define TRIG_PIN 27;
#define ECHO_PIN 26;

// Create an instance of the Adafruit_NeoPixel class
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800); 

void setup() {
  pinMode(TRIG_PIN, OUTPUT);  
	pinMode(ECHO_PIN, INPUT);  
	Serial.begin(9600);  

  strip.begin(); // Initialize the NeoPixel strip
  strip.show(); // Set initial color to black
}

uint16_t offset = 0;
float offsetMagnitudeR = 25;
float offsetMagnitudeG = 9;
float offsetMagnitudeB = 73;

float duration, distance;

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);

  for (int i = 0; i < NUM_LEDS; i++) {
    const int freqMult = 3;
    uint8_t sinValR = (sin((i*freqMult + offset/offsetMagnitudeR)/3.14) + 1) * 255/2;
    uint8_t sinValG = (sin((i*freqMult + offset/offsetMagnitudeG)/3.14) + 1) * 255/2;
    uint8_t sinValB = (sin((i*freqMult + offset/offsetMagnitudeB)/3.14) + 1) * 255/2;

    strip.setPixelColor(i, sinValR, sinValG, sinValB); // Set the color of the i-th LED
    strip.show(); // Update the LED strip with the new colors
  }
  delay(10); // Wait for 100 milliseconds

  offset++;
}