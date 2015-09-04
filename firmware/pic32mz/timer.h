#ifndef _TIMER_H_
#define _TIMER_H_
////////////////////////////////////////////////////////////////////////////////
#include "system.h"
///////////////////////////////////////////////////////////////////////////////

typedef struct
{
    union
    {
        volatile UINT32 T1CON;
        volatile __T1CONbits_t T1CONbits;
    };
    volatile UINT32 T1CONCLR;
    volatile UINT32 T1CONSET;
    volatile UINT32 T1CONINV;

    volatile UINT32 TMR1;
    volatile UINT32 TMR1CLR;
    volatile UINT32 TMR1SET;
    volatile UINT32 TMR1INV;

    volatile UINT32 PR1;
    volatile UINT32 PR1CLR;
    volatile UINT32 PR1SET;
    volatile UINT32 PR1INV;
}
TIMER1_REGS;

typedef struct
{
    union
    {
        volatile UINT32 TxCON;
        volatile __T2CONbits_t TxCONbits;
    };
    volatile UINT32 TxCONCLR;
    volatile UINT32 TxCONSET;
    volatile UINT32 TxCONINV;

    volatile UINT32 TMRx;
    volatile UINT32 TMRxCLR;
    volatile UINT32 TMRxSET;
    volatile UINT32 TMRxINV;

    volatile UINT32 PRx;
    volatile UINT32 PRxCLR;
    volatile UINT32 PRxSET;
    volatile UINT32 PRxINV;
}
TIMERx_REGS;

typedef struct
{
    SYSTEM_SFR *tmrIEC;
    SYSTEM_SFR *tmrIFS;
    UINT32 tmrMask;
}
TIMERx_INT_REGS;

typedef struct TIMERx_MODULE *TIMERx_HANDLE;
typedef struct TIMERx_MODULE
{
    TIMERx_REGS *regs;
    TIMERx_INT_REGS intRegs;
    BOOL (*EventHandler) ( TIMERx_HANDLE timer );

}
TIMERx_MODULE;

typedef struct
{
    BOOL (*EventHandler) ( TIMERx_HANDLE timer );
	BOOL use32bit;
    UINT32 period;
}
TIMER_CONFIG;

///////////////////////////////////////////////////////////////////////////////

#define TIMER_MODULE_COUNT          9

///////////////////////////////////////////////////////////////////////////////

//#define TIMER1                      &timer1Module
#define TIMER2                      &timerModule[0]
#define TIMER3                      &timerModule[1]
#define TIMER4                      &timerModule[2]
#define TIMER5                      &timerModule[3]
#define TIMER6                      &timerModule[4]
#define TIMER7                      &timerModule[5]
#define TIMER8                      &timerModule[6]
#define TIMER9                      &timerModule[7]

///////////////////////////////////////////////////////////////////////////////

//extern TIMER1_MODULE timer1Module;
extern TIMERx_MODULE timerModule[TIMER_MODULE_COUNT-1];

///////////////////////////////////////////////////////////////////////////////

BOOL TIMER_Initialize ( TIMERx_HANDLE timer, const TIMER_CONFIG *cfg );
VOID TIMER_Int ( TIMERx_HANDLE timer );

INLINE BOOL TIMER_GetInt ( TIMERx_HANDLE timer ) { return (( timer->intRegs.tmrIEC->REG & timer->intRegs.tmrMask ) != 0 ); }
INLINE VOID TIMER_DisableInt ( TIMERx_HANDLE timer ) { timer->intRegs.tmrIEC->CLR = timer->intRegs.tmrMask; }
INLINE VOID TIMER_EnableInt ( TIMERx_HANDLE timer ) { timer->intRegs.tmrIEC->SET = timer->intRegs.tmrMask; }

////////////////////////////////////////////////////////////////////////////////
#endif