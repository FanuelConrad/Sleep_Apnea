#include "ECG_sensor.h"

ECG_sensor::ECG_sensor(byte LO_p_pin, byte LO_n_pin)
{
}

ECG_sensor::ECG_sensor()
{
}

void ECG_sensor::init()
{
    pinMode(LO_p_pin, INPUT); // Setup for leads off detection LO +
    pinMode(LO_n_pin, INPUT); // Setup for leads off detection LO -

    LO_p_pin = 8;
    LO_n_pin = 9;
    instance1 = 0, timer;
    hrv = 0, hr = 72, interval = 0;
    value = 0, count = 0;
    flag = 0;
    shutdown_pin = 10;
    threshold = 100;     // to identify R peak
    timer_value = 10000; // 10 seconds timer to calculate hr
}

void ECG_sensor::set_standby_mode()
{
    digitalWrite(shutdown_pin, LOW);
}

void ECG_sensor::set_normal_mode()
{
    digitalWrite(shutdown_pin, HIGH);
}

bool ECG_sensor::check_if_leads_are_removed()
{
    if ((digitalRead(8) == 1) || (digitalRead(9) == 1))
        return true;
}

double ECG_sensor::calculate_hr()
{
    if (check_if_leads_are_removed())
    {

        Serial.println("leads off!");

        digitalWrite(shutdown_pin, LOW); // standby mode

        instance1 = micros();

        timer = millis();
    }

    else
    {
        digitalWrite(shutdown_pin, HIGH); // normal mode

        if ((value > threshold) && (!flag))
        {

            count++;

            Serial.println("in");

            flag = 1;

            interval = micros() - instance1; // RR interval

            instance1 = micros();
        }

        else if ((value < threshold))
        {

            flag = 0;
        }

        if ((millis() - timer) > 10000)
        {

            hr = count * 6;

            timer = millis();

            count = 0;
        }
    }
    return hr;
}

double ECG_sensor::calculate_hrv(double hr)
{
    hrv = hr / 60 - interval / 1000000;
    return hrv;
}

int ECG_sensor::getValue()
{
    value = analogRead(A0);

    value = map(value, 250, 400, 0, 100); // to flatten the ecg values a bit
    return value;
}