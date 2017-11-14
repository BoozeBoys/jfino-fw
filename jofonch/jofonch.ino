#include <CommandParser.h>
#include <BTS7960B.h>

CommandParser CP;
BTS7960B MM;

void setup() {
  Serial.begin(115200);
}

void loop() {
  while(Serial.available()) {
    if (!CP.put(Serial.read())) {
      break;
    }

    const char *cmd = CP.command();

    if (strcmp(cmd, "POWER") == 0 && CP.argsN() == 1) {
      MM.setEnabled(atoi(CP.arg(1)) != 0);
      Serial.println("OK");
    } else if (strcmp(cmd, "MOTOR") == 0 && CP.argsN() == 2) {
      int motorSX = atoi(CP.arg(1));
      int motorDX = atoi(CP.arg(2));

      MM.setSpeed(MOTOR_SX, motorSX);
      MM.setSpeed(MOTOR_DX, motorDX);

      Serial.println("OK");
    } else if (strcmp(cmd, "STATUS") == 0) {
      char buf[1024];

      snprintf(buf, 1024, "POWER %d", MM.isEnabled());
      Serial.println(buf);

      for (int i = 0; i < MAX_MOTORS; i++) {
        snprintf(buf, 1024, "MOTOR%d %d %d", i, MM.speed(i), MM.current(i));
        Serial.println(buf);
      }
      Serial.println("OK");
    } else {
      Serial.println("ERR");
    }

    CP.reset();
  }

  MM.update();
}
