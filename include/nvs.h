void Nvs_Device_Role_Set(String Role, String TaskNumber)
{
    prefs.begin("storage");
    prefs.putString("Role", Role);
    Serial.println("<" + String(TaskNumber) + "," + String(prefs.getString("Role", "0")) + ",Role_Set>");
    prefs.end();
}
void Nvs_Device_Role_Read(String TaskNumber)
{
    prefs.begin("storage");
    Serial.println("<" + String(TaskNumber) + "," + String(prefs.getString("Role", "0")) + ",Role_Read>");
    prefs.end();
}

void Nvs_Device_Interval_Set(unsigned int Interval, String TaskNumber)
{
    prefs.begin("storage");
    prefs.putUInt("Interval", Interval);
    Serial.println("<" + String(TaskNumber) + "," + String(prefs.getString("Role", "0")) + "," + String(prefs.getUInt("Interval", 0)) + "," + "Interval Set>");
    Act_Time_Interval = prefs.getUInt("Interval", 0);
    prefs.end();
}
