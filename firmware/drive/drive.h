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
#ifndef _DRIVE_H_
#define _DRIVE_H_
////////////////////////////////////////////////////////////////////////////////

#include "system.h"
#include "drive_config.h"
#include "kinematics.h"
#include "planner.h"
#include "stepper.h"

////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    DRIVE_COMMAND_CODE_RAPID,
    DRIVE_COMMAND_CODE_FEED
}
DRIVE_COMMAND_CODE;

typedef struct
{
    FLOAT x;
    FLOAT y;
    FLOAT z;
}
DRIVE_COMMAND_PARAMS;

typedef enum
{
    DRIVE_EVENT_EMPTY,
    DRIVE_EVENT_ERROR
}
DRIVE_EVENT;

////////////////////////////////////////////////////////////////////////////////

VOID DRIVE_Initialize ( VOID );
VOID DRIVE_Task ( VOID );
BOOL DRIVE_Command ( DRIVE_COMMAND_CODE cmd, DRIVE_COMMAND_PARAMS *params );

extern BOOL DRIVE_EventHandler ( DRIVE_EVENT event, VOID *data, UINT16 size );

////////////////////////////////////////////////////////////////////////////////
#endif
