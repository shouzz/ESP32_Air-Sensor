#include <Wire.h>
#include <ZE08_CH2O.h>
#include "Adafruit_SGP30.h"
#include "Adafruit_PM25AQI.h"
#include "SHT2x.h"
Adafruit_SGP30 sgp;
Adafruit_PM25AQI aqi = Adafruit_PM25AQI();
uint32_t start;
uint32_t stop;
SHT2x sht;
ZE08_CH2O mySensor(15, 13);
double ch2o;
/* return absolute humidity [mg/m^3] with approximation formula
 * @param temperature [°C]
 * @param humidity [%RH]
 */
uint32_t getAbsoluteHumidity(float temperature, float humidity)
{
  // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
  const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
  const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity);                                                                // [mg/m^3]
  return absoluteHumidityScaled;
}

// 获取串口数据
void GetSerialStuff(String& Str) {
  String tempStr = ""; // 声明变量 tempStr，用于临时存储串口输入的数据
  while(Serial.available()) { // 当串口有数据时，循环执行
    tempStr += (char)Serial.read();  // 把读取的串口数据，逐个组合到inStr变量里
  }
  Str = tempStr; // 把引用指针的变量赋值为 tempStr
}



void setup()
{
  Serial.begin(115200);
  pinMode(23, OUTPUT);
  mySensor.begin(ZE08_CH2O_MODE_ACTIVE);
  delay(5000);
  while (!Serial)
  {
    delay(10);
  } // Wait for serial console to open!
  Serial.println("SGP30 TVOC Sensor");
  Serial.println("PMSA003I Air Quality Sensor");

  if (!sgp.begin())
  {
    Serial.println("Sensor not found :(");
    while (1)
      ;
  }
  Serial.print("Found SGP30 serial #");
  Serial.print(sgp.serialnumber[0], HEX);

  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);

  if (!aqi.begin_I2C())
  {
    Serial.println("Could not find PM 2.5 sensor!");
    while (1)
      delay(10);
  }
  Serial.println("PM25 Start!");

  sht.begin(22, 23);
}
int counter = 0;

void loop()
{
digitalWrite(23, HIGH);
double ch2O = mySensor.read_value();
ch2o = ch2O / 1000;
PM25_AQI_Data data;
sht.read();
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
delay(100);
// Serial.println();
// Serial.println(F("---------------------------------------"));
// Serial.println(F("Air Monitoring Data"));
// Serial.println(F("---------------------------------------"));
// Serial.println(F("TVOC/C02/CH2O/Temp/Humi"));
// Serial.println(F("---------------------------------------"));
Serial.print("TVOC ");

Serial.print(sgp.TVOC);

Serial.println(" ppb\t");
delay(100);
Serial.print("CH2O ");
Serial.print(ch2o);
Serial.println(" mg/m3\t");
delay(100);
Serial.print("eCO2 ");

Serial.print(sgp.eCO2);

Serial.println(" ppm");
delay(100);
Serial.print("Temperature:");

Serial.print(sht.getTemperature(), 1);

Serial.println("℃");
delay(100);
Serial.print("Humidity:");

Serial.print(sht.getHumidity(), 1);

Serial.println("%");
delay(100);
// Serial.println(F("---------------------------------------"));
// Serial.println(F("PM Sensor (environmental)"));
// Serial.println(F("---------------------------------------"));
Serial.print(F("PM 1.0: "));

Serial.println(data.pm10_env);
delay(100);
Serial.print(F("PM 2.5: "));

Serial.println(data.pm25_env);
delay(100);
Serial.print(F("PM 10: "));

Serial.println(data.pm100_env);
delay(100);
// Serial.println(F("---------------------------------------"));
Serial.print(F("Particles > 0.3um / 0.1L air:"));
Serial.println(data.particles_03um);
delay(100);
Serial.print(F("Particles > 0.5um / 0.1L air:"));
Serial.println(data.particles_05um);
delay(100);
Serial.print(F("Particles > 1.0um / 0.1L air:"));
Serial.println(data.particles_10um);
delay(100);
Serial.print(F("Particles > 2.5um / 0.1L air:"));
Serial.println(data.particles_25um);
delay(100);
Serial.print(F("Particles > 5.0um / 0.1L air:"));
Serial.println(data.particles_50um);
delay(100);
Serial.print(F("Particles > 10 um / 0.1L air:"));
Serial.println(data.particles_100um);

// Serial.println(F("---------------------------------------"));
digitalWrite(23, LOW);

delay(10000);
}
