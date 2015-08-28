////////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2015 Microchip Technology Inc. (www.microchip.com)
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//      http://www.apache.org/licenses/LICENSE-2.0
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
////////////////////////////////////////////////////////////////////////////////
#define _PRINT_C_
#include "print.h"
////////////////////////////////////////////////////////////////////////////////

UINT8 printBuff[64];

////////////////////////////////////////////////////////////////////////////////

VOID Print ( CHAR8 *str )
{
    while ( UART_Transmit ( UART_PC, (const UINT8*)str, strlen ( str )) != TRUE );
}

////////////////////////////////////////////////////////////////////////////////

VOID PrintFLOAT ( FLOAT number, UINT8 fract )
{
    CHAR str[20];
    CHAR *ptr = str;
    UINT8 i, digit;
    UINT32 base, integer;
    FLOAT rounding;

    if ( number < 0.0 )
    {
        *ptr++ = '-';
        number = - number;
    }

    rounding = 0.5;
    for ( i = 0; i < fract; i ++ )
    {
        rounding /= 10.0;
    }

    number += rounding;

    integer = (UINT32)number;
    number -= (FLOAT)integer;

    base = 1;
    while ( base * 10 < integer )
    {
        base *= 10;
    }

    while ( base > 0 )
    {
        digit = integer / base;
        *ptr++ = digit + '0';
        integer -= digit * base;
        base /= 10;
    }

    if ( fract != 0 )
    {
        *ptr++ = '.';

        for ( i = 0; i < fract; i ++ )
        {
            number *= 10;
            digit = (UINT8)number;
            *ptr++ = digit + '0';
            number -= digit;
        }
    }

    UART_Transmit ( UART_PC, (UINT8*)str, ptr - str );
}

////////////////////////////////////////////////////////////////////////////////
