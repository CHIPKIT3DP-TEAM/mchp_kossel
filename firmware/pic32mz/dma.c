/*****************************************************************************
                     Microchip Technology Incorporated

    FileName:        dma.c
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
#define     DMA_C
#include    "dma.h"
////////////////////////////////////////////////////////////////////////////////

DMA_CHANNEL dmaChannel[DMA_CHANNEL_COUNT] =
{
    { (DMA_REGS*)&DCH0CON },
    { (DMA_REGS*)&DCH1CON },
    { (DMA_REGS*)&DCH2CON },
    { (DMA_REGS*)&DCH3CON },
    { (DMA_REGS*)&DCH4CON },
    { (DMA_REGS*)&DCH5CON },
    { (DMA_REGS*)&DCH6CON },
    { (DMA_REGS*)&DCH7CON }
};

////////////////////////////////////////////////////////////////////////////////

BOOL DMA_Initialize ( DMA_HANDLE dma, DMA_CONFIG *cfg )
{
    dma->regs->DCHxCONCLR = _DCH1CON_CHEN_MASK;
    DMACON = _DMACON_ON_MASK;
    dma->EventHandler = cfg->EventHandler;
    dma->regs->DCHxCON = cfg->con;
    dma->regs->DCHxECON = cfg->econ;
    dma->regs->DCHxINT = cfg->icon;

    return ( TRUE );
}

////////////////////////////////////////////////////////////////////////////////

VOID DMA_Enable ( DMA_HANDLE dma )
{
    dma->regs->DCHxCONSET = _DCH1CON_CHEN_MASK;
}

////////////////////////////////////////////////////////////////////////////////

VOID DMA_Disable ( DMA_HANDLE dma )
{
    dma->regs->DCHxCONCLR = _DCH1CON_CHEN_MASK;
}

////////////////////////////////////////////////////////////////////////////////

UINT32 DMA_GetEventFlags ( DMA_HANDLE dma )
{
    return ( dma->regs->DCHxINT & DMA_EVENT_FLAGS_MASK );
}

////////////////////////////////////////////////////////////////////////////////

VOID DMA_ClearEventFlags ( DMA_HANDLE dma, UINT32 flags )
{
    flags &= DMA_EVENT_FLAGS_MASK;
    dma->regs->DCHxINTCLR = flags;
}

////////////////////////////////////////////////////////////////////////////////


UINT32 DMA_GetSrcPointer ( DMA_HANDLE dma )
{
    return ( dma->regs->DCHxSPTR );
}

////////////////////////////////////////////////////////////////////////////////

UINT32 DMA_GetDestPointer ( DMA_HANDLE dma )
{
    return ( dma->regs->DCHxDPTR );
}

////////////////////////////////////////////////////////////////////////////////

VOID DMA_Transfer ( DMA_HANDLE dma, const VOID *srcAddr, VOID *destAddr, UINT16 srcSize, UINT16 destSize, UINT8 cellSize, UINT8 event )
{
    dma->regs->DCHxCONCLR = _DCH1CON_CHEN_MASK;
    
    dma->regs->DCHxSSA = SYSTEM_ToPhysical ( srcAddr );
    dma->regs->DCHxDSA = SYSTEM_ToPhysical ( destAddr );
    dma->regs->DCHxSSIZ = srcSize;
    dma->regs->DCHxDSIZ = destSize;
    dma->regs->DCHxCSIZ = cellSize;
    
    dma->regs->DCHxINTCLR = DMA_EVENT_FLAGS_MASK;
    dma->regs->DCHxINTSET = ( event & DMA_EVENT_FLAGS_MASK ) << 16;
    dma->regs->DCHxCONSET = _DCH1CON_CHEN_MASK;
}

////////////////////////////////////////////////////////////////////////////////

VOID DMA_Interrupt ( DMA_HANDLE dma )
{
    UINT32 flags;
    
    flags = dma->regs->DCHxINT;
    flags &= ( flags >> 16 ) & DMA_EVENT_FLAGS_MASK;

    dma->EventHandler ( dma, flags );
}

////////////////////////////////////////////////////////////////////////////////
