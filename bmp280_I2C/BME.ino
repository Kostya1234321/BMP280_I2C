void Init_BMP280() {

  Serial.println("Загрузка BMP280");
  int i=0;
  while (!bmp280.begin(0x76)){
    Serial.println("BMP280 подключен по I2C");
    i++;
    if(i>10)break;
  }
}

void TEM_PRE_ALTI() {
  uint32_t static Time = millis();
  if (millis() - Time > 3000) {
    Time = millis();

    temperature = pressure = altitude = 0;
    
    for (int i = 0; i < calculation; i++) {
      temperature += bmp280.readTemperature();   // Считываем показания температуры в градусах Цельсия
      pressure += bmp280.readPressure();// Считываем показания давления в Паскалях        
      altitude += bmp280.readAltitude(1013.25);  // Расчитываем высоту относительно уровня моря
    }
    temperature /= calculation;
    pressure /= calculation;
    altitude /= calculation;
    
  }
}
