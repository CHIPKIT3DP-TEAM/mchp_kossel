/*****************************************************************************
                     Microchip Technology Incorporated

    FileName:        spi.h
    Dependencies:    See Includes Section
    Processor:       PIC32

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
#ifndef SPI_H
#define SPI_H

#ifndef __XC32__
    #error Wrong architecture, PIC32 only
#endif

////////////////////////////////////////////////////////////////////////////////

#include "system.h"

////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    union
    {
        volatile UINT32 SPIxCON;
        volatile __SPI1CONbits_t SPIxCONbits;
    };
    volatile UINT32 SPIxCONCLR;
    volatile UINT32 SPIxCONSET;
    volatile UINT32 SPIxCONINV;

    union
    {
        volatile UINT32 SPIxSTAT;
        volatile __SPI1STATbits_t SPIxSTATbits;
    };
    volatile UINT32 SPIxSTATCLR;
    volatile UINT32 SPIxSTATSET;
    volatile UINT32 SPIxSTATINV;
    
    volatile UINT32 SPIxBUF;
    volatile UINT32 resv0;
    volatile UINT32 resv1;
    volatile UINT32 resv2;
    
    volatile UINT32 SPIxBRG;
    volatile UINT32 SPIxBRGCLR;
    volatile UINT32 SPIxBRGSET;
    volatile UINT32 SPIxBRGINV;

    union
    {
        volatile UINT32 SPIxCON2;
        volatile __SPI1CON2bits_t SPIxCON2bits;
    };
    volatile UINT32 SPIxCON2CLR;
    volatile UINT32 SPIxCON2SET;
    volatile UINT32 SPIxCON2INV;
}
SPI_REGS;

typedef struct
{
    SPI_REGS *regs;
    UINT8 errIRQ;
    UINT8 rxIRQ;
    UINT8 txIRQ;
}
SPI_MODULE, *SPI_HANDLE;

typedef struct
{
    union
    {
        struct
        {
            UINT32  resv0           : 4;
            UINT32  disableSDI      : 1;
            UINT32  master          : 1;
            UINT32  clockPolarity   : 1;
            UINT32  slaveSSEnable   : 1;
            UINT32  clockEdge       : 1;
            UINT32  samplePhase     : 1;
            UINT32  bitMode         : 2;
            UINT32  disableSDO      : 1;
            UINT32  stopInIdle      : 1;
            UINT32  resv1           : 2;
            UINT32  enhBuffer       : 1;
            UINT32  frameEdge       : 1;
            UINT32  resv2           : 5;
            UINT32  clockSelect     : 1;
            UINT32  frameCount      : 3;
            UINT32  frameWidth      : 1;
            UINT32  masterSSEnable  : 1;
            UINT32  framePolarity   : 1;
            UINT32  frameDirection  : 1;
            UINT32  frameEnble      : 1;

            UINT32  audioMode       : 2;
            UINT32  resv3           : 1;
            UINT32  audioMono       : 1;
            UINT32  resv4           : 3;
            UINT32  audioEnable     : 1;
            UINT32  ignoreUnderrun  : 1;
            UINT32  ignoreOverflow  : 1;
            UINT32  underrunError   : 1;
            UINT32  overflowError   : 1;
            UINT32  frameError      : 1;
            UINT32  resv5           : 2;
            UINT32  signExtend      : 1;
            UINT32  resv6           : 16;
        };
        struct
        {
            UINT32 con;
            UINT32 con2;
        };
    };
}
SPI_CONFIG;

////////////////////////////////////////////////////////////////////////////////

#define SPI_INIT_CON        0

#define SPI_MODE_0          0b01
#define SPI_MODE_1          0b00
#define SPI_MODE_2          0b11
#define SPI_MODE_3          0b10

#define SPI_BITMODE_8       0b00
#define SPI_BITMODE_16      0b01
#define SPI_BITMODE_32      0b10

#define SPI_BITMODE_16_16   0b00
#define SPI_BITMODE_16_32   0b01
#define SPI_BITMODE_32_32   0b10
#define SPI_BITMODE_24_32   0b11

#define SPI_CLOCK_PBCLK     0
#define SPI_CLOCK_REFCLKO   1

#define SPI_SAMPLE_MIDDLE   0
#define SPI_SAMPLE_END      1

////////////////////////////////////////////////////////////////////////////////

#ifdef _SPI6_BASE_ADDRESS
    #define SPI6                    ( &spiModule[5] )
    #ifndef SPI_MODULE_COUNT
        #define SPI_MODULE_COUNT    6
    #endif
#endif

#ifdef _SPI5_BASE_ADDRESS
    #define SPI5                    ( &spiModule[4] )
    #ifndef SPI_MODULE_COUNT
        #define SPI_MODULE_COUNT    5
    #endif
#endif

#ifdef _SPI4_BASE_ADDRESS
    #define SPI4                    ( &spiModule[3] )
    #ifndef SPI_MODULE_COUNT
        #define SPI_MODULE_COUNT    4
    #endif
#endif

#ifdef _SPI3_BASE_ADDRESS
    #define SPI3                    ( &spiModule[2] )
    #ifndef SPI_MODULE_COUNT
        #define SPI_MODULE_COUNT    3
    #endif
#endif

#ifdef _SPI2_BASE_ADDRESS
    #define SPI2                    ( &spiModule[1] )
    #ifndef SPI_MODULE_COUNT
        #define SPI_MODULE_COUNT    2
    #endif
#endif

#define SPI1                        ( &spiModule[0] )
#ifndef SPI_MODULE_COUNT
    #define SPI_MODULE_COUNT        1
#endif

////////////////////////////////////////////////////////////////////////////////

extern SPI_MODULE    spiModule[SPI_MODULE_COUNT];

////////////////////////////////////////////////////////////////////////////////

BOOL SPI_Initialize ( SPI_HANDLE spi, SPI_CONFIG *cfg );
BOOL SPI_SetBaudrate ( SPI_HANDLE spi, UINT32 baudrate );
VOID SPI_SetBRG ( SPI_HANDLE spi, UINT32 brg );
VOID SPI_Enable ( SPI_HANDLE spi );
VOID SPI_Disable ( SPI_HANDLE spi );

////////////////////////////////////////////////////////////////////////////////
#endif
