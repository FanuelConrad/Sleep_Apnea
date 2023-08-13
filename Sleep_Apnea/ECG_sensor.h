#ifndef ECG_SENSOR_H
#define ECG_SENSOR_H

#include <Arduino.h>

class ECG_sensor
{
private:
    byte LO_p_pin;
    byte LO_n_pin;
    long instance1, timer;
    double hrv, hr, interval;
    int value, count;
    bool flag;
    int shutdown_pin;
    int threshold;   // to identify R peak
    int timer_value; // 10 seconds timer to calculate hr

public:
    ECG_sensor(byte LO_p_pin, byte LO_n_pin);
    ECG_sensor();

    void init();
    bool check_if_leads_are_removed();
    double calculate_hr();
    double calculate_hrv(double hr);
    int getValue();
    void set_standby_mode();
    void set_normal_mode();
};

#endif