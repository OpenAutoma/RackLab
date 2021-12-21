
#include "main.hpp"
#include <Arduino.h>
#include <TMCStepper.h>
#include <AccelStepper.h>
#include <SoftwareSerial.h>
#include <MultiStepper.h>

MultiStepper steppers;

SoftwareSerial SerialDriver0(DRIVER0_SERIAL_RX_PIN, DRIVER0_SERIAL_TX_PIN);
SoftwareSerial SerialDriver1(DRIVER1_SERIAL_RX_PIN, DRIVER1_SERIAL_TX_PIN);
SoftwareSerial SerialDriver2(DRIVER2_SERIAL_RX_PIN, DRIVER2_SERIAL_TX_PIN);
SoftwareSerial SerialDriver3(DRIVER3_SERIAL_RX_PIN, DRIVER3_SERIAL_TX_PIN);
// SoftwareSerial SerialDriver4(DRIVER4_SERIAL_RX_PIN, DRIVER4_SERIAL_TX_PIN);
// // SoftwareSerial SerialDriver5(DRIVER5_SERIAL_RX_PIN, DRIVER5_SERIAL_TX_PIN);
// // SoftwareSerial SerialDriver6(DRIVER6_SERIAL_RX_PIN, DRIVER6_SERIAL_TX_PIN);
// // SoftwareSerial SerialDriver7(DRIVER7_SERIAL_RX_PIN, DRIVER7_SERIAL_TX_PIN);

 TMC2209Stepper driver0(&SerialDriver0, R_SENSE, DRIVER_ADDRESS1);
 TMC2209Stepper driver1(&SerialDriver1, R_SENSE, DRIVER_ADDRESS1);
 TMC2209Stepper driver2(&SerialDriver2, R_SENSE, DRIVER_ADDRESS1);
 TMC2209Stepper driver3(&SerialDriver3, R_SENSE, DRIVER_ADDRESS1);
// TMC2209Stepper driver4(&SerialDriver4, R_SENSE, DRIVER_ADDRESS1);
// TMC2209Stepper driver5(&SerialDriver5, R_SENSE, DRIVER_ADDRESS1);
// TMC2209Stepper driver6(&SerialDriver6, R_SENSE, DRIVER_ADDRESS1);
// TMC2209Stepper driver7(&SerialDriver7, R_SENSE, DRIVER_ADDRESS1);
static AccelStepper X_stepper(AccelStepper::DRIVER, DRIVER0_STEP_PIN, DRIVER0_DIR_PIN);
static AccelStepper Y_stepper(AccelStepper::DRIVER, DRIVER1_STEP_PIN, DRIVER1_DIR_PIN);
static AccelStepper Z_stepper(AccelStepper::DRIVER, DRIVER2_STEP_PIN, DRIVER2_DIR_PIN);
static AccelStepper W_stepper(AccelStepper::DRIVER, DRIVER3_STEP_PIN, DRIVER3_DIR_PIN);

void SetupSteppers()
{

    // pinMode(DRIVER0_STEP_PIN, OUTPUT);
    // pinMode(DRIVER0_DIR_PIN, OUTPUT);
    // pinMode(DRIVER0_ENABLE_PIN, OUTPUT);
    // digitalWrite(DRIVER0_ENABLE_PIN, HIGH);

    SerialDriver0.begin(TMC_BAUD_RATE);
    SerialDriver0.listen();
    driver0.begin();
    driver0.toff(5);
    driver0.rms_current(XStepper_Miliamps);
    driver0.microsteps(MICROSTEPS);
    driver0.pwm_autoscale(true);

    X_stepper.setMaxSpeed(XStepper_MaxSpeed /* XStepper_steps_per_mm*/ ); 
    X_stepper.setAcceleration(XStepper_Acceleration /** XStepper_steps_per_mm*/ );
    X_stepper.setEnablePin(DRIVER0_ENABLE_PIN);
    X_stepper.setPinsInverted(false, false, true);
    X_stepper.enableOutputs();

    SerialDriver1.begin(TMC_BAUD_RATE);
    SerialDriver1.listen();
    driver1.begin();
    driver1.toff(5);
    driver1.rms_current(YStepper_Miliamps);
    driver1.microsteps(MICROSTEPS);
    driver1.pwm_autoscale(true);

    Y_stepper.setMaxSpeed(YStepper_MaxSpeed /*YStepper_steps_per_mm*/ ); 
    Y_stepper.setAcceleration(YStepper_Acceleration/*YStepper_steps_per_mm**/ );
    Y_stepper.setEnablePin(DRIVER1_ENABLE_PIN);
    Y_stepper.setPinsInverted(false, false, true);
    Y_stepper.enableOutputs();

    SerialDriver2.begin(TMC_BAUD_RATE);
    SerialDriver2.listen();
    driver2.begin();
    driver2.toff(5);
    driver2.rms_current(ZStepper_Miliamps);
    driver2.microsteps(MICROSTEPS);
    driver2.pwm_autoscale(true);

    Z_stepper.setMaxSpeed(ZStepper_MaxSpeed/*ZStepper_steps_per_mm */ ); 
    Z_stepper.setAcceleration(ZStepper_Acceleration/*ZStepper_steps_per_mm*/ );
    Z_stepper.setEnablePin(DRIVER2_ENABLE_PIN);
    Z_stepper.setPinsInverted(false, false, true);
    Z_stepper.enableOutputs();

    SerialDriver3.begin(TMC_BAUD_RATE);
    SerialDriver3.listen();
    driver3.begin();
    driver3.toff(5);
    driver3.rms_current(WStepper_Miliamps);
    driver3.microsteps(MICROSTEPS);
    driver3.pwm_autoscale(true);

    W_stepper.setMaxSpeed(WStepper_MaxSpeed /*WStepper_steps_per_mm */ ); 
    W_stepper.setAcceleration(WStepper_Acceleration/*WStepper_steps_per_mm */);
    W_stepper.setEnablePin(DRIVER3_ENABLE_PIN);
    W_stepper.setPinsInverted(false, false, true);
    W_stepper.enableOutputs();


    steppers.addStepper(X_stepper);
    steppers.addStepper(Y_stepper);
    steppers.addStepper(Z_stepper);
    steppers.addStepper(W_stepper);

}

void XMoveTo(long value)
{
    X_stepper.disableOutputs();
    X_stepper.moveTo(value*XStepper_steps_per_mm); 
    X_stepper.enableOutputs();
}
void YMoveTo(long value)
{
    Y_stepper.disableOutputs();
    Y_stepper.moveTo(value*YStepper_steps_per_mm); 
    Y_stepper.enableOutputs();
}
void ZMoveTo(long value)
{
    Z_stepper.disableOutputs();
    Z_stepper.moveTo(value*ZStepper_steps_per_mm); 
    Z_stepper.enableOutputs();
}
void WMoveTo(long value)
{
    W_stepper.disableOutputs();
    W_stepper.moveTo(value*WStepper_steps_per_mm); 
    W_stepper.enableOutputs();
}


void XMove(long value)
{
    X_stepper.disableOutputs();
    X_stepper.move(value*XStepper_steps_per_mm); 
    X_stepper.enableOutputs();
}
void XAtHome( )
{
    X_stepper.setCurrentPosition(0);
    X_stepper.moveTo(0);
}

void YMove(long value)
{
    Y_stepper.disableOutputs();
    Y_stepper.move(value*YStepper_steps_per_mm); 
    Y_stepper.enableOutputs();
}
void YAtHome( )
{
    Y_stepper.setCurrentPosition(0);
    Y_stepper.moveTo(0);
}

void ZMove(long value)
{
    Z_stepper.disableOutputs();
    Z_stepper.move(value*ZStepper_steps_per_mm); 
    Z_stepper.enableOutputs();
}
void ZAtHome( )
{
    Z_stepper.setCurrentPosition(0);
    Z_stepper.moveTo(0);
}

void WMove(long value)
{
    W_stepper.disableOutputs();
    W_stepper.move(value*WStepper_steps_per_mm); 
    W_stepper.enableOutputs();
}
void WAtHome( )
{
    W_stepper.setCurrentPosition(0);
    W_stepper.moveTo(0);
}

void MotorsOff()
{
    X_stepper.disableOutputs();
    Y_stepper.disableOutputs();
    Z_stepper.disableOutputs();
    W_stepper.disableOutputs();
}

void MoveTo(long * pos)
{
    steppers.moveTo(pos);
}
void SteppersRun()
{
    steppers.run();
}

void MoveUpdate()
{
    X_stepper.run();
    Y_stepper.run();
    Z_stepper.run();
    W_stepper.run();
}

long GetXPos()
{
    return X_stepper.currentPosition ()/XStepper_steps_per_mm;
}
long GetYPos()
{
    return Y_stepper.currentPosition ()/YStepper_steps_per_mm;
}
long GetZPos()
{
    return Z_stepper.currentPosition ()/ZStepper_steps_per_mm;
}
long GetWPos()
{
    return W_stepper.currentPosition ()/WStepper_steps_per_mm;
}