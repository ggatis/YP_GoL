/**
 * @file    Pipes.h
 *
 * @brief   Declaration of Pipe implementations
 *
 * @note    This example code is free software: you can redistribute it and/or modify it.
 *
 *          This program is provided by EDI on an "AS IS" basis without
 *          any warranties in the hope that it will be useful.
 * 
 * Gatis Gaigals, 2024
 */

#ifndef _PIPES_H_
#define _PIPES_H_

#include "Pipeline.h"

//sample 1
StatusCode reverse_processor( ByteArray* in, ByteArray* out );

//sample 2
void GoLinit( ByteArray* in, ByteArray* out );
StatusCode GoL( ByteArray* in, ByteArray* out );

#endif // _PIPES_H_
