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
#define _DRIVE_C_
#include "drive.h"
////////////////////////////////////////////////////////////////////////////////

STEPPER stepper[STEPPER_NUMBER_OF];

////////////////////////////////////////////////////////////////////////////////
VOID DRIVE_Initialize ( VOID )
{
    int i;
    
    KINEMATICS_Initialize ();
    PLANNER_Initialize ();
    
    for ( i = 0; i < STEPPER_NUMBER_OF; i ++ )
        STEPPER_Initialize ( &stepper[i] );
}
////////////////////////////////////////////////////////////////////////////////
VOID DRIVE_Task ( VOID )
{
}
////////////////////////////////////////////////////////////////////////////////
BOOL DRIVE_Command ( DRIVE_COMMAND_CODE cmd, DRIVE_COMMAND_PARAMS *params )
{
    
    
    return ( TRUE );
}
////////////////////////////////////////////////////////////////////////////////
BOOL KINEMATICS_EventHandler ( KINEMATICS_EVENT event, VOID *data, UINT16 size )
{

    return ( TRUE );
}
////////////////////////////////////////////////////////////////////////////////
BOOL PLANNER_EventHandler ( PLANNER_EVENT event, VOID *data, UINT16 size )
{

    return ( TRUE );
}
////////////////////////////////////////////////////////////////////////////////
BOOL STEPPER_EventHandler ( STEPPER_EVENT event, VOID *data, UINT16 size )
{

    return ( TRUE );
}
////////////////////////////////////////////////////////////////////////////////
