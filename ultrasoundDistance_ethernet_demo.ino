/*
Ultrasound Distance Sensor connecetd with Ethernet Demo

This sketch demonstrates application of Ultrasound Distance Measuring Module Sensor for in-store consumer experience scenario 1.

Devices used:
1. Arduino Uno Prototype Board
2. Ultrasound Distance Measuring Module HC-SR04
3. Male-to-Female Jumper Wires
4. 5V-1A Power Supply

Circult Connection:
HC-SR04 -> Arduino Uno:
VCC -> 5V VCC
GND -> GND
Trig -> 2
Echo -> 4
*/

#include <SPI.h>
#include <Ethernet.h>

//sensor connection settings
int trigPin = 2;
int echoPin = 4;

//program status
String lastSensorMessage = "";

//MAC address for Ethernet Shield
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};
//set the static IP address if DHCP fails to assign
IPAddress ip(192, 168, 0, 177);
char server[] = "www.sensligence.com";
EthernetClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    //wait for serial port to connect
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  long distance = getDistance();
  if (distance < 3000) {
    Serial.println(distance);
    processDistance(distance);
    delay (1000);
  }
}

void processDistance(long distance) {
  String perceivedMessage = "";
  if (distance < 50) {
    perceivedMessage = "near";
  }
  else {
    perceivedMessage = "far";
  }

  if (perceivedMessage != lastSensorMessage) {
    lastSensorMessage = perceivedMessage;
    Serial.println(perceivedMessage);

    //start Ethernet connection
    if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to configure Ethernet using HDCP");
      //try to configure using IP address instead of DHCP
      Ethernet.begin(mac, ip);
    }
    
    //wait for a second to initialize Ethernet shield
    delay (1000);

    while (!client.connected()) {
      Serial.println("\nStarting connection to server...");

      // if you get a connection, report back via serial:
      if (client.connect(server, 80)) {
        Serial.println("connected to server");
      }
    }
    
    //Prepare data to post
    String data = "{Value:\"" + perceivedMessage + "\"}";
    
    // Make a HTTP request:
    client.println("POST /api/sensorData HTTP/1.1");
    client.println("Host: www.sensligence.com");
    client.println("Sensligence-API-Key: YOUR_API_KEY");
    //client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);

    delay(3000);

    // if there are incoming bytes available
    // from the server, read them and print them:
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }

    client.flush();
    client.stop();
  }
}

long getDistance() {
  long cm = 0, duration;

  //logic to trigger distance sensor
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //read signal from sensor
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  //speed of sound is 340 m/s or 29 microseconds per centimeter
  cm = duration / 29 / 2;

  return cm;
}
