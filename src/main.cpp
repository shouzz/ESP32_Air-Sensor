#include "config.h"
#include "sensor.h"
#include "nvs.h"
#include "Serial.h"
#include "setup.h"
void setup()
{
  intlization(); //初始化
}

void loop()
{
  Serial_Control(); //串口控制
  Air_Sensor_loop(); //定时读传感器
  rtc_wdt_feed(); //喂狗
  // Serial.println("喂狗");
}
