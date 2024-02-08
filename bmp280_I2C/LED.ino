void Plain_Effect_LEDs(float number, float min, float max) {
  static uint32_t Time, Led_humidity, Led_humidity_pass;

  number = constrain(number, min, max);
  Led_humidity = map(100 * number, 100 * max, 100 * min, 180 * 182, 0 * 182);

  if ((float)(millis() - Time) * (fabs(Led_humidity - Led_humidity_pass)) > 1e3) {
    Time = millis();
    strip.fill(strip.ColorHSV(Led_humidity, saturation, value), 0, LED_COUNT);
    Led_humidity_pass = Led_humidity;
  } else strip.fill(strip.ColorHSV(Led_humidity, saturation, value), 0, LED_COUNT);

  strip.show();
}



void Setup_weather_prediction() {
  for (int i = 0; i < N; i++) time_array[i] = (float)i;
  for (int i = 0; i < N; i++) pressure_array[i] = bmp280.readPressure();
}

void Weather_prediction() {

  static uint32_t Time = millis();
  if (millis() - Time > 3000) {
    Time = millis();

    for (int i = 0; i < N - 1; i++) {
      pressure_array[i] = pressure_array[i + 1];
      Serial.println(pressure_array[i]);
    }

    pressure_array[N - 1] = pressure;

    sumX = 0;
    sumY = 0;
    sumX2 = 0;
    sumXY = 0;
    for (int i = 0; i < N; i++) {  // для всех элементов массива
      sumX += time_array[i];
      sumY += pressure_array[i];
      sumX2 += time_array[i] * time_array[i];
      sumXY += time_array[i] * pressure_array[i];
    }

    a = 0;
    a = N * sumXY;  // расчёт коэффициента наклона приямой
    a = a - (sumX * sumY);
    a = a / (N * sumX2 - sumX * sumX);

    oled.setCursor(90, 7);
    oled.setScale(1);  // масштаб текста (1..4)
    oled.print(a);

    Plain_Effect_LEDs(a, -0.5, 0.5);
  }
}



void LED_Doing(byte Number_command) {
  static uint32_t Time = millis();
  if (millis() - Time > 100) {
    Time = millis();
    switch (Number_command) {
      case 1: Plain_Effect_LEDs((float)temperature, 18, 35); break;
      case 2: Plain_Effect_LEDs((float)pressure / 101325, 0.9, 1.1); break;
      case 3: Plain_Effect_LEDs((float)pressure * 0.00750063755419211, 700, 800); break;
      case 4: Plain_Effect_LEDs((float)(altitude - relative_altitude), -25, 100); break;
      case 5: Plain_Effect_LEDs((float)abs(13 - Roshi_Point(sensor.tem, sensor.hum)), 0, 8); break;
      case 6: Plain_Effect_LEDs((float)sensor.hum, 75, 25); break;
      case 7: Plain_Effect_LEDs((float)myRTC.getHour(h12Flag, pmFlag), 0, 23); break;
    }
  }
  strip.show();
}
