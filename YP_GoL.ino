#include "YP_GoL.h"

//GoL globals
volatile int width   = 12;
volatile int height  = 12;


#include <stdint.h>
#include <stdio.h>  //c printf
//#include <iostream>
//#include <cstdio>

#define REDEFINE_WRITE 1
#if 0 == REDEFINE_WRITE
/* Private function prototypes -----------------------------------------------*/
extern "C" PUTCHAR_PROTOTYPE {
  HAL_UART_Transmit( SerialUSB.getHandle(), (uint8_t*)&ch, 1, HAL_MAX_DELAY );
  return ch;
}
#else   //0 == REDEFINE_WRITE
//Override the _write function to use SerialUSB
extern "C" int _write( int file, char* ptr, int len ) {
    //Write the character array to SerialUSB
    return (int)SerialUSB.write( (uint8_t*)ptr, len );
}
#endif  //0 == REDEFINE_WRITE


volatile uint32_t mySysTick = 0;
volatile uint32_t lastS2IOtick;
volatile uint8_t  ActiveCommand = 0;


#include "Pipeline.h"
#include "Pipes.h"

ByteArray* pRaMonBuff = nullptr;  //serial activity

//#include "CRC16.h"
//#include "SlipDecoder.h"
//#include "SlipEncoder.h"


/*********************************************************************/
/*                               Pins                                */
/*********************************************************************/
#include "LED.h"

/*********************************************************************/
/*                              Serials                              */
/*********************************************************************/
void serialEvent1() {
    LEDtoggle();
    //SerialUSB.println( F("sEv1") );
    printf("sEv1\r\n");
}

void serialEvent2() {
    LEDtoggle();
    //SerialUSB.println( F("sEv2") );
    printf("sEv2\r\n");
    if ( pRaMonBuff ) {
        lastS2IOtick = mySysTick;
        while ( 0 < Serial2.available() ) {
            LEDtoggle();
            pRaMonBuff->append( (uint8_t)Serial2.read() );
        }
    }
}

/*********************************************************************/
/*                               Setup                               */
/*********************************************************************/
void setupPins( void ) {
  LEDinit();
}

void setupSerials( void ) {
  //Serial.end();
  SerialUSB.begin( 115200 );
  //Initialize serial and wait for port to open:
  while ( !SerialUSB ) {
    ;   //wait for serial port to connect. Needed for native USB port only
  }
  LEDoff();

  Serial1.end();
  //Serial1.setRx( PA10 );
  //Serial1.setTx( PA9 );
  Serial1.begin( 115200 );
  //Serial1.print( "S1" );

  Serial2.end();
  //Serial2.setRx( PA3 );
  //Serial2.setTx( PA2 );
  Serial2.setRx( PA_3_ALT1 );
  Serial2.setTx( PA_2_ALT1 );
  Serial2.begin( 115200 );

  Serial4.end();
  //Serial5.end();

}

void setupTimers( void ) {

#if 0 == _SYSTIME_
  //initCurrentTime(); temp!!!
#endif
#if defined( TIM1 )
  TIM_TypeDef *Instance = TIM1;
#else
  TIM_TypeDef *Instance = TIM2;
#endif

  //Instantiate HardwareTimer object.
  //Thanks to 'new' instanciation, HardwareTimer is not destructed when setup() function is finished.
/* temp!!!
  pMyTim = new HardwareTimer( Instance );
  pMyTim->setMode( 2, TIMER_OUTPUT_COMPARE );
  pMyTim->setOverflow( 10, HERTZ_FORMAT );  //10 Hz
  pMyTim->attachInterrupt( _100msCallback );
  pMyTim->resume();
*/
}


//dynamically allocated objects
Pipeline* pPipeline = nullptr;
int       Iteration = 0;

void setupObjects() {

    //Initialize Pipeline object specifying the default buffer size
    pPipeline = new Pipeline( width * height );

    //Add a GoL processor to the Pipeline list
    pPipeline->AddProcessor( GoL );

    //init GoL
    GoLinit( pPipeline->getFrontEnd(), pPipeline->getBackEnd() );

    printf("Iteration [0]\r\n");
    pPipeline->getFrontEnd()->print2D( width, height );

}

void setup( void ) {

  pRaMonBuff = new ByteArray( 300 );
  
  setupPins();
  setupSerials();

  printf("\r\nYP_GoL\r\n");

  Serial1.write("Serial1\r\n");
  Serial2.write("Serial2\r\n");

  //setupTimers();
  setupObjects();
  //setup mySysTick
  mySysTick = HAL_GetTick();

}

void clean() {
    //Delete dynamically allocated objects
    if ( pRaMonBuff ) delete pRaMonBuff;
    if ( pPipeline  ) delete pPipeline;
}


/*********************************************************************/
/*                               Main                                */
/*********************************************************************/
void loop() {

    mySysTick += 250;
    while ( HAL_GetTick() < ( mySysTick - 50 ) ) {;};
    LEDon();

    printf("Iteration [%d]\r\n", ++Iteration );
    
    if ( StatusCode::OK == pPipeline->processAll() ) {
        pPipeline->getBackEnd()->print2D( width, height );
    } else {
        printf("Processing failed in pipe: %d.\r\n", pPipeline->getFaultyPipe() );
    }
    pPipeline->swapIO();

    while ( HAL_GetTick() < mySysTick ) {;};
    LEDoff();

}
