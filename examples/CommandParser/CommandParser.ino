#include <CommandParser.h>

CommandParser cp;

void setup() {
  Serial.begin(9600);
}

void loop() {
  while(Serial.available()) {
    if (!cp.put(Serial.read())) {
      continue;
    }
    Serial.println("comando trovato");

    Serial.println(cp.command());
    for (int i = 1; i <= cp.argsN(); i++) {
      Serial.println(cp.arg(i));
    }

    cp.reset();
  }
}


