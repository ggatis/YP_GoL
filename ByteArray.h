/**
 * @file    ByteArray.h
 *
 * @brief   Declaration of class ByteArray
 *
 * @note    This example code is free software: you can redistribute it and/or modify it.
 *
 *          This program is provided by EDI on an "AS IS" basis without
 *          any warranties in the hope that it will be useful.
 * 
 * Gatis Gaigals @ EDI, 2024
 */

#ifndef _ByteArray_H_
#define _ByteArray_H_

#include <string>   //cpp string
#include <stdint.h>
//#include <stdio.h>  //c printf

//#include <USBSerial.h>
//#include "HardwareSerial.h"


/**
 * @brief   The ByteArray class provides methods for ByteArray.
 */

class ByteArray {
    public:

        /**
          * @brief  class constructor for empty instance
          *
          * @param  -
          */
                    ByteArray( void );

        /**
          * @brief  class constructor, not initialised buffer
          *
          * @param  buffersize  buffer size
          */
                    ByteArray( uint16_t buffersize );

        /**
          * @brief  class constructor, size, pointe to buffer
          *
          * @param  size  buffer size, it all contains data
          *         dataptr  pointer to buffer
          */
                    ByteArray( uint16_t size, uint8_t* dataptr );

        /**
          * @brief  class constructor, all parameters
          *
          * @param  size  buffer size, it all contains data
          *         filled  useful data bytes count
          *         dataptr  pointer to buffer
          */
                    ByteArray( uint16_t size, uint16_t filled, uint8_t* dataptr );

        /**
          * @brief  class constructor, initialised repeating a char
          *
          * @param  repeats  character repeat count
          *         c        character
          */
                    ByteArray( uint16_t repeats, char c );

        /**
          * @brief  class constructor from string
          *
          * @param  aString
         */
                    ByteArray( const std::string& aString );

        /**
          * @brief  class constructor from rvalue string
          *
          * @param  aString
         */
                    ByteArray( std::string&& aString );

        /**
          * @brief  class copy constructor, initialised using const ByteArray,
          *         _size is reduced to _count
          *
          * @param  aByteArray   input ByteArray
          */
                    ByteArray( const ByteArray& other );

        /**
          * @brief  move constructor
          *
          * @param  ByteArray& aByteArray
          */
                    ByteArray( ByteArray&& other ) noexcept;

        /**
          * @brief  class destructor
          *
          * @param  -
          */
                   ~ByteArray( void );

        /**
          * @brief  copy assignment operator
          *
          * @param  const ByteArray& aByteArray
          */
        ByteArray& operator = ( const ByteArray& other );

        /**
          * @brief  move assignment operator
          *
          * @param  ByteArray& aByteArray
          */
        ByteArray& operator = ( ByteArray&& other ) noexcept;

        /**
         * @brief   returns data buffer
         *
         * @param   -
         *
         * @return  ByteArray data buffer
         */
        uint8_t*    data( void ) const;

        /**
         * @brief   returns size of data in array
         *
         * @param   -
         *
         * @return  ByteArray data size
         */
        uint16_t    count( void ) const;

        /**
         * @brief   returns size of array
         *
         * @param   -
         *
         * @return  ByteArray array size
         */
        uint16_t    size( void ) const;

        /**
         * @brief   clears the contents of the byte array and makes it null
         *
         * @param   -
         *
         * @return  -
         */
        void        clear( void );

        /**
         * @brief   extends the content to the _size
         *
         * @param   -
         *
         * @return  -
         */
        void        extendo( void );

        /**
         * @brief   updates count of the data size in arrray
         *          in the case it is manipulated from outside
         *
         * @param   -
         *
         * @return  correctly updated count of the data size in arrray
         */
        uint16_t    update_count( uint16_t newcount );

        /**
         * @brief   return byte at index
         *
         * @param   index  array index
         *
         * @return  byte at position index
         */
        uint8_t     at( uint16_t index ) const;

        /**
         * @brief   return byte at index
         *
         * @param   index  array index
         *
         * @return  byte at position index
         */
        uint8_t     at( int index ) const;

        /**
         * @brief   return byte at x*width+y
         *
         * @param   x       x
         * @param   y       y
         * @param   width   width
         * @param   height  height
         *
         * @return  byte at position if the position is valid
         */
        uint8_t     peek( int x, int y, int width, int height ) const;

        /**
         * @brief   store a byte and return 0 for valid x*width+y
         *
         * @param   x       x
         * @param   y       y
         * @param   width   width
         * @param   height  height
         *
         * @return  0 if position was valid
         */
        uint8_t     poke( uint8_t aByte, int x, int y, int width, int height );

        /**
         * @brief   incoming ByteArray with added abyte
         *
         * @param   byte  byte to append
         *
         * @return  byte count in array
         */
        ByteArray   append( uint8_t abyte );

        /**
         * @brief   incoming ByteArray with added abyte x repeats
         *
         * @param   repeats byte repeats
         *          byte    byte to append
         *
         * @return  byte count in array
         */
        ByteArray   append( int repeats, uint8_t abyte );

        /**
         * @brief   return ByteArray converted form HEX
         *
         * @param   hexEncoded  HEX encoded array
         *
         * @return  ByteArray converted form HEX
         */
        ByteArray   fromHex( const ByteArray &hexEncoded ) const;

        /**
         * @brief   returns mid
         *
         * @param   uint16_t index
         *          int size
         *
         * @return  ByteArray
         */
        ByteArray   mid( uint16_t index, int size ) const;

        /**
         * @brief   Removes n bytes from the end of the byte array.
         *          If n is greater than size(), the result is an empty byte array.
         *
         * @param   n   bytes to remove rom the end
         *
         * @return  ByteArray
         */
        ByteArray   chop( int n );

        /**
         * @brief   prints the buffer ar chars
         *
         * @param   -
         *
         * @return  -
         */
        void        print( void ) const;

        /**
         * @brief   prints the buffer as chars in 2D
         *
         * @param   -
         *
         * @return  -
         */
        void        print2D( int width, int height ) const;

        /**
         * @brief   prints the buffer as numbers in 2D
         *
         * @param   -
         *
         * @return  -
         */
        void        print2Dd( int width, int height ) const;

    private:
        //<! size
        uint16_t        _size;
        //<! count
        uint16_t        _count;
        //<! data
        uint8_t* const  _data;
};

#endif // _ByteArray_H_
