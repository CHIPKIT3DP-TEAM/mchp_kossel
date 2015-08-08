/******************************************************************************
                     Microchip Technology, Inc.

File Name:      ped_i2c.c
Abstracts:      I2C dirver (PED implementation)
Dependencies:   see include section
Processor:      PIC24-dsPIC/PIC32
Compiler:       XC16/XC32

Copyright © 2009-2013 Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED ?AS IS? WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*******************************************************************************/

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
VOID I2C_InitBRG ( I2C_HANDLE i2c, UINT16 brg, UINT16 flags )
{
    i2c->regs->I2CxBRG = brg;
    i2c->regs->I2CxCON = flags | I2CxCON_INIT_MASK;
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
    {
        return ( FALSE );
    }

    i2c->regs->I2CxCONbits.SEN = TRUE;

    if ( I2C_ReadyWait ( i2c ) != TRUE )
    {
        return ( FALSE );
    }

    i2c->regs->I2CxTRN = addr;

    if ( I2C_ReadyWait ( i2c ) != TRUE )
    {
        return ( FALSE );
    }

    if ( i2c->regs->I2CxSTATbits.ACKSTAT == 0 )
    {
        return ( TRUE );
    }
    else
    {
        return ( FALSE );
    }
}
///////////////////////////////////////////////////////////////////////////////
BOOL I2C_Restart ( I2C_HANDLE i2c, UINT8 addr )
{
    i2c->ack = FALSE;

    if ( I2C_ReadyWait ( i2c ) != TRUE )
    {
        return ( FALSE );
    }

    i2c->regs->I2CxCONbits.RSEN = TRUE;

    if ( I2C_ReadyWait ( i2c ) != TRUE )
    {
        return ( FALSE );
    }

    i2c->regs->I2CxTRN = addr;

    if ( I2C_ReadyWait ( i2c ) != TRUE )
    {
        return ( FALSE );
    }

    if ( i2c->regs->I2CxSTATbits.ACKSTAT == 0 )
    {
        return ( TRUE );
    }
    else
    {
        return ( FALSE );
    }
}
///////////////////////////////////////////////////////////////////////////////
BOOL I2C_ReceiveByte ( I2C_HANDLE i2c, UINT8 *data )
{
    if ( i2c->ack == TRUE )
    {
        i2c->regs->I2CxCONbits.ACKDT = I2C_ACK;
        i2c->regs->I2CxCONbits.ACKEN = TRUE;
    }
    i2c->ack = TRUE;

    if ( I2C_ReadyWait ( i2c ) != TRUE )
    {
        return ( FALSE );
    }

    i2c->regs->I2CxCONbits.RCEN = TRUE;

    if ( I2C_ReadyWait ( i2c ) != TRUE )
    {
        return ( FALSE );
    }

    *data = i2c->regs->I2CxRCV;

    return ( TRUE );
}
///////////////////////////////////////////////////////////////////////////////
UINT16 I2C_ReceiveData ( I2C_HANDLE i2c, UINT8 *addr, UINT16 count )
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
        {
            break;
        }

        i2c->regs->I2CxCONbits.RCEN = TRUE;

        if ( I2C_ReadyWait ( i2c ) != TRUE )
        {
            break;
        }

        *addr = i2c->regs->I2CxRCV;
        addr ++;
        count --;
        read ++;
    }

    return ( read );
}
///////////////////////////////////////////////////////////////////////////////
BOOL I2C_SendByte ( I2C_HANDLE i2c, UINT8 data )
{
    if ( I2C_ReadyWait ( i2c ) != TRUE )
    {
        return ( FALSE );
    }

    i2c->regs->I2CxTRN = data;

    if ( I2C_ReadyWait ( i2c ) != TRUE )
    {
        return ( FALSE );
    }

    if ( i2c->regs->I2CxSTATbits.ACKSTAT == 1 )
    {
        return ( FALSE );
    }

    return ( TRUE );
}
///////////////////////////////////////////////////////////////////////////////
UINT16 I2C_SendData ( I2C_HANDLE i2c, const UINT8 *addr, UINT16 count )
{
    UINT16 written = 0;

    while ( count > 0 )
    {
        if ( I2C_ReadyWait ( i2c ) != TRUE )
        {
            break;
        }

        i2c->regs->I2CxTRN = *addr;
        addr ++;
        count --;
        written ++;

        if ( I2C_ReadyWait ( i2c ) != TRUE )
        {
            break;
        }

        if ( i2c->regs->I2CxSTATbits.ACKSTAT == 1 )
        {
            break;
        }
    }

    return ( written );
}
///////////////////////////////////////////////////////////////////////////////
BOOL I2C_Stop ( I2C_HANDLE i2c )
{
    if ( I2C_ReadyWait ( i2c ) != TRUE )
    {
        return ( FALSE );
    }

    if ( i2c->ack == TRUE )
    {
        i2c->regs->I2CxCONbits.ACKDT = I2C_NAK;
        i2c->regs->I2CxCONbits.ACKEN = TRUE;
    }

    if ( I2C_ReadyWait ( i2c ) != TRUE )
    {
        return ( FALSE );
    }

    i2c->regs->I2CxCONbits.PEN = TRUE;

    return ( TRUE );
}
///////////////////////////////////////////////////////////////////////////////
