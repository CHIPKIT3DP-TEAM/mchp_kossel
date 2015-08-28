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
#ifndef _TIME_H_
#define _TIME_H_
////////////////////////////////////////////////////////////////////////////////

#include "system.h"

////////////////////////////////////////////////////////////////////////////////

VOID TIME_Initialize ( VOID );
VOID TIME_Update ( UINT32 time );
VOID TIME_Delay10us( UINT16 time );
VOID TIME_Delay1ms ( UINT32 time );
UINT32 TIME_Get1ms ( VOID );
BOOL TIME_Elapsed1ms ( UINT32 time );
UINT32 TIME_Passed1ms ( UINT32 time );

////////////////////////////////////////////////////////////////////////////////
#endif
