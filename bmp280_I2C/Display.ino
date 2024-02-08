void Display_Connection() {
  oled.init();   // инициализация
  oled.clear();  // очистка
}

void Display_write(String message, int coor_x, int coor_y, int scale, byte Num_com) {
  byte static Num_messege = number_screen;

  if (Num_messege != Num_com) {
    Num_messege = Num_com;
    oled.clear();  // очистка
  }

  oled.setCursor(coor_x, coor_y);
  oled.setScale(scale);  // масштаб текста (1..4)
  oled.print(message);
}

void Display_Doing(byte Number_command) {
  static uint32_t Time;
  String getMinute, getHour;

  if (myRTC.getMinute() > 9) getMinute = (String)myRTC.getMinute();
  else getMinute = "0" + (String)myRTC.getMinute();

  if (myRTC.getHour(h12Flag, pmFlag) > 9) getHour = (String)myRTC.getHour(h12Flag, pmFlag);
  else getHour = "0" + (String)myRTC.getHour(h12Flag, pmFlag);


  switch (Number_command) {
    case 1:
      Display_write("Temperature", 30, 0, 1, Number_command);
      Display_write((String)sensor.tem + " C", 22, 3, 2, Number_command);  //temperature
      break;
    case 2:
      Display_write("Pressure", 40, 0, 1, Number_command);
      Display_write("0." + (String)round(pressure / 101.325) + " atm", 17, 3, 2, Number_command);
      break;
    case 3:
      Display_write("Pressure", 40, 0, 1, Number_command);
      Display_write((String)(pressure * 0.00750063755419211) + " mm", 10, 3, 2, Number_command);
      break;
    case 4:
      Display_write("Altitude", 40, 0, 1, Number_command);
      Display_write((String)(altitude - relative_altitude) + " m", 22, 3, 2, Number_command);
      break;
    case 5:
      Display_write("Roshi Point", 30, 0, 1, Number_command);
      Display_write((String)Roshi_Point(sensor.tem, sensor.hum) + " C", 20, 3, 2, Number_command);
      break;
    case 6:
      Display_write("Humidity", 40, 0, 1, Number_command);
      Display_write((String)sensor.hum + " %", 22, 3, 2, Number_command);
      break;
    case 7:
      Display_write("Time", 53, 0, 1, Number_command);
      Display_write((getHour + ":" + getMinute), 9, 3, 4, Number_command);
      break;
    default:;
  }
}
