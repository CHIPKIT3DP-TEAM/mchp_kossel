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
#define _OCMP_C_
#include "ocmp.h"
////////////////////////////////////////////////////////////////////////////////

OCMP_MODULE ocmpModule[OCMP_MODULE_COUNT] =
{
    {
        (OCMP_REGS*) _OCMP1_BASE_ADDRESS,
    },
    {
        (OCMP_REGS*) _OCMP2_BASE_ADDRESS,
    },
    {
        (OCMP_REGS*) _OCMP3_BASE_ADDRESS,
    },
    {
        (OCMP_REGS*) _OCMP4_BASE_ADDRESS,
    },
    {
        (OCMP_REGS*) _OCMP5_BASE_ADDRESS,
    },
    {
        (OCMP_REGS*) _OCMP6_BASE_ADDRESS,
    },
    {
        (OCMP_REGS*) _OCMP7_BASE_ADDRESS,
    },
    {
        (OCMP_REGS*) _OCMP8_BASE_ADDRESS,
    },
    {
        (OCMP_REGS*) _OCMP9_BASE_ADDRESS,
    },
};

////////////////////////////////////////////////////////////////////////////////

BOOL OCMP_Open ( OCMP_HANDLE ocmp, const OCMP_CONFIG *cfg )
{
    // OCMP_DisableInt ( ocmp );

    // TODO
    
    return ( TRUE );
}

////////////////////////////////////////////////////////////////////////////////

BOOL OCMP_Generate ( OCMP_HANDLE ocmp, const UINT8 *data, const UINT16 size )
{
    // TODO
    
    return ( TRUE );
}

////////////////////////////////////////////////////////////////////////////////

VOID OCMP_Int ( OCMP_HANDLE ocmp )
{
    // TODO
}

////////////////////////////////////////////////////////////////////////////////
