// File name: client_2.ino
// Decription: Initiating MQTT protocol for Arduino Client. 128 bytes limit for packet size
// Client Role: SUB
// Library Used: ArduinoMqttClient, WifiNINA
// Author: Hoan Pham (mhpham23@vt.edu)
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

// Macros ////////////////////////////////////////////////////////////////////////////////
#define BAUDRATE 9600
#define DELAY_TIME 5000
#define MSG_INTERVAL 8000
#define CLIENT_ROLE SUB
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
const char topic[]  = "real_unique_topic";
const char topic2[]  = "real_unique_topic_2";
const char topic3[]  = "real_unique_topic_3";
//////////////////////////////////////////////////////////////////////////////////////////


// Constructors ///////////////////////////////////////////////////////////////////////////
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
//////////////////////////////////////////////////////////////////////////////////////////

// Time tracking /////////////////////////////////////////////////////////////////////////
//set interval for sending messages (milliseconds)
const long interval = MSG_INTERVAL;
unsigned long previousMillis = 0;
int count = 0;
//////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
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

  // Subscriber code /////////////////////////////////////////////
  // set the message receive callback
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic);
  mqttClient.subscribe(topic2);
  mqttClient.subscribe(topic3);

  // topics can be unsubscribed using:
  // mqttClient.unsubscribe(topic);

  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.print("Topic: ");
  Serial.println(topic2);
  Serial.print("Topic: ");
  Serial.println(topic3);

  Serial.println();
  ////////////////////////////////////////////////////////////////

}

void loop() 
{
  // put your main code here, to run repeatedly:
  // call poll() regularly to allow the library to receive MQTT messages and
  // send MQTT keep alive which avoids being disconnected by the broker
  mqttClient.poll();

}

//call-back function
void onMqttMessage(int messageSize) 
{
  // we received a message, print out the topic and contents
  Serial.println("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  // use the Stream interface to print the contents
  while (mqttClient.available()) 
  {
    Serial.print((char)mqttClient.read());
  }
  Serial.println();
  Serial.println();
}
