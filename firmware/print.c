////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
#define _PRINT_C_
#include "print.h"
////////////////////////////////////////////////////////////////////////////////

UINT8 printBuff[64];

////////////////////////////////////////////////////////////////////////////////

VOID Print ( CHAR *str )
{
    while ( UART_Transmit ( UART_PC, str, strlen ( str )) != TRUE );
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
