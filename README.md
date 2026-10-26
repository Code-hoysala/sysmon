# sysmon

`sysmon` is a lightweight, non-blocking Arduino library that monitors the internal health and operating vitals of your microcontroller. It acts as an embedded system monitor (similar to `top` or `htop`), tracking key metrics like free RAM, uptime, and loop execution frequency without impacting performance.

## Features
- **Performance Profiling:** Measures actual loop execution frequency (`Hz`) in real time.
- **Vitals Tracking:** Monitors uptime and estimates available free RAM headroom on AVR-based boards.
- **Zero Memory Overhead:** Built entirely with static allocation (`malloc`-free), optimized for resource-constrained AVR and ARM microcontrollers.

---

## Hardware Requirements
- **Microcontroller:** Arduino Uno, Mega, or any compatible AVR/ARM board.
- **Communication:** Standard `Serial` interface for printing health reports.

---

## Quick Start Example

```cpp
#include <sysmon.h>

SystemMonitor sys;

void setup() {
    Serial.begin(9600);
    sys.begin();
}

void loop() {
    // Print system vitals report every 3 seconds
    static unsigned long lastReport = 0;
    if (millis() - lastReport >= 3000) {
        lastReport = millis();
        sys.printReport();
    }

    // Must be called at the end of loop to measure execution frequency
    sys.update();
}
