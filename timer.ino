#include <SharpIR.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define sensorpin A0

float volts;
float time1 = 0.00, time2 = 0.00, lap_time;

int distance, exit_condition, check = 0;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setCursor(10, 5);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("Init Done");
  display.display();
}

void loop() {

  volts = analogRead(sensorpin) * 0.0048828125;
  distance = 13 * pow(volts, -1);

  if (distance >= 15)
    check = 1;

  if (distance > 0 && distance < 15 && check == 1) {
    time1 = millis();
    exit_condition = 0;
    check = 0;
    while (exit_condition == 0) {
      volts = analogRead(sensorpin) * 0.0048828125;
      distance = 13 * pow(volts, -1);

      time2 = millis();
      lap_time = (time2 - time1) / 1000.00;

      display.clearDisplay();
      display.setCursor(10, 5);
      display.setTextSize(3);
      display.setTextColor(WHITE);
      display.print(lap_time);
      display.display();

      if (distance >= 15)
        check = 1;

      if (distance < 15 && distance > 0 && check == 1)
        exit_condition = 1;
    }
    check = 0;
  }
}
