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
#define _MAIN_C_
#include "main.h"
////////////////////////////////////////////////////////////////////////////////

//HEATER _heater = { 4450, 25, 100000, 4700, 20000, 30000, 30000, 65535, SYS_AD_THERM0, SYS_PWM_HOTEND0 };
//HEATER *heater = &_heater;

UINT8 uartRxBuff[64];
PERSISTENT_DATA persistData;
NON_VOLATILE_DATA nvData;

////////////////////////////////////////////////////////////////////////////////

const UART_CONFIG uartCfg =
{
    .baudrate = UART_PC_BAUDRATE,
    .EventHandler = &UART_PC_EventHandler,
    .dataParity = UART_DATA_8_PARITY_NONE,
    .stopBits = 1,
    .flowControl = FALSE
};

const I2C_CONFIG i2cConfig =
{
    .baudrate = 400000,
    .highSpeed = TRUE
};

MCP98244_EE mcp98244 =
{
    .i2c = MAIN_I2C,
    .address = MCP98244_I2C_EE_BASE_ADDRESS
};

NVSTORAGE nvs_ =
{
    .persistSize = sizeof ( PERSISTENT_DATA ),
    .nvSize = sizeof ( NON_VOLATILE_DATA ),
    .mediaSize = 0,
    .mediaHandle = &mcp98244,
    .MediaRead = (NVS_FUNC_READ)&MCP98244_EE_Read,
    .MediaWrite = (NVS_FUNC_WRITE)&MCP98244_EE_Write,
};
NVS_HANDLE nvs = &nvs_;

////////////////////////////////////////////////////////////////////////////////

INT main ( VOID )
{
    UINT32 timemark100ms, timemark1s;
//    UINT8 stage = 0;

    MAIN_Initialize ();

//    HEATER_SetTargetTemperature ( heater, 180 );
    timemark100ms = TIME_Get1ms ();
    timemark1s = TIME_Get1ms ();
    
    UART_Receive ( UART_PC, uartRxBuff, 8 );

    while ( TRUE )
    {
        BUS_Task ();
        
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
            
            Print ( "assa\r\n" );
        }

        SYSTEM_Idle ();
    }
}

////////////////////////////////////////////////////////////////////////////////

VOID MAIN_Initialize ( VOID )
{
    SYSTEM_Initialize ();
    TIME_Initialize ();
    
    TIME_Delay1ms ( 100 );
    
    if ( UART_Initialize ( UART_PC, &uartCfg ) != TRUE )
        SYSTEM_Halt ();
    
    if ( I2C_Initialize ( MAIN_I2C, &i2cConfig ) != TRUE )
        SYSTEM_Halt ();

    if ( SNS_Initialize () != TRUE )
        SYSTEM_Halt ();
    
    nvs->mediaSize = MCP98244_EE_Initialize ( &mcp98244 );
    if ( nvs->mediaSize == 0 )
        SYSTEM_Halt ();
    
    if ( NVS_Initialize ( nvs ) != TRUE )
        SYSTEM_Halt ();

    if ( NVS_ReadPersistent ( &persistData, sizeof ( persistData )) != TRUE )
        SYSTEM_Halt ();
    
    if ( NVS_ReadNonVolatile ( &nvData, sizeof ( nvData )) != TRUE )
        SYSTEM_Halt ();

    BUS_Initialize ();

    DRIVE_Initialize ();
//    HEATER_Initialize ( heater );
    
    SYSTEM_Halt ();
}

////////////////////////////////////////////////////////////////////////////////

VOID HEATER_EventHandler ( UINT8 event, UINT16 value )
{

}

////////////////////////////////////////////////////////////////////////////////

VOID SYSTEM_T1InterruptHandler ( VOID )
{
    TIME_Update ( 1 );
}

////////////////////////////////////////////////////////////////////////////////

BOOL UART_PC_EventHandler ( UART_HANDLE uart, UART_EVENT event, const UINT8 * data, const UINT16 size )
{
    switch ( event )
    {
        case UART_EVENT_RECEIVED:
            UART_Receive ( UART_BUS, uartRxBuff, 8 );
            break;
            
        case UART_EVENT_SENT:
            Nop ();
            break;

        default:
            SYSTEM_Halt ();
            break;
    }
    
    return ( TRUE );
}

////////////////////////////////////////////////////////////////////////////////
