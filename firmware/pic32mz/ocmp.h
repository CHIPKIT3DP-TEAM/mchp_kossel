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
