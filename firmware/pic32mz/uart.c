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
#define _UART_C_
#include "uart.h"
////////////////////////////////////////////////////////////////////////////////

UART_MODULE uartModule[UART_MODULE_COUNT] =
{
    {
        (UART_REGS*) _UART1_BASE_ADDRESS,
        {
            (SYSTEM_SFR*) &IEC3, _IEC3_U1RXIE_MASK,
            (SYSTEM_SFR*) &IEC3, _IEC3_U1TXIE_MASK,
            (SYSTEM_SFR*) &IEC3, _IEC3_U1EIE_MASK
        }
    },
    {
        (UART_REGS*) _UART2_BASE_ADDRESS,
        {
            (SYSTEM_SFR*) &IEC4, _IEC4_U2RXIE_MASK,
            (SYSTEM_SFR*) &IEC4, _IEC4_U2TXIE_MASK,
            (SYSTEM_SFR*) &IEC4, _IEC4_U2EIE_MASK
        }
    },
    {
        (UART_REGS*) _UART3_BASE_ADDRESS,
        {
            (SYSTEM_SFR*) &IEC4, _IEC4_U3RXIE_MASK,
            (SYSTEM_SFR*) &IEC4, _IEC4_U3TXIE_MASK,
            (SYSTEM_SFR*) &IEC4, _IEC4_U3EIE_MASK
        }
    },
    {
        (UART_REGS*) _UART4_BASE_ADDRESS,
        {
            (SYSTEM_SFR*) &IEC5, _IEC5_U4RXIE_MASK,
            (SYSTEM_SFR*) &IEC5, _IEC5_U4TXIE_MASK,
            (SYSTEM_SFR*) &IEC5, _IEC5_U4EIE_MASK
        }
    },
    {
        (UART_REGS*) _UART5_BASE_ADDRESS,
        {
            (SYSTEM_SFR*) &IEC5, _IEC5_U5RXIE_MASK,
            (SYSTEM_SFR*) &IEC5, _IEC5_U5TXIE_MASK,
            (SYSTEM_SFR*) &IEC5, _IEC5_U5EIE_MASK
        }
    },
    {
        (UART_REGS*) _UART6_BASE_ADDRESS,
        {
            (SYSTEM_SFR*) &IEC5, _IEC5_U6RXIE_MASK,
            (SYSTEM_SFR*) &IEC5, _IEC5_U6TXIE_MASK,
            (SYSTEM_SFR*) &IEC5, _IEC5_U6EIE_MASK
        }
    },
};

////////////////////////////////////////////////////////////////////////////////

BOOL UART_Initialize ( UART_HANDLE uart, const UART_CONFIG *cfg )
{
    // TODO: check uart for validity

    UART_DisableRxInt ( uart );
    UART_DisableTxInt ( uart );

    uart->regs->UxSTA = UART_UXSTA_INIT_MASK;
    uart->regs->UxMODE = UART_UXMODE_INIT_MASK;
    uart->regs->UxMODEbits.PDSEL = cfg->dataParity;
    uart->EventHandler = cfg->EventHandler;

    if ( cfg->stopBits > 1 )
        uart->regs->UxMODEbits.STSEL = 1;
    
    if ( cfg->flowControl )
    {
        uart->regs->UxMODEbits.RTSMD = 0;
        uart->regs->UxMODEbits.UEN = 2;
    }

    if ( uart->regs->UxMODEbits.BRGH )
        uart->regs->UxBRG = ( SYSTEM_GetPeripheralClock () / cfg->baudrate - 2 ) / 4;
    else
        uart->regs->UxBRG = ( SYSTEM_GetPeripheralClock () / cfg->baudrate - 8 ) / 16;

    uart->intRegs.errorIEC->SET = uart->intRegs.errorMask;
    
    uart->regs->UxMODEbits.ON = TRUE;

    return ( TRUE );
}

////////////////////////////////////////////////////////////////////////////////

BOOL UART_Transmit ( UART_HANDLE uart, const UINT8 *data, const UINT16 size )
{
    if ( uart->txCount != 0 )
    {
        return ( FALSE );
    }
    else
    {
        uart->txBuffer = data;
        uart->txPtr = data;
        uart->txSize = size;
        uart->txCount = size;
        UART_EnableTxInt ( uart );
        uart->regs->UxSTAbits.UTXEN = TRUE;

        return ( TRUE );
    }
}

////////////////////////////////////////////////////////////////////////////////

BOOL UART_Receive ( UART_HANDLE uart, UINT8 *buffer, const UINT16 size )
{
    UART_DisableRxInt ( uart );
    {
        uart->rxBuffer = buffer;
        uart->rxPtr = buffer;
        uart->rxSize = size;
        uart->rxCount = 0;
    }
    UART_EnableRxInt ( uart );
    uart->regs->UxSTAbits.URXEN = TRUE;
    
    return ( TRUE );
}

////////////////////////////////////////////////////////////////////////////////

BOOL UART_Discard ( UART_HANDLE uart, const UINT16 size )
{
    SYSTEM_DisableInterrupts ();
    {
        if ( size >= uart->rxCount )
        {
            uart->rxPtr = uart->rxBuffer;
            uart->rxCount = 0;
        }
        else
        {
            memcpy ( uart->rxBuffer, uart->rxBuffer + size, uart->rxCount - size );
            uart->rxPtr -= size;
            uart->rxCount -= size;
        }
    }
    SYSTEM_EnableInterrupts ();

    return ( TRUE );
}

////////////////////////////////////////////////////////////////////////////////

VOID UART_RxInt ( UART_HANDLE uart )
{
    UINT8 byte;

    byte = uart->regs->UxRXREG;
    *uart->rxPtr++ = byte;
    if ( ++uart->rxCount == uart->rxSize )
    {
        UART_DisableRxInt ( uart );
        uart->EventHandler ( uart, UART_EVENT_RECEIVED, uart->rxBuffer, uart->rxCount );
    }
}

////////////////////////////////////////////////////////////////////////////////

VOID UART_TxInt ( UART_HANDLE uart )
{
    uart->regs->UxTXREG = *uart->txPtr++;
    if ( --uart->txCount == 0 )
    {
        UART_DisableTxInt ( uart );
        uart->EventHandler ( uart, UART_EVENT_SENT, uart->txBuffer, uart->txSize );
    }
}

////////////////////////////////////////////////////////////////////////////////

VOID UART_ErrorInt ( UART_HANDLE uart )
{
//    ASSERT ( FALSE );
    uart->EventHandler ( uart, uart->regs->UxSTA & UART_UXSTA_ERROR_MASK, NULL, 0 );
    uart->regs->UxSTACLR = UART_UXSTA_ERROR_MASK;
}

////////////////////////////////////////////////////////////////////////////////
