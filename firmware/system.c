/******************************************************************************

File Name:       system.c
Dependencies:    USB Embedded Host library, MFI library
Processor:       PIC32
Company:         Microchip Technology, Inc.

Copyright 2009-2012 Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

 *******************************************************************************/
#define     SYSTEM_C
#include    "system.h"

////////////////////////////////////////////////////////////////////////////////

UINT8 sysIntCount = 0;

////////////////////////////////////////////////////////////////////////////////

VOID SYS_Initialize ( VOID )
{
    LATA   = 0b0000000000000000;
    TRISA  = 0b1000010000110000;
    ANSELA = 0b0000010000000000;

    LATB   = 0b0000000000100000;
    TRISB  = 0b1011011100011111;
    ANSELB = 0b0011001000000000;

    LATC   = 0b0000000000001000;
    TRISC  = 0b0000000000000110;
    ANSELC = 0b0000000000000100;

    LATD   = 0b0000001000000000;
    TRISD  = 0b0100000000100000;
    ANSELD = 0b0000000000000000;

    LATE   = 0b0000000000000000;
    TRISE  = 0b0000000000000000;
    ANSELE = 0b0000000000000000;

    LATF   = 0b0000000000000000;
    TRISF  = 0b0000000000101111;
    ANSELF = 0b0000000000000000;

    LATG   = 0b0000000000000000;
    TRISG  = 0b0000000110000000;
    ANSELG = 0b0000000000000000;

    SYS_LedOn ( SYS_LED_SYSTEM );
    while ( OSCCONbits.SLOCK == 0 )
    {
        Nop ( );
    }
    SYS_LedOff ( SYS_LED_SYSTEM );

    PB1DIV = 127;
    PB2DIV = _PB2DIV_ON_MASK + SYS_GetClock () / SYS_GetPeripheralClock () - 1;
    PB3DIV = _PB3DIV_ON_MASK + SYS_GetClock () / SYS_GetPeripheralClock () - 1;
    PB4DIV = _PB4DIV_ON_MASK + SYS_GetClock () / SYS_GetPeripheralClock () - 1;
    PB5DIV = _PB5DIV_ON_MASK;
    PB7DIV = _PB5DIV_ON_MASK;
    PB8DIV = 0;
    
//    AD1CON1 = 0b1000011011100100;
//    AD1CON2 = 0b0000010000010000;
//    AD1CON3 = 0b0001111100000000 | (( SYS_GetPeripheralClock () + 10000000 ) / 20000000 ); // 67..133 ns AD clock
//    AD1CON4 = 0b0000000000000000;
//    AD1CHS0 = 0b0000000000000000;
//    AD1CSSH = 0b0000000000000000;
//    AD1CSSL = 0b0111000000110000;

    TIME_Initialize ();

    TMR1 = 0;
    T1CON = 0;
    PR1 = SYS_GetPeripheralClock () / 1000;
    T1CONbits.TON = TRUE;
    IPC1bits.T1IP = 2;
    IFS0bits.T1IF = FALSE;
    IEC0bits.T1IE = TRUE;

    SYS_IntEnable ();
}

////////////////////////////////////////////////////////////////////////////////

VOID SYS_Idle ( VOID )
{
    LATGCLR = _LATG_LATG15_MASK;
    asm volatile ("wait");
    LATGSET = _LATG_LATG15_MASK;
}

////////////////////////////////////////////////////////////////////////////////

VOID SYS_IntEnable ( VOID )
{
    if ( sysIntCount )
        sysIntCount --;
    else
        SYSTEM_Halt ();        
    
    if ( sysIntCount == 0 )
        asm volatile("ei");
}

////////////////////////////////////////////////////////////////////////////////

VOID SYS_IntDisable ( VOID )
{
    asm volatile("di");
    
    if ( sysIntCount < 255 )
        sysIntCount ++;
    else
        SYSTEM_Halt ();
}

////////////////////////////////////////////////////////////////////////////////

VOID SYS_LedOn ( UINT8 led )
{
    LATB |= ( led & 0b1111 ) << 6;
}

////////////////////////////////////////////////////////////////////////////////

VOID SYS_LedOff ( UINT8 led )
{
    LATB &= (( led ^ 0b1111 ) & 0b1111 ) << 6;
}

////////////////////////////////////////////////////////////////////////////////

UINT16 SYS_GetADC ( UINT8 chn )
{
    return (( &ADC1BUF0 )[chn] );
}

////////////////////////////////////////////////////////////////////////////////

VOID SYS_SetPWM ( UINT8 chn, UINT16 val )
{
//    switch ( chn )
//    {
//        case 4:
//            OC4RS = val / SYS_PWM_FREQ_MULTIPLIER;
//            break;
//
//        case 5:
//            OC5RS = val / SYS_PWM_FREQ_MULTIPLIER;
//            break;
//    }
}

////////////////////////////////////////////////////////////////////////////////

//VOID ISR _USB1Interrupt ( VOID )
//{
//    USBDeviceTasks ();
//}

////////////////////////////////////////////////////////////////////////////////

VOID ISR _T1Interrupt ( VOID )
{
    IFS0bits.T1IF = FALSE;
    SYS_T1Interrupt ();
}

////////////////////////////////////////////////////////////////////////////////
// Section: System Interrupts
////////////////////////////////////////////////////////////////////////////////

VOID ISR _DefaultInterrupt ( void )
{
    SYSTEM_Halt ();
    Nop();
    Nop();
}
////////////////////////////////////////////////////////////////////////////////
VOID ISR _OscillatorFail ( void )
{
    SYSTEM_Halt ();
    Nop();
    Nop();
}
////////////////////////////////////////////////////////////////////////////////
VOID ISR _AddressError ( void )
{
    SYSTEM_Halt ();
    Nop();
    Nop();
}
////////////////////////////////////////////////////////////////////////////////
VOID ISR _StackError ( void )
{
    SYSTEM_Halt ();
    Nop();
    Nop();
}
////////////////////////////////////////////////////////////////////////////////
VOID ISR _MathError ( void )
{
    SYSTEM_Halt ();
    Nop();
    Nop();
}
////////////////////////////////////////////////////////////////////////////////