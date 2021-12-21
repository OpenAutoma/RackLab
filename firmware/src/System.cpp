#include "main.hpp"
#include <Arduino.h>


byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;

byte decToBcd(byte val)
{
return ( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
return ( (val/16*10) + (val%16) );
}

void SetTime(
    int second,
    int minute,
    int hour,
    int dayOfWeek,
    int dayOfMonth,
    int month,
    int year)
{
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write(decToBcd(0));
    Wire.write(decToBcd(second)); // 0 to bit 7 starts the clock
    Wire.write(decToBcd(minute));
    Wire.write(decToBcd(hour)); // If you want 12 hour am/pm you need to set
    // bit 6 (also need to change readDateDs1307)
    Wire.write(decToBcd(dayOfWeek));
    Wire.write(decToBcd(dayOfMonth));
    Wire.write(decToBcd(month));
    Wire.write(decToBcd(year));
    Wire.endTransmission();

}

void TimeToString(char v[])
{
    sprintf(v, "Lab clock: %i-%i-%iT%i:%i:%i\n", year,month, dayOfMonth, hour, minute, second );
} 

void GetTime()
{
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write(decToBcd(0));
    Wire.endTransmission();
    Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
    second = bcdToDec(Wire.read() & 0x7f);
    minute = bcdToDec(Wire.read());
    hour = bcdToDec(Wire.read() & 0x3f); // Need to change this if 12 hour am/pm
    dayOfWeek = bcdToDec(Wire.read());
    dayOfMonth = bcdToDec(Wire.read());
    month = bcdToDec(Wire.read());
    year = bcdToDec(Wire.read());
}