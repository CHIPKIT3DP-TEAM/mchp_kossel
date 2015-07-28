/*******************************************************************************
  Timekeeping and delay routines for 16 / 32 bit devices

  Company:
    Microchip Technology Inc.

  File Name:
    time.c

  Summary:
    Timekeeping and delay routines for 16 / 32 bit devices

  Description:
    Subset of functions to provide system-clock-independend real time keeping
    and delay functionality in natural units (us, ms).
 
*******************************************************************************/
/*******************************************************************************
Copyright (c) 2012 Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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

#define     _TIME_C_
#include    "time.h"

////////////////////////////////////////////////////////////////////////////////

volatile UINT32 time1ms;
static volatile UINT32 timeCycles;

////////////////////////////////////////////////////////////////////////////////
VOID TIME_Initialize ( VOID )
{
    time1ms = 0;
}
////////////////////////////////////////////////////////////////////////////////
VOID TIME_Update ( UINT32 time )
{
    time1ms += time;  
}
////////////////////////////////////////////////////////////////////////////////
VOID TIME_Delay10us ( UINT16 delay )
{
    #if defined ( __C30__ ) || defined ( __XC16__ )
        timeCycles = delay;
        timeCycles *= ( SYS_GetInstructionClock () + 487 ) / 488;
        timeCycles /= 2048;
        Nop ();
    
        if ( timeCycles >= 5 )
        {
            timeCycles -= 5;
            while ( timeCycles -- );
        }       
    #elif defined ( __C32__ ) || defined ( __XC32__ )
// FIXME - reuse Tmr1 in polling mode ?
//        timeCycles = delay;
//        timeCycles *= ( SYSTEM_GetInstructionClock () + 3905 ) / 3906;
//        timeCycles /= 128;
//        if ( timeCycles >= 5 )
//        {
//            timeCycles -= 5;
//            while ( timeCycles -- );
//        }    
    #endif
}
////////////////////////////////////////////////////////////////////////////////
VOID TIME_Delay1ms ( UINT32 delay )
{
    delay += time1ms + 1;
    
    while ((INT32)( delay - time1ms ) < 0 )
    {
        SYSTEM_Idle ();
    }
}
////////////////////////////////////////////////////////////////////////////////
UINT32 TIME_Get1ms ( VOID )
{
    return ( time1ms );
}
////////////////////////////////////////////////////////////////////////////////
BOOL TIME_Elapsed1ms ( UINT32 time )
{
    return ((INT32)( time - time1ms ) < 0 );
}
////////////////////////////////////////////////////////////////////////////////
UINT32 TIME_Passed1ms ( UINT32 time )
{
    return ( time1ms - time );
}
////////////////////////////////////////////////////////////////////////////////
