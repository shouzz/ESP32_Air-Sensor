void intlization()
{

    Wire.begin(19, 18);
    Serial.setTimeout(10); //设置串口接收超时时间
    Serial.begin(115200);
    pinMode(23, OUTPUT);
    rtc_wdt_protect_off();                  //看门狗写保护关闭 关闭后可以喂狗
    rtc_wdt_enable();                       //启用看门狗
    rtc_wdt_feed();                         //喂狗
    rtc_wdt_set_time(RTC_WDT_STAGE0, 5000); // 设置看门狗超时 5000ms
    mySensor.begin(ZE08_CH2O_MODE_QA);
    sgp.begin();
    aqi.begin_I2C();
    dht.begin();
    prefs.begin("storage");
    Act_Time_Interval = prefs.getUInt("Interval", 0);
    prefs.end();
    Air_Sensor();
}