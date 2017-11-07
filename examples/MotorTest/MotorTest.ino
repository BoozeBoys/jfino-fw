#include "BTS7960B.h"

BTS7960B MM;

void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(500);

  MM.enable();
}

unsigned long timeSerial = 0;

void loop()
{
  if (millis()-timeSerial > 1000)
  {
    timeSerial = millis();

    int cur_dx = MM.read(MOTOR_DX);
    int cur_sx = MM.read(MOTOR_SX);
  }

  if (Serial.available())
  {
    int value = Serial.parseInt();
    Serial.print("SPD:");
    Serial.println(value);

    if (!MM.write(MOTOR_DX, value))
      Serial.println("ERROR DX");
    if (!MM.write(MOTOR_SX, value))
      Serial.println("ERROR SX");
  }

  MM.update();
}
