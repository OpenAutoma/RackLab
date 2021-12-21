#include "main.hpp"
#include <Arduino.h>

void SetupEndstops()
{
    pinMode(ENDSTOP_1, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(ENDSTOP_1),X_Endstop_ISR,FALLING);

    pinMode(ENDSTOP_2, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(ENDSTOP_2),Y_Endstop_ISR,FALLING);

    pinMode(ENDSTOP_3, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(ENDSTOP_3),Z_Endstop_ISR,FALLING);
}



void X_Endstop_ISR()
{
  //DisplayStrings("X endstop","triggered" );
  ZeroPosition(0);
  XAtHome( );
}
void Y_Endstop_ISR()
{
  //DisplayStrings("Y endstop","triggered" );
  ZeroPosition(1);
  YAtHome( );
}
void Z_Endstop_ISR()
{
  DisplayStrings("Z endstop","triggered" );
  
  ZeroPosition(2);
  ZAtHome( );
}
void W_Endstop_ISR()
{
  //DisplayStrings("Z endstop","triggered" );
  ZeroPosition(3);
  WAtHome( );
}


// void EndstopsSanityCheck()
// {
//   if(digitalRead(X_Endstop) == digitalRead(X_Endstop_inv))
//   {
//       DisplayStrings("! Error !", "", "Check X endstop" );
//       while (true)
//       {
//         LEDToggleX(5, 200);
//       }
//   }
//   if(digitalRead(Y_Endstop) == digitalRead(Y_Endstop_inv))
//   {
//       DisplayStrings("! Error !", "", "Check Y endstop" );
//       while (true)
//       {
//         LEDToggleX(5, 200);
//       }
//   }
//   if(digitalRead(Z_Endstop) == digitalRead(Z_Endstop_inv))
//   {
//       DisplayStrings("! Error !", "", "Check Z endstop" );
//       while (true)
//       {
//         LEDToggleX(5, 200);
//       }
//   }
// }
