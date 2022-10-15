#include <Wire.h>
#include <ZE08_CH2O.h>
#include "Adafruit_SGP30.h"
#include "Adafruit_PM25AQI.h"
#include <Adafruit_Sensor.h>
#include "DHT.h"
#define DHTPIN 21
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SGP30 sgp;
Adafruit_PM25AQI aqi = Adafruit_PM25AQI();
ZE08_CH2O mySensor(15, 13);
double ch2o;

void Air_Sensor()
{
  digitalWrite(23, HIGH);
  double ch2O = mySensor.read_value();
  ch2o = ch2O / 1000;
  PM25_AQI_Data data;
  if (!aqi.read(&data))
  {
    Serial.println("Could not read from AQI");
    delay(500); // try again in a bit!
    return;
  }
  if (!sgp.IAQmeasure())

  {
    Serial.println("Measurement failed");
    return;
  }
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  delay(100);
  Serial.println();
  Serial.println(F("---------------------------------------"));
  Serial.println(F("Air Monitoring Data"));
  Serial.println(F("---------------------------------------"));
  Serial.println(F("TVOC/C02/CH2O/Temp/Humi"));
  Serial.println(F("---------------------------------------"));
  Serial.print("TVOC ");
  Serial.print(sgp.TVOC);
  Serial.println(" ppb\t");
  Serial.print("CH2O ");
  Serial.print(ch2o);
  Serial.println(" μg/m3\t");
  Serial.print("eCO2 ");
  Serial.print(sgp.eCO2);
  Serial.println(" ppm");
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  Serial.print(F("PM 1.0: "));
  Serial.println(data.pm10_env);
  Serial.print(F("PM 2.5: "));
  Serial.println(data.pm25_env);
  Serial.print(F("PM 10: "));
  Serial.println(data.pm100_env);
  Serial.print(F("Particles > 0.3um / 0.1L air:"));
  Serial.println(data.particles_03um);
  Serial.print(F("Particles > 0.5um / 0.1L air:"));
  Serial.println(data.particles_05um);
  Serial.print(F("Particles > 1.0um / 0.1L air:"));
  Serial.println(data.particles_10um);
  Serial.print(F("Particles > 2.5um / 0.1L air:"));
  Serial.println(data.particles_25um);
  Serial.print(F("Particles > 5.0um / 0.1L air:"));
  Serial.println(data.particles_50um);
  Serial.print(F("Particles > 10 um / 0.1L air:"));
  Serial.println(data.particles_100um);
  digitalWrite(23, LOW);
}
void setup()
{
  Wire.begin(19, 18);
  Serial.begin(115200);
  pinMode(23, OUTPUT);
  mySensor.begin(ZE08_CH2O_MODE_ACTIVE);
  sgp.begin();
  aqi.begin_I2C();
  dht.begin();
}

void loop()
{
  Air_Sensor();
  delay(3000);
}
