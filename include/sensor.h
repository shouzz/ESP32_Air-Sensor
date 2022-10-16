
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
    // float f = dht.readTemperature(true);
    // if (isnan(h) || isnan(t) || isnan(f))
    // {
    //     Serial.println(F("Failed to read from DHT sensor!"));
    //     return;
    // }
    // float hic = dht.computeHeatIndex(t, h, false);
    temp = t;
    humidity = h;
    tvoc = sgp.TVOC;
    eco2 = sgp.eCO2;
    pm10 = data.pm10_env;
    pm25 = data.pm25_env;
    pm100 = data.pm100_env;
    particles_03um = data.particles_03um;
    particles_05um = data.particles_05um;
    particles_10um = data.particles_10um;
    particles_25um = data.particles_25um;
    particles_50um = data.particles_50um;
    particles_100um = data.particles_100um;
    // Serial.print(sgp.TVOC);
    // Serial.println(" ppb\t");
    // Serial.print("CH2O ");
    // Serial.print(ch2o);
    // Serial.println(" μg/m3\t");
    // Serial.print("eCO2 ");
    // Serial.print(sgp.eCO2);
    // Serial.println(" ppm");
    // Serial.print(F("Humidity: "));
    // Serial.print(h);
    // Serial.print(F("%  Temperature: "));
    // Serial.print(t);
    // Serial.println(F("°C "));
    // Serial.print(F("PM 1.0: "));
    // Serial.println(data.pm10_env);
    // Serial.print(F("PM 2.5: "));
    // Serial.println(data.pm25_env);
    // Serial.print(F("PM 10: "));
    // Serial.println(data.pm100_env);
    // Serial.print(F("c:"));
    // Serial.println(data.particles_03um);
    // Serial.print(F("Particles > 0.5um / 0.1L air:"));
    // Serial.println(data.particles_05um);
    // Serial.print(F("Particles > 1.0um / 0.1L air:"));
    // Serial.println(data.particles_10um);
    // Serial.print(F("Particles > 2.5um / 0.1L air:"));
    // Serial.println(data.particles_25um);
    // Serial.print(F("Particles > 5.0um / 0.1L air:"));
    // Serial.println(data.particles_50um);
    // Serial.print(F("Particles > 10 um / 0.1L air:"));
    // Serial.println(data.particles_100um);
    Act_Time = millis();
    digitalWrite(23, LOW);
}

void Air_Sensor_loop()
{
    if (millis() - Act_Time >= Act_Time_Interval)
    {
        Air_Sensor();
        // Serial.println("Air_Sensor");
    }
    // else if (millis() - Act_Time < Act_Time_Interval)
    // {
    
    // }
    
}

void Get_Air_Sensor(String TaskNumber)
{
    prefs.begin("storage");
    Serial.println("<" + String(TaskNumber) + "," + String(prefs.getString("Role", "0")) + "," + String(temp) + "," + String(humidity) + "," + String(tvoc) + "," + String(eco2) + "," + String(pm10) + "," + String(pm25) + "," + String(pm100) + "," + String(particles_03um) + "," + String(particles_05um) + "," + String(particles_10um) + "," + String(particles_25um) + "," + String(particles_50um) + "," + String(particles_100um) + "," + String(ch2o) + ",Get_Sensor>");
    prefs.end();
    // Air_Sensor();
}