////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
#define _MCP9800_C_
#include "mcp9800.h"
////////////////////////////////////////////////////////////////////////////////

BOOL MCP9800_Initialize ( MCP9800_HANDLE mcp9800 )
{
    volatile FLOAT temp;
    
    if ( I2C_Start ( mcp9800->i2c, mcp9800->address + I2C_WRITE ))
    if ( I2C_WriteByte ( mcp9800->i2c, MCP9800_REG_CONFIG ))
    if ( I2C_WriteByte ( mcp9800->i2c, mcp9800->config ))
    if ( I2C_Stop ( mcp9800->i2c ))
    if ( I2C_Start ( mcp9800->i2c, mcp9800->address + I2C_WRITE ))
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
            UINT8 bytel;
            UINT8 byteh;
        };
    }
    temp = { MCP9800_TEMPERATURE_ERROR };
    FLOAT res;
    
    if ( I2C_Restart ( mcp9800->i2c, mcp9800->address + I2C_READ ))
    if ( I2C_ReadByte ( mcp9800->i2c, &temp.byteh ))
    if ( I2C_ReadByte ( mcp9800->i2c, &temp.bytel ))
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
