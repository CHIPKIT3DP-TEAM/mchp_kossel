/*********************************************************************
 *
 *                  DMA API definitions
 *
 *********************************************************************
 * FileName:        Dma.h
 * Dependencies:	p32xxxx.h
 * 					int.h
 *
 * Processor:       PIC32
 *
 * Compiler:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the ?Company?) for its PIC32/PIC24F Microcontroller is intended
 * and supplied to you, the Company?s customer, for use solely and
 * exclusively on Microchip PIC32/PIC24F Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN ?AS IS? CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * $Id: Dma.h,v 1.9 2007/01/17 21:35:46 C12878 Exp $
 * $Name:  $
 *
 ********************************************************************/

#ifndef _DMA_H_
#define _DMA_H_

#include <xc.h>
#include "system.h"

typedef struct
{
    volatile UINT32 DCHxCON;
    volatile UINT32 DCHxCONCLR;
    volatile UINT32 DCHxCONSET;
    volatile UINT32 DCHxCONINV;
    
    volatile UINT32 DCHxECON;
    volatile UINT32 DCHxECONCLR;
    volatile UINT32 DCHxECONSET;
    volatile UINT32 DCHxECONINV;
    
    volatile UINT32 DCHxINT;
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
    volatile UINT32 DCHxSPTRCLR;
    volatile UINT32 DCHxSPTRSET;
    volatile UINT32 DCHxSPTRINV;

    volatile UINT32 DCHxDPTR;
    volatile UINT32 DCHxDPTRCLR;
    volatile UINT32 DCHxDPTRSET;
    volatile UINT32 DCHxDPTRINV;

    volatile UINT32 DCHxCSIZ;
    volatile UINT32 DCHxCSIZCLR;
    volatile UINT32 DCHxCSIZSET;
    volatile UINT32 DCHxCSIZINV;

    volatile UINT32 DCHxCPTR;
    volatile UINT32 DCHxCPTRCLR;
    volatile UINT32 DCHxCPTRSET;
    volatile UINT32 DCHxCPTRINV;

    volatile UINT32 DCHxDAT;
    volatile UINT32 DCHxDATCLR;
    volatile UINT32 DCHxDATSET;
    volatile UINT32 DCHxDATINV;

} DMACH_REGS;


#endif /*_DMA_H_*/


