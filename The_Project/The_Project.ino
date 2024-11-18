const int soilMoisturePin = 10;
const int motor1A 13;
const int motor2A 14;

const double pctThreshold = 0.5;

void setup() {
  Serial.begin(9600);

  // initialize motor pins as output.
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);  

}

void loop() {
  int moisture = analogRead(soilMoisturePin);
  double moisturePct = moisture / 4095.0;

  Serial.println(moisturePct);

  if(moisturePct < pctThreshold){
    // THE PLANT IS GOING TO DIE (Imminent danger)

    // Rotate
    digitalWrite(motor1A, HIGH);     
    digitalWrite(motor2A, LOW);   
    delay(5);

    // Stop
    digitalWrite(motor1A, LOW);     
    digitalWrite(motor2A, LOW);    
    delay(2000); // wait for a second
    
  } else{
    //THE PLANT IS CHILLIN
  }

  // wait 5 seconds between every read
  delay(5000);
}
