////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
#define _MCP98244_C_
#include "mcp98244.h"
////////////////////////////////////////////////////////////////////////////////

BOOL MCP98244_Initialize ( MCP98244_HANDLE mcp98244 )
{
    FLOAT temp;
    
    if ( I2C_Start ( mcp98244->i2c, mcp98244->tempAddress + I2C_WRITE ))
    if ( I2C_WriteByte ( mcp98244->i2c, MCP98244_REG_CONFIG ))
    if ( I2C_WriteByte ( mcp98244->i2c, mcp98244->configH ))
    if ( I2C_WriteByte ( mcp98244->i2c, mcp98244->configL ))
    if ( I2C_Restart ( mcp98244->i2c, mcp98244->tempAddress + I2C_WRITE ))
    if ( I2C_WriteByte ( mcp98244->i2c, MCP98244_REG_RESOLUTION ))
    if ( I2C_WriteByte ( mcp98244->i2c, 0 ))
    if ( I2C_WriteByte ( mcp98244->i2c, mcp98244->resolution ))
    if ( I2C_Restart ( mcp98244->i2c, mcp98244->tempAddress + I2C_WRITE ))
    if ( I2C_WriteByte ( mcp98244->i2c, MCP98244_REG_TEMPERATURE ))
    {
        if ( I2C_Stop ( mcp98244->i2c ))
        {
            temp = MCP98244_ReadTemperature ( mcp98244 );
            if ( temp > ( MCP98244_TEMPERATURE_MIN ) && temp < ( MCP98244_TEMPERATURE_MAX ))
                return ( TRUE );
        }
        
        return ( FALSE );
    }
    
    I2C_Stop ( mcp98244->i2c );
    return ( FALSE );
}

////////////////////////////////////////////////////////////////////////////////

FLOAT MCP98244_ReadTemperature ( MCP98244_HANDLE mcp98244 )
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
    
    if ( I2C_Start ( mcp98244->i2c, mcp98244->tempAddress + I2C_READ ))
    if ( I2C_ReadByte ( mcp98244->i2c, &temp.byteH ))
    if ( I2C_ReadByte ( mcp98244->i2c, &temp.byteL ))
    {
        temp.usign &= 0b0001111111111111;
        if ( temp.usign & 0b000100000000000 )
        {
            temp.usign &= 0b0000111111111111;
            temp.sign = -temp.sign;
        }
    }
    
    I2C_Stop ( mcp98244->i2c );
    
    res = temp.sign;
    res /= 0x10;
    return ( res );
}

////////////////////////////////////////////////////////////////////////////////

BOOL MCP98244_CheckEECRC ( MCP98244_HANDLE mcp98244 )
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
    
    if ( I2C_Start ( mcp98244->i2c, mcp98244->tempAddress + I2C_READ ))
    if ( I2C_ReadByte ( mcp98244->i2c, &temp.byteH ))
    if ( I2C_ReadByte ( mcp98244->i2c, &temp.byteL ))
    {
        temp.usign &= 0b0001111111111111;
        if ( temp.usign & 0b000100000000000 )
        {
            temp.usign &= 0b0000111111111111;
            temp.sign = -temp.sign;
        }
    }
    
    I2C_Stop ( mcp98244->i2c );
    
    res = temp.sign;
    res /= 0x10;
    return ( res );
}

////////////////////////////////////////////////////////////////////////////////
