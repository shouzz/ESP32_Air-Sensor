#include <Wire.h>
#include <ZE08_CH2O.h>
#include "Adafruit_SGP30.h"
#include "Adafruit_PM25AQI.h"
#include <Adafruit_Sensor.h>
#include "DHT.h"
#include <Preferences.h>
#include "soc/rtc_wdt.h" //设置看门狗用
#define DHTPIN 21
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SGP30 sgp;
Adafruit_PM25AQI aqi = Adafruit_PM25AQI();
ZE08_CH2O mySensor(15, 13);
PM25_AQI_Data data;
Preferences prefs;
float temp ;// 存储温度
float humidity ; // 存储湿度
float tvoc ; // 存储TVOC
float eco2 ; // 存储eCO2
float pm10 ; // 存储PM1
float pm25 ; // 存储PM2.5
float pm100 ; // 存储PM10
float particles_03um ; // 存储0.3um / 0.1L air:
float particles_05um ; // 存储0.5um / 0.1L air:
float particles_10um ; // 存储1.0um / 0.1L air:
float particles_25um ; // 存储2.5um / 0.1L air:
float particles_50um ; // 存储5.0um / 0.1L air:
float particles_100um ; // 存储10.0um / 0.1L air:
float ch2o ; // 存储CH2O

//时间触发器
unsigned int Act_Time ; //传感器读取时间
unsigned int Act_Time_Interval; //传感器读取时间间隔





