#include <Wire.h>             // Стандартная библиотека шины I2C
#include <Adafruit_BMP280.h>  // Библиотека датчика
#include <Adafruit_NeoPixel.h>//
#include <EEPROM.h>
#include <DS3231.h>
#include <GyverOLED.h>
#include <iarduino_AM2320.h>  //  подключаем библиотеку для работы с модулем влажности и температуры AM2320

#define LED_COUNT 5
#define LED_PIN 3
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define calculation 100
#define Pin_button1 2
#define Pin_button2 11
#define Pin_button3 10
#define number_screen 7
#define N 36

iarduino_AM2320 sensor; 
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);  // Создаем объект для управления диодами  //
Adafruit_BMP280 bmp280;                                             // Создаем объект bmp280
float temperature, pressure, altitude, relative_altitude = 0;       // Показатели датчика
uint8_t saturation = 255, value = 8;                               // Переменные для LED
byte Number_command = number_screen;                                // Задаем начальние настройки светодиодам
DS3231 myRTC;                                                       // Объект RTC


// RTC переменные
bool century = false;
bool h12Flag;
bool pmFlag;

uint32_t Time = millis();


/*unsigned long*/ float pressure_long, aver_pressure, pressure_array[N], time_array[N]={0,1},Pressure[N];
/*unsigned long*/ float sumX, sumY, sumX2, sumXY,delta=0;
float a, b;


void setup() {
  init_serial_pin_led_Hum();
  Init_BMP280();
  Display_Connection(); 
  Setup_weather_prediction();
}

void loop() {

  Number_command = Doing_Button(Number_command);
  TEM_PRE_ALTI();
  HUM();
  Display_Doing(Number_command);
 // LED_Doing(Number_command);
  Weather_prediction() ;
}

void init_serial_pin_led_Hum() {
  Serial.begin(9600);                 // Инициализируем монитор порта на скорости 9600
  EEPROM.get(70, relative_altitude);  //EEPROM
  Serial.print(relative_altitude);
  pinMode(Pin_button1, INPUT);  //d4
  pinMode(Pin_button2, INPUT);  //d6
  pinMode(Pin_button3, INPUT);  //d5
  pinMode(7, OUTPUT);
  strip.begin();   // Инициализируем объект NeoPixel        //
  sensor.begin();  // Инициируем работу с модулем AM2320
}