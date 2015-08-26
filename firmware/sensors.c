////////////////////////////////////////////////////////////////////////////////
//
//
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
    .address = MCP98244_I2C_BASE_ADDRESS_TEMP,
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
