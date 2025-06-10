#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <MPU6050.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening(); // Transmitter mode
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  String command = "";

  if (ay > 10000) {
    command = "F"; // Forward
  } else if (ay < -10000) {
    command = "B"; // Backward
  } else if (ax > 10000) {
    command = "R"; // Right
  } else if (ax < -10000) {
    command = "L"; // Left
  } else {
    command = "S"; // Stop
  }

  radio.write(&command, sizeof(command));
  delay(100);
}
