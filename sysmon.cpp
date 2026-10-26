#include "sysmon.h"

// External reference for AVR stack-heap pointer check (Arduino Uno/Mega)
#if defined(__AVR__)
extern unsigned int __heap_start;
extern void *__brkval;
#endif

SystemMonitor::SystemMonitor() {
    _startTime = 0;
    _lastCheckTime = 0;
    _loopCounter = 0;
    _currentHz = 0;
}

void SystemMonitor::begin() {
    _startTime = millis();
    _lastCheckTime = _startTime;
    _loopCounter = 0;
    _currentHz = 0;
}

void SystemMonitor::update() {
    _loopCounter++;
    unsigned long currentTime = millis();
    
    // Calculate frequency every 1 second
    if (currentTime - _lastCheckTime >= 1000) {
        _currentHz = _loopCounter;
        _loopCounter = 0;
        _lastCheckTime = currentTime;
    }
}

unsigned long SystemMonitor::getUptimeSeconds() {
    return (millis() - _startTime) / 1000;
}

unsigned long SystemMonitor::getLoopFrequency() {
    return _currentHz;
}

int SystemMonitor::getFreeMemory() {
#if defined(__AVR__)
    // Calculate free RAM between heap pointer and stack pointer
    int freeValue;
    if ((int)__brkval == 0) {
        freeValue = ((int)&freeValue) - ((int)&__heap_start);
    } else {
        freeValue = ((int)&freeValue) - ((int)__brkval);
    }
    return freeValue;
#else
    return -1; // Not supported on non-AVR architectures out-of-the-box
#endif
}

void SystemMonitor::printReport() {
    Serial.println(F("--- [SYS_MONITOR Vitals] ---"));
    Serial.print(F("Uptime: "));
    Serial.print(getUptimeSeconds());
    Serial.println(F(" s"));
    
    Serial.print(F("Loop Speed: "));
    Serial.print(getLoopFrequency());
    Serial.println(F(" Hz"));
    
#if defined(__AVR__)
    Serial.print(F("Free RAM: "));
    Serial.print(getFreeMemory());
    Serial.println(F(" bytes"));
#endif
    Serial.println(F("----------------------------"));
}
