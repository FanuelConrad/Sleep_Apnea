#include "ECG_sensor.h"
#include "Max300_sensor.h"

ECG_sensor ecg_sensor(8, 9);
Max300_sensor max300_sensor;

void setup()
{
  Serial.begin(9600);

  ecg_sensor.init();
  max300_sensor.init();
}

void loop()
{
  Serial.print(ecg_sensor.calculate_hr());

  Serial.print(",");

  Serial.print(ecg_sensor.calculate_hrv(ecg_sensor.calculate_hr()));

  Serial.print(",");

  Serial.println(ecg_sensor.getValue());

  delay(1);

  max300_sensor.print_max300_data();
}
