#include <CommandParser.h>
#include <BTS7960B.h>

#define STATUS_LEN 100
#define ALARM_TIMEOUT_MS 200

CommandParser CP;
BTS7960B MM;
static char status_buf[STATUS_LEN];
static unsigned long t0;

void setup() {
  Serial.begin(115200);
  Serial.println("HELO");
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
}
