/*****************************************************************************
                     Microchip Technology Incorporated

    FileName:        spi.c
    Dependencies:    See Includes Section
    Processor:       PIC24, PIC32

Copyright � 2009-2013 Microchip Technology Inc.  All rights reserved.

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

******************************************************************************/
#define     SPI_C
#include    "spi.h"

////////////////////////////////////////////////////////////////////////////////

SPI_MODULE spiModule[SPI_MODULE_COUNT] =
{
    #ifdef SPI1
        {
            (SPI_REGS*) _SPI1_BASE_ADDRESS,
            _SPI1_FAULT_VECTOR, _SPI1_RX_VECTOR, _SPI1_TX_VECTOR,
        },
    #endif

    #ifdef SPI2
        {
            (SPI_REGS*) _SPI2_BASE_ADDRESS,
            _SPI2_FAULT_VECTOR, _SPI2_RX_VECTOR, _SPI2_TX_VECTOR,
        },
    #endif

    #ifdef SPI3
        {
            (SPI_REGS*) _SPI3_BASE_ADDRESS,
            _SPI3_FAULT_VECTOR, _SPI3_RX_VECTOR, _SPI3_TX_VECTOR,
        },
    #endif

    #ifdef SPI4
        {
            (SPI_REGS*) _SPI4_BASE_ADDRESS,
            _SPI4_FAULT_VECTOR, _SPI4_RX_VECTOR, _SPI4_TX_VECTOR,
        },
    #endif

    #ifdef SPI5
        {
            (SPI_REGS*) _SPI5_BASE_ADDRESS,
            _SPI5_FAULT_VECTOR, _SPI5_RX_VECTOR, _SPI5_TX_VECTOR,
        },
    #endif

    #ifdef SPI6
        {
            (SPI_REGS*) _SPI6_BASE_ADDRESS,
            _SPI6_FAULT_VECTOR, _SPI6_RX_VECTOR, _SPI6_TX_VECTOR,
        },
    #endif
};

////////////////////////////////////////////////////////////////////////////////

BOOL SPI_Initialize ( SPI_HANDLE spi, SPI_CONFIG *cfg )
{
    SPI_Disable ( spi );
    spi->regs->SPIxCON = cfg->con;
    spi->regs->SPIxCON2 = cfg->con2;
    SPI_Enable ( spi );

    return ( TRUE );
}

////////////////////////////////////////////////////////////////////////////////

BOOL SPI_SetBaudrate ( SPI_HANDLE spi, UINT32 baudrate )
{
    spi->regs->SPIxBRG = ( SYSTEM_GetPeripheralClock () + baudrate / 2 ) / baudrate - 1;
    
    if (( SYSTEM_GetPeripheralClock () / ( spi->regs->SPIxBRG + 1 )) == baudrate )
        return ( TRUE );
    else
        return ( FALSE );
}

////////////////////////////////////////////////////////////////////////////////

VOID SPI_SetBRG ( SPI_HANDLE spi, UINT32 brg )
{
    spi->regs->SPIxBRG = brg;
}

////////////////////////////////////////////////////////////////////////////////

VOID SPI_Enable ( SPI_HANDLE spi )
{
    spi->regs->SPIxCONSET = _SPI1CON_ON_MASK;
}

////////////////////////////////////////////////////////////////////////////////

VOID SPI_Disable ( SPI_HANDLE spi )
{
    spi->regs->SPIxCONCLR = _SPI1CON_ON_MASK;
}

////////////////////////////////////////////////////////////////////////////////

