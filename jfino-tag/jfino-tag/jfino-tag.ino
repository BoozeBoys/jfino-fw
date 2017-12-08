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

void setup() {
  while(!SerialUSB);
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

  DW1000Ranging.initCommunication(WB_RST, WB_SS, WB_IRQ);
  DW1000Ranging.startAsTag("82:17:5B:D5:A9:9A:E2:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);

  SerialUSB.println("");
  SerialUSB.println("Init done...");
  SerialUSB.println("");

  // TEST ADDRESS SWITCH
  uint8_t val = 0;
  val += !digitalRead(SW_1) << 0;
  val += !digitalRead(SW_2) << 1;
  val += !digitalRead(SW_4) << 2;
  val += !digitalRead(SW_8) << 3;
  val += !digitalRead(SW_16) << 4;
  SerialUSB.print("ADDRESS: 0x");  SerialUSB.println(val, HEX);
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

