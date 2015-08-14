////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
#define _BUS_C_
#include "bus.h"
////////////////////////////////////////////////////////////////////////////////

static BOOL BUS_UARTEventHandler ( UART_HANDLE uart, UART_EVENT event, const UINT8 * data, const UINT16 size );

////////////////////////////////////////////////////////////////////////////////

UINT8 busRxBuff[64];

////////////////////////////////////////////////////////////////////////////////

static UART_CONFIG busUartCfg =
{
    .baudrate = UART_BUS_BAUDRATE,
    .EventHandler = &BUS_UARTEventHandler,
    .dataParity = UART_DATA_8_PARITY_NONE,
    .stopBits = 1,
    .flowControl = FALSE
};

////////////////////////////////////////////////////////////////////////////////

VOID BUS_Initialize ( VOID )
{
    UART_Initialize ( UART_BUS, &busUartCfg );
    UART_Receive ( UART_BUS, busRxBuff, 8 );
}

////////////////////////////////////////////////////////////////////////////////

VOID BUS_Task ( VOID )
{
    static UINT32 time = 0;
    
    if ( TIME_Elapsed1ms ( time ))
    {
        time = TIME_Get1ms () + BUS_TASK_PERIOD;
        UART_Transmit ( UART_BUS, (const UINT8*)"assa\r\n", 6 );
    }
}

////////////////////////////////////////////////////////////////////////////////

BOOL BUS_UARTEventHandler ( UART_HANDLE uart, UART_EVENT event, const UINT8 * data, const UINT16 size )
{
    switch ( event )
    {
        case UART_EVENT_RECEIVED:
            UART_Receive ( UART_BUS, busRxBuff, 8 );
            break;
            
        case UART_EVENT_SENT:
            Nop ();
            break;

        default:
            SYSTEM_Halt ();
            break;
    }
    
    return ( TRUE );
}
////////////////////////////////////////////////////////////////////////////////
