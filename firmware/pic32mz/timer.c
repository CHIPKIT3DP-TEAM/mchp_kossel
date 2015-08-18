#define _TIMER_C_
#include "timer.h"

TIMERx_MODULE timerModule[TIMER_MODULE_COUNT-1] = 
{
    {   // Timer2
        (TIMERx_REGS*) _TMR2_BASE_ADDRESS,
        {
            (SYSTEM_SFR*) &IEC0, (SYSTEM_SFR*) &IFS0, _IEC0_T2IE_MASK,
        }
    },
    {   // Timer3
        (TIMERx_REGS*) _TMR3_BASE_ADDRESS,
        {
            (SYSTEM_SFR*) &IEC0, (SYSTEM_SFR*) &IFS0, _IEC0_T3IE_MASK,
        }
    },
    {   // Timer4
        (TIMERx_REGS*) _TMR4_BASE_ADDRESS,
        {
            (SYSTEM_SFR*) &IEC0, (SYSTEM_SFR*) &IFS0, _IEC0_T4IE_MASK,
        }
    },
    {   // Timer5
        (TIMERx_REGS*) _TMR5_BASE_ADDRESS,
        {
            (SYSTEM_SFR*) &IEC0, (SYSTEM_SFR*) &IFS0, _IEC0_T5IE_MASK,
        }
    },
    {   // Timer6
        (TIMERx_REGS*) _TMR6_BASE_ADDRESS,
        {
            (SYSTEM_SFR*) &IEC0, (SYSTEM_SFR*) &IFS0, _IEC0_T6IE_MASK,
        }
    },
    {   // Timer7
        (TIMERx_REGS*) _TMR7_BASE_ADDRESS,
        {
            (SYSTEM_SFR*) &IEC1, (SYSTEM_SFR*) &IFS1, _IEC1_T7IE_MASK,
        }
    },
    {   // Timer8
        (TIMERx_REGS*) _TMR8_BASE_ADDRESS,
        {
            (SYSTEM_SFR*) &IEC1, (SYSTEM_SFR*) &IFS1, _IEC1_T8IE_MASK,
        }
    },
    {   // Timer9
        (TIMERx_REGS*) _TMR9_BASE_ADDRESS,
        {
            (SYSTEM_SFR*) &IEC1, (SYSTEM_SFR*) &IFS1, _IEC1_T9IE_MASK,
        }
    },
};

static const unsigned short TMR_PRESCALERS[] = {1,2,4,8,16,32,64,256};

BOOL TIMERx_Initialize ( TIMERx_HANDLE timer, const TIMER_CONFIG *cfg )
{
    int i;
    unsigned long prVal;
    // TODO: check timer for validity
    
    TIMER_DisableInt ( timer );
    
    timer->EventHandler = cfg->EventHandler;
    
    // Determine the configuration that will be closest to desired resolution
    for (i = 0; i < 8; i++)
    {
        prVal = (SYSTEM_GetPeripheralClock () / TMR_PRESCALERS[i]) / cfg->period;
        if (prVal <= 65535) // Can be represented in 16 bits
            break;
    }
    if (i >= 9) // We could not find a value. Go to 32-bit mode
    {
        timer->regs->TxCONbits.T32 = 1;
    }
    else
    {
        timer->regs->TxCONbits.T32 = 0;
    }
    timer->regs->PRx = prVal;
    timer->regs->TMRx = 0;
    
    TIMER_EnableInt ( timer );
 
    timer->regs->TxCONbits.ON = 1;
    
    return TRUE;
}

void TIMERx_Int ( TIMERx_HANDLE timer )
{
//    timer->intRegs.tmrIFS->CLR = timer->intRegs.tmrMask;
    if ( timer->EventHandler != NULL )
    {
        timer->EventHandler(timer);
    }
}
