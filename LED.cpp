#include <Arduino.h>
#include "LED.h"

void LEDon( void ) {
  digitalWrite( LED_BUILTIN, LOW );
}

void LEDoff( void ) {
  digitalWrite( LED_BUILTIN, HIGH );
}

void LEDset( uint8_t state ) {
  if ( state ) {
    LEDon();
  } else {
    LEDoff();
  }
}

void LEDtoggle( void ) {
  if ( HIGH == digitalRead( LED_BUILTIN ) ) {
    digitalWrite( LED_BUILTIN, LOW );
  } else {
    digitalWrite( LED_BUILTIN, HIGH );
  }
}

void LEDinit( void ) {
  pinMode( LED_BUILTIN, OUTPUT );
  LEDon();
}
