/*
    This file is part of Repetier-Firmware.

    Repetier-Firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Repetier-Firmware is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Repetier-Firmware.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef SYSTEM_H
#define SYSTEM_H

#include <xc.h>
#include <GenericTypeDefs.h>
#include <stdbool.h>

#define ISR                 __attribute__((interrupt, no_auto_psv))
#define ISRFAST             __attribute__((interrupt, no_auto_psv, shadow))
#define SYSTEM_Halt()       asm volatile ("sdbbp")
#define INLINE              extern inline __attribute__((always_inline))

typedef float   FLOAT;

#ifdef SYSTEM_C

    #include "time.h"

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
    #pragma config UPLLFSEL = FREQ_24MHZ    // USB PLL Input Frequency Selection (USB PLL input is 24 MHz)
    #pragma config UPLLEN = ON              // USB PLL Enable (USB PLL is enabled)
    #pragma config FNOSC = SPLL             // Oscillator Selection Bits (System PLL)
    #pragma config DMTINTV = WIN_127_128    // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
    #pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disable SOSC)
    #pragma config IESO = ON                // Internal/External Switch Over (Enabled)
    #pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)
    #pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
    #pragma config FCKSM = CSECME           // Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Enabled)
    #pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
    #pragma config WDTSPGM = STOP           // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
    #pragma config WINDIS = NORMAL          // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
    #pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled)
    #pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window size is 25%)
    #pragma config FDMTEN = OFF             // Deadman Timer Enable (Deadman Timer is disabled)
    #pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
    #pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
    #pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (Communicate on PGEC2/PGED2)
    #pragma config TRCEN = OFF              // Trace Enable (Trace features in the CPU are disabled)
    #pragma config BOOTISA = MIPS32         // Boot ISA Selection (Boot code and Exception code is MIPS32)
    #pragma config FECCCON = OFF_UNLOCKED   // Dynamic Flash ECC Configuration (ECC and Dynamic ECC are disabled (ECCCON bits are writable))
    #pragma config FSLEEP = OFF             // Flash Sleep Mode (Flash is powered down when the device is in Sleep mode)
    #pragma config DBGPER = ALLOW_PG2       // Debug Mode CPU Access Permission (Allow CPU access to Permission Group 2 permission regions)
    #pragma config EJTAGBEN = NORMAL        // EJTAG Boot (Normal EJTAG functionality)

    #ifdef __DEBUG
        #pragma config CP    = OFF       // Code Protect
    #else
        #pragma config CP    = ON        // Code Protect
    #endif

#endif

typedef union
{
    struct
    {
        INT16 x;
        INT16 y;
        INT16 z;
    };
    struct
    {
        INT16 u;
        INT16 v;
        INT16 w;
    };
}
VECTOR_INT;

typedef union
{
    struct
    {
        FLOAT x;
        FLOAT y;
        FLOAT z;
    };
    struct
    {
        FLOAT u;
        FLOAT v;
        FLOAT w;
    };
}
VECTOR_FLOAT;

typedef volatile unsigned int SFR;

////////////////////////////////////////////////////////////////////////////////

#define SYS_GetClock()               200000000ul
#define SYS_GetPeripheralClock()     40000000ul
#define SYS_GetInstructionClock()    SYS_GetClock ()

#if (( SYS_GetClock () / SYS_GetPeripheralClock ()) * SYS_GetPeripheralClock () != SYS_GetClock ())
    #error Uneven Peripheral Clock divider
#endif

////////////////////////////////////////////////////////////////////////////////

#define SYS_LED_SYSTEM           0b0001
#define SYS_LED_1                0b0010
#define SYS_LED_2                0b0100
#define SYS_LED_3                0b1000

#define SYS_AD_BED               4
#define SYS_AD_12V               5
#define SYS_AD_THERM0            12
#define SYS_AD_THERM1            13
#define SYS_AD_THERM2            14

////////////////////////////////////////////////////////////////////////////////

VOID SYS_Initialize ( VOID );
VOID SYS_Idle ( VOID );
VOID SYS_IntEnable ( VOID );
VOID SYS_IntDisable ( VOID );
VOID SYS_LedOn ( UINT8 led );
VOID SYS_LedOff ( UINT8 led );
UINT16 SYS_GetADC ( UINT8 chn );
VOID SYS_SetPWM ( UINT8 chn, UINT16 val );
VOID SYS_SetTimerPeriod ( UINT8 module, UINT16 val );
VOID SYS_EnableTimerInterrupt ( UINT8 module );
VOID SYS_DisableTimerInterrupt ( UINT8 module );

extern VOID SYS_T1Interrupt ( VOID );
extern VOID SYS_T2Interrupt ( VOID );
extern VOID SYS_T3Interrupt ( VOID );
extern VOID SYS_T4Interrupt ( VOID );
extern VOID SYS_T5Interrupt ( VOID );

////////////////////////////////////////////////////////////////////////////////

#endif