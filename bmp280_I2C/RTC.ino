void Time_correction_RTC() {
  byte Time_Hour, Time_min;

  Time_Hour = myRTC.getHour(h12Flag, pmFlag);
  Time_min = myRTC.getMinute();

  oled.clear();  // очистка
  Display_write("Time hour", 36, 0, 1, Number_command);
  Display_write((String)Time_Hour, 43, 2, 4, Number_command);
  Time_Hour = Time_setting(Time_Hour, "Time_Hour");

  oled.clear();  // очистка
  Display_write("Time min", 36, 0, 1, Number_command);
  Display_write((String)Time_min, 43, 2, 4, Number_command);
  Time_min = Time_setting(Time_min, "Time_min");

  oled.clear();  // очистка
  myRTC.setMinute(Time_min);
  myRTC.setHour(Time_Hour);
  myRTC.setSecond(0);
}

byte Time_setting(byte Time_number, String string_time) {
  int static Last_Time_number=Time_number;
  while (menu_comand_button(number_screen + 1)) { delay(10); }
  while (!menu_comand_button(number_screen + 1)) {

    
    Display_write(string_time, 36, 0, 1, Number_command);
    Display_write((String)Time_number, 43, 2, 4, Number_command);
    if (ckick_Button1()) Time_number++;
    if (ckick_Button2()) Time_number--;
    if (Time_number == 9 && Last_Time_number==10)oled.clear();
    if (Time_number == 60 && string_time == "Time_min") {oled.clear();Time_number = 0;}
    if (Time_number == 255 && string_time == "Time_min") Time_number = 59;
    if (Time_number == 24 && string_time == "Time_Hour") {oled.clear();Time_number = 0;}
    if (Time_number == 255 && string_time == "Time_Hour") Time_number = 23;

    Last_Time_number=Time_number;
  }
  return Time_number;
}