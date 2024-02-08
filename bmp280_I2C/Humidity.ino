float Roshi_Point(float Temp, float Hum) {
  float k, a = 17.27, b = 237.7, Tp;
  k = (a * Temp) / (b + Temp) + log((float)Hum / 100.0);
  Tp = (b * k) / (a - k);
  return Tp;
}

void HUM() {
  uint32_t static Time = millis();
  if (millis() - Time > 1500) {
    Time = millis();
    sensor.read();
  }
}