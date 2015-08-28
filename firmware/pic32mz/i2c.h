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
#ifndef I2C_H
#define I2C_H
////////////////////////////////////////////////////////////////////////////////

#include "system.h"
#include "time.h"

#ifndef __XC32__
    #error Wrong architecture, PIC32 only
#endif

////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    union
    {
        volatile UINT32 I2CxCON;
        volatile __I2C1CONbits_t I2CxCONbits;
    };
    volatile UINT32 I2CxCONCLR;
    volatile UINT32 I2CxCONSET;
    volatile UINT32 I2CxCONINV;
    
    union
    {
        volatile UINT32 I2CxSTAT;
        volatile __I2C1STATbits_t I2CxSTATbits;
    };
    volatile UINT32 I2CxSTATCLR;
    volatile UINT32 I2CxSTATSET;
    volatile UINT32 I2CxSTATINV;

    volatile UINT32 I2CxADD;
    volatile UINT32 I2CxADDCLR;
    volatile UINT32 I2CxADDSET;
    volatile UINT32 I2CxADDINV;

    volatile UINT32 I2CxMSK;
    volatile UINT32 I2CxMSKCLR;
    volatile UINT32 I2CxMSKSET;
    volatile UINT32 I2CxMSKINV;

    volatile UINT32 I2CxBRG;
    volatile UINT32 I2CxBRGCLR;
    volatile UINT32 I2CxBRGSET;
    volatile UINT32 I2CxBRGINV;

    volatile UINT32 I2CxTRN;
    volatile UINT32 I2CxTRNCLR;
    volatile UINT32 I2CxTRNSET;
    volatile UINT32 I2CxTRNINV;

    volatile UINT32 I2CxRCV;
}
I2C_REGS;

typedef struct
{
    I2C_REGS    *regs;
    BOOL        ack;
}
I2C_MODULE, *I2C_HANDLE;

typedef union
{
    struct
    {
        UINT32 resv0            : 6;
        UINT32 stretchEnable    : 1;
        UINT32 generalCallEnable: 1;
        UINT32 smbusLevels      : 1;
        UINT32 highSpeed        : 1;
        UINT32 address10bit     : 1;
        UINT32 strictAddressing : 1;
        UINT32 resv2            : 1;
        UINT32 stopInIdle       : 1;
        UINT32 resv3            : 2;
        UINT32 dataHold         : 1;
        UINT32 addressHold      : 1;
        UINT32 slaveBusCollDet  : 1;
        UINT32 holdTime         : 1;
        UINT32 ignoreOverflow   : 1;
        UINT32 startInt         : 1;
        UINT32 stopInt          : 1;
        UINT32 resv4            : 9;

        UINT32 address;
        UINT32 mask;
        UINT32 baudrate;
    };
    
    UINT32 con;
}
I2C_CONFIG;    

////////////////////////////////////////////////////////////////////////////////

#ifdef _I2C5_BASE_ADDRESS
    #define I2C5                    &i2cModules[4]
    #ifndef I2C_MODULE_COUNT
        #define I2C_MODULE_COUNT    5
    #endif
#endif

#ifdef _I2C4_BASE_ADDRESS
    #define I2C4                    &i2cModules[3]
    #ifndef I2C_MODULE_COUNT
        #define I2C_MODULE_COUNT    4
    #endif
#endif

#ifdef _I2C3_BASE_ADDRESS
    #define I2C3                    &i2cModules[2]
    #ifndef I2C_MODULE_COUNT
        #define I2C_MODULE_COUNT    3
    #endif
#endif

#ifdef _I2C2_BASE_ADDRESS
    #define I2C2                    &i2cModules[1]
    #ifndef I2C_MODULE_COUNT
        #define I2C_MODULE_COUNT    2
    #endif
#endif

#ifdef _I2C1_BASE_ADDRESS
    #define I2C1                    &i2cModules[0]
    #ifndef I2C_MODULE_COUNT
        #define I2C_MODULE_COUNT    1
    #endif
#endif


#define I2C_READ    1
#define I2C_WRITE   0
#define I2C_ACK     0
#define I2C_NAK     1

#define I2C_GENERAL_CALL_ADDRESS            0x00
#define I2C_START_BYTE                      0x01
#define I2C_10BIT_ADDRESS_CONST_BITS        0x1E

#define I2C_ENABLE_SMB_SUPPORT              0x0100
#define I2C_ENABLE_HIGH_SPEED               0x0200
#define I2C_STOP_IN_IDLE                    0x2000
#define I2C_7BIT_ADDRESS                    0x0000
#define I2C_USE_10BIT_ADDRESS               0x0400
#define I2C_ENABLE_GENERAL_CALL             0x0080
#define I2C_DISABLE_IPMI                    0x0800

#define I2CxCON_INIT_MASK                   0b1000000000000000
#define I2CxCON_BUSY_MASK                   0b0000000000011111

////////////////////////////////////////////////////////////////////////////////

#define I2C_TIMEOUT_1MS             10
#define I2C_PULSE_GOBBLER_DELAY     (( SYSTEM_GetPeripheralClock () * 104 ) / 1000000000 )

////////////////////////////////////////////////////////////////////////////////

extern I2C_MODULE i2cModules[I2C_MODULE_COUNT];

BOOL    I2C_Initialize ( I2C_HANDLE i2c, I2C_CONFIG *cfg );
BOOL    I2C_Ready ( I2C_HANDLE i2c );
BOOL    I2C_Start ( I2C_HANDLE i2c, UINT8 addr );
BOOL    I2C_Restart ( I2C_HANDLE i2c, UINT8 addr );
BOOL    I2C_WriteByte ( I2C_HANDLE i2c, UINT8 data );
UINT16  I2C_WriteData ( I2C_HANDLE i2c, const UINT8 *addr, UINT16 count );
BOOL    I2C_ReadByte ( I2C_HANDLE i2c, UINT8 *data );
UINT16  I2C_ReadData ( I2C_HANDLE i2c, UINT8 *addr, UINT16 count );
BOOL    I2C_Stop ( I2C_HANDLE i2c );

////////////////////////////////////////////////////////////////////////////////
#endif
