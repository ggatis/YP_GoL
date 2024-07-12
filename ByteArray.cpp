/**
 * @file    ByteArray.cpp
 *
 * @brief   Implementation of class ByteArray
 *
 * @note    This example code is free software: you can redistribute it and/or modify it.
 *
 *          This program is provided by EDI on an "AS IS" basis without
 *          any warranties in the hope that it will be useful.
 * 
 * Gatis Gaigals @ EDI, 2024
 */

#include <cstddef>
#include <cstring>
#include <stdio.h>
#include <algorithm>    //std::min
#include "ByteArray.h"


/**
  * @brief  class constructor for empty instance
  *
  * @param  -
 */
ByteArray::ByteArray( void ) :
    _size( 0 ), _count( 0 ), _data( (uint8_t*)nullptr ) {
}


/**
  * @brief  class constructor, not initialised buffer
  *
  * @param  buffersize  buffer size
 */
ByteArray::ByteArray( uint16_t buffersize ) :
    _size( buffersize ), _count( 0 ), _data( new uint8_t[(size_t)buffersize] ) {
}


/**
  * @brief  class constructor, size, pointe to buffer
  *
  * @param  size  buffer size, it all contains data
  *         dataptr  pointer to buffer
 */
ByteArray::ByteArray( uint16_t size, uint8_t* dataptr ) :
    _size( size ), _count( size ), _data( dataptr ) {
}


/**
  * @brief  class constructor, all parameters
  *
  * @param  size  buffer size, it all contains data
  *         filled  useful data bytes count
  *         dataptr  pointer to buffer
 */
ByteArray::ByteArray( uint16_t size,  uint16_t filled, uint8_t* dataptr ) :
    _size( size ), _count( filled ), _data( dataptr ) {
}


/**
  * @brief  class constructor, initialised repeating a char
  *
  * @param  repeats   character repeat count
  *         c         character
 */
ByteArray::ByteArray( uint16_t repeats, char c ) :
    _size( repeats ), _count( repeats ), _data( new uint8_t[(size_t)repeats] ) {
    //std::memset( _data, c, (size_t)repeats);  //?
    std::memset( const_cast<uint8_t*>( _data ), c, (size_t)repeats );
}


/**
  * @brief  class constructor from string
  *
  * @param  aString
 */
ByteArray::ByteArray( const std::string& aString ) :
    _size( aString.size() ), _count( aString.size() ), _data( new uint8_t[aString.size()] ) {
    std::memcpy( _data, aString.data(), aString.size() );
}


/**
  * @brief  class constructor from rvalue string
  *
  * @param  aString
 */
ByteArray::ByteArray( std::string&& aString ) :
    _size( aString.size() ), _count( aString.size() ), _data( new uint8_t[aString.size()] ) {
    std::memcpy( _data, aString.data(), aString.size() );
}


/**
  * @brief  class copy constructor, initialised using const ByteArray,
  *         _size is reduced to _count
  *
  * @param  aByteArray   input ByteArray
 */
ByteArray::ByteArray( const ByteArray& other ) :
    _size( other._count ),
    _count( other._count ),
    _data( new uint8_t[other._count] ) {
    std::memcpy( _data, other._data, _count );
}


/**
  * @brief  move constructor
  *
  * @param  ByteArray& aByteArray
  */
ByteArray::ByteArray( ByteArray&& other ) noexcept :
    _size( other._size ),
    _count( other._count ),
    _data( other._data ) {
    //overtake aByteArray._data, overtake aByteArray._size
    //invalidate
    //aByteArray._data  = nullptr;    //*const
    const_cast<uint8_t*&>( other._data ) = nullptr; //const_cast
    other._size  = 0;
    other._count = 0;
}


/**
  * @brief  class destructor
  *
  * @param  -
 */
ByteArray::~ByteArray( void ) {
    delete[] _data;
}


/**
  * @brief  copy assignment operator
  *         _size is not reduced to _count
  *
  * @param  const ByteArray& aByteArray
  */
ByteArray&
ByteArray::operator = ( const ByteArray& other ) {
    if ( this != &other ) {
        _count = std::min( _size, other._count );
        std::memcpy( _data, other._data, _count );
    }
    return *this;
}


/**
  * @brief  move assignment operator
  *
  * @param  ByteArray& aByteArray
  */
ByteArray&
ByteArray::operator = ( ByteArray&& other ) noexcept {
    if ( this != &other ) {
        //_size can not be changed since memory is already taken
        _count = std::min( _size, other._count );
        //the object is already made. _data is  *const
        //delete[] _data;
        //_data  = aByteArray._data;
        std::memcpy( _data, other._data, _count );
        //aByteArray._data  = nullptr;  //not alloved for *const
        //at least correct the properties aka invalidate
        other._size  = 0;
        other._count = 0;
    }
    return *this;
}


/**
 * @brief   returns data buffer
 *
 * @param   -
 *
 * @return  ByteArray data buffer
 */
uint8_t*
ByteArray::data( void ) const {
    return _data;
}

/**
 * @brief   returns size of data in array
 *
 * @param   -
 *
 * @return  ByteArray data size
 */
uint16_t
ByteArray::count( void ) const {
    return _count;
}

/**
 * @brief   returns size of array
 *
 * @param   -
 *
 * @return  ByteArray array size
 */
uint16_t
ByteArray::size( void ) const {
    return _size;
}

/**
 * @brief   clears the contents of the byte array and makes it null
 *
 * @param   -
 *
 * @return  -
 */
void
ByteArray::clear( void ) {
    _count = 0;
}

/**
 * @brief   extends the content to the _size
 *
 * @param   -
 *
 * @return  -
 */
void
ByteArray::extendo( void ) {
    if ( _data ) {
        _count = _size;
    }
    printf("extendo dataptr, count, size: %08X, %d, %d\r\n",
        (uint32_t)_data, _count, _size );
}

/**
 * @brief   updates count of the data size in arrray in the case it is manipulated from outside
 *
 * @param   -
 *
 * @return  correctly updated count of the data size in arrray
 */
uint16_t
ByteArray::update_count( uint16_t newcount ) {
    if ( _data )
        _count = ( newcount > _size ) ? _size : newcount;
    return _count;
}

/**
 * @brief   return byte at index
 *
 * @param   index  array index
 *
 * @return  byte at position index
 */
uint8_t
ByteArray::at( uint16_t index ) const {
    //if ( index < _count )
    if ( index < _count )
        return _data[index];
    return 0;
}

/**
 * @brief   return byte at index
 *
 * @param   index  array index
 *
 * @return  byte at position index
 */
uint8_t
ByteArray::at( int index ) const {
    //if ( index < _count )
    if ( index < (int)_count )
        return _data[index];
    return 0;
}

/**
 * @brief   returns ByteArray
 *
 * @param   byte  byte to append
 *
 * @return  ByteArray
 */
ByteArray
ByteArray::append( uint8_t abyte ) {
    if ( _count < _size ) {
        _data[_count++] = abyte;
    }
    return *this;
}


/**
 * @brief   returns ByteArray
 *
 * @param   repeats byte repeats
 *          byte    byte to append
 *
 * @return  ByteArray
 */
ByteArray
ByteArray::append( int repeats, uint8_t abyte ) {
    int i = repeats;
    while ( ( 0 < i-- ) && ( _count < _size ) ) {
        _data[_count++] = abyte;
    }
    return *this;
}


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
uint8_t 
ByteArray::peek( int x, int y, int width, int height ) const {
    if ( ( 0 <= y ) && ( y < height ) ) {
        if ( ( 0 <= x ) && ( x < width ) ) {
            uint16_t offset = y * width + x;
            if ( offset < _count ) {
                return _data[offset];
            }
        }
    }
    printf("-");
    return 0;
}


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
uint8_t
ByteArray::poke( uint8_t aByte, int x, int y, int width, int height ) {    
    if ( ( 0 <= y ) && ( y < height ) ) {
        if ( ( 0 <= x ) && ( x < width ) ) {
            uint16_t offset = y * width + x;
            if ( offset < _count ) {
                _data[offset] = aByte;
                return 0;
            } else {
                printf("poke ptr, offset, count, size: %08X, %d, %d, %d\r\n",
                    (uint32_t)_data, offset, _count, _size );
                return 255;
            }
        }
    }
    printf("+");
    printf("x, y, w, h: %d, %d, %d, %d\r\n", x, y, width, height );
    return 255;
}


/**
 * @brief   return ByteArray converted form HEX
 *
 * @param   hexEncoded  HEX encoded array
 *
 * @return  ByteArray converted form HEX
 */
ByteArray
ByteArray::fromHex( const ByteArray &hexEncoded ) const {

    ByteArray tfromHex( ( hexEncoded._count >> 1 ) + ( hexEncoded._count & 1 ) );

    for ( uint16_t i = 0; i < tfromHex._count; i++ ) {
        uint16_t j = 0;
        uint8_t abyte = 0;

        uint8_t hexb = hexEncoded.at( j++ );
        if ( ( '0' <= hexb ) && ( hexb <= '9' ) ) {
            abyte += hexb - '0';
        } else if ( ( 'a' <= hexb ) && ( hexb <= 'f' ) ) {
            abyte += hexb - 'a' + 10;
        } else if ( ( 'A' <= hexb ) && ( hexb <= 'F' ) ) {
            abyte += hexb - 'a' + 10;
        }
        abyte = abyte << 4;

        hexb = hexEncoded.at( j++ );
        if ( ( '0' <= hexb ) && ( hexb <= '9' ) ) {
            abyte += hexb - '0';
        } else if ( ( 'a' <= hexb ) && ( hexb <= 'f' ) ) {
            abyte += hexb - 'a' + 10;
        } else if ( ( 'A' <= hexb ) && ( hexb <= 'F' ) ) {
            abyte += hexb - 'a' + 10;
        }

        tfromHex.append( abyte );
    }
    return tfromHex;
}


///**
// * @brief   return ByteArray converted form string
// *
// * @param   aString     const std::string&
// *
// * @return  ByteArray
// */
/*
ByteArray
ByteArray::fromString( const std::string &aString ) {

    ByteArray temp( aString.size() );

    for ( char c : str ) {
        temp.append( static_cast<uint8_t>( c ) );
    }
    return temp;

}
*/

/**
 * @brief   returns middle from ByteArray
 *
 * @param   index   first byte (0 based)
 *          size    size of returnned array, -1 means rest starting from index
 *
 * @return  ByteArray
 */
ByteArray
ByteArray::mid( uint16_t index, int size ) const {
    //optimizeet!
    if ( size > 0 ) {

        ByteArray temp( size );
        for ( uint16_t i = index; i < ( index + size ); i++ ) {
            if ( i < _count ) {
                temp.append( at( i ) );
            } else {
                break;
            }
        }
        return temp;

    } else if ( size < 0 ) {

        int aSize = _count - index;
        if ( aSize > 0 ) {
            ByteArray temp( aSize );
            for ( uint16_t i = index; i < ( index + aSize ); i++ ) {
                temp.append( at( i ) );
            }
            return temp;
        }
    }

    return ByteArray();

}


/**
 * @brief   Removes n bytes from the end of the byte array.
 *          If n is greater than size(), the result is an empty byte array.
 *
 * @param   n   bytes to remove rom the end
 *
 * @return  ByteArray
 */
ByteArray
ByteArray::chop( int n ) {
    if ( n > _count ) {
        _count = 0;
    } else if ( n > 0 ) {
        _count -= n;
    }
    return *this;
}


/**
 * @brief   prints the buffer as chars
 *
 * @param   -
 *
 * @return  -
 */
void
ByteArray::print( void ) const {
    for ( uint16_t i = 0; i < count(); i++ ) {
        printf( "%c", at( i ) );
    }
}


/**
 * @brief   prints the buffer as chars in 2D
 *
 * @param   -
 *
 * @return  -
 */
void
ByteArray::print2D( int width, int height ) const {
    for ( int y = 0; y < height; ++y ) {
        for ( int x = 0; x < width; ++x ) {
            int offset = y * width + x;
            if ( offset < _count ) printf("%c", _data[offset] );
        }
        printf("\r\n");
    }
}


/**
 * @brief   prints the buffer as numbers in 2D
 *
 * @param   -
 *
 * @return  -
 */
void
ByteArray::print2Dd( int width, int height ) const {
    for ( int y = 0; y < height; ++y ) {
        for ( int x = 0; x < width; ++x ) {
            int offset = y * width + x;
            if ( offset < _count ) printf("%4d", _data[offset] );
        }
        printf("\r\n");
    }
}
