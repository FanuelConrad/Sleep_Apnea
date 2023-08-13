#ifndef MAX300_SENSOR_H
#define MAX300_SENSOR_H

#include <Arduino.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

class Max300_sensor
{
private:
    /* data */
public:
    Max300_sensor();

    int REPORTING_PERIOD_MS;
    // Time at which the last beat occurred
    uint32_t tsLastReport;

    void init();
    static void onBeatDetected();
    void print_max300_data();
};

#endif