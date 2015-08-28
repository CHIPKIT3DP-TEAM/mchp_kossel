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
#ifndef _UART_H_
#define _UART_H_
////////////////////////////////////////////////////////////////////////////////
#include "system.h"
///////////////////////////////////////////////////////////////////////////////

typedef struct
{
    union
    {
        volatile UINT32 UxMODE;
        volatile __U1MODEbits_t UxMODEbits;
    };
    volatile UINT32 UxMODECLR;
    volatile UINT32 UxMODESET;
    volatile UINT32 UxMODEINV;

    union
    {
        volatile UINT32 UxSTA;
        volatile __U1STAbits_t UxSTAbits;
    };
    volatile UINT32 UxSTACLR;
    volatile UINT32 UxSTASET;
    volatile UINT32 UxSTAINV;

    volatile UINT32 UxTXREG;
    volatile UINT32 resv0;
    volatile UINT32 resv1;
    volatile UINT32 resv2;

    volatile UINT32 UxRXREG;
    volatile UINT32 resv3;
    volatile UINT32 resv4;
    volatile UINT32 resv5;

    volatile UINT32 UxBRG;
    volatile UINT32 UxBRGCLR;
    volatile UINT32 UxBRGSET;
    volatile UINT32 UxBRGINV;
}
UART_REGS;

typedef struct
{
    SYSTEM_SFR *rxIEC;
    UINT32 rxMask;
    SYSTEM_SFR *txIEC;
    UINT32 txMask;
    SYSTEM_SFR *errorIEC;
    UINT32 errorMask;
}
UART_INT_REGS;

typedef enum
{
    UART_EVENT_SENT             = 0x00,
    UART_EVENT_RECEIVED         = 0x01,
    UART_EVENT_ERROR_OVERFLOW   = 0x02,
    UART_EVENT_ERROR_FRAMING    = 0x04,
    UART_EVENT_ERROR_PARITY     = 0x08
}
UART_EVENT;

typedef struct UART_MODULE *UART_HANDLE;
typedef struct UART_MODULE
{
    UART_REGS *regs;
    UART_INT_REGS intRegs;
    BOOL (*EventHandler) ( UART_HANDLE uart, UART_EVENT event, const UINT8 * data, const UINT16 size );

    UINT8 *rxBuffer;
    UINT8 *rxPtr;
    UINT16 rxSize;
    UINT16 rxCount;
    UINT16 pattern;
    
    const UINT8 *txBuffer;
    const UINT8 *txPtr;
    UINT16 txSize;
    UINT16 txCount;
}
UART_MODULE;

#define UART_PATTERN_NONE       0xFFFF

typedef enum
{
    UART_DATA_8_PARITY_NONE = 0b00,
    UART_DATA_8_PARITY_EVEN = 0b01,
    UART_DATA_8_PARITY_ODD = 0b10,
    UART_DATA_9_PARITY_NONE = 0b11,
}
UART_DATA_PARITY;

typedef struct
{
    BOOL (*EventHandler) ( UART_HANDLE uart, UART_EVENT event, const UINT8 * data, const UINT16 size );
    UINT32 baudrate;
    UINT8 dataParity    :2;
    UINT8 stopBits      :2;
    UINT8 flowControl   :1;
}
UART_CONFIG;

///////////////////////////////////////////////////////////////////////////////

#define UART_MODULE_COUNT           6
#define UART_UXMODE_INIT_MASK       0b0000000000001000
#define UART_UXSTA_INIT_MASK        0b0000000000000000
#define UART_UXSTA_ERROR_MASK       0b0000000000001110

///////////////////////////////////////////////////////////////////////////////

#define UART1                       &uartModule[0]
#define UART2                       &uartModule[1]
#define UART3                       &uartModule[2]
#define UART4                       &uartModule[3]
#define UART5                       &uartModule[4]
#define UART6                       &uartModule[5]

///////////////////////////////////////////////////////////////////////////////

extern UART_MODULE uartModule[UART_MODULE_COUNT];

///////////////////////////////////////////////////////////////////////////////

BOOL UART_Initialize ( UART_HANDLE uart, const UART_CONFIG *cfg );
BOOL UART_Transmit ( UART_HANDLE uart, const UINT8 *data, const UINT16 size );
BOOL UART_Receive ( UART_HANDLE uart, UINT8 *data, const UINT16 size );
BOOL UART_Discard ( UART_HANDLE uart, const UINT16 size );
VOID UART_RxInt ( UART_HANDLE uart );
VOID UART_TxInt ( UART_HANDLE uart );
VOID UART_ErrorInt ( UART_HANDLE uart );

INLINE UINT16 UART_GetRxCount ( UART_HANDLE uart )  { return ( uart->rxCount ); }
INLINE BOOL UART_GetRxInt ( UART_HANDLE uart )      { return (( uart->intRegs.rxIEC->REG & uart->intRegs.rxMask ) != 0 ); }
INLINE VOID UART_DisableRxInt ( UART_HANDLE uart )  { uart->intRegs.rxIEC->CLR = uart->intRegs.rxMask; }
INLINE VOID UART_EnableRxInt ( UART_HANDLE uart )   { uart->intRegs.rxIEC->SET = uart->intRegs.rxMask; }

INLINE UINT16 UART_GetTxCount ( UART_HANDLE uart )  { return ( uart->txCount ); }
INLINE BOOL UART_GetTxInt ( UART_HANDLE uart )      { return (( uart->intRegs.txIEC->REG & uart->intRegs.txMask ) != 0 ); }
INLINE VOID UART_DisableTxInt ( UART_HANDLE uart )  { uart->intRegs.txIEC->CLR = uart->intRegs.txMask; }
INLINE VOID UART_EnableTxInt ( UART_HANDLE uart )   { uart->intRegs.txIEC->SET = uart->intRegs.txMask; }

INLINE VOID UART_SuspendRx ( UART_HANDLE uart )     { UART_DisableRxInt ( uart ); }
INLINE VOID UART_ResumeRx ( UART_HANDLE uart )      { UART_EnableRxInt ( uart ); }

////////////////////////////////////////////////////////////////////////////////
#endif