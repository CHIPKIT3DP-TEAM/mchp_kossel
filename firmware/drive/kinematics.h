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
#ifndef _KINEMATICS_H_
#define _KINEMATICS_H_
////////////////////////////////////////////////////////////////////////////////

#include "system.h"
#include "drive_config.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    KINEMATICS_COMMAND_CODE_RAPID,
    KINEMATICS_COMMAND_CODE_FEED
}
KINEMATICS_COMMAND_CODE;

typedef struct
{
    FLOAT x;
    FLOAT y;
    FLOAT z;
}
KINEMATICS_COMMAND_PARAMS;

typedef enum
{
    KINEMATICS_EVENT_
}
KINEMATICS_EVENT;

////////////////////////////////////////////////////////////////////////////////

VOID KINEMATICS_Initialize ( VOID );
VOID KINEMATICS_Task ( VOID );
BOOL KINEMATICS_Command ( KINEMATICS_COMMAND_CODE cmd, KINEMATICS_COMMAND_PARAMS *params );

extern BOOL KINEMATICS_EventHandler ( KINEMATICS_EVENT event, VOID *data, UINT16 size );

////////////////////////////////////////////////////////////////////////////////
#endif
