////////////////////////////////////////////////////////////////////////////////
//
//
//
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
    CNPUA  = 0b0000000000000000;
    
    LATB   = 0b0000000000100000;
    TRISB  = 0b1011011100011111;
    ANSELB = 0b0011001000000000;
    CNPUB  = 0b1000010100000011;
    
    LATC   = 0b0000000000001000;
    TRISC  = 0b0000000000000110;
    ANSELC = 0b0000000000000100;
    CNPUC  = 0b0000000000000000;

    LATD   = 0b1000001000000000;
    TRISD  = 0b0100000000100000;
    ANSELD = 0b0000000000000000;
    CNPUD  = 0b0100000000000000;

    LATE   = 0b0000000000000000;
    TRISE  = 0b0000000000000000;
    ANSELE = 0b0000000000000000;
    CNPUE  = 0b0000000000000000;

    LATF   = 0b0000000000000000;
    TRISF  = 0b0000000000101111;
    ANSELF = 0b0000000000000000;
    CNPUE  = 0b0000000000101101;

    LATG   = 0b0000000000000010;
    TRISG  = 0b0000000110000000;
    ANSELG = 0b0000000000000000;
    CNPUG  = 0b0000000000000000;

    PRECON = _PRECON_PREFEN_MASK + 2;               // Prefetch enable, 2 WS 
    
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    {
        PB1DIV = 1;                                     // Flash
        PB2DIV = _PB2DIV_ON_MASK + SYSTEM_GetPBDiv ();  // PMP, I2C, UART, SPI
        PB3DIV = _PB3DIV_ON_MASK + SYSTEM_GetPBDiv ();  // ADC, Comp, TMR, OC, IC
        PB4DIV = _PB4DIV_ON_MASK + SYSTEM_GetPBDiv ();  // IO
        PB5DIV = _PB5DIV_ON_MASK;                       // Crypto, RNG, USB, CAN, Eth
        PB7DIV = _PB7DIV_ON_MASK;                       // CPU, DMT
        PB8DIV = 0;                                     // EBI
    }
    SYSKEY = 0;
    
//    FIXME - scan ?
//    AD1CON1 = 0b1000011011100100;
//    AD1CON2 = 0b0000010000010000;
//    AD1CON3 = 0b0001111100000000 | (( SYS_GetPeripheralClock () + 10000000 ) / 20000000 ); // 67..133 ns AD clock
//    AD1CON4 = 0b0000000000000000;
//    AD1CHS0 = 0b0000000000000000;
//    AD1CSSH = 0b0000000000000000;
//    AD1CSSL = 0b0111000000110000;

    U4RXR = 0b1011; // RF2
    SDI2R = 0b0100; //RF0
    U1RXR = 0b1011; //RD14
    
    RPF8R = 0b0010; // U4TX
    RPD0R = 0b1100; // OC1
    RPD1R = 0b1011; // OC2
    RPD2R = 0b1011; // OC3
    RPD3R = 0b1011; // OC4
    RPG9R = 0b1101; // OC9
    RPD11R = 0b0110; // SDO2
    RPD15R = 0b0001; // U1TX

    TIME_Initialize ();

    TMR1 = 0;
    T1CON = 0;
    PR1 = SYSTEM_GetPeripheralClock () / 1000;
    IPC1bits.T1IP = 2;
    IFS0bits.T1IF = FALSE;
    IEC0bits.T1IE = TRUE;
    T1CONbits.TON = TRUE;

    IPC28bits.U1EIP = 3;
    IPC28bits.U1RXIP = 4;
    IPC28bits.U1TXIP = 3;
    
    IPC42bits.U4EIP = 3;
    IPC42bits.U4RXIP = 4;
    IPC43bits.U4TXIP = 3;

    IPC43bits.I2C4MIP = 1;
    IEC5bits.I2C4MIE = TRUE;
    
    PRISS = 0x76543210;
    INTCONSET = _INTCON_MVEC_MASK;
    SYSTEM_EnableInterrupts ();
}

////////////////////////////////////////////////////////////////////////////////

VOID SYSTEM_Idle ( VOID )
{
    SYSTEM_LED4Off ();
    _nop ();
    _wait ();
    SYSTEM_LED4On ();
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
    return (( &ADCDATA0 )[chn] );
}

////////////////////////////////////////////////////////////////////////////////
// Application Interrupts
////////////////////////////////////////////////////////////////////////////////

VOID __ISR_AT_VECTOR ( _TIMER_1_VECTOR, IPL2SRS ) SYSTEM_Timer1Interrupt ( VOID )
{
    IFS0CLR = _IFS0_T1IF_MASK;
    SYSTEM_T1InterruptHandler ();
}

////////////////////////////////////////////////////////////////////////////////

VOID __ISR_AT_VECTOR ( _UART1_RX_VECTOR, IPL4SRS ) SYSTEM_UART1RxInterrupt ( VOID )
{
    IFS3CLR = _IFS3_U1RXIF_MASK;
    UART_RxInt ( UART1 );
}

////////////////////////////////////////////////////////////////////////////////

VOID __ISR_AT_VECTOR ( _UART1_TX_VECTOR, IPL3SRS ) SYSTEM_UART1TxInterrupt ( VOID )
{
    IFS3CLR = _IFS3_U1TXIF_MASK;
    UART_TxInt ( UART1 );
}

////////////////////////////////////////////////////////////////////////////////

VOID __ISR_AT_VECTOR ( _UART1_FAULT_VECTOR, IPL3SRS ) SYSTEM_UART1ErrorInterrupt ( VOID )
{
    IFS3CLR = _IFS3_U1EIF_MASK;
    UART_ErrorInt ( UART1 );
}

////////////////////////////////////////////////////////////////////////////////

VOID __ISR_AT_VECTOR ( _UART4_RX_VECTOR, IPL4SRS ) SYSTEM_UART4RxInterrupt ( VOID )
{
    IFS3CLR = _IFS5_U4RXIF_MASK;
    UART_RxInt ( UART4 );
}

////////////////////////////////////////////////////////////////////////////////

VOID __ISR_AT_VECTOR ( _UART4_TX_VECTOR, IPL3SRS ) SYSTEM_UART4TxInterrupt ( VOID )
{
    IFS3CLR = _IFS5_U4TXIF_MASK;
    UART_TxInt ( UART4 );
}

////////////////////////////////////////////////////////////////////////////////

VOID __ISR_AT_VECTOR ( _UART4_FAULT_VECTOR, IPL3SRS ) SYSTEM_UART4ErrorInterrupt ( VOID )
{
    IFS3CLR = _IFS5_U4EIF_MASK;
    UART_ErrorInt ( UART4 );
}

////////////////////////////////////////////////////////////////////////////////

VOID __ISR ( _I2C4_MASTER_VECTOR, IPL1SRS ) SYSTEM_I2C4MasterInterrupt ( VOID )
{
    // Formal handler to support wake up from Idle
    IFS5CLR = _IFS5_I2C4MIF_MASK;
}

////////////////////////////////////////////////////////////////////////////////
// System Interrupts
////////////////////////////////////////////////////////////////////////////////

// overloading doesn't work, use system-defined
//VOID _DefaultInterrupt ( VOID )
//{
//    SYSTEM_Halt ();
//}

////////////////////////////////////////////////////////////////////////////////

VOID _general_exception_handler ( UINT32 cause, UINT32 status )
{
    SYSTEM_Halt ();
    Nop();
    Nop();
}
////////////////////////////////////////////////////////////////////////////////
