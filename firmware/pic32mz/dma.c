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
#define     _DMA_C_
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
