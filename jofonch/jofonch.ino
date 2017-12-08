#include <CommandParser.h>
#include <BTS7960B.h>
#include <DW1000Ranging.h>

#define STATUS_LEN 100
#define ALARM_TIMEOUT_MS 200

CommandParser CP;
BTS7960B MM;
static char status_buf[STATUS_LEN];
static unsigned long t0;

#define MAX_ANCHORS 5

uint16_t anchors[MAX_ANCHORS];

// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

void setup() {
  Serial.begin(115200);
  Serial.println("HELO");
  //init the configuration
  DW1000Ranging.initCommunication(&Serial, &SPI, PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  //define the sketch as anchor. It will be great to dynamically change the type of module
  //DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachBlinkDevice(addDevice);
  DW1000Ranging.attachInactiveDevice(delDevice);
  //Enable the filter to smooth the distance
  //DW1000Ranging.useRangeFilter(true);
  
  //we start the module as an anchor
  DW1000Ranging.startAsAnchor("82:17:5B:D5:A9:9A:E2:9A", DW1000.MODE_LONGDATA_RANGE_ACCURACY);
}


void loop() {
  while(Serial.available()) {
    if (!CP.put(Serial.read())) {
      break;
    }

    t0 = millis();

    const char *cmd = CP.command();

    if (strcmp(cmd, "POWER") == 0 && CP.argsN() == 1) {
      MM.setEnabled(atoi(CP.arg(1)) != 0);
      Serial.println("OK");
    } else if (strcmp(cmd, "SPEED") == 0 && CP.argsN() == 2) {
      int motorSX = atoi(CP.arg(1));
      int motorDX = atoi(CP.arg(2));

      MM.setSpeed(MOTOR_SX, motorSX);
      MM.setSpeed(MOTOR_DX, motorDX);

      Serial.println("OK");
    } else if (strcmp(cmd, "STATUS") == 0 && CP.argsN() == 0) {
      snprintf(status_buf, STATUS_LEN, "POWER %d", MM.isEnabled());
      Serial.println(status_buf);

      for (int i = 0; i < MAX_MOTORS; i++) {
        snprintf(status_buf, STATUS_LEN, "SPEED %d %d", i, MM.speed(i));
        Serial.println(status_buf);

        snprintf(status_buf, STATUS_LEN, "CURRENT %d %d", i, MM.current(i));
        Serial.println(status_buf);
      }

      for (int i = 0; i < MAX_ANCHORS; i++) {
        if (anchors[i] != 0) {
          Serial.print("ANCHOR "); 
          Serial.print(anchors[i], HEX);
          Serial.print(" ");
          Serial.print(DW1000Ranging.searchDistantDevice((byte *)&anchors[i])->getRange());
          Serial.print(" ");
          Serial.println(DW1000Ranging.searchDistantDevice((byte *)&anchors[i])->getRXPower());
        }
      }

      Serial.println("OK");
    } else {
      Serial.println("ERR");
    }

    CP.reset();
  }

  if ((millis() - t0) > ALARM_TIMEOUT_MS) {
    MM.setSpeed(MOTOR_SX, 0);
    MM.setSpeed(MOTOR_DX, 0);
  }

  MM.update();
  DW1000Ranging.loop();
}


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

