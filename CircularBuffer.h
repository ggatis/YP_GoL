/**
 * @file    CircularBuffer.h
 *
 * @brief   Declaration of class CircularBuffer
 *
 * @note    This example code is free software: you can redistribute it and/or modify it.
 *
 *          This program is provided by EDI on an "AS IS" basis without
 *          any warranties in the hope that it will be useful.
 * 
 * Gatis Gaigals, 2024
 */

#ifndef _CircularBuffer_H_
#define _CircularBuffer_H_

#include <string>   //cpp string
#include <stdint.h>
//#include <stdio.h>  //c printf

#include "ByteArray.h"

/**
 * @brief   The CircularBuffer class provides methods for CircularBuffer.
 */

class CircularBuffer : public ByteArray {
    public:

        /**
          * @brief  class constructor, not initialised buffer
          *
          * @param  size  buffer size
          */
                    CircularBuffer( uint16_t size );

        /**
          * @brief  class constructor, size, pointe to buffer
          *
          * @param  size  buffer size, it all contains data
          *         dataptr  pointer to buffer
          */
                    CircularBuffer( uint16_t size, uint8_t* dataptr );

        /**
          * @brief  class constructor, all parameters
          *
          * @param  size  buffer size, it all contains data
          *         filled  useful data bytes count
          *         dataptr  pointer to buffer
          */
                    CircularBuffer( uint16_t size, uint16_t filled, uint8_t* dataptr );

        /**
          * @brief  class constructor, initialised repeating a char
          *
          * @param  repeats  character repeat count
          *         c        character
          */
                    CircularBuffer( uint16_t repeats, char c );

        /**
          * @brief  class constructor from string
          *
          * @param  aString
         */
                    CircularBuffer( const std::string& aString );

        /**
          * @brief  class constructor from rvalue string
          *
          * @param  aString
         */
                    CircularBuffer( std::string&& aString );

        /**
          * @brief  class copy constructor, initialised using const CircularBuffer,
          *
          * @param  aCircularBuffer   input CircularBuffer
          */
                    CircularBuffer( const CircularBuffer& other );

        /**
          * @brief  move constructor
          *
          * @param  CircularBuffer& aCircularBuffer
          */
                    CircularBuffer( CircularBuffer&& other ) noexcept;

        /**
          * @brief  class destructor
          *
          * @param  -
          */
                   ~CircularBuffer( void );

        /**
          * @brief  copy assignment operator
          *
          * @param  const CircularBuffer& aCircularBuffer
          */
        CircularBuffer& operator = ( const CircularBuffer& other );

        /**
          * @brief  move assignment operator
          *
          * @param  CircularBuffer& aCircularBuffer
          */
        CircularBuffer& operator = ( CircularBuffer&& other ) noexcept;

        /**
         * @brief   returns data buffer
         *
         * @param   -
         *
         * @return  CircularBuffer data buffer
         */
        uint8_t*    data( void ) const;

        /**
         * @brief   returns size of data in array
         *
         * @param   -
         *
         * @return  CircularBuffer data size
         */
        uint16_t    count( void ) const;

        /**
         * @brief   returns size of array
         *
         * @param   -
         *
         * @return  CircularBuffer array size
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
         * @brief   returns flag indicating that bufer is empty
         *
         * @param   -
         *
         * @return  buffer is empty flag
         */
        bool isEmpty( void ) const;

        /**
         * @brief   returns flag indicating that bufer is full
         *
         * @param   -
         *
         * @return  buffer is full flag
         */
        bool isFull( void ) const;

        /**
         * @brief   returns oldest byte, advances tail
         *
         * @param   -
         *
         * @return  byte at tail
         */
        uint8_t     get( void );

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
         * @brief   incoming CircularBuffer with added abyte
         *
         * @param   byte  byte to put in buffer
         *
         * @return  byte count in buffer
         */
        CircularBuffer  put( uint8_t abyte );

        /**
         * @brief   incoming CircularBuffer with added abyte
         *
         * @param   byte  byte to put in buffer
         *
         * @return  byte count in buffer
         */
        CircularBuffer  append( uint8_t abyte );

        /**
         * @brief   incoming CircularBuffer with added abyte x repeats
         *
         * @param   repeats byte repeats
         *          byte    byte to append
         *
         * @return  byte count in array
         */
        CircularBuffer  append( int repeats, uint8_t abyte );

        /**
         * @brief   returns mid
         *
         * @param   uint16_t index
         *          int size
         *
         * @return  CircularBuffer
         */
        CircularBuffer   mid( uint16_t index, int size ) const;

        /**
         * @brief   Removes n bytes from the end of the byte array.
         *          If n is greater than size(), the result is an empty byte array.
         *
         * @param   n   bytes to remove rom the end
         *
         * @return  CircularBuffer
         */
        CircularBuffer   chop( int n );

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
        //<! head
        uint16_t _head;
        //<! tail
        uint16_t _tail;

        inline void add( uint8_t item ) {
            data()[_head] = item;
            if ( _count == _size ) {
                _tail = ( _tail + 1 ) % _size;  //Advance tail if buffer is full
            } else {
                ++_count;
            }
            _head = ( _head + 1 ) % _size;      //Move head to next position
        }
};

#endif // _CircularBuffer_H_
