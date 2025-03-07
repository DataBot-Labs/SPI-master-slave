#include <SPI.h>

#define CS_PIN 4  // Use GPIO 5 for ESP32 #1 or GPIO 4 for ESP32 #2

volatile byte receivedData = 0;

void setup() {
  SPI.begin(18, 19, 23, CS_PIN); // SCK, MISO, MOSI, CS
  pinMode(CS_PIN, INPUT);
  Serial.begin(115200);
}

void loop() {
  if (digitalRead(CS_PIN) == LOW) {
    receivedData = SPI.transfer(0x00);  // Dummy byte
    Serial.print("Received: ");
    Serial.println(receivedData, HEX);
    pinMode(MISO, OUTPUT);
    digitalWrite(MISO, HIGH); // Signal Ready
if (digitalRead(CS_PIN) == LOW) {
  digitalWrite(MISO, LOW); // Signal Busy
  delayMicroseconds(50); // Processing
  receivedData = SPI.transfer(0x00);
  Serial.print("Received: ");
  Serial.println(receivedData, HEX);
  SPI.transfer(receivedData + 1);
  digitalWrite(MISO, HIGH); // Signal Ready Again
  
}
    // Send back data + 1
    SPI.transfer(receivedData + 1);
    delay(10);
  }
}