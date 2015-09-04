#define _TIMER_C_
#include <sys/attribs.h>
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
	timer->regs->TxCONbits.T32 = cfg->use32bit;
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

void __ISR_AT_VECTOR(_TIMER_2_VECTOR, IPL7AUTO) _T2ISR(void)
{
	
}

void __ISR_AT_VECTOR(_TIMER_3_VECTOR, IPL7AUTO) _T3ISR(void)
{
	TIMERx_Int(TIMER2);
}

void __ISR_AT_VECTOR(_TIMER_4_VECTOR, IPL7AUTO) _T4ISR(void)
{
	TIMERx_Int(TIMER3);
}

void __ISR_AT_VECTOR(_TIMER_5_VECTOR, IPL7AUTO) _T5ISR(void)
{
	TIMERx_Int(TIMER4);
}

void __ISR_AT_VECTOR(_TIMER_6_VECTOR, IPL7AUTO) _T6ISR(void)
{
	TIMERx_Int(TIMER5);
}

void __ISR_AT_VECTOR(_TIMER_7_VECTOR, IPL7AUTO) _T7ISR(void)
{
	TIMERx_Int(TIMER6);
}

void __ISR_AT_VECTOR(_TIMER_8_VECTOR, IPL7AUTO) _T8ISR(void)
{
	TIMERx_Int(TIMER7);
}

void __ISR_AT_VECTOR(_TIMER_9_VECTOR, IPL7AUTO) _T9ISR(void)
{
	TIMERx_Int(TIMER8);
}

