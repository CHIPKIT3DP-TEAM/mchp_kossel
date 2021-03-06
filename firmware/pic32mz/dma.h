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
#ifndef _DMA_H_
#define _DMA_H_
////////////////////////////////////////////////////////////////////////////////

#include "system.h"

#ifndef __XC32__
    #error Wrong architecture, PIC32 only
#endif

////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    union
    {
        volatile UINT32 DCHxCON;
        volatile __DCH0CONbits_t DCHxCONbits;
    };
    volatile UINT32 DCHxCONCLR;
    volatile UINT32 DCHxCONSET;
    volatile UINT32 DCHxCONINV;

    union
    {
        volatile UINT32 DCHxECON;
        volatile __DCH0ECONbits_t DCHxECONbits;
    };
    volatile UINT32 DCHxECONCLR;
    volatile UINT32 DCHxECONSET;
    volatile UINT32 DCHxECONINV;

    union
    {
        volatile UINT32 DCHxINT;
        volatile __DCH0INTbits_t DCHxINTbits;
    };
    volatile UINT32 DCHxINTCLR;
    volatile UINT32 DCHxINTSET;
    volatile UINT32 DCHxINTINV;

    volatile UINT32 DCHxSSA;
    volatile UINT32 DCHxSSACLR;
    volatile UINT32 DCHxSSASET;
    volatile UINT32 DCHxSSAINV;

    volatile UINT32 DCHxDSA;
    volatile UINT32 DCHxDSACLR;
    volatile UINT32 DCHxDSASET;
    volatile UINT32 DCHxDSAINV;

    volatile UINT32 DCHxSSIZ;
    volatile UINT32 DCHxSSIZCLR;
    volatile UINT32 DCHxSSIZSET;
    volatile UINT32 DCHxSSIZINV;

    volatile UINT32 DCHxDSIZ;
    volatile UINT32 DCHxDSIZCLR;
    volatile UINT32 DCHxDSIZSET;
    volatile UINT32 DCHxDSIZINV;

    volatile UINT32 DCHxSPTR;
    volatile UINT32 resv0;
    volatile UINT32 resv1;
    volatile UINT32 resv2;

    volatile UINT32 DCHxDPTR;
    volatile UINT32 resv3;
    volatile UINT32 resv4;
    volatile UINT32 resv5;
    
    volatile UINT32 DCHxCSIZ;
    volatile UINT32 DCHxCSIZCLR;
    volatile UINT32 DCHxCSIZSET;
    volatile UINT32 DCHxCSIZINV;

    volatile UINT32 DCHxCPTR;
    volatile UINT32 resv6;
    volatile UINT32 resv7;
    volatile UINT32 resv8;
    
    volatile UINT32 DCHxDAT;
    volatile UINT32 DCHxDATCLR;
    volatile UINT32 DCHxDATSET;
    volatile UINT32 DCHxDATINV;
}
DMA_REGS;

typedef struct DMA_CHANNEL *DMA_HANDLE;
typedef struct DMA_CHANNEL
{
    DMA_REGS *regs;
    VOID (*EventHandler) ( DMA_HANDLE dma, UINT32 event );
}
DMA_CHANNEL;

typedef union
{
    struct
    {
        UINT32 priority         : 2;
        UINT32 resv0            : 2;
        UINT32 autoEnable       : 1;
        UINT32 chainEnable      : 1;
        UINT32 allowEventsDis   : 1;
        UINT32 enable           : 1;
        UINT32 chainSelect      : 1;
        UINT32 resv1            : 23;

        UINT32 resv2            : 3;
        UINT32 abortIRQEnable   : 1;
        UINT32 startIRQEnable   : 1;
        UINT32 patternAbort     : 1;
        UINT32 resv3            : 2;
        UINT32 startIRQ         : 8;
        UINT32 abortIRQ         : 8;
        UINT32 resv4            : 8;

        UINT32 resv5            : 16;
        UINT32 addrErrorInt     : 1;
        UINT32 abortInt         : 1;
        UINT32 cellTransferInt  : 1;
        UINT32 blockDoneInt     : 1;
        UINT32 destHalfInt      : 1;
        UINT32 destDoneInt      : 1;
        UINT32 sourceHalfInt    : 1;
        UINT32 sourceDoneInt    : 1;
        UINT32 resv6            : 8;
    };
    struct
    {
        UINT32 con;
        UINT32 econ;
        UINT32 icon;
        VOID (*EventHandler) ( DMA_HANDLE dma, UINT32 event );
    };
}
DMA_CONFIG;

////////////////////////////////////////////////////////////////////////////////

#define DMA_CHANNEL_COUNT       8
#define DMA7                    ( &dmaChannel[7] )
#define DMA6                    ( &dmaChannel[6] )
#define DMA5                    ( &dmaChannel[5] )
#define DMA4                    ( &dmaChannel[4] )
#define DMA3                    ( &dmaChannel[3] )
#define DMA2                    ( &dmaChannel[2] )
#define DMA1                    ( &dmaChannel[1] )
#define DMA0                    ( &dmaChannel[0] )

////////////////////////////////////////////////////////////////////////////////

#define DMA_EVENT_FLAGS_MASK        0x000000FF

#define DMA_EVENT_ADDRESS_ERROR     0x00000001
#define DMA_EVENT_ABORT             0x00000002
#define DMA_EVENT_CELL_TRANSFER     0x00000004
#define DMA_EVENT_BLOCK_DONE        0x00000008
#define DMA_EVENT_DEST_HALF         0x00000010
#define DMA_EVENT_DEST_DONE         0x00000020
#define DMA_EVENT_SOURCE_HALF       0x00000040
#define DMA_EVENT_SOURCE_DONE       0x00000080

////////////////////////////////////////////////////////////////////////////////

extern DMA_CHANNEL    dmaChannel[DMA_CHANNEL_COUNT];

////////////////////////////////////////////////////////////////////////////////

BOOL DMA_Initialize ( DMA_HANDLE dma, DMA_CONFIG *cfg );
VOID DMA_Enable ( DMA_HANDLE dma );
VOID DMA_Disable ( DMA_HANDLE dma );
UINT32 DMA_GetEventFlags ( DMA_HANDLE dma );
VOID DMA_ClearEventFlags ( DMA_HANDLE dma, UINT32 flags );
UINT32 DMA_GetSrcPointer ( DMA_HANDLE dma );
UINT32 DMA_GetDestPointer ( DMA_HANDLE dma );
VOID DMA_Transfer ( DMA_HANDLE dma, const VOID *srcAddr, VOID *destAddr, UINT16 srcSize, UINT16 destSize, UINT8 cellSize, UINT8 event );
VOID DMA_Interrupt ( DMA_HANDLE dma );

////////////////////////////////////////////////////////////////////////////////
#endif
