/* 
Ultrasound Distance Sensor connecetd with WiFi Shield 

This sketch demonstrates application of Ultrasound Distance Measuring Module Sensor for in-store consumer experience scenario 1. 

Devices used: 
1. Arduino Uno R3 Prototype Board
2. WiFi Shield
3. Ultrasound Distance Measuring Module HC-SR04 
4. Male-to-Female Jumper Wires 
5. 5V-1A Power Supply 
  
Circult Connection: 
HC-SR04 -> Arduino Uno: 
VCC -> 5V VCC 
GND -> GND 
Trig -> 2 
Echo -> 4 
*/ 

#include <SPI.h>
#include <WiFi.h>

//sensor connection settings
int trigPin = 2;
int echoPin = 4;

//program status
String lastSensorMessage = "";

//wifi settings
char ssid[] = "YOUR_WIFI_SSID";
char password[] = "YOUR_WIFI_PASSWORD";
int keyIndex = 0;
int status = WL_IDLE_STATUS;
char server[] = "www.sensligence.com";
WiFiClient client;

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

    //Connect to wifi
    connectToWifi(ssid, password);


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

void connectToWifi(char ssid[], char password[])
{
  //Connect to wifi
  if (status != WL_CONNECTED) {
    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
      // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
      status = WiFi.begin(ssid, password);
      //status = WiFi.begin(ssid);

      // wait 10 seconds for connection:
      delay(10000);
    }
    Serial.println("Connected to wifi");
    printWifiStatus();
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
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
