// File name: light_sensor.ino
// Decription: Basic function for light sensor
// Author: Hoan Pham (mhpham23@vt.edu)
#define BAUDRATE 9600
#define LED_PIN 9 // Output pin controlling LED
#define LDR_PIN A0 // Input pin measuring light intensity
#define THRESHOLD 700 // Light intensity threshold -> condition for light status


void setup() {

  // put your setup code here, to run once:
  Serial.begin(BAUDRATE);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int LDRValue = analogRead(LDR_PIN);
  Serial.print("sensor = ");
  Serial.println(LDRValue);
  
  if (LDRValue <= THRESHOLD)
  {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Insufficient Light; Light status: ON");
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Sufficient light; Light status: OFF");
  } 
}
