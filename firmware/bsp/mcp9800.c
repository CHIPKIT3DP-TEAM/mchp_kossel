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
#define _MCP9800_C_
#include "mcp9800.h"
////////////////////////////////////////////////////////////////////////////////

BOOL MCP9800_Initialize ( MCP9800_HANDLE mcp9800 )
{
    FLOAT temp;
    UINT8 config;
    
    config = mcp9800->config | (( mcp9800->faultQueue / 2 ) << 3 );
    
    if ( I2C_Start ( mcp9800->i2c, mcp9800->address + I2C_WRITE ))
    if ( I2C_WriteByte ( mcp9800->i2c, MCP9800_REG_CONFIG ))
    if ( I2C_WriteByte ( mcp9800->i2c, config ))
    if ( I2C_Restart ( mcp9800->i2c, mcp9800->address + I2C_WRITE ))
    if ( I2C_WriteByte ( mcp9800->i2c, MCP9800_REG_TEMPERATURE ))
    {
        if ( I2C_Stop ( mcp9800->i2c ))
        {
            temp = MCP9800_ReadTemperature ( mcp9800 );
            if ( temp > ( MCP9800_TEMPERATURE_MIN ) && temp < ( MCP9800_TEMPERATURE_MAX ))
                return ( TRUE );
        }
        
        return ( FALSE );
    }
    
    I2C_Stop ( mcp9800->i2c );
    return ( FALSE );
}

////////////////////////////////////////////////////////////////////////////////

FLOAT MCP9800_ReadTemperature ( MCP9800_HANDLE mcp9800 )
{
    union
    {
        INT16 sign;
        UINT16 usign;
        struct
        {
            UINT8 byteL;
            UINT8 byteH;
        };
    }
    temp = { MCP9800_TEMPERATURE_ERROR };
    FLOAT res;
    
    if ( I2C_Start ( mcp9800->i2c, mcp9800->address + I2C_READ ))
    if ( I2C_ReadByte ( mcp9800->i2c, &temp.byteH ))
    if ( I2C_ReadByte ( mcp9800->i2c, &temp.byteL ))
    {
        if ( temp.usign & 0b100000000000000 )
        {
            temp.usign &= 0b0111111111111111;
            temp.sign = -temp.sign;
        }
    }
    
    I2C_Stop ( mcp9800->i2c );
    
    res = temp.sign;
    res /= 0x100;
    return ( res );
}

////////////////////////////////////////////////////////////////////////////////
