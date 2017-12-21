#include <CommandParser.h>
#include <BTS7960B.h>
#include <DW1000Ranging.h>

#define ALARM_TIMEOUT_MS 200

CommandParser CP;
BTS7960B MM;
static unsigned long t0;

#ifdef __AVR_ATmega328P__
  // Arduino uno, duemilanove, etc...
  #define ENABLE_DW1000 0
  // connection pins
  const uint8_t PIN_RST = 9; // reset pin
  const uint8_t PIN_IRQ = 2; // irq pin
  const uint8_t PIN_SS = SS; // spi select pin
  #define SERIALPORT Serial
  #define SPIPORT SPI
  #define MAX_ANCHORS 4
#else
  // Arduino M0: jfino
  #define ENABLE_DW1000 1
  // connection pins
  const uint8_t PIN_RST = 9; // reset pin
  const uint8_t PIN_IRQ = 3; // irq pin
  const uint8_t PIN_SS = 10; // spi select pin
  #define SERIALPORT SerialUSB
  #define SPIPORT SPI1
  #define MAX_ANCHORS 32
#endif

uint16_t anchors[MAX_ANCHORS];

void setup() {
  SERIALPORT.begin(115200);
  SERIALPORT.println("HELO");

 #if ENABLE_DW1000
  //init the configuration
  DW1000Ranging.initCommunication(&SERIALPORT, &SPIPORT, PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  //define the sketch as anchor. It will be great to dynamically change the type of module
  //DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(addDevice);
  DW1000Ranging.attachInactiveDevice(delDevice);
  //Enable the filter to smooth the distance
  //DW1000Ranging.useRangeFilter(true);
  
  //we start the module as an tag
  DW1000Ranging.startAsTag("00:01:02:03:04:05:06:07", DW1000.MODE_LONGDATA_RANGE_ACCURACY, false);
 #endif
}


void loop() {
  while(SERIALPORT.available()) {
    if (!CP.put(SERIALPORT.read())) {
      break;
    }

    t0 = millis();

    const char *cmd = CP.command();

    if (strcmp(cmd, "POWER") == 0 && CP.argsN() == 1) {
      MM.setEnabled(atoi(CP.arg(1)) != 0);
      SERIALPORT.println("OK");
    } else if (strcmp(cmd, "SPEED") == 0 && CP.argsN() == 2) {
      int motorSX = atoi(CP.arg(1));
      int motorDX = atoi(CP.arg(2));

      MM.setSpeed(MOTOR_SX, motorSX);
      MM.setSpeed(MOTOR_DX, motorDX);

      SERIALPORT.println("OK");
    } else if (strcmp(cmd, "STATUS") == 0 && CP.argsN() == 0) {
      SERIALPORT.print("POWER "); SERIALPORT.println(MM.isEnabled());
      
      for (int i = 0; i < MAX_MOTORS; i++) {
        SERIALPORT.print("SPEED "); SERIALPORT.print(i); SERIALPORT.print(" "); SERIALPORT.println(MM.speed(i));
        SERIALPORT.print("CURRENT "); SERIALPORT.print(i); SERIALPORT.print(" "); SERIALPORT.println(MM.current(i));
      }

      for (int i = 0; i < MAX_ANCHORS; i++) {
        if (anchors[i] != 0) {
          SERIALPORT.print("ANCHOR "); 
          SERIALPORT.print(anchors[i], HEX);
          SERIALPORT.print(" ");
          SERIALPORT.print(DW1000Ranging.searchDistantDevice((byte *)&anchors[i])->getRange());
          SERIALPORT.print(" ");
          SERIALPORT.println(DW1000Ranging.searchDistantDevice((byte *)&anchors[i])->getRXPower());
        }
      }

      SERIALPORT.println("OK");
    } else {
      SERIALPORT.println("ERR");
    }

    CP.reset();
  }

  if ((millis() - t0) > ALARM_TIMEOUT_MS) {
    MM.setSpeed(MOTOR_SX, 0);
    MM.setSpeed(MOTOR_DX, 0);
  }

  MM.update();
#if ENABLE_DW1000
  DW1000Ranging.loop();
#endif
}


#if ENABLE_DW1000

void addDevice(DW1000Device* device) {
  for (int i=0; i < MAX_ANCHORS; i++) {
    if (anchors[i] == 0) {
      anchors[i] = device->getShortAddress();
      return;
    }
  }
}

void delDevice(DW1000Device* device) {
  for (int i=0; i < MAX_ANCHORS; i++) {
    if (anchors[i] == device->getShortAddress()) {
      anchors[i] = 0;
      return;
    }
  }
}

#endif
