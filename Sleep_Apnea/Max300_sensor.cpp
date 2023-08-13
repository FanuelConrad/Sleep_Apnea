#include "Max300_sensor.h"

// Create a PulseOximeter object
PulseOximeter pox;

Max300_sensor::Max300_sensor()
{
}

// Callback routine is executed when a pulse is detected
void Max300_sensor::onBeatDetected()
{
    Serial.println("Beat!");
}

void Max300_sensor::init()
{
    Serial.print("Initializing pulse oximeter..");

    REPORTING_PERIOD_MS = 1000;
    // Time at which the last beat occurred
    tsLastReport = 0;

    // Initialize sensor
    if (!pox.begin())
    {
        Serial.println("FAILED");
        for (;;)
            ;
    }
    else
    {
        Serial.println("SUCCESS");
    }

    // Configure sensor to use 7.6mA for LED drive
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

    // Register a callback routine
    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void Max300_sensor::print_max300_data()
{
    // Read from the sensor
    pox.update();

    // Grab the updated heart rate and SpO2 levels
    if (millis() - tsLastReport > REPORTING_PERIOD_MS)
    {
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");

        tsLastReport = millis();
    }
}