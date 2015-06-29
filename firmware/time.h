/*******************************************************************************
  Timekeeping and delay routines for 16 / 32 bit devices definitions header

  Company:
    Microchip Technology Inc.

  File Name:
    time.h

  Summary:
    Timekeeping and delay routines for 16 / 32 bit devices definitions header

  Description:
    Subset of functions to provide system-clock-independend real time keeping
    and delay functionality in natural units (us, ms).
 
*******************************************************************************/
// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

#ifndef _TIME_H_
#define _TIME_H_

#include "system.h"

VOID TIME_Initialize ( VOID );
VOID TIME_Task ( UINT16 time );
VOID TIME_Delay10us( UINT16 time );
VOID TIME_Delay1ms ( UINT16 time );
UINT16 TIME_Get1ms ( VOID );
UINT16 TIME_Get100ms ( VOID );
BOOL TIME_Elapsed1ms ( UINT16 time );
BOOL TIME_Elapsed100ms ( UINT16 time );
UINT16 TIME_Passed1ms ( UINT16 time );
UINT16 TIME_Passed100ms ( UINT16 time );

////////////////////////////////////////////////////////////////////////////////
#endif
