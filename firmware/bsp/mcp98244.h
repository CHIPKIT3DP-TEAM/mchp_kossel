////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _MCP98244_H_
#define _MCP98244_H_
////////////////////////////////////////////////////////////////////////////////
#include "system.h"
#include "i2c.h"
////////////////////////////////////////////////////////////////////////////////

typedef union
{
    struct
    {
        UINT8 eventMode     : 1;
        UINT8 eventPolrity  : 1;
        UINT8 eventSelect   : 1;
        UINT8 eventEnable   : 1;
        UINT8 resv0         : 4;
        UINT8 shutdown      : 1;
        UINT8 hysteresis    : 2;
        UINT8 resv1         : 5;
        
        UINT8 resolution;
        
        I2C_HANDLE  i2c;
        UINT8       address;
    };
    UINT8       configL;
    UINT8       configH;
}
MCP98244_TEMP, *MCP98244_TEMP_HANDLE;

typedef union
{
    I2C_HANDLE  i2c;
    UINT8       address;
}
MCP98244_EE, *MCP98244_EE_HANDLE;

////////////////////////////////////////////////////////////////////////////////

#define MCP98244_I2C_BASE_ADDRESS_TEMP       0b00110000
#define MCP98244_I2C_BASE_ADDRESS_EE         0b10100000

#define MCP98244_REG_CAPABILITY         0b0000
#define MCP98244_REG_CONFIG             0b0001
#define MCP98244_REG_LIMIT_UPPER        0b0010
#define MCP98244_REG_LIMIT_LOWER        0b0011
#define MCP98244_REG_CRITICAL           0b0100
#define MCP98244_REG_TEMPERATURE        0b0101
#define MCP98244_REG_MANUFACTURER_ID    0b0110
#define MCP98244_REG_DEVICE_ID          0b0111
#define MCP98244_REG_TSE2004AV          0b1000
#define MCP98244_REG_RESOLUTION         0b1001

#define MCP98244_EVENT_COMPARATOR       0
#define MCP98244_EVENT_INTERRUPT        1
#define MCP98244_EVENT_LIMITS           0
#define MCP98244_EVENT_CRITICAL         1
#define MCP98244_HYSTERESIS_0_0         0b00
#define MCP98244_HYSTERESIS_1_5         0b01
#define MCP98244_HYSTERESIS_3_0         0b10
#define MCP98244_HYSTERESIS_6_0         0b11

#define MCP98244_RESOLUTION_0_5         0b00
#define MCP98244_RESOLUTION_0_25        0b01
#define MCP98244_RESOLUTION_0_125       0b10
#define MCP98244_RESOLUTION_0_0625      0b11

#define MCP98244_MANUFACTURER_ID        0x0054

#define MCP98244_TEMPERATURE_MIN        10
#define MCP98244_TEMPERATURE_MAX        80
#define MCP98244_TEMPERATURE_ERROR      -273

////////////////////////////////////////////////////////////////////////////////

BOOL MCP98244_TEMP_Initialize ( MCP98244_TEMP_HANDLE mcp98244temp );
BOOL MCP98244_EE_Initialize ( MCP98244_EE_HANDLE mcp98244ee );
FLOAT MCP98244_TEMP_Read ( MCP98244_TEMP_HANDLE mcp9800 );

////////////////////////////////////////////////////////////////////////////////
#endif
