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

