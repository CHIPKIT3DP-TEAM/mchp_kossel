/********************************************************************
  File Information:
    FileName:       stub_btc.c
    Dependencies:   See INCLUDES section
    Processor:      PIC32 Microcontrollers
    Hardware:
    Complier:       C32 (for PIC32)
    Company:        Microchip Technology, Inc.

    Software License Agreement:

    The software supplied herewith by Microchip Technology Incorporated
    (the "Company") for its PIC(r) Microcontroller is intended and
    supplied to you, the Company's customer, for use solely and
    exclusively on Microchip PIC Microcontroller products. The
    software is owned by the Company and/or its supplier, and is
    protected under applicable copyright laws. All rights are reserved.
    Any use in violation of the foregoing restrictions may subject the
    user to criminal sanctions under applicable laws, as well as to
    civil liability for the breach of the terms and conditions of this
    license.

    THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
    WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
    TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
    IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
    CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************/
#define _UART_C_
#include "uart.h"
////////////////////////////////////////////////////////////////////////////////

UART_MODULE uartModule[UART_MODULE_COUNT] =
{
    {
        (UART_REGS*) _UART1_BASE_ADDRESS,
        (SYSTEM_SFR*) &IEC1, _IEC3_U1RXIE_MASK,
        (SYSTEM_SFR*) &IEC1, _IEC3_U1TXIE_MASK,
        (SYSTEM_SFR*) &IEC1, _IEC3_U1EIE_MASK
    },
    {
        (UART_REGS*) _UART2_BASE_ADDRESS,
        (SYSTEM_SFR*) &IEC1, _IEC4_U2RXIE_MASK,
        (SYSTEM_SFR*) &IEC1, _IEC4_U2TXIE_MASK,
        (SYSTEM_SFR*) &IEC1, _IEC4_U2EIE_MASK
    },
    {
        (UART_REGS*) _UART3_BASE_ADDRESS,
        (SYSTEM_SFR*) &IEC1, _IEC4_U3RXIE_MASK,
        (SYSTEM_SFR*) &IEC2, _IEC4_U3TXIE_MASK,
        (SYSTEM_SFR*) &IEC1, _IEC4_U3EIE_MASK
    },
    {
        (UART_REGS*) _UART4_BASE_ADDRESS,
        (SYSTEM_SFR*) &IEC2, _IEC5_U4RXIE_MASK,
        (SYSTEM_SFR*) &IEC2, _IEC5_U4TXIE_MASK,
        (SYSTEM_SFR*) &IEC2, _IEC5_U4EIE_MASK
    },
    {
        (UART_REGS*) _UART5_BASE_ADDRESS,
        (SYSTEM_SFR*) &IEC2, _IEC5_U5RXIE_MASK,
        (SYSTEM_SFR*) &IEC2, _IEC5_U5TXIE_MASK,
        (SYSTEM_SFR*) &IEC2, _IEC5_U5EIE_MASK
    },
    {
        (UART_REGS*) _UART6_BASE_ADDRESS,
        (SYSTEM_SFR*) &IEC2, _IEC5_U6RXIE_MASK,
        (SYSTEM_SFR*) &IEC2, _IEC5_U6TXIE_MASK,
        (SYSTEM_SFR*) &IEC2, _IEC5_U6EIE_MASK
    },
};

////////////////////////////////////////////////////////////////////////////////

BOOL UART_Open ( UART_HANDLE uart, const UART_CONFIG *cfg )
{
    // TODO: check uart for validity

    UART_DisableRxInt ( uart );
    UART_DisableTxInt ( uart );

    uart->regs->UxSTA = UART_UXSTA_INIT_MASK;
    uart->regs->UxMODE = UART_UXMODE_INIT_MASK;
    uart->regs->UxMODEbits.PDSEL = cfg->dataParity;
    uart->EventHandler = cfg->EventHandler;

    if ( cfg->stopBits > 1 )
    {
        uart->regs->UxMODEbits.STSEL = 1;
    }
    
    if ( cfg->flowControl )
    {
        uart->regs->UxMODEbits.RTSMD = 0;
        uart->regs->UxMODEbits.UEN = 2;
    }
    
    uart->intRegs.errorIEC->SET = uart->intRegs.errorMask;
    
    uart->regs->UxMODEbits.ON = TRUE;

    return ( TRUE );
}

////////////////////////////////////////////////////////////////////////////////

BOOL UART_SetBaudrate ( UART_HANDLE uart, UINT32 baudrate )
{
    if ( uart->regs->UxMODEbits.BRGH )
    {
        uart->regs->UxBRG = ( SYSTEM_GetPeripheralClock () / baudrate - 2 ) / 4;
    }
    else
    {
        uart->regs->UxBRG = ( SYSTEM_GetPeripheralClock () / baudrate - 8 ) / 16;
    }

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
        uart->EventHandler ( UART_EVENT_RECEIVED, uart->rxBuffer, uart->rxCount );
    }
}

////////////////////////////////////////////////////////////////////////////////

VOID UART_TxInt ( UART_HANDLE uart )
{
    uart->regs->UxTXREG = *uart->txPtr++;
    if ( --uart->txCount == 0 )
    {
        UART_DisableTxInt ( uart );
        uart->EventHandler ( UART_EVENT_SENT, uart->txBuffer, uart->txSize );
    }
}

////////////////////////////////////////////////////////////////////////////////

VOID UART_ErrorInt ( UART_HANDLE uart )
{
//    ASSERT ( FALSE );
    uart->regs->UxSTACLR = UART_UXSTA_ERROR_MASK;
}

////////////////////////////////////////////////////////////////////////////////
