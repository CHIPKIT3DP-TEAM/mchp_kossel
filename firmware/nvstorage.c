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
#define _NVSTORAGE_C_
#include "nvstorage.h"
////////////////////////////////////////////////////////////////////////////////

MCP98244_EE seeprom_ =
{
    .i2c = MAIN_I2C,
    .address = MCP98244_I2C_EE_BASE_ADDRESS
};
MCP98244_EE_HANDLE seeprom = &seeprom_;

////////////////////////////////////////////////////////////////////////////////

BOOL NVS_Initialize ()
{
    if ( MCP98244_EE_Initialize ( seeprom ) != TRUE )
        return ( FALSE );
    else
        return ( TRUE );
}

////////////////////////////////////////////////////////////////////////////////
