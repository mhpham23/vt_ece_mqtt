// File name: ldr_pub_client.ino
// Decription: Initiating MQTT protocol for Arduino Client. 128 bytes limit for packet size
//              Measure light instensity by using LDR circuit. Publishing light intensity value to broker
// Client Role: Publisher
// Library Used: ArduinoMqttClient, WifiNINA
// Author: Hoan Pham (mhpham23@vt.edu)

#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

// Macros ////////////////////////////////////////////////////////////////////////////////
#define BAUDRATE 9600
#define DELAY_TIME 5000
#define MSG_INTERVAL 8000
#define CLIENT_ROLE PUB
#define LED_PIN 9 // Output pin controlling LED
#define LDR_PIN A0 // Input pin measuring light intensity
#define THRESHOLD 700 // Light intensity threshold -> condition for light status
//////////////////////////////////////////////////////////////////////////////////////////

///////please enter your sensitive data in the Secret tab/arduino_secrets.h //////////////
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
///////////////////////////////////////////////////////////////////////////////////////////

//Network Information/////////////////////////////////////////////////////////////////////
const char broker[] = "test.mosquitto.org";
const char localhost_broker[] = MQTT_IP;
int        port     = LISTENING_PORT;
//////////////////////////////////////////////////////////////////////////////////////////

// Declaring topics //////////////////////////////////////////////////////////////////////
const char topic[]  = "light_intensity";
const char topic2[]  = "real_unique_topic_2";
const char topic3[]  = "real_unique_topic_3";
const char topic4[] = "light_intensity/relay";
//////////////////////////////////////////////////////////////////////////////////////////

// Time tracking /////////////////////////////////////////////////////////////////////////
//set interval for sending messages (milliseconds)
const long interval = MSG_INTERVAL;
unsigned long previousMillis = 0;
int count = 0;
//////////////////////////////////////////////////////////////////////////////////////////

// Constructors ///////////////////////////////////////////////////////////////////////////
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
//////////////////////////////////////////////////////////////////////////////////////////


void setup() {
  /* Setting up Wifi and MQTT connection */
  // put your setup code here, to run once:
  //Initialize serial port
  Serial.begin(BAUDRATE);

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(DELAY_TIME);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(localhost_broker);

  if (!mqttClient.connect(localhost_broker, port)) 
  {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  /* Finish setting up WIFI and MQTT connection */

  /* Setting up LDR sensor */
  pinMode(LDR_PIN, INPUT); // Setting sensor gpio_pin to input
  /* End task */

}

void loop() {
  // put your main code here, to run repeatedly:
  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();

  unsigned long currentMillis = millis(); // Tracking time

  /* Message task starts here */
  if (currentMillis - previousMillis >= interval) 
  {
    // save the last time a message was sent
    previousMillis = currentMillis;

    //record random value from A0, A1 and A2
    int LDRValue = analogRead(LDR_PIN);

    Serial.print("Sending message to topic: ");
    Serial.println(topic);
    Serial.println(LDRValue);

    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(topic);
    mqttClient.print(LDRValue);
    mqttClient.endMessage();

    Serial.println();
  } /* END TASK */

}
