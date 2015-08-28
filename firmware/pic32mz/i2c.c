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
#define I2C_C
#include "i2c.h"
///////////////////////////////////////////////////////////////////////////////

I2C_MODULE i2cModules[I2C_MODULE_COUNT] =
{
    #ifdef _I2C1_BASE_ADDRESS
    {
        (I2C_REGS*)_I2C1_BASE_ADDRESS
    },
    #endif

    #ifdef _I2C2_BASE_ADDRESS
    {
        (I2C_REGS*)_I2C2_BASE_ADDRESS
    },
    #endif

    #ifdef _I2C3_BASE_ADDRESS
    {
        (I2C_REGS*)_I2C3_BASE_ADDRESS
    },
    #endif

    #ifdef _I2C4_BASE_ADDRESS
    {
        (I2C_REGS*)_I2C4_BASE_ADDRESS
    },
    #endif

    #ifdef _I2C5_BASE_ADDRESS
    {
        (I2C_REGS*)_I2C5_BASE_ADDRESS
    }
    #endif
};

///////////////////////////////////////////////////////////////////////////////
BOOL I2C_Initialize ( I2C_HANDLE i2c, const I2C_CONFIG *cfg )
{
    UINT32 baud, margin;
    
    baud = SYSTEM_GetPeripheralClock () / ( 2 * cfg->baudrate ) - I2C_PULSE_GOBBLER_DELAY - 2;
    if ( baud < 2 )
        return ( FALSE );
    
    i2c->regs->I2CxBRG = baud;
    i2c->regs->I2CxADD = cfg->address;
    i2c->regs->I2CxMSK = cfg->mask;
    i2c->regs->I2CxCON = cfg->con | I2CxCON_INIT_MASK;
    
    baud = SYSTEM_GetPeripheralClock () / ( 2 * ( i2c->regs->I2CxBRG + 2 + I2C_PULSE_GOBBLER_DELAY ));
    margin = baud / 20; // +-5%
    if (( baud < cfg->baudrate + margin ) && ( baud > cfg->baudrate - margin ))
        return ( TRUE );
    else
        return ( FALSE );
}
///////////////////////////////////////////////////////////////////////////////
BOOL I2C_Ready ( I2C_HANDLE i2c )
{
    if (( i2c->regs->I2CxCON & I2CxCON_BUSY_MASK ) != 0 )
    {
        return ( FALSE );
    }
    else
    {
        if (( i2c->regs->I2CxSTATbits.TRSTAT ) != 0 )
        {
            return ( FALSE );
        }
    }

    return ( TRUE );
}
///////////////////////////////////////////////////////////////////////////////
BOOL I2C_ReadyWait ( I2C_HANDLE i2c )
{
    UINT32 timeout;
    
    timeout = TIME_Get1ms () + I2C_TIMEOUT_1MS;

    do
    {
        if ( I2C_Ready ( i2c ) == TRUE )
        {
            return ( TRUE );
        }

        SYSTEM_Idle ();
    }
    while ( TIME_Elapsed1ms ( timeout ) == FALSE );

    return ( FALSE );
}
///////////////////////////////////////////////////////////////////////////////
BOOL I2C_Start ( I2C_HANDLE i2c, UINT8 addr )
{
    i2c->ack = FALSE;

    if ( I2C_ReadyWait ( i2c ) != TRUE )
        return ( FALSE );

    i2c->regs->I2CxCONbits.SEN = TRUE;

    if ( I2C_ReadyWait ( i2c ) != TRUE )
        return ( FALSE );

    i2c->regs->I2CxTRN = addr;

    if ( I2C_ReadyWait ( i2c ) != TRUE )
        return ( FALSE );

    if ( i2c->regs->I2CxSTATbits.ACKSTAT == 0 )
        return ( TRUE );
    else
        return ( FALSE );
}
///////////////////////////////////////////////////////////////////////////////
BOOL I2C_Restart ( I2C_HANDLE i2c, UINT8 addr )
{
    i2c->ack = FALSE;

    if ( I2C_ReadyWait ( i2c ) != TRUE )
        return ( FALSE );

    i2c->regs->I2CxCONbits.RSEN = TRUE;

    if ( I2C_ReadyWait ( i2c ) != TRUE )
        return ( FALSE );

    i2c->regs->I2CxTRN = addr;

    if ( I2C_ReadyWait ( i2c ) != TRUE )
        return ( FALSE );

    if ( i2c->regs->I2CxSTATbits.ACKSTAT == 0 )
        return ( TRUE );
    else
        return ( FALSE );
}
///////////////////////////////////////////////////////////////////////////////
BOOL I2C_ReadByte ( I2C_HANDLE i2c, UINT8 *data )
{
    if ( i2c->ack == TRUE )
    {
        i2c->regs->I2CxCONbits.ACKDT = I2C_ACK;
        i2c->regs->I2CxCONbits.ACKEN = TRUE;
    }
    i2c->ack = TRUE;

    if ( I2C_ReadyWait ( i2c ) != TRUE )
        return ( FALSE );

    i2c->regs->I2CxCONbits.RCEN = TRUE;

    if ( I2C_ReadyWait ( i2c ) != TRUE )
        return ( FALSE );

    *data = i2c->regs->I2CxRCV;

    return ( TRUE );
}
///////////////////////////////////////////////////////////////////////////////
UINT16 I2C_ReadData ( I2C_HANDLE i2c, UINT8 *addr, UINT16 count )
{
    UINT16 read = 0;

    while ( count > 0 )
    {
        if ( i2c->ack == TRUE )
        {
            i2c->regs->I2CxCONbits.ACKDT = I2C_ACK;
            i2c->regs->I2CxCONbits.ACKEN = TRUE;
        }
        i2c->ack = TRUE;

        if ( I2C_ReadyWait ( i2c ) != TRUE )
            break;

        i2c->regs->I2CxCONbits.RCEN = TRUE;

        if ( I2C_ReadyWait ( i2c ) != TRUE )
            break;

        *addr = i2c->regs->I2CxRCV;
        addr ++;
        count --;
        read ++;
    }

    return ( read );
}
///////////////////////////////////////////////////////////////////////////////
BOOL I2C_WriteByte ( I2C_HANDLE i2c, UINT8 data )
{
    if ( I2C_ReadyWait ( i2c ) != TRUE )
        return ( FALSE );

    i2c->regs->I2CxTRN = data;

    if ( I2C_ReadyWait ( i2c ) != TRUE )
        return ( FALSE );

    if ( i2c->regs->I2CxSTATbits.ACKSTAT == 1 )
        return ( FALSE );

    return ( TRUE );
}
///////////////////////////////////////////////////////////////////////////////
UINT16 I2C_WriteData ( I2C_HANDLE i2c, const UINT8 *addr, UINT16 count )
{
    UINT16 written = 0;

    while ( count > 0 )
    {
        if ( I2C_ReadyWait ( i2c ) != TRUE )
            break;

        i2c->regs->I2CxTRN = *addr;
        addr ++;
        count --;
        written ++;

        if ( I2C_ReadyWait ( i2c ) != TRUE )
            break;

        if ( i2c->regs->I2CxSTATbits.ACKSTAT == 1 )
            break;
    }

    return ( written );
}
///////////////////////////////////////////////////////////////////////////////
BOOL I2C_Stop ( I2C_HANDLE i2c )
{
    if ( I2C_ReadyWait ( i2c ) != TRUE )
        return ( FALSE );

    if ( i2c->ack == TRUE )
    {
        i2c->regs->I2CxCONbits.ACKDT = I2C_NAK;
        i2c->regs->I2CxCONbits.ACKEN = TRUE;
    }

    if ( I2C_ReadyWait ( i2c ) != TRUE )
        return ( FALSE );

    i2c->regs->I2CxCONbits.PEN = TRUE;

    return ( TRUE );
}
///////////////////////////////////////////////////////////////////////////////
