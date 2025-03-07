#include <SPI.h>

#define CS_ESP32_1 9
#define CS_ESP32_2 8

void setup() {
  SPI.begin(); 
  SPI.setClockDivider(SPI_CLOCK_DIV8); // 20 MHz (84 MHz / 4)
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);

  pinMode(CS_ESP32_1, OUTPUT);
  pinMode(CS_ESP32_2, OUTPUT);
  
  digitalWrite(CS_ESP32_1, HIGH);
  digitalWrite(CS_ESP32_2, HIGH);

  Serial.begin(115200);
}

void loop() {
  byte received1, received2;

  // Send Data to ESP32 #1
  Serial.println("Sending to ESP32 #1...");
  digitalWrite(CS_ESP32_1, LOW);
  // Wait until ESP32 signals Ready
while (digitalRead(MISO) == LOW) {
  delayMicroseconds(10); // Wait for ESP32 Ready Signal
  // Flush SPI Buffer before every transfer
while (SPI.transfer(0x00) != 0x00) {
  delayMicroseconds(10); // Just in case
}
}
  received1 = SPI.transfer(0xA1);
  digitalWrite(CS_ESP32_1, HIGH);
  Serial.print("ESP32 #1 Response: ");
  Serial.println(received1, HEX);

  delay(500);

  // Send Data to ESP32 #2
  Serial.println("Sending to ESP32 #2...");
  digitalWrite(CS_ESP32_2, LOW);
  // Flush SPI Buffer before every transfer
while (SPI.transfer(0x00) != 0x00) {
  delayMicroseconds(10); // Just in case
}
  
  received2 = SPI.transfer(0xB2);
  digitalWrite(CS_ESP32_2, HIGH);
  Serial.print("ESP32 #2 Response: ");
  Serial.println(received2, HEX);

  delay(1000);
}
