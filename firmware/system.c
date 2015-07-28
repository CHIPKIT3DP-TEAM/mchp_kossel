////////////////////////////////////////////////////////////////////////////////
#define     _SYSTEM_C_
#include    "system.h"
////////////////////////////////////////////////////////////////////////////////

UINT8 sysIntCount = 1;

////////////////////////////////////////////////////////////////////////////////

VOID SYSTEM_Initialize ( VOID )
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

    PRECON = _PRECON_PREFEN_MASK + 2;               // Prefetch enable, 2 WS 
    
    PB1DIV = 1;                                     // Flash
    PB2DIV = _PB2DIV_ON_MASK + SYSTEM_GetPBDiv ();  // PMP, I2C, UART, SPI
    PB3DIV = _PB3DIV_ON_MASK + SYSTEM_GetPBDiv ();  // ADC, Comp, TMR, OC, IC
    PB4DIV = _PB4DIV_ON_MASK + SYSTEM_GetPBDiv ();  // IO
    PB5DIV = _PB5DIV_ON_MASK;                       // Crypto, RNG, USB, CAN, Eth
    PB7DIV = _PB7DIV_ON_MASK;                       // CPU, DMT
    PB8DIV = 0;                                     // EBI
    
//    FIXME - scan ?
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
    PR1 = SYSTEM_GetPeripheralClock () / 1000;
    IPC1bits.T1IP = 2;
    IFS0bits.T1IF = FALSE;
    IEC0bits.T1IE = TRUE;
    T1CONbits.TON = TRUE;

    PRISS = 0x76543210;
    INTCONSET = _INTCON_MVEC_MASK;
    SYSTEM_EnableInterrupts ();
}

////////////////////////////////////////////////////////////////////////////////

VOID SYSTEM_Idle ( VOID )
{
    // FIXME - activity LED indication ?
    _wait ();
}

////////////////////////////////////////////////////////////////////////////////

VOID SYSTEM_EnableInterrupts ( VOID )
{
    if ( sysIntCount )
        sysIntCount --;
    else
        SYSTEM_Halt ();        
    
    if ( sysIntCount == 0 )
        __builtin_enable_interrupts ();
}

////////////////////////////////////////////////////////////////////////////////

VOID SYSTEM_DisableInterrupts ( VOID )
{
    __builtin_disable_interrupts ();
    
    if ( sysIntCount < 255 )
        sysIntCount ++;
    else
        SYSTEM_Halt ();
}

////////////////////////////////////////////////////////////////////////////////

UINT16 SYS_GetADC ( UINT8 chn )
{
//    return (( &ADC1BUF0 )[chn] );
}

////////////////////////////////////////////////////////////////////////////////
// Application Interrupts
////////////////////////////////////////////////////////////////////////////////

//VOID __ISR ( _TIMER_1_VECTOR, IPL2SRS ) _T1Interrupt ( VOID )
//{
//    IFS0CLR = _IFS0_T1IF_MASK;
//    SYSTEM_T1InterruptHandler ();
//}

////////////////////////////////////////////////////////////////////////////////

VOID __ISR ( _UART1_RX_VECTOR, IPL4SRS ) SYSTEM_Uart1RxInterrupt ( VOID )
{
    IFS3CLR = _IFS3_U1RXIF_MASK;

}

////////////////////////////////////////////////////////////////////////////////
// System Interrupts
////////////////////////////////////////////////////////////////////////////////

VOID _DefaultInterrupt ( VOID )
{
    SYSTEM_Halt ();
}

////////////////////////////////////////////////////////////////////////////////

VOID _general_exception_handler ( UINT32 cause, UINT32 status )
{
    
    
    SYSTEM_Halt ();
    Nop();
    Nop();
}
//////////////////////////////////////////////////////////////////////////////////
//VOID ISR _OscillatorFail ( void )
//{
//    SYSTEM_Halt ();
//    Nop();
//    Nop();
//}
//////////////////////////////////////////////////////////////////////////////////
//VOID ISR _AddressError ( void )
//{
//    SYSTEM_Halt ();
//    Nop();
//    Nop();
//}
//////////////////////////////////////////////////////////////////////////////////
//VOID ISR _StackError ( void )
//{
//    SYSTEM_Halt ();
//    Nop();
//    Nop();
//}
//////////////////////////////////////////////////////////////////////////////////
//VOID ISR _MathError ( void )
//{
//    SYSTEM_Halt ();
//    Nop();
//    Nop();
//}
//////////////////////////////////////////////////////////////////////////////////
