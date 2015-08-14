/********************************************************************
  File Information:
    FileName:       stub_btc.h
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
#ifndef _OCMP_H_
#define _OCMP_H_
////////////////////////////////////////////////////////////////////////////////
#include "system.h"
///////////////////////////////////////////////////////////////////////////////

typedef struct
{
    union
    {
        volatile UINT32 OCxCON;
        volatile __OC1CONbits_t OCxCONbits;
    };
    volatile UINT32 OCxCONCLR;
    volatile UINT32 OCxCONSET;
    volatile UINT32 OCxCONINV;

    volatile UINT32 OCxR;
    volatile UINT32 OCxRCLR;
    volatile UINT32 OCxRSET;
    volatile UINT32 OCxRINV;

    volatile UINT32 OCxRS;
    volatile UINT32 OCxRSCLR;
    volatile UINT32 OCxRSSET;
    volatile UINT32 OCxRSINV;
}
OCMP_REGS;


typedef enum
{
    OCMP_EVENT_DONE
}
OCMP_EVENT;

typedef struct
{
    OCMP_REGS *regs;
//    UART_INT_REGS intRegs;
//    BOOL (*EventHandler) ( UART_EVENT event, const UINT8 * data, const UINT16 dataSize );
//
//    UINT8 *rxBuffer;
//    UINT8 *rxPtr;
//    UINT16 rxSize;
//    UINT16 rxCount;
//    UINT16 pattern;
//    
//    const UINT8 *txBuffer;
//    const UINT8 *txPtr;
//    UINT16 txSize;
//    UINT16 txCount;
}
volatile OCMP_MODULE, *OCMP_HANDLE;


typedef enum
{
    OCMP_MODE_PWM_FAULT_ON = 0b111,
    OCMP_MODE_PWM_FAULT_OFF = 0b110,
    OCMP_MODE_PULSE_CONTINUOUS = 0b101,
    OCMP_MODE_PULSE_SINGLE = 0b100,
    OCMP_MODE_INVERT = 0b011,
    OCMP_MODE_HIGH_TO_LOW = 0b010,
    OCMP_MODE_LOW_TO_HIGH = 0b001,
    OCMP_MODE_DISABLED = 0b000
}
OCMP_MODE;

typedef struct
{
    BOOL (*EventHandler) ( OCMP_EVENT event, const UINT8 * data, const UINT16 size );
    UINT8 dataParity    :2;
    UINT8 stopBits      :2;
    UINT8 flowControl   :1;
}
OCMP_CONFIG;

///////////////////////////////////////////////////////////////////////////////

#define OCMP_MODULE_COUNT             9
//#define OC_INIT_MASK                0b0000000000001000

///////////////////////////////////////////////////////////////////////////////

#define OCMP1                   ocmpModuleocmpModule[0]
#define OCMP2                   ocmpModuleocmpModule[1]
#define OCMP3                   ocmpModuleocmpModule[2]
#define OCMP4                   ocmpModuleocmpModule[3]
#define OCMP5                   ocmpModuleocmpModule[4]
#define OCMP6                   ocmpModuleocmpModule[5]
#define OCMP7                   ocmpModuleocmpModule[6]
#define OCMP8                   ocmpModuleocmpModule[7]
#define OCMP9                   ocmpModuleocmpModule[8]

///////////////////////////////////////////////////////////////////////////////

extern OCMP_MODULE ocmpModule[OCMP_MODULE_COUNT];

///////////////////////////////////////////////////////////////////////////////

BOOL OCMP_Open ( OCMP_HANDLE ocmp, const OCMP_CONFIG *cfg );
BOOL OCMP_Generate ( OCMP_HANDLE ocmp, const UINT8 *data, const UINT16 size );
VOID OCMP_Int ( OCMP_HANDLE ocmp );

//INLINE UINT16 OC_GetCount ( OCMP_HANDLE ocmp )  { return ( ocmp->Count ); }
//INLINE BOOL OC_GetInt ( OCMP_HANDLE ocmp )      { return (( ocmp->intRegs.rxIEC->REG & oc->intRegs.rxMask ) != 0 ); }
INLINE VOID OCMP_DisableInt ( OCMP_HANDLE ocmp )  { }//ocmp->intRegs.rxIEC->CLR = ocmp->intRegs.rxMask; }
INLINE VOID OCMP_EnableInt ( OCMP_HANDLE ocmp )   { }//ocmp->intRegs.rxIEC->SET = ocmp->intRegs.rxMask; }

INLINE VOID OCMP_Suspend ( OCMP_HANDLE ocmp )     { OCMP_DisableInt ( ocmp ); }
INLINE VOID OCMP_Resume ( OCMP_HANDLE ocmp )      { OCMP_EnableInt ( ocmp ); }

////////////////////////////////////////////////////////////////////////////////
#endif
