/**
 * @file    Processors.h
 *
 * @brief   Declaration of Pipe Processors
 *
 * @note    This example code is free software: you can redistribute it and/or modify it.
 *
 *          This program is provided by EDI on an "AS IS" basis without
 *          any warranties in the hope that it will be useful.
 * 
 * Gatis Gaigals, 2024
 */

#ifndef _PROCESSORS_H_
#define _PROCESSORS_H_

#include "Pipe.h"

StatusCode reverse_processor( ByteArray* in, ByteArray* out );

void GoLinit( ByteArray* in, ByteArray* out );
StatusCode GoL( ByteArray* in, ByteArray* out );

#include <vector>


class Processors {

public:

    Processors( uint16_t buffersize = 128 ) : defaultBufferSize( buffersize ) {
        //Create the first buffer
        ByteArray* initialBuffer = new ByteArray( defaultBufferSize );
        buffers.push_back( initialBuffer );
    }

    ~Processors() {
        //Clean up dynamically allocated ByteArray objects
        for ( auto buffer : buffers ) {
            delete[] buffer->data();
            delete buffer;
        }
        //Clean up dynamically allocated Pipe objects
        for ( auto pipe : pipes ) {
            delete pipe;
        }
    }

    StatusCode AddProcessor( Pipe::ProcessorFunc processor, int outputBufferSize = -1 ) {
        //Check input buffer - if it is reason to continue
        ByteArray* inputBuffer  = buffers.back();
        if ( ( nullptr == inputBuffer ) || ( nullptr == inputBuffer->data() ) ) {
            return StatusCode::ERROR;
        }

        //Create new buffer
        ByteArray* outputBuffer = new ByteArray( ( outputBufferSize < 1 ) ? defaultBufferSize : outputBufferSize );

        if ( ( nullptr == outputBuffer ) || ( nullptr == outputBuffer->data() ) ) {
            return StatusCode::ERROR;
        }

        //Add the output buffer to the buffers list
        buffers.push_back( outputBuffer );

        //Create a new Pipe with these buffers
        Pipe* newPipe           = new Pipe( inputBuffer, outputBuffer, processor );
        if ( nullptr == newPipe ) {
            return StatusCode::ERROR;
        }

        pipes.push_back( newPipe );

        return StatusCode::OK;

    }

    ByteArray* getInputBuffer() const {
        //Return the first buffer, which is the input buffer
        return buffers.front();
    }

    ByteArray* getFrontEnd() const {
        //Return the first buffer, which is the input buffer
        return buffers.front();
    }

    ByteArray* getOutputBuffer() const {
        //Return the last buffer, which is the output buffer
        return buffers.back();
    }

    ByteArray* getBackEnd() const {
        //Return the last buffer, which is the output buffer
        return buffers.back();
    }

    ByteArray* getBuffer( size_t index ) const {
        if ( index < buffers.size() ) {
            return buffers[index];
        }
        return nullptr;
    }

    StatusCode processStep( uint8_t i ) {
        if ( i > 0 && i <= pipes.size() ) {
            faultyPipe = 0;     //Reset the faulty pipe indicator
            StatusCode status = pipes[i-1]->process();
            if ( status != StatusCode::OK ) {
                faultyPipe = i; //Count pipes from 1
            }
            return status;
        }
        faultyPipe = i;         //Count pipes from 1
        return StatusCode::ERROR;
    }

    StatusCode processAll() {
        faultyPipe = 0;         //Reset the faulty pipe indicator
        for ( size_t i = 0; i < pipes.size(); ++i ) {
            StatusCode status = pipes[i]->process();
            if ( status != StatusCode::OK ) {
                faultyPipe = i + 1; //Count pipes from 1
                return status;
            }
        }
        return StatusCode::OK;
    }

    uint8_t getFaultyPipe() const {
        return faultyPipe;
    }

    size_t getBufferCount() const {
        return buffers.size();
    }

    size_t getPipeCount() const {
        return pipes.size();
    }

    //Takes two buffer indices x and y as arguments.
    //Swaps the buffers at positions x and y if both indices are within the bounds of the buffers vector.
    void swapBuffers( uint16_t x, uint16_t y ) {
        if ( x < buffers.size() && y < buffers.size() ) {
            std::swap( buffers[x], buffers[y] );
        }
    }

    //Swaps the first and last buffers in the buffers vector if there are at least two buffers.
    void swapIO() {
        if ( buffers.size() >= 2 ) {
            std::swap( buffers.front(), buffers.back() );
        }
    }


private:

    uint8_t     faultyPipe          = 0;
    uint16_t    defaultBufferSize   = 128;

    std::vector<ByteArray*> buffers;
    std::vector<Pipe*> pipes;

};

#endif // _PROCESSORS_H_
