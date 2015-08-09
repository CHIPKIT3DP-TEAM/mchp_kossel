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
#define _OCMP_C_
#include "ocmp.h"
////////////////////////////////////////////////////////////////////////////////

OCMP_MODULE ocmpModule[OCMP_MODULE_COUNT] =
{
    {
        (OCMP_REGS*) _OCMP1_BASE_ADDRESS,
    },
    {
        (OCMP_REGS*) _OCMP2_BASE_ADDRESS,
    },
    {
        (OCMP_REGS*) _OCMP3_BASE_ADDRESS,
    },
    {
        (OCMP_REGS*) _OCMP4_BASE_ADDRESS,
    },
    {
        (OCMP_REGS*) _OCMP5_BASE_ADDRESS,
    },
    {
        (OCMP_REGS*) _OCMP6_BASE_ADDRESS,
    },
    {
        (OCMP_REGS*) _OCMP7_BASE_ADDRESS,
    },
    {
        (OCMP_REGS*) _OCMP8_BASE_ADDRESS,
    },
    {
        (OCMP_REGS*) _OCMP9_BASE_ADDRESS,
    },
};

////////////////////////////////////////////////////////////////////////////////

BOOL OCMP_Open ( OCMP_HANDLE ocmp, const OCMP_CONFIG *cfg )
{
    // OCMP_DisableInt ( ocmp );

    // TODO
    
    return ( TRUE );
}

////////////////////////////////////////////////////////////////////////////////

BOOL OCMP_Generate ( OCMP_HANDLE ocmp, const UINT8 *data, const UINT16 size )
{
    // TODO
    
    return ( TRUE );
}

////////////////////////////////////////////////////////////////////////////////

VOID OCMP_Int ( OCMP_HANDLE ocmp )
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////
