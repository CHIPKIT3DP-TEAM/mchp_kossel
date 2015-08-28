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
#ifndef _STEPPER_H_
#define _STEPPER_H_
////////////////////////////////////////////////////////////////////////////////

#include "system.h"
#include <string.h>
#include <math.h>

////////////////////////////////////////////////////////////////////////////////

#define STEPPER_MOVE_QUEUE_COUNT    256

typedef struct
{
    union
    {
        UINT8 flags;
        struct
        {
            UINT8 running   :1;
        };
    };
    INT32 moveQueue[STEPPER_MOVE_QUEUE_COUNT];
    UINT8 moveQueueTail;
    UINT8 moveQueueHead;
    UINT8 moveQueueCount;

    FLOAT stepsPerMM;
    UINT32 clock;
    INT32 position;
    FLOAT speed;

    VOID ( *Enable )( VOID );
    VOID ( *Disable )( VOID );
    VOID ( *Step )( VOID );
    VOID ( *DirForward )( VOID );
    VOID ( *DirBackward )( VOID );
    VOID ( *SetPeriod )( UINT16 );
    VOID ( *TimerOn )( VOID );
    VOID ( *TimerOff )( VOID );
}
STEPPER;

typedef enum
{
    STEPPER_EVENT_
}
STEPPER_EVENT;

////////////////////////////////////////////////////////////////////////////////

VOID STEPPER_Initialize ( STEPPER *stepper );
VOID STEPPER_Task ( STEPPER *stepper );
BOOL STEPPER_WriteSegment ( STEPPER *stepper, FLOAT distance, FLOAT time );
VOID STEPPER_Interrupt ( STEPPER *stepper );

extern BOOL STEPPER_EventHandler ( STEPPER_EVENT event, VOID *data, UINT16 size );

////////////////////////////////////////////////////////////////////////////////
#endif
