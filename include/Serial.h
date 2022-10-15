void Serial_Control()
{
    if (Serial.available())
    {
        String SerialString = Serial.readString();
        String Str_cmd = SerialString.substring(1, SerialString.indexOf(','));
        String Str_TaskNumber = SerialString.substring(SerialString.indexOf(',') + 1, SerialString.lastIndexOf(','));
        String Str_data = SerialString.substring(SerialString.lastIndexOf(',') + 1, SerialString.lastIndexOf('>'));
        if (Str_cmd = "Role_Set")
        {
            Nvs_Device_Role_Set(Str_data, Str_TaskNumber);
        }
        else if (Str_cmd = "Interval_Set")
        {
            Nvs_Device_Interval_Set(Str_data.toInt(), Str_TaskNumber);
        }
        else if (Str_cmd = "Role_Read")
        {
        }
        else if (Str_cmd == "Get_Sensor")
        {
            if (millis() >= 15000)
            {
                Get_Air_Sensor(Str_TaskNumber);
            }

            else
            {
                Serial.println("<" + String(prefs.getString("Role", "0")) + "," + String(Str_TaskNumber) + "," + "sensor initializing>");
            }
        }
    }

}