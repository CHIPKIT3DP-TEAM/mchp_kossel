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

}
////////////////////////////////////////////////////////////////////////////////
BOOL PLANNER_EventHandler ( PLANNER_EVENT event, VOID *data, UINT16 size )
{
}
////////////////////////////////////////////////////////////////////////////////
BOOL STEPPER_EventHandler ( STEPPER_EVENT event, VOID *data, UINT16 size )
{
}
////////////////////////////////////////////////////////////////////////////////
