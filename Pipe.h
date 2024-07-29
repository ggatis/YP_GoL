/**
 * @file    Pipe.h
 *
 * @brief   Declaration of class Pipe
 *
 * @note    This example code is free software: you can redistribute it and/or modify it.
 *
 *          This program is provided by EDI on an "AS IS" basis without
 *          any warranties in the hope that it will be useful.
 * 
 * Gatis Gaigals, 2024
 */

#ifndef _PIPE_H_
#define _PIPE_H_

#include "ByteArray.h"

#define EXCEPTIONS_SUPPORTED 0


enum class StatusCode {
    OK,
    PENDING,
    ERROR
};


class Pipe {

public:

    using ProcessorFunc = StatusCode (*)( ByteArray*, ByteArray* );

    Pipe( ByteArray* pInput_data, ByteArray* pOutput_data, ProcessorFunc processor )
        : pInput_data( pInput_data ), pOutput_data( pOutput_data ), processor( processor ) {}

    StatusCode process() {
#if EXCEPTIONS_SUPPORTED
        try {
            //Clear the output buffer before processing
            //pOutput_data->clear();
            //Process the input data and store the result in the output data
            return processor( pInput_data, pOutput_data );
        } catch (...) {
            return StatusCode::ERROR;
        }
#else
        //Clear the output buffer before processing
        //pOutput_data->clear();
        //Process the input data and store the result in the output data
        return processor( pInput_data, pOutput_data );
#endif
    }

    void swapBuffers() {
        std::swap( pInput_data, pOutput_data );
    }

    ByteArray* getInputBuffer( void ) const {
        return pInput_data;
    }

    ByteArray* getOutputBuffer( void ) const {
        return pOutput_data;
    }


protected:

    ByteArray*      pInput_data;
    ByteArray*      pOutput_data;
    ProcessorFunc   processor;

};

#endif // PIPE_H
