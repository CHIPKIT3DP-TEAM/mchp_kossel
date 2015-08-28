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
