////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _BUS_H_
#define _BUS_H_
////////////////////////////////////////////////////////////////////////////////
#include "system.h"
#include "bsp/uart.h"
////////////////////////////////////////////////////////////////////////////////

#define BUS_TASK_PERIOD         1000

////////////////////////////////////////////////////////////////////////////////

VOID BUS_Initialize ( VOID );
VOID BUS_Task ( VOID );

////////////////////////////////////////////////////////////////////////////////
#endif