#include "ECG_sensor.h"

ECG_sensor ecg_sensor(8,9);

void setup() {
 
 ecg_sensor.init();

}

void loop() {
  Serial.print(ecg_sensor.calculate_hr());

    Serial.print(",");

    Serial.print(ecg_sensor.calculate_hrv(ecg_sensor.calculate_hr()));

    Serial.print(",");

    Serial.println(ecg_sensor.getValue());

    delay(1);

}
