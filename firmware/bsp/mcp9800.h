////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _MCP9800_H_
#define _MCP9800_H_
////////////////////////////////////////////////////////////////////////////////
#include "system.h"
#include "i2c.h"
////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    I2C_HANDLE  i2c;
    UINT8       address;
    UINT8       config;
}
MCP9800, *MCP9800_HANDLE;

////////////////////////////////////////////////////////////////////////////////

#define MCP9800_I2C_BASE_ADDRESS    0b10010000

#define MCP9800_REG_TEMPERATURE     0b00
#define MCP9800_REG_CONFIG          0b01
#define MCP9800_REG_HYSTERESIS      0b10
#define MCP9800_REG_LIMIT           0b11

#define MCP9800_CONFIG_SHUTDOWN_ENABLE  0b00000001
#define MCP9800_CONFIG_SHUTDOWN_DISABLE 0b00000000
#define MCP9800_CONFIG_ALERT_INTERRUPT  0b00000010
#define MCP9800_CONFIG_ALERT_COMPARATOR 0b00000000
#define MCP9800_CONFIG_ALERT_HIGH       0b00000100
#define MCP9800_CONFIG_ALERT_LOW        0b00000000
#define MCP9800_CONFIG_FAULT_QUEUE_1    0b00000000
#define MCP9800_CONFIG_FAULT_QUEUE_2    0b00001000
#define MCP9800_CONFIG_FAULT_QUEUE_4    0b00010000
#define MCP9800_CONFIG_FAULT_QUEUE_6    0b00011000
#define MCP9800_CONFIG_RESOLUTION_9     0b00000000
#define MCP9800_CONFIG_RESOLUTION_10    0b00100000
#define MCP9800_CONFIG_RESOLUTION_11    0b01000000
#define MCP9800_CONFIG_RESOLUTION_12    0b01100000
#define MCP9800_CONFIG_CONTINUOUS       0b00000000
#define MCP9800_CONFIG_ONE_SHOT         0b10000000

#define MCP9800_TEMPERATURE_MIN         10
#define MCP9800_TEMPERATURE_MAX         80
#define MCP9800_TEMPERATURE_ERROR       -273

////////////////////////////////////////////////////////////////////////////////

BOOL MCP9800_Initialize ( MCP9800_HANDLE mcp9800 );
FLOAT MCP9800_ReadTemperature ( MCP9800_HANDLE mcp9800 );

////////////////////////////////////////////////////////////////////////////////
#endif
