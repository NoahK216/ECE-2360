// the setup function runs one time at the beginning of the program
void setup() {
 // Put a line of code here to begin the Serial object
 Serial.begin(9600);
}




// Write in the value of R1 that you've chosen
const double R1 = 2000;
const double VIN = 3.3;
const int R1_pin = 34; 


// the loop function loops forever after the setup() is complete
void loop() {
 // Read the value from A0
 unsigned int ADC_A0 = analogRead(R1_pin);
 // Calculate V_A0 from ADC_A0
 double V_A0 = (ADC_A0/4095.0) * VIN;
 // Calculate R2 from V_A0 and R1
 double R2 = R1 * (VIN/V_A0 - 1);

 // Print ADC_A0, V_A0, and R2 to the serial monitor on a single line
 Serial.print("ADC reading: ");
 Serial.print(ADC_A0);
 Serial.print(" V_A0: ");
 Serial.print(V_A0);
 Serial.print(" R2: ");
 Serial.println(R2);

 // Wait 0.5 seconds
 delay(500);
}