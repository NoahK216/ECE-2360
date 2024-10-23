#include <Adafruit_NeoPixel.h> // Include the Adafruit NeoPixel library

#define xAxis 34 //joystick x
#define yAxis 35 //joystick y
#define btn 33 //joystick button

// #define AXIS_CENTER 2047.5 // (4095+0)/2
#define AXIS_CENTER 3000.0 // (4095+0)/2

#define LED_PIN 26 // NeoPixel LED strip
#define NUM_LEDS 8 // Number of LEDs

// Create an instance of the Adafruit_NeoPixel class
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800); 


double heading(double x, double y) {
  double head = atan2(y, x); // Slope Y, Slope X
  return head * (180.0/M_PI) + 180.0;
}

void setup() {
  // Initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  // Set the mode of the button pin to input
  pinMode(btn, INPUT);  

  strip.begin(); // Initialize the NeoPixel strip
  strip.show(); // Set initial color to black
}

double smoothlyChangingHue = 0;
double smoothlyChangingBrightness = 0;

void loop() {
  // Read the analog value for x,y axis
  int xValue = analogRead(xAxis);
  int yValue = analogRead(yAxis); 

  int adjustedX = xValue - AXIS_CENTER;
  int adjustedY = yValue - AXIS_CENTER;
  double degrees = heading(adjustedX, adjustedY);
  double dist = sqrt((double)(adjustedX * adjustedX + adjustedY * adjustedY));

  // Read the digital value from the button pin
  int btnValue = digitalRead(btn);
  
  // print out the values
  Serial.printf("Joystick value is %d , %d , %lf, %lf\n",xValue, yValue, degrees, dist);

  double currentHue = degrees / 360.0 * 65535.0;
  while (currentHue - smoothlyChangingHue > 65535.0 / 2.0) {
    currentHue -= 65535.0;
  }
  while (smoothlyChangingHue - currentHue > 65535.0 / 2.0) {
    currentHue += 65535.0;
  }

  double currentBrightness = dist >= 1000.0 ? 120.0 : 0.0;

  smoothlyChangingHue += (currentHue - smoothlyChangingHue) * 0.1;
  smoothlyChangingBrightness += (currentBrightness - smoothlyChangingBrightness) * 0.1;

  int color = strip.ColorHSV((int)(smoothlyChangingHue), 255, (int)(smoothlyChangingBrightness));

  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show(); // Update the LED strip with the new colors
  
  delay(15);  // Delay between reads
}
