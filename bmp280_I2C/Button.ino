byte Doing_Button(byte Number_command) {
  menu_comand_button(Number_command);
  if (ckick_Button1()) Number_command++;
  if (ckick_Button2()) Number_command--;
  if (Number_command == number_screen + 1) Number_command = 1;
  if (Number_command == 0) Number_command = number_screen;

  return Number_command;
}

bool menu_comand_button(byte Number_command) {
  int static a = 1;
  uint32_t static Time;
  if (!digitalRead(Pin_button2) && !digitalRead(Pin_button3) && a) {
    Time = millis();
    a = 0;
  }
  if (digitalRead(Pin_button2) && digitalRead(Pin_button3) && (millis() - Time) > 5000) {
    Time = millis();
    switch (Number_command) {
      case 1:; break;
      case 2:; break;
      case 3:; break;
      case 4: Setting_altitude(); break;
      case 5:; break;
      case 6:; break;
      case 7: Time_correction_RTC(); break;
      case number_screen + 1:; break;
    }
    a = 1;
    return 1;
  }
  return 0;
}

void Setting_altitude() {
  relative_altitude = altitude;
  EEPROM.put(70, relative_altitude);
}

bool ckick_Button1() {
  bool status = 0;
  byte static command = 1, last_command = 1;

  command = digitalRead(Pin_button3);
  if (last_command != command) {
    delay(15);

    if (last_command != command && command == 0) status = 1;
    if (last_command != command) last_command = command;

    return status;
  }
  return status;
}

bool ckick_Button2() {
  bool status = 0;
  byte static command = 1, last_command = 1;

  command = digitalRead(Pin_button2);
  if (last_command != command) {
    delay(15);

    if (last_command != command && command == 0) status = 1;
    if (last_command != command) last_command = command;

    return status;
  }
  return status;
}