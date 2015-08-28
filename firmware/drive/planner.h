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
#ifndef _PLANNER_H_
#define _PLANNER_H_
////////////////////////////////////////////////////////////////////////////////

#include "system.h"
#include "drive_config.h"

////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    FLOAT x;
    FLOAT y;
    FLOAT z;
}
PLANNER_COORD;

typedef enum
{
    PLANNER_EVENT_
}
PLANNER_EVENT;

////////////////////////////////////////////////////////////////////////////////

VOID PLANNER_Initialize ( VOID );
VOID PLANNER_Task ( VOID );
BOOL PLANNER_Move ( PLANNER_COORD *move );

extern BOOL PLANNER_EventHandler ( PLANNER_EVENT event, VOID *data, UINT16 size );

////////////////////////////////////////////////////////////////////////////////
#endif
