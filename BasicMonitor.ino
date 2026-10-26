#include <sysmon.h>

SystemMonitor sys;

void setup() {
    Serial.begin(9600);
    sys.begin();
}

void loop() {
    // Your normal non-blocking code goes here...
    
    // Every 3 seconds, print the system vitals report
    static unsigned long lastReport = 0;
    if (millis() - lastReport >= 3000) {
        lastReport = millis();
        sys.printReport();
    }

    // Must be called at the end of loop to measure performance frequency
    sys.update();
}
