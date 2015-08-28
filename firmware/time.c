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
