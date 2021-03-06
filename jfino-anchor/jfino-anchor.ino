#include <SPI.h>
#include "DW1000Ranging.h"

#define LED_CPU 5

#define WB_RST 9
#define WB_IRQ 3
#define WB_SS 10

#define SW_1 A2
#define SW_2 A4
#define SW_4 A3
#define SW_8 8
#define SW_16 A1

void newRange() {
  SerialUSB.print("DEV ID: "); SerialUSB.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
  SerialUSB.print("\t RANGE: "); SerialUSB.print(DW1000Ranging.getDistantDevice()->getRange()); SerialUSB.print(" m");
  SerialUSB.print("\t POWER: "); SerialUSB.print(DW1000Ranging.getDistantDevice()->getRXPower()); SerialUSB.println(" dBm");
}

void setup() {
  SerialUSB.begin(115200);
  
  SerialUSB.println("Start configuration module...");
  SerialUSB.println("");
  
  pinMode(LED_CPU, OUTPUT);
  digitalWrite(LED_CPU, LOW);

  pinMode(SW_1, INPUT_PULLUP);
  pinMode(SW_2, INPUT_PULLUP);
  pinMode(SW_4, INPUT_PULLUP);
  pinMode(SW_8, INPUT_PULLUP);
  pinMode(SW_16, INPUT_PULLUP);

  // TEST ADDRESS SWITCH
  uint8_t val = 0;
  val += !digitalRead(SW_1) << 0;
  val += !digitalRead(SW_2) << 1;
  val += !digitalRead(SW_4) << 2;
  val += !digitalRead(SW_8) << 3;
  val += !digitalRead(SW_16) << 4;

  DW1000Ranging.initCommunication(&SerialUSB, &SPI1, WB_RST, WB_SS, WB_IRQ);
  //DW1000Ranging.attachNewRange(newRange);
  char addr_buf[32];
  sprintf(addr_buf, "%02X:00:11:22:33:44:55:66", val);
  DW1000Ranging.startAsAnchor(addr_buf, DW1000.MODE_LONGDATA_RANGE_ACCURACY, false);

  SerialUSB.println("");
  SerialUSB.println("Init done...");
  SerialUSB.println("");
}

bool led_status = false;
unsigned long led_time = 0;

void loop() {
  // TEST CPU_LED
  if (millis()-led_time > 250)
  {
    led_time = millis();
    digitalWrite(LED_CPU, led_status);
    led_status = !led_status;
  }

  // TEST DW1000
  DW1000Ranging.loop();
}

