/********************************************************************
  File Information:
    FileName:       stub_btc.c
    Dependencies:   See INCLUDES section
    Processor:      PIC32 Microcontrollers
    Hardware:
    Complier:       C32 (for PIC32)
    Company:        Microchip Technology, Inc.

    Software License Agreement:

    The software supplied herewith by Microchip Technology Incorporated
    (the "Company") for its PIC(r) Microcontroller is intended and
    supplied to you, the Company's customer, for use solely and
    exclusively on Microchip PIC Microcontroller products. The
    software is owned by the Company and/or its supplier, and is
    protected under applicable copyright laws. All rights are reserved.
    Any use in violation of the foregoing restrictions may subject the
    user to criminal sanctions under applicable laws, as well as to
    civil liability for the breach of the terms and conditions of this
    license.

    THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
    WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
    TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
    IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
    CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************/
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
