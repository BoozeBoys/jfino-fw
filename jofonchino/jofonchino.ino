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
      if (atoi(CP.arg(1)) != 0) {
        MM.enable();       
      } else {
        MM.disable();
      }
    } else if (strcmp(cmd, "MOTOR") == 0 && CP.argsN() == 2) {
      int motorSX = atoi(CP.arg(1));
      int motorDX = atoi(CP.arg(2));

      MM.write(MOTOR_SX, motorSX);
      MM.write(MOTOR_DX, motorDX);
    } else {
      Serial.println("ERR");
    }
    
    CP.reset();
  }
  // AGGIUNGO MOTORE
  MM.update();
}
