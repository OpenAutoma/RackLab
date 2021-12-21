#include "main.hpp"
#include <Arduino.h>



void Init()
{
    
    pinMode(LED_STATUS, OUTPUT);

    // Fans
    pinMode(FAN0, OUTPUT);
    pinMode(FAN1, OUTPUT);
    pinMode(FAN2, OUTPUT);
    pinMode(FAN3, OUTPUT);
    pinMode(FAN4, OUTPUT);
    pinMode(FAN5, OUTPUT);

    pinMode(ENDSTOP_1, INPUT_PULLUP);
    pinMode(ENDSTOP_2, INPUT_PULLUP);
    pinMode(ENDSTOP_3, INPUT_PULLUP);
    pinMode(ENDSTOP_4, INPUT_PULLUP);
    pinMode(ENDSTOP_5, INPUT_PULLUP);
    pinMode(ENDSTOP_6, INPUT_PULLUP);
    pinMode(ENDSTOP_7, INPUT_PULLUP);
    pinMode(ENDSTOP_8, INPUT_PULLUP);
    pinMode(PROBE, INPUT_PULLUP);
 
    



    Wire.setSDA(I2C_SDA);
    Wire.setSCL(I2C_SCL);

    Wire.begin(I2C_SDA, I2C_SCL ); 

    Serial.begin(BAUDRATE );

}