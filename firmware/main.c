/*
    This file is part of Repetier-Firmware.

    Repetier-Firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Repetier-Firmware is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Repetier-Firmware.  If not, see <http://www.gnu.org/licenses/>.

    This firmware is a nearly complete rewrite of the sprinter firmware
    by kliment (https://github.com/kliment/Sprinter)
    which based on Tonokip RepRap firmware rewrite based off of Hydra-mmm firmware.

    Main author: repetier

*/
/**
\mainpage Repetier-Firmware for Arduino based RepRaps
<CENTER>Copyright &copy; 2011-2013 by repetier
</CENTER>

\section Intro Introduction


\section GCodes Implemented GCodes

 look here for descriptions of gcodes: http://linuxcnc.org/handbook/gcode/g-code.html
 and http://objects.reprap.org/wiki/Mendel_User_Manual:_RepRapGCodes

*/

#define _MAIN_C_
#include "main.h"

//HEATER _heater = { 4450, 25, 100000, 4700, 20000, 30000, 30000, 65535, SYS_AD_THERM0, SYS_PWM_HOTEND0 };
//HEATER *heater = &_heater;

//UINT8 uartRxBuff[UART_FIFO_SIZE], uartTxBuff[UART_FIFO_SIZE];
//UART_HANDLE uart_obj, *uart = &uart_obj;

////////////////////////////////////////////////////////////////////////////////

INT main ( VOID )
{
    UINT16 timemark100ms, timemark1s;
    UINT8 stage = 0;

    MAIN_Initialize ();

//    HEATER_SetTargetTemperature ( heater, 180 );
    timemark100ms = TIME_Get1ms ();
    timemark1s = TIME_Get1ms ();

    while ( TRUE )
    {
//        CDCTxService ();

        if ( TIME_Elapsed1ms ( timemark100ms ))
        {
            timemark100ms += 100;

//            HEATER_Task ( heater );
//
//            FloatToUART ( uart, heater->targetTemp, 2 );
//            UART_WriteData ( uart, "    ", 4 );
//            FloatToUART ( uart, heater->currentTemp, 2 );
//            UART_WriteData ( uart, "    ", 4 );
//            FloatToUART ( uart, heater->targetTemp - heater->currentTemp, 2 );
//            UART_WriteData ( uart, "    ", 4 );
//            FloatToUART ( uart, heater->integralDelta, 2 );
//            UART_WriteData ( uart, "    ", 4 );
//            FloatToUART ( uart, heater->pidDrive, 2 );
//            UART_WriteData ( uart, "    ", 4 );
//            FloatToUART ( uart, heater->pDrive, 2 );
//            UART_WriteData ( uart, "    ", 4 );
//            FloatToUART ( uart, heater->iDrive, 2 );
//            UART_WriteData ( uart, "    ", 4 );
//            FloatToUART ( uart, heater->dDrive, 2 );
//            UART_WriteData ( uart, "\r\n", 2 );

//            switch ( stage )
//            {
//                case 0:
//                    if ( DRIVE_Move (  0, 100, 100, 10 ) == TRUE )
//                    {
//                        stage ++;
//                    }
//                    break;
//                case 1:
//                    if ( DRIVE_Move ( 100, 0, 100, 10 ) == TRUE )
//                    {
//                        stage ++;
//                    }
//                    break;
//                case 2:
//                    if ( DRIVE_Move ( 0, -100, 100, 10 ) == TRUE )
//                    {
//                        stage ++;
//                    }
//                    break;
//                case 3:
//                    if ( DRIVE_Move ( -100, 0, 100, 10 ) == TRUE )
//                    {
//                        stage = 0;
//                    }
//                    break;
//            }
        }
        else if ( TIME_Elapsed1ms ( timemark1s ))
        {
            timemark1s += 1000;
            
            
        }

        SYSTEM_Idle ();
    }
}

////////////////////////////////////////////////////////////////////////////////

VOID MAIN_Initialize ( VOID )
{
    SYSTEM_Initialize ();
    TIME_Initialize ();

    DRIVE_Initialize ();
//    UART_Initialize ( uart, UART_1, uartRxBuff, sizeof ( uartRxBuff ), uartTxBuff, sizeof ( uartTxBuff ));
//    UART_Configure ( uart, 115200, UART_BRGH );
//    HEATER_Initialize ( heater );
}

////////////////////////////////////////////////////////////////////////////////

VOID HEATER_EventHandler ( UINT8 event, UINT16 value )
{

}

////////////////////////////////////////////////////////////////////////////////

//VOID FloatToUART ( UART *uart, FLOAT number, UINT8 fract )
//{
//    CHAR str[20];
//    CHAR *ptr = str;
//    UINT8 i, digit;
//    UINT32 base, integer;
//    FLOAT rounding;
//
//    if ( number < 0.0 )
//    {
//        *ptr++ = '-';
//        number = - number;
//    }
//
//    rounding = 0.5;
//    for ( i = 0; i < fract; i ++ )
//    {
//        rounding /= 10.0;
//    }
//
//    number += rounding;
//
//    integer = (UINT32)number;
//    number -= (FLOAT)integer;
//
//    base = 1;
//    while ( base * 10 < integer )
//    {
//        base *= 10;
//    }
//
//    while ( base > 0 )
//    {
//        digit = integer / base;
//        *ptr++ = digit + '0';
//        integer -= digit * base;
//        base /= 10;
//    }
//
//    if ( fract != 0 )
//    {
//        *ptr++ = '.';
//
//        for ( i = 0; i < fract; i ++ )
//        {
//            number *= 10;
//            digit = (UINT8)number;
//            *ptr++ = digit + '0';
//            number -= digit;
//        }
//    }
//
//    UART_WriteData ( uart, (UINT8*)str, ptr - str );
//}

////////////////////////////////////////////////////////////////////////////////

VOID SYSTEM_T1InterruptHandler ( VOID )
{
    TIME_Update ( 1 );
}

////////////////////////////////////////////////////////////////////////////////