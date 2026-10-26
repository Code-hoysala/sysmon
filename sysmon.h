#ifndef SYSMON_H
#define SYSMON_H

#include <Arduino.h>

class SystemMonitor {
public:
    SystemMonitor();
    
    void begin();
    void update(); // Call at the end of every loop() to track frequency
    
    // Vitals getters
    unsigned long getUptimeSeconds();
    unsigned long getLoopFrequency(); // Loops per second (Hz)
    int getFreeMemory();              // Estimated free RAM (AVR specific)
    
    // Print formatted health report over Serial
    void printReport();

private:
    unsigned long _startTime;
    unsigned long _lastCheckTime;
    unsigned long _loopCounter;
    unsigned long _currentHz;
};

#endif
