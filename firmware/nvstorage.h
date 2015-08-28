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
#ifndef _NVSTORAGE_H_
#define _NVSTORAGE_H_
////////////////////////////////////////////////////////////////////////////////
#include "system.h"
#include "bsp/mcp98244.h"
////////////////////////////////////////////////////////////////////////////////

typedef BOOL ( *NVS_FUNC_READ )( VOID *handle, UINT8 addr, VOID *data, UINT16 size );
typedef BOOL ( *NVS_FUNC_WRITE )( VOID *handle, UINT8 addr, const VOID *data, UINT16 size );

typedef struct
{
    UINT32 persistSize;
    UINT32 nvSize;
    UINT32 nvAddr;
    
    UINT32 mediaSize;
    VOID *mediaHandle;
    NVS_FUNC_READ MediaRead;
    NVS_FUNC_WRITE MediaWrite;
}
NVSTORAGE, *NVS_HANDLE;

typedef struct PACKED
{
    UINT32  count   : 24;
    UINT32  crc     : 8;
}
NVS_BLOCK_HEADER;

////////////////////////////////////////////////////////////////////////////////

BOOL NVS_Initialize ( NVS_HANDLE nvs );
BOOL NVS_ReadPersistent ( VOID *data, UINT16 size );
BOOL NVS_ReadNonVolatile ( VOID *data, UINT16 size );
BOOL NVS_WritePersistent ( const VOID *data, UINT16 size );
BOOL NVS_WriteNonVolatile ( const VOID *data, UINT16 size );

////////////////////////////////////////////////////////////////////////////////
#endif
