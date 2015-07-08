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

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <xc.h>
#include <GenericTypeDefs.h>

#define ISR                 __attribute__((interrupt, no_auto_psv))
#define ISRFAST             __attribute__((interrupt, no_auto_psv, shadow))
#define SYSTEM_Halt()       asm volatile ("sdbbp")
#define INLINE              extern inline __attribute__((always_inline))

typedef float   FLOAT;

typedef struct
{
    volatile INT32 REG;
    volatile INT32 CLR;
    volatile INT32 SET;
    volatile INT32 INV;
}
SYSTEM_SFR;

#ifdef _SYSTEM_C_

    #include "time.h"

#endif

////////////////////////////////////////////////////////////////////////////////

#define SYSTEM_GetClock()               200000000ul
#define SYSTEM_GetPeripheralClock()     40000000ul
#define SYSTEM_GetInstructionClock()    SYSTEM_GetClock ()

#if (( SYSTEM_GetClock () / SYSTEM_GetPeripheralClock ()) * SYSTEM_GetPeripheralClock () != SYSTEM_GetClock ())
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

VOID SYSTEM_Initialize ( VOID );
VOID SYSTEM_Idle ( VOID );
VOID SYSTEM_EnableInterrupts ( VOID );
VOID SYSTEM_DisableInterrupts ( VOID );
UINT16 SYSTEM_GetADC ( UINT8 chn );

extern VOID SYS_T1Interrupt ( VOID );
extern VOID SYS_T2Interrupt ( VOID );
extern VOID SYS_T3Interrupt ( VOID );
extern VOID SYS_T4Interrupt ( VOID );
extern VOID SYS_T5Interrupt ( VOID );

////////////////////////////////////////////////////////////////////////////////

#endif
