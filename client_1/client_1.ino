// File name: client_1.ino
// Decription: Initiating MQTT protocol for Arduino Client
// Client Role: TBD
// Library Used: ArduinoMqttClient, WifiNINA
// Author: Hoan Pham (mhpham23@vt.edu)
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

///////please enter your sensitive data in the Secret tab/arduino_secrets.h //////////////
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
///////////////////////////////////////////////////////////////////////////////////////////

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// Declaring topics //////////////////////////////////////////////////////////////////////

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
