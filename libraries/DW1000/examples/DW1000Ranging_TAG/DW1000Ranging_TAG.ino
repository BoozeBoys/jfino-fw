/**
 * 
 * @todo
 *  - move strings to flash (less RAM consumption)
 *  - fix deprecated convertation form string to char* startAsTag
 *  - give example description
 */
#include <SPI.h>
#include "DW1000Ranging.h"

// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

void setup() {
  while(!SerialUSB);
  SerialUSB.begin(115200);
  delay(1000);
  //init the configuration
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  //define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(newDevice);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  //Enable the filter to smooth the distance
  //DW1000Ranging.useRangeFilter(true);
  
  //we start the module as a tag
  DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);
}

void loop() {
  DW1000Ranging.loop();
}

void newRange() {
  SerialUSB.print("from: "); SerialUSB.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
  SerialUSB.print("\t Range: "); SerialUSB.print(DW1000Ranging.getDistantDevice()->getRange()); SerialUSB.print(" m");
  SerialUSB.print("\t RX power: "); SerialUSB.print(DW1000Ranging.getDistantDevice()->getRXPower()); SerialUSB.println(" dBm");
}

void newDevice(DW1000Device* device) {
  SerialUSB.print("ranging init; 1 device added ! -> ");
  SerialUSB.print(" short:");
  SerialUSB.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device* device) {
  SerialUSB.print("delete inactive device: ");
  SerialUSB.println(device->getShortAddress(), HEX);
}

