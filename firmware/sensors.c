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
#define _SENSORS_C_
#include "sensors.h"
////////////////////////////////////////////////////////////////////////////////

MCP9800 tempMosfets_ =
{
    .i2c = MAIN_I2C,
    .address = MCP9800_I2C_BASE_ADDRESS,
    .shutdown = FALSE,
    .resolution = MCP9800_RESOLUTION_0_0625
};
MCP9800_HANDLE tempMosfets = &tempMosfets_;

MCP98244_TEMP tempSteppers_ =
{
    .i2c = MAIN_I2C,
    .address = MCP98244_I2C_TEMP_BASE_ADDRESS,
    .shutdown = FALSE,
    .resolution = MCP98244_RESOLUTION_0_0625
};
MCP98244_TEMP_HANDLE tempSteppers = &tempSteppers_;

////////////////////////////////////////////////////////////////////////////////

BOOL SNS_Initialize ( VOID )
{
    if ( MCP9800_Initialize ( tempMosfets ) != TRUE )
        return ( FALSE );
    
    if ( MCP98244_TEMP_Initialize ( tempSteppers ) != TRUE )
        return ( FALSE );
    
    return ( TRUE );
}

////////////////////////////////////////////////////////////////////////////////
