/**
 * @file    Reverse.h
 *
 * @brief   Declaration of class Reverse
 *
 * @note    This example code is free software: you can redistribute it and/or modify it.
 *
 *          This program is provided by EDI on an "AS IS" basis without
 *          any warranties in the hope that it will be useful.
 * 
 * Gatis Gaigals, 2024
 */

#include "Processors.h"

StatusCode reverse_processor( ByteArray* in, ByteArray* out ) {
    //Reverse the input data and store in the output data
    uint16_t size = in->count();
    for ( int i = size - 1; i >= 0; --i ) {
        out->append( in->at( i ) );
    }
    //out->update_count( size );
    return StatusCode::OK;
}


#include "YP_GoL.h" //parameters for GoL

uint8_t decode( uint8_t aByte ) {
    return ( '*' == aByte ) ? 1 : 0;
}

uint8_t encode( uint8_t aByte ) {
    return ( aByte ) ? '*' : ' ';
}

inline int wrap( int i, int maxi ) {
    return ( i + maxi ) % maxi;
}


void GoLinit( ByteArray* pIn, ByteArray* pOut ) {
    pIn->extendo();
    pOut->extendo();
    for ( int y = 0; y < height; ++y ) {
        for ( int x = 0; x < width; ++x ) {
            pIn->poke( encode(
                    ( 9 == ( random() % 10 ) ) ? 1 : 0
                ), x, y, width, height );
        }
    }
}


StatusCode GoL( ByteArray* pIn, ByteArray* pOut ) {

    for ( int y = 0; y < height; y++ ) {
        for ( int x = 0; x < width; x++ ) {

            printf("w, h: %d, %d,", width, height );
            printf(" %2d, %2d", x, y );

            uint8_t currentState = decode( pIn->peek( x, y, width, height ) );

            printf(", %1d", currentState );

            int liveNeighbors = -currentState;
            for ( int dy = -1; dy <= 1; ++dy ) {
                for ( int dx = -1; dx <= 1; ++dx ) {
                    liveNeighbors +=
                        decode( pIn->peek(
                            wrap( x + dx, width ),
                            wrap( y + dy, height ),
                            width,
                            height
                        ) );
                }
            }

            printf(", %1d", liveNeighbors );

            uint8_t newState = 0;
            if ( currentState == 1 ) {
                newState = ( liveNeighbors == 2 || liveNeighbors == 3 ) ? 1 : 0;
            } else {
                newState = ( liveNeighbors == 3 ) ? 1 : 0;
            }

            printf(", %1d", newState );

            pOut->poke( encode( newState ), x, y, width, height );

            printf("\r\n");
        
        }

        if ( ( height - 1 ) <= y ) {
            //the loop did not want to terminate on 'y < height'!!!
//            printf("A. '( height - 1 ) <= y', h, y: %d, %d\r\n", height, y );
            goto getAway;
//        } else {
//            printf("B. '( height - 1 ) > y', h, y: %d, %d\r\n", height, y );
        }

    }
getAway:
    return StatusCode::OK;
}
