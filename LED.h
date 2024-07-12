#include <stdint.h>

#define LED_BUILTIN   13

void LEDon( void );
void LEDoff( void );
void LEDset( uint8_t state );
void LEDtoggle( void );
void LEDinit( void );
