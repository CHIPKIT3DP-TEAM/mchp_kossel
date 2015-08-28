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
#ifndef _MCP9800_H_
#define _MCP9800_H_
////////////////////////////////////////////////////////////////////////////////
#include "system.h"
#include "i2c.h"
////////////////////////////////////////////////////////////////////////////////

typedef union
{
    struct
    {
        UINT8 shutdown      : 1;
        UINT8 alert         : 1;
        UINT8 alertLevel    : 1;
        UINT8 resv0         : 2;
        UINT8 resolution    : 2;
        UINT8 resv1         : 1;
        
        UINT8 faultQueue;
        
        I2C_HANDLE  i2c;
        UINT8       address;
    };
    UINT8 config;
}
MCP9800, *MCP9800_HANDLE;

////////////////////////////////////////////////////////////////////////////////

#define MCP9800_I2C_BASE_ADDRESS    0b10010000

#define MCP9800_REG_TEMPERATURE     0b00
#define MCP9800_REG_CONFIG          0b01
#define MCP9800_REG_HYSTERESIS      0b10
#define MCP9800_REG_LIMIT           0b11

#define MCP9800_ALERT_COMPARATOR    0
#define MCP9800_ALERT_INTERRUPT     1
#define MCP9800_RESOLUTION_0_5      0b00
#define MCP9800_RESOLUTION_0_25     0b01
#define MCP9800_RESOLUTION_0_125    0b10
#define MCP9800_RESOLUTION_0_0625   0b11

#define MCP9800_TEMPERATURE_MIN     10
#define MCP9800_TEMPERATURE_MAX     80
#define MCP9800_TEMPERATURE_ERROR   -273

////////////////////////////////////////////////////////////////////////////////

BOOL    MCP9800_Initialize ( MCP9800_HANDLE mcp9800 );
FLOAT   MCP9800_ReadTemperature ( MCP9800_HANDLE mcp9800 );

////////////////////////////////////////////////////////////////////////////////
#endif
