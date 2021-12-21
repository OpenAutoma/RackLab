#include "main.hpp"
#include <Arduino.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

void LEDToggleX(int cycles = 5, int delayValue = 100)
{
    for(int i = 0; i < cycles; i++)
    {
    digitalWrite(LED_STATUS, HIGH);
    delay(delayValue);
    digitalWrite(LED_STATUS, LOW);
    delay(delayValue);
    }
}



void DisplayStrings(String line1)
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(line1);
  display.display();
}
void DisplayStrings(String line1, String line2)
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(line1);
  display.println(line2);
  display.display();
}
void DisplayStrings(String line1, String line2, String line3)
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(line1);
  display.println(line2);
  display.println(line3);
  display.display();
}
void DisplayStrings(String line1, String line2, String line3, String line4)
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(line1);
  display.println(line2);
  display.println(line3);
  display.println(line4);
  display.display();
}
void DisplayLine4(String line1)
{
  display.clearDisplay();
  display.setCursor(2, 0);
  display.println(line1);
  display.display();
}

void oled_setup(void) {


    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.println(F("SSD1306 allocation failed"));
    while(true)
    {
      LEDToggleX(5,50);
    }
  }

  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.println(F("Starting..."));

  display.display();
}

