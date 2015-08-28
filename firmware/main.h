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
#ifndef _MAIN_H_
#define _MAIN_H_
////////////////////////////////////////////////////////////////////////////////
#include "system.h"
#include "time.h"
#include "bus.h"
#include "print.h"
#include "nvstorage.h"
#include "sensors.h"
#include "drive/drive.h"
////////////////////////////////////////////////////////////////////////////////

typedef struct PACKED
{
    UINT16 id;
    UINT16 revision;
    
    UINT8 settings[0x100];
}
PERSISTENT_DATA;

typedef struct PACKED
{
    UINT32 uptime;
    UINT32 runtime;
}
NON_VOLATILE_DATA;

////////////////////////////////////////////////////////////////////////////////
VOID MAIN_Initialize ( VOID );
BOOL UART_PC_EventHandler ( UART_HANDLE uart, UART_EVENT event, const UINT8 * data, const UINT16 size );
BOOL UART_BUS_EventHandler ( UART_HANDLE uart, UART_EVENT event, const UINT8 * data, const UINT16 size );

////////////////////////////////////////////////////////////////////////////////
#endif
