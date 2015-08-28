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
#define _NVSTORAGE_C_
#include "nvstorage.h"
////////////////////////////////////////////////////////////////////////////////

BOOL NVS_Initialize ( NVS_HANDLE nvs )
{
    if (( nvs->persistSize + nvs->nvSize > nvs->mediaSize ))
        return ( FALSE );

    
    
    return ( TRUE );
}

////////////////////////////////////////////////////////////////////////////////

BOOL NVS_ReadPersistent ( VOID *data, UINT16 size )
{
    
    
    return ( TRUE );
}    

////////////////////////////////////////////////////////////////////////////////

BOOL NVS_ReadNonVolatile ( VOID *data, UINT16 size )
{
    
    
    return ( TRUE );
}    

////////////////////////////////////////////////////////////////////////////////

BOOL NVS_Write ( const VOID *data, UINT16 size )
{


    return ( TRUE );    
}    

////////////////////////////////////////////////////////////////////////////////
