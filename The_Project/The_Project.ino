/* Noah Klein & Ayden Coughlin */

/* IOT Stuff */

//#include <WiFi.h>
//#include <PubSubClient.h>

// Replace the next variables with your SSID/Password combination
const char* ssid = "Noah's Pixel 7";
const char* password = "sadbuttrue";

// Add your MQTT Broker address, example:
const char* mqtt_server = "broker.hivemq.com";
const char* unique_identifier = "sunfounder-client-noahayden";

// WiFiClient espClient;
// PubSubClient client(espClient);
long lastMsg = 0;
int value = 0;

/* Pin definitions and constants */

const int soilMoisturePin = 35;
const int motor1A = 13;
const int motor2A = 14;

const double pctThreshold = 50;

void setup() {
  Serial.begin(9600);

  // set up wifi
  // setup_wifi();
  // client.setServer(mqtt_server, 1883);
  // client.setCallback(callback);

  // initialize motor pins as output.
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
}

// void setup_wifi() {
//   delay(10);
//   // We start by connecting to a WiFi network
//   Serial.println();
//   Serial.print("Connecting to ");
//   Serial.println(ssid);

//   WiFi.begin(ssid, password);

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }

//   Serial.println("");
//   Serial.println("WiFi connected");
//   Serial.println("IP address: ");
//   Serial.println(WiFi.localIP());
// }

// void callback(char* topic, byte* message, unsigned int length) {
//   Serial.print("Message arrived on topic: ");
//   Serial.print(topic);
//   Serial.print(". Message: ");
//   String messageTemp;

//   for (int i = 0; i < length; i++) {
//     Serial.print((char)message[i]);
//     messageTemp += (char)message[i];
//   }
//   Serial.println();

  // If a message is received on the topic "SF/LEDNOAHAYDEN", you check if the message is either "on" or "off".
  // Changes the output state according to the message
  //if (String(topic) == "SF/LEDNOAHAYDEN") {
  //  Serial.print("Changing state to ");
  //  if (messageTemp == "on") {
  //    Serial.println("on");
  //    digitalWrite(ledPin, HIGH);
  //  } else if (messageTemp == "off") {
  //    Serial.println("off");
  //    digitalWrite(ledPin, LOW);
  //  }
  //}
// }

// void reconnect() {
//   // Loop until we're reconnected
//   while (!client.connected()) {
//     Serial.print("Attempting MQTT connection...");
//     // Attempt to connect
//     if (client.connect(unique_identifier)) {
//       Serial.println("connected");
//       // Subscribe
//       client.subscribe("SF/LEDNOAHAYDEN");
//     } else {
//       Serial.print("failed, rc=");
//       Serial.print(client.state());
//       Serial.println(" try again in 5 seconds");
//       // Wait 5 seconds before retrying
//       delay(5000);
//     }
//   }
// }

#define PLANT_WARNINGS_SIZE 4
char *plantWarnings[PLANT_WARNINGS_SIZE] = {"Plant is thirsty", "Moisture is require", "HELP", "Plant needs a Cherry Pepsi™"};

void loop() {
  // MQTT Stuff
  // if (!client.connected()) {
    // reconnect();
  // }
  // client.loop();

  int moisture = analogRead(soilMoisturePin);
  double readingPct = moisture / 4095.0;
  double relativeHumidity = 100.0 - (readingPct * 100.0);


  Serial.printf("\nRelative humidity: %.2f\n", relativeHumidity);

  if(relativeHumidity < pctThreshold){
    Serial.println(plantWarnings[random(PLANT_WARNINGS_SIZE)]);
    //Serial.printf("Plant is thirsty");
    // THE PLANT IS GOING TO DIE (Imminent danger)

    // if the button pressed, publish the temperature to topic "SF/TEMP"
    
    // long now = millis();
    // if (now - lastMsg > 5000) {
      // lastMsg = now;
      // char tempString[8];
      // itostrf(moisture, 1, 2, tempString);
      // sprintf("%d", &tempString, moisture);
      // client.publish("SF/TEMP", "TEMP");
    // }
    

    // Rotate our pump
    digitalWrite(motor1A, HIGH);     
    digitalWrite(motor2A, LOW);   
    //delay(500);

    // Stop the pump
    digitalWrite(motor1A, LOW);     
    digitalWrite(motor2A, LOW);    
    
  } else{
    //THE PLANT IS CHILLIN
    Serial.println("The plant is chillin");
  }

  // wait 1 seconds between every read
  delay(1000);
}
