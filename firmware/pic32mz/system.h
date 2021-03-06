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
#ifndef _SYSTEM_H_
#define _SYSTEM_H_
////////////////////////////////////////////////////////////////////////////////
#include <xc.h>
#include <GenericTypeDefs.h>
////////////////////////////////////////////////////////////////////////////////

#define SYSTEM_Halt()               __builtin_software_breakpoint ()
#define INLINE                      extern inline __attribute__((always_inline))
#define PACKED                      __attribute__((packed))
#define SYSTEM_ToPhysical( x )      ((UINT32)x & 0x1FFFFFFF )
#define SYSTEM_ToVirtual( x )       ((VOID*)( x | 0xA0000000 ))

////////////////////////////////////////////////////////////////////////////////

typedef float   FLOAT;

typedef struct
{
    volatile INT32 REG;
    volatile INT32 CLR;
    volatile INT32 SET;
    volatile INT32 INV;
}
SYSTEM_SFR;

////////////////////////////////////////////////////////////////////////////////

#ifdef _SYSTEM_C_

    #include <sys/attribs.h>
    #include "time.h"
    #include "uart.h"

    #pragma config FMIIEN = OFF             // Ethernet RMII/MII Enable (RMII Enabled)
    #pragma config FETHIO = OFF             // Ethernet I/O Pin Select (Alternate Ethernet I/O)
    #pragma config PGL1WAY = OFF            // Permission Group Lock One Way Configuration (Allow multiple reconfigurations)
    #pragma config PMDL1WAY = OFF           // Peripheral Module Disable Configuration (Allow multiple reconfigurations)
    #pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration (Allow multiple reconfigurations)
    #pragma config FUSBIDIO = OFF           // USB USBID Selection (Controlled by Port Function)
    #pragma config FPLLIDIV = DIV_3         // System PLL Input Divider (3x Divider)
    #pragma config FPLLRNG = RANGE_5_10_MHZ // System PLL Input Range (5-10 MHz Input)
    #pragma config FPLLICLK = PLL_POSC      // System PLL Input Clock Selection (POSC is input to the System PLL)
    #pragma config FPLLMULT = MUL_50        // System PLL Multiplier (PLL Multiply by 50)
    #pragma config FPLLODIV = DIV_2         // System PLL Output Clock Divider (2x Divider)
    #pragma config UPLLFSEL = FREQ_24MHZ    // USB PLL Input Frequency Selection (USB PLL input is 24 MHz)
    #pragma config FNOSC = SPLL             // Oscillator Selection Bits (System PLL)
    #pragma config DMTINTV = WIN_127_128    // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
    #pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disable SOSC)
    #pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
    #pragma config POSCMOD = EC             // Primary Oscillator Configuration (External clock mode)
    #pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
    #pragma config FCKSM = CSECME           // Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Enabled)
    #pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
    #pragma config WDTSPGM = STOP           // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
    #pragma config WINDIS = NORMAL          // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
    #pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled)
    #pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window size is 25%)
    #pragma config DMTCNT = DMT31           // Deadman Timer Count Selection (2^31 (2147483648))
    #pragma config FDMTEN = OFF             // Deadman Timer Enable (Deadman Timer is disabled)
    #pragma config DEBUG = ON               // Background Debugger Enable (Debugger is disabled)
    #pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
    #pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (Communicate on PGEC2/PGED2)
    #pragma config TRCEN = OFF              // Trace Enable (Trace features in the CPU are disabled)
    #pragma config BOOTISA = MIPS32         // Boot ISA Selection (Boot code and Exception code is MIPS32)
    #pragma config FECCCON = OFF_UNLOCKED   // Dynamic Flash ECC Configuration (ECC and Dynamic ECC are disabled (ECCCON bits are writable))
    #pragma config FSLEEP = OFF             // Flash Sleep Mode (Flash is powered down when the device is in Sleep mode)
    #pragma config DBGPER = PG_ALL          // Debug Mode CPU Access Permission (Allow CPU access to Permission Group 2 permission regions)
    #pragma config SMCLR = MCLR_NORM        // Soft Master Clear Enable bit (MCLR pin generates a normal system Reset)
    #pragma config SOSCGAIN = GAIN_1X       // Secondary Oscillator Gain Control bits (1x gain setting)
    #pragma config SOSCBOOST = OFF          // Secondary Oscillator Boost Kick Start Enable bit (Normal start of the oscillator)
    #pragma config POSCGAIN = GAIN_1X       // Primary Oscillator Gain Control bits (1x gain setting)
    #pragma config POSCBOOST = OFF          // Primary Oscillator Boost Kick Start Enable bit (Normal start of the oscillator)
    #pragma config EJTAGBEN = NORMAL        // EJTAG Boot (Normal EJTAG functionality)

    #pragma config CP    = OFF              // Code Protect

#endif

////////////////////////////////////////////////////////////////////////////////

#define SYSTEM_GetClock()               200000000ul
#define SYSTEM_GetPeripheralClock()     40000000ul
#define SYSTEM_GetInstructionClock()    SYSTEM_GetClock ()
#define SYSTEM_GetPBDiv()               ( SYSTEM_GetClock () / SYSTEM_GetPeripheralClock () - 1 )

#if (( SYSTEM_GetClock () / SYSTEM_GetPeripheralClock ()) * SYSTEM_GetPeripheralClock () != SYSTEM_GetClock ())
    #error Uneven Peripheral Clock divider
#endif

////////////////////////////////////////////////////////////////////////////////

#define SYSTEM_LED1On()         LATGSET = 1<<6
#define SYSTEM_LED2On()         LATDSET = 1<<4
#define SYSTEM_LED3On()         LATBSET = 1<<11
#define SYSTEM_LED4On()         LATGSET = 1<<15

#define SYSTEM_LED1Off()        LATGCLR = 1<<6
#define SYSTEM_LED2Off()        LATDCLR = 1<<4
#define SYSTEM_LED3Off()        LATBCLR = 1<<11
#define SYSTEM_LED4Off()        LATGCLR = 1<<15

#define SYSTEM_LED1Toggle()     LATGINV = 1<<6
#define SYSTEM_LED2Toggle()     LATDINV = 1<<4
#define SYSTEM_LED3Toggle()     LATBINV = 1<<11
#define SYSTEM_LED4Toggle()     LATGINV = 1<<15

#define SYS_AD_BED              4
#define SYS_AD_12V              5
#define SYS_AD_THERM0           12
#define SYS_AD_THERM1           13
#define SYS_AD_THERM2           14

#define UART_PC                 UART4
#define UART_PC_BAUDRATE        250000

#define UART_BUS                UART1
#define UART_BUS_BAUDRATE       20000

#define MAIN_I2C                I2C4

////////////////////////////////////////////////////////////////////////////////

VOID SYSTEM_Initialize ( VOID );
VOID SYSTEM_Idle ( VOID );
VOID SYSTEM_EnableInterrupts ( VOID );
VOID SYSTEM_DisableInterrupts ( VOID );
UINT16 SYSTEM_GetADC ( UINT8 chn );

extern VOID SYSTEM_T1InterruptHandler ( VOID );

////////////////////////////////////////////////////////////////////////////////

#endif
