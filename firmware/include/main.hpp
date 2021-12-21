#include <Wire.h>
#include "AccelStepper.h"
#include "Adafruit_PWMServoDriver.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"


#pragma once

#ifndef MAIN_HPP
#define MAIN_HPP


// some taken from 
// https://github.com/murrayhenwood/BIGTREETECH-OCTOPUS-V1.0/blob/master/Firmware/Marlin-bugfix-2.0.x/Marlin/src/pins/stm32f4/pins_BTT_OCTOPUS_V1_common.h


/**********************************/
/************** Pins **************/
/**********************************/

#define LED_STATUS PA13
#define LED_RGB PB0

#define PS_ON PE11


/************** I2C **************/
#define I2C_SDA PB9
#define I2C_SCL PB8

/************** SPI **************/
#define SPI3_MISO PB4
#define SPI3_MOSI PB5
#define SPI3_SCK PB3
#define SPI3_CS PA15

/************** CAN Bus **************/
#define CAN_RX1 PD0
#define CAN_TX1 PD1

/************** Heaters **************/
#define HEATER_BED_PIN                      PA1   // Hotbed
#define HEATER_0_PIN                        PA2   // Heater0
#define HEATER_1_PIN                        PA3   // Heater1
#define HEATER_2_PIN                        PB10  // Heater2
#define HEATER_3_PIN                        PB11  // Heater3

/************** Fans **************/
#define FAN0 PA8
#define FAN1 PE5
#define FAN2 PD12
#define FAN3 PD13
#define FAN4 PD14
#define FAN5 PD15

/************** End stops **************/
#define ENDSTOP_1 PG6
#define ENDSTOP_2 PG9
#define ENDSTOP_3 PG10
#define ENDSTOP_4 PG11
#define ENDSTOP_5 PG12
#define ENDSTOP_6 PG13
#define ENDSTOP_7 PG14
#define ENDSTOP_8 PG15
#define PROBE PB7

/************** Drivers **************/

#define DRIVER_SPI_MISO PA6
#define DRIVER_SPI_MOSI PA7
#define DRIVER_SPI_SCK PA5

#define DRIVER0_SERIAL_TX_PIN                  PC4
#define DRIVER0_SERIAL_RX_PIN                  PC4
#define DRIVER1_SERIAL_TX_PIN                  PD11
#define DRIVER1_SERIAL_RX_PIN                  PD11
#define DRIVER2_SERIAL_TX_PIN                  PC6
#define DRIVER2_SERIAL_RX_PIN                  PC6
#define DRIVER3_SERIAL_TX_PIN                  PC7
#define DRIVER3_SERIAL_RX_PIN                  PC7
#define DRIVER4_SERIAL_TX_PIN                  PF2
#define DRIVER4_SERIAL_RX_PIN                  PF2
#define DRIVER5_SERIAL_TX_PIN                  PE4
#define DRIVER5_SERIAL_RX_PIN                  PE4
#define DRIVER6_SERIAL_TX_PIN                  PE1
#define DRIVER6_SERIAL_RX_PIN                  PE1
#define DRIVER7_SERIAL_TX_PIN                  PD3
#define DRIVER7_SERIAL_RX_PIN                  PD3

#define DRIVER0_STEP_PIN                          PF13  
#define DRIVER0_DIR_PIN                           PF12
#define DRIVER0_ENABLE_PIN                        PF14
//#define DRIVER0_CS_PIN                          PC4

#define DRIVER1_STEP_PIN                          PG0   
#define DRIVER1_DIR_PIN                           PG1
#define DRIVER1_ENABLE_PIN                        PF15
//#define DRIVER1_CS_PIN                          PD11

#define DRIVER2_STEP_PIN                          PF11  
#define DRIVER2_DIR_PIN                           PG3
#define DRIVER2_ENABLE_PIN                        PG5
//#define DRIVER2_CS_PIN                          PC6

#define DRIVER3_STEP_PIN                         PG4   
#define DRIVER3_DIR_PIN                          PC1
#define DRIVER3_ENABLE_PIN                       PA0
//#define DRIVER3_CS_PIN                         PC7

#define DRIVER4_STEP_PIN                         PF9   /
#define DRIVER4_DIR_PIN                          PF10
#define DRIVER4_ENABLE_PIN                       PG2
//#define DRIVER4_CS_PIN                        PF2

#define DRIVER5_STEP_PIN                         PC13  
#define DRIVER5_DIR_PIN                          PF0
#define DRIVER5_ENABLE_PIN                       PF1
//#define DRIVER5_CS_PIN                         PE4

#define DRIVER6_STEP_PIN                         PE2   
#define DRIVER6_DIR_PIN                          PE3
#define DRIVER6_ENABLE_PIN                       PD4
//#define DRIVER6_CS_PIN                         PE1

#define DRIVER7_STEP_PIN                         PE6   
#define DRIVER7_DIR_PIN                          PA14
#define DRIVER7_ENABLE_PIN                       PE0
//#define DRIVER7_CS_PIN                         PD3

// /************** X Axis **************/
// #define X_Motor_STEP DRIVER0_STEP_PIN
// #define X_Motor_DIR DRIVER0_DIR_PIN
// #define X_Motor_ENABLE DRIVER0_ENABLE_PIN
// #define X_Endstop ENDSTOP_1

// /************** Y Axis **************/
// #define Y_Motor_STEP DRIVER1_STEP_PIN
// #define Y_Motor_DIR DRIVER1_DIR_PIN
// #define Y_Motor_ENABLE DRIVER1_ENABLE_PIN
// #define Y_Endstop ENDSTOP_2

// /************** Z Axis **************/
// #define Z_Motor_STEP DRIVER2_STEP_PIN
// #define Z_Motor_DIR DRIVER2_DIR_PIN
// #define Z_Motor_ENABLE DRIVER2_ENABLE_PIN
// #define Z_Endstop ENDSTOP_3

/**
 *                      -------
 *            GND | 9  |       | 8 | 3.3V
 *  (ESP-CS) PB12 | 10 |       | 7 | PB15 (ESP-MOSI)
 *           3.3V | 11 |       | 6 | PB14 (ESP-MISO)
 * (ESP-IO0)  PD7 | 12 |       | 5 | PB13 (ESP-CLK)
 * (ESP-IO4) PD10 | 13 |       | 4 | NC
 *             NC | 14 |       | 3 | PE15 (ESP-EN)
 *  (ESP-RX)  PD8 | 15 |       | 2 | NC
 *  (ESP-TX)  PD9 | 16 |       | 1 | PE14 (ESP-RST)
 *                      -------
 *                       WIFI
 */
#define ESP_WIFI_MODULE_COM                    3  // Must also set either SERIAL_PORT or SERIAL_PORT_2 to this
#define ESP_WIFI_MODULE_BAUDRATE        BAUDRATE  // Must use same BAUDRATE as SERIAL_PORT & SERIAL_PORT_2
#define ESP_WIFI_MODULE_RESET_PIN           PG7
#define ESP_WIFI_MODULE_ENABLE_PIN          PG8
#define ESP_WIFI_MODULE_GPIO0_PIN           PD7
#define ESP_WIFI_MODULE_GPIO4_PIN           PD10


/**************************************/
/************** Not Pins **************/
/**************************************/

#define MaxSpeed 3333 // steps per second (1000*200/60)
#define MaxAcc 3333*10

#define XStepper_Miliamps 1500
#define XStepper_steps_per_mm 66 // steps
#define XStepper_MaxSpeed MaxSpeed*2 // mm/s
#define XStepper_Acceleration MaxAcc // mm/s^2

#define YStepper_Miliamps 1500
#define YStepper_steps_per_mm 66 // steps
#define YStepper_MaxSpeed MaxSpeed*2 // mm/s
#define YStepper_Acceleration MaxAcc // mm/s^2

#define ZStepper_Miliamps 1700
#define ZStepper_steps_per_mm 6600 // steps
#define ZStepper_MaxSpeed MaxSpeed*1.7 // mm/s
#define ZStepper_Acceleration MaxAcc // mm/s^2

#define WStepper_Miliamps 600
#define WStepper_steps_per_mm 2 // steps
#define WStepper_MaxSpeed MaxSpeed // mm/s
#define WStepper_Acceleration MaxAcc // mm/s^2

#define MICROSTEPS        16
#define R_SENSE           0.11f
#define DRIVER_ADDRESS1   0b00
#define TMC_BAUD_RATE     19200
#define SERIAL_PORT       Serial1

#define BAUDRATE 115200

#define DS1307_I2C_ADDRESS 0x68 //0x78 //  0x3C// 0x68 
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // 0x78 // 0x3C //
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64



#define SERVOMIN  500 // 150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  2400 // 600 // This is the 'maximum' pulse length count (out of 4096)
//#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
//#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

#define LATCH_SERVO_0_INDEX 0
#define LATCH_SERVO_0_CLOSED_ANGLE 15
#define LATCH_SERVO_0_OPEN_ANGLE 105


#define LATCH_SERVO_1_INDEX 1
#define LATCH_SERVO_1_CLOSED_ANGLE 165
#define LATCH_SERVO_1_OPEN_ANGLE 75


void Init();
void SetTime(
    int second,
    int minute,
    int hour,
    int dayOfWeek,
    int dayOfMonth,
    int month,
    int year);
void TimeToString(char[]);
void GetTime();

void X_Endstop_ISR();
void Y_Endstop_ISR();
void Z_Endstop_ISR();
void SetupEndstops();
void EndstopsSanityCheck();
void SetupSteppers();

void LEDToggleX(int cycles , int delayValue );

void oled_setup(void);
void DisplayStrings(String line1);
void DisplayStrings(String line1, String line2);
void DisplayStrings(String line1, String line2, String line3);
void DisplayStrings(String line1, String line2, String line3, String line4);
void DisplayLine4(String line1);

void MoveUpdate();
void MotorsOff();
void XMove(long value);
void YMove(long value);
void ZMove(long value);
void WMove(long value);
void XAtHome( );
void YAtHome( );
void ZAtHome( );
void WAtHome( );
void XMoveTo(long value);
void YMoveTo(long value);
void ZMoveTo(long value);
void WMoveTo(long value);

void ZeroPosition(int pos);
void MoveTo(long * pos);
void SteppersRun();

long GetXPos();
long GetYPos();
long GetZPos();
long GetWPos();

// void OpenLatch()
// {
//   pwm.writeMicroseconds(LATCH_SERVO_0_INDEX, map(LATCH_SERVO_0_OPEN_ANGLE, 0, 180, SERVOMIN, SERVOMAX));
//   pwm.writeMicroseconds(LATCH_SERVO_1_INDEX, map(LATCH_SERVO_1_OPEN_ANGLE, 0, 180, SERVOMIN, SERVOMAX));
//     latchState = false;
// }

// void CloseLatch()
// {
//   pwm.writeMicroseconds(LATCH_SERVO_0_INDEX, map(LATCH_SERVO_0_CLOSED_ANGLE, 0, 180, SERVOMIN, SERVOMAX));
//   pwm.writeMicroseconds(LATCH_SERVO_1_INDEX, map(LATCH_SERVO_1_CLOSED_ANGLE, 0, 180, SERVOMIN, SERVOMAX));
//     latchState = true;
// }
// void ToggleLatch()
// {
//     if(latchState)
//     {
//         OpenLatch();
//     }
//     else
//     {
//         CloseLatch();
//     }
//     latchState != latchState;
// }







#endif