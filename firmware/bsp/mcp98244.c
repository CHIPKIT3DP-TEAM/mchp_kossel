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
#define _MCP98244_C_
#include "mcp98244.h"
////////////////////////////////////////////////////////////////////////////////

BOOL MCP98244_TEMP_Initialize ( MCP98244_TEMP_HANDLE mcp98244temp )
{
    FLOAT temp;
    
    if ( I2C_Start ( mcp98244temp->i2c, mcp98244temp->address + I2C_WRITE ))
    if ( I2C_WriteByte ( mcp98244temp->i2c, MCP98244_REG_CONFIG ))
    if ( I2C_WriteByte ( mcp98244temp->i2c, mcp98244temp->configH ))
    if ( I2C_WriteByte ( mcp98244temp->i2c, mcp98244temp->configL ))
    if ( I2C_Restart ( mcp98244temp->i2c, mcp98244temp->address + I2C_WRITE ))
    if ( I2C_WriteByte ( mcp98244temp->i2c, MCP98244_REG_RESOLUTION ))
    if ( I2C_WriteByte ( mcp98244temp->i2c, 0 ))
    if ( I2C_WriteByte ( mcp98244temp->i2c, mcp98244temp->resolution ))
    if ( I2C_Restart ( mcp98244temp->i2c, mcp98244temp->address + I2C_WRITE ))
    if ( I2C_WriteByte ( mcp98244temp->i2c, MCP98244_REG_TEMPERATURE ))
    {
        if ( I2C_Stop ( mcp98244temp->i2c ))
        {
            temp = MCP98244_TEMP_Read ( mcp98244temp );
            if ( temp > ( MCP98244_TEMPERATURE_MIN ) && temp < ( MCP98244_TEMPERATURE_MAX ))
                return ( TRUE );
        }
        
        return ( FALSE );
    }
    
    I2C_Stop ( mcp98244temp->i2c );
    return ( FALSE );
}

////////////////////////////////////////////////////////////////////////////////

FLOAT MCP98244_TEMP_Read ( MCP98244_TEMP_HANDLE mcp98244temp )
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
    temp = { MCP98244_TEMPERATURE_ERROR };
    FLOAT res;
    
    if ( I2C_Start ( mcp98244temp->i2c, mcp98244temp->address + I2C_READ ))
    if ( I2C_ReadByte ( mcp98244temp->i2c, &temp.byteH ))
    if ( I2C_ReadByte ( mcp98244temp->i2c, &temp.byteL ))
    {
        temp.usign &= 0b0001111111111111;
        if ( temp.usign & 0b000100000000000 )
        {
            temp.usign &= 0b0000111111111111;
            temp.sign = -temp.sign;
        }
    }
    
    I2C_Stop ( mcp98244temp->i2c );
    
    res = temp.sign;
    res /= 0x10;
    return ( res );
}

////////////////////////////////////////////////////////////////////////////////

UINT32 MCP98244_EE_Initialize ( MCP98244_EE_HANDLE mcp98244ee )
{
    if ( I2C_Start ( mcp98244ee->i2c, MCP98244_I2C_EE_SELECT_PAGE0 + I2C_WRITE ))
    if ( I2C_WriteByte ( mcp98244ee->i2c, 0 ))
    if ( I2C_Stop ( mcp98244ee->i2c ))
        return ( MCP98244_CAPACITY );
    
    I2C_Stop ( mcp98244ee->i2c );
    return ( 0 );
}

////////////////////////////////////////////////////////////////////////////////

BOOL MCP98244_EE_Read ( MCP98244_EE_HANDLE mcp98244ee, UINT8 addr, VOID *data, UINT16 size )
{
    UINT8 cmd = MCP98244_I2C_EE_SELECT_PAGE0;
    
    if ( addr > 0x100 )
    {
        cmd = MCP98244_I2C_EE_SELECT_PAGE1;
        addr -= 0x100;
    }
    if ( I2C_Start ( mcp98244ee->i2c, cmd + I2C_WRITE ))
    if ( I2C_WriteByte ( mcp98244ee->i2c, addr ))
    if ( I2C_Restart ( mcp98244ee->i2c, mcp98244ee->address + I2C_READ ))
    if ( I2C_ReadData ( mcp98244ee->i2c, data, size ))
    if ( I2C_Stop ( mcp98244ee->i2c ))
        return ( TRUE );
    
    I2C_Stop ( mcp98244ee->i2c );
    return ( FALSE );
}

////////////////////////////////////////////////////////////////////////////////

BOOL MCP98244_EE_Write ( MCP98244_EE_HANDLE mcp98244ee, UINT8 addr, const VOID *data, UINT16 size )
{
    return ( TRUE );
}

////////////////////////////////////////////////////////////////////////////////
