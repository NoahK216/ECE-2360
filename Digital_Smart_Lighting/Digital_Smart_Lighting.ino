#include <Adafruit_NeoPixel.h> // Include the Adafruit NeoPixel library
#include "ColorConverter.h"


#define LED_PIN 32 // NeoPixel LED strip
#define NUM_LEDS 8 // Number of LEDs
#define MIN_SENSOR 1000 // Sensor reading in the dark
#define MAX_SENSOR 4095 // Sensor reading in the light

#define X_AXIS_PIN 39   // joystick X axis
#define Y_AXIS_PIN 36   // joystick Y axis

int xAxisValue = 0; // To store value of the X axis
int yAxisValue = 0; // To store value of the Y axis
double head = 0.0;

// Create an instance of the Adafruit_NeoPixel class
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800); 

int ledR, ledG, ledB;

void setup() {
  strip.begin(); // Initialize the NeoPixel strip
  strip.show(); // Update the LED strip with the new colors


  // There's a bug with the serial monitor in this demo
  // do not use
  Serial.begin(9600);
}

void loop() {
  // read analog X and Y analog values
  xAxisValue = analogRead(X_AXIS_PIN) - MAX_SENSOR/2.0;
  yAxisValue = analogRead(Y_AXIS_PIN) - MAX_SENSOR/2.0;
  head = fmod(degrees(atan2(yAxisValue, xAxisValue)) + 360, 360);

  // print data to Serial Monitor on Arduino IDE
  Serial.print("x = ");
  Serial.print(xAxisValue);
  Serial.print(", y = ");
  Serial.print(yAxisValue);
  Serial.print(", head = ");
  Serial.println(head);



  // read the value from the light sensor
  int photoValue = analogRead(39);

  for (int i = 0; i < NUM_LEDS; i++) {
    if(photoValue > (4095.0 / NUM_LEDS) * (i+0.5)) {
      //ColorConverter::HsvToRgb(double hue, double saturation, double value, uint8_t & red, uint8_t & green, uint8_t & blue);
      ColorConverter::HsvToRgb(head, 255, 255, &ledR, &ledG, &ledB);
      strip.setPixelColor(i, ledR, ledG, ledB); // Set the color of the i-th LED to blue
    }
    else {
      strip.setPixelColor(i, 0, 0, 0); // Set the color of the i-th LED to black
    }
  }

  // Display the colors on the strip
  strip.show();


  delay(50);  // wait before reading again
}
