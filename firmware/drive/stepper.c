#define _STEPPER_C_
#include "stepper.h"

////////////////////////////////////////////////////////////////////////////////

//CONST FFP FFP_CONST_0_5 = { 0x007F0000 };
//CONST FFP FFP_CONST_1   = { 0x00800000 };
//CONST FFP FFP_CONST_10  = { 0x00832000 };

////////////////////////////////////////////////////////////////////////////////
VOID STEPPER_Initialize ( STEPPER *stepper )
{
    stepper->moveQueueHead = 0;
    stepper->moveQueueTail = 0;
    stepper->moveQueueCount = 0;
}
////////////////////////////////////////////////////////////////////////////////
VOID STEPPER_Task ( STEPPER *stepper )
{
}
////////////////////////////////////////////////////////////////////////////////
INT32 sqrt32 ( INT32 a )
{
    return ( sqrtf ( a ));
}
////////////////////////////////////////////////////////////////////////////////
INT32 sqare32 ( INT32 a )
{
    return ( a * a * 0x10 );
}
////////////////////////////////////////////////////////////////////////////////
INT32 mult32 ( INT32 a, INT32 b )
{
    return ( a * b );
}
////////////////////////////////////////////////////////////////////////////////
INT32 div32 ( INT32 a, INT32 b )
{
    return ( a / b );
}
////////////////////////////////////////////////////////////////////////////////
INT64 sqrt64 ( INT64 a )
{
    return ( sqrtf ( a ));
}
////////////////////////////////////////////////////////////////////////////////
INT64 sqare64 ( INT64 a )
{
    a /= 0x10000;
    return ( a * a );
}
////////////////////////////////////////////////////////////////////////////////
INT64 mult64 ( INT64 a, INT64 b )
{
    return (( a / 0x10000 ) * ( b / 0x10000 ));
}
////////////////////////////////////////////////////////////////////////////////
INT64 div64 ( INT64 a, INT64 b )
{
    return (( a * 0x10000 ) / ( b / 0x10000 ));
}
////////////////////////////////////////////////////////////////////////////////
FLOAT fsqrt ( FLOAT x )
{
    union
    {
        FLOAT   x;
        INT32   i;
    }
    u;

    u.x = x;
    u.i = 0x5f3759df - ( u.i / 2 );
    return ( x * u.x * ( 1.5 - u.x * u.x / 2 ));
}
////////////////////////////////////////////////////////////////////////////////
VOID FFP_Sqrt ( VOID )
{
    FLOAT x;

//    x = FFP_SaveAFLOAT ();
//    x = sqrtf ( x );
//    FFP_LoadAFLOAT ( x );
}
////////////////////////////////////////////////////////////////////////////////
BOOL STEPPER_WriteSegment ( STEPPER *stepper, FLOAT distance, FLOAT travelTime )
{
    BOOL passed = TRUE;
    BOOL dir = 0;
    FLOAT entrySpeed = stepper->speed;

    ////////////////////////////////////////////////////////////////////////////
    //  FLOAT
    ////////////////////////////////////////////////////////////////////////////
    //              seg1        seg2        seg3        seg4        seg5
    //
    //  dsPIC       35.2        40.0        35.2        39.9        37.0
    //  PIC32       2.77        3.84        3.48        3.58        3.69
    //
    ////////////////////////////////////////////////////////////////////////////

//    {
//        INT16 steps;
//        FLOAT time, speed, newSpeed, dSpeed, accel, accelRev, accel2;
//        FLOAT period, descrim;
//
//        steps = floorf ( distance * stepper->stepsPerMM + 0.5 );
//        stepper->speed = 2 * steps / travelTime - entrySpeed;
//
//        if ( steps < 0 )
//        {
//            steps = -steps;
//            speed = -entrySpeed / stepper->clock;
//            dir = 1;
//        }
//        else
//        {
//            speed = entrySpeed / stepper->clock;
//        }
//
//        time = travelTime * stepper->clock;
//
//        if ( steps > 1 )
//        {
//            accel = 2 * ((FLOAT)steps - speed * time ) / ( time * time );
//            accelRev = 1 / accel;
//            accel2 = accel * 2;
//            dSpeed = accel / speed;
//            period = 1 / speed;
//
//            while ( steps > 1 )
//            {
//                if (( dSpeed > 1E-7 ) || ( dSpeed < -1E-7 ))
//                {
//                    descrim = speed * speed;
//                    descrim += accel2;
//                    newSpeed = sqrtf ( descrim );
//                    dSpeed = newSpeed - speed;
//                    period = dSpeed * accelRev;
//                    speed = newSpeed;
//                }
//                else
//                {
//                    dSpeed = accel * period;
//                }
//
//                period = floorf ( period + 0.5 );
//                time -= period;
//
//                if ( dir == 1 ) period = -period;
//                stepper->moveQueue[stepper->moveQueueHead++] = period;
//                stepper->moveQueueCount ++;
//
//                steps --;
//            }
//        }
//
//        if ( dir == 1 ) time = -time;
//        stepper->moveQueue[stepper->moveQueueHead++] = time;
//        stepper->moveQueueCount ++;
//
//        Nop ();
//    }

    ////////////////////////////////////////////////////////////////////////////
    //  FFP
    ////////////////////////////////////////////////////////////////////////////
    //              seg1        seg2        seg3        seg4        seg5
    //
    //  dsPIC       6.76        4.80
    //  PIC32       
    ////////////////////////////////////////////////////////////////////////////

//    {
//        INT16 steps;
//        FLOAT time, speed, dspeed, accel, period, store;
//
////        steps = floorf ( distance * stepper->stepsPerMM + 0.5 );
//        FFP_LoadAFLOAT ( distance );
//        FFP_LoadBFLOAT ( stepper->stepsPerMM );
//        FFP_Mult ();
//        steps = FFP_SaveAINT32 ();
//
//        // stepper->speed = 2 * steps / travelTime - entrySpeed;
//        FFP_ShiftA ( 1 );
//        FFP_LoadBFLOAT ( travelTime );
//        FFP_Div ();
//        FFP_LoadBFLOAT ( entrySpeed );
//        FFP_Sub ();
//        stepper->speed = FFP_SaveAFLOAT ();
//
//        // time = travelTime * stepper->clock;
//        FFP_LoadAFLOAT ( travelTime );
//        FFP_LoadBINT32 ( stepper->clock );
////        FFP_Mult ();
//        time = FFP_SaveAFLOAT ();
//
//        if ( steps < 0 )
//        {
//            steps = -steps;
//            dir = 1;
//        }
//
//        if ( steps > 1 )
//        {
//            // speed = stepper->speed / stepper->clock;
//            FFP_LoadAFLOAT ( entrySpeed );
////            FFP_Div ();
//            if ( dir ) FFP_NegA ();
//            speed = FFP_SaveAFLOAT ();
//
//            // accel = 2 * ((FLOAT)steps - speed * time ) / ( time * time );
//            FFP_LoadAFLOAT ( time );
//            FFP_Copy ();
//            FFP_Mult ();
//            store = FFP_SaveAFLOAT ();
//
//            FFP_LoadAFLOAT ( speed );
//            FFP_Mult ();
//            FFP_NegA ();
//            FFP_LoadBINT32 ( steps );
//            FFP_Add ();
//            FFP_ShiftA ( 1 );
//            FFP_LoadBFLOAT ( store );
//            FFP_Div ();
//            accel = FFP_SaveAFLOAT ();
//
//            // dSpeed = accel / speed;
//            FFP_LoadAFLOAT ( accel );
//            FFP_LoadBFLOAT ( speed );
//            FFP_Div ();
//            dspeed = FFP_SaveAFLOAT ();
//
//            // period = 1 / speed;
//            FFP_LoadAFFP ( FFP_CONST_1 );
//            FFP_Div ();
//            period = FFP_SaveAFLOAT ();
//
//            while ( steps > 1 )
//            {
//                if (( steps & 0b111 ) == 0 )
//                {
//                    // accel = 2 * ((FLOAT)steps - speed * time ) / ( time * time );
//                    FFP_LoadAFLOAT ( time );
//                    FFP_Copy ();
//                    FFP_Mult ();
//                    store = FFP_SaveAFLOAT ();
//
//                    FFP_LoadAFLOAT ( speed );
//                    FFP_Mult ();
//                    FFP_NegA ();
//                    FFP_LoadBINT32 ( steps );
//                    FFP_Add ();
//                    FFP_ShiftA ( 1 );
//                    FFP_LoadBFLOAT ( store );
//                    FFP_Div ();
//                    accel = FFP_SaveAFLOAT ();
//
//                    // dSpeed = accel / speed;
//                    FFP_LoadAFLOAT ( accel );
//                    FFP_LoadBFLOAT ( speed );
//                    FFP_Div ();
//                    dspeed = FFP_SaveAFLOAT ();
//                }
//
//                if (( dspeed < -1E-7 ) || ( dspeed > 1E-7 ))
//                {
//                    // descrim = speed * speed;
//                    // descrim += accel * 2;
//                    // newspeed = sqrtf ( descrim );
//                    FFP_LoadAFLOAT ( speed );
//                    FFP_Copy ();
//                    FFP_Mult ();
//                    FFP_LoadBFLOAT ( accel );
//                    FFP_ShiftB ( 1 );
//                    FFP_Add ();
//                    FFP_Sqrt ();
//
//                    // dspeed = newspeed - speed;
//                    FFP_Swap ();
//                    FFP_LoadAFLOAT ( speed );
//                    FFP_NegA ();
//                    FFP_Add ();
//                    dspeed = FFP_SaveAFLOAT ();
//
//                    // speed = newspeed;
//                    speed = FFP_SaveBFLOAT ();
//
//                    // period = dspeed / accel;
//                    FFP_LoadBFLOAT ( accel );
//                    FFP_Div ();
//                    period = FFP_SaveAFLOAT ();
//                }
//                else
//                {
//                    // dspeed = accel * period;
//                    FFP_LoadAFLOAT ( accel );
//                    FFP_LoadBFLOAT ( period );
//                    FFP_Mult ();
//                    dspeed = FFP_SaveAFLOAT ();
//                }
//
//                // period = floorf ( period + 0.5 );
//                // time -= period;
//                FFP_LoadAFLOAT ( time );
//                FFP_LoadBFLOAT ( period );
//                FFP_Sub ();
//                time = FFP_SaveAFLOAT ();
//                FFP_Swap ();
//
//                FFP_LoadBFLOAT ( stepper->clock );
//                FFP_Mult ();
//
//                if ( dir == 1 )
//                    // period = -period;
//                    FFP_NegA ();
//                stepper->moveQueue[stepper->moveQueueHead++] = FFP_SaveAINT32 ();
//                stepper->moveQueueCount ++;
//
//                steps --;
//            }
//        }
//
//        FFP_LoadAFLOAT ( time );
//        FFP_LoadBFLOAT ( stepper->clock );
//        FFP_Mult ();
//
//        if ( dir == 1 )
//            // time = -time;
//            FFP_NegA ();
//        stepper->moveQueue[stepper->moveQueueHead++] = FFP_SaveAINT32 ();
//        stepper->moveQueueCount ++;
//
//        Nop ();
//    }

    ////////////////////////////////////////////////////////////////////////////
    //  FLOAT time division
    ////////////////////////////////////////////////////////////////////////////
    //              seg1        seg2        seg3        seg4        seg5
    //
    //  dsPIC       67          40          37.5        37.5        39
    //  PIC32       11.3        7.6         7.3         6.5         7.8
    //  reference
    ////////////////////////////////////////////////////////////////////////////

    {
        INT32 steps;
        FLOAT time, dtime, dtimesq, speed, dspeed, accel, distdither;
        FLOAT period;
        FLOAT x;

        time = travelTime;
        x = distance * stepper->stepsPerMM;
        steps = x;

        x *= 2;
        x /= travelTime;
        x -= entrySpeed;
        stepper->speed = x;
        speed = entrySpeed;

        if ( steps < 0 )
        {
            dir = 1;
            steps = -steps;
            speed = -speed;
        }

        if ( x < 0 )    x = -x;

        if ( x > speed )
            dtime = 1 / ( x * 100 );
        else
            dtime = 1 / ( speed * 100 );

        accel = 2 * ( steps - speed * time ) / ( time * time );
        dspeed = accel * dtime;
        dtimesq = dtime * dtime;
        period = 0;
        distdither = 0;

        while ( steps > 1 )
        {
            distdither += dtime * speed + dtimesq * accel;
            if ( distdither > 1 )
            {
//                period -= distance + dtime;
                time -= period;

                if ( dir == 1 ) period = -period;
                stepper->moveQueue[stepper->moveQueueHead++] = period * stepper->clock;
                stepper->moveQueueCount ++;

                period = 0;
                distdither -= 1;
                steps --;
            }

            period += dtime;
            speed += dspeed;
        }

        if ( dir == 1 ) time = -time;
        stepper->moveQueue[stepper->moveQueueHead++] = time * stepper->clock;
        stepper->moveQueueCount ++;

        Nop ();
    }




    ////////////////////////////////////////////////////////////////////////////
    //  Array test
    ////////////////////////////////////////////////////////////////////////////
    {
        FLOAT steps;
        FLOAT time, speed, newSpeed, accel;
        FLOAT period, descrim, sample, ratio;

        steps = floorf ( distance * stepper->stepsPerMM + 0.5 );
        if ( steps < 0 )
        {
            dir = 1;
            steps = -steps;
            speed = -entrySpeed;
        }
        else
        {
            speed = entrySpeed;
        }
        
        stepper->moveQueueHead -= steps;
        time = travelTime;

        while ( steps > 1 )
        {
            accel = 2 * ( steps - speed * time ) / ( time * time );
            descrim = speed * speed;
            descrim += 2 * accel;
            newSpeed = sqrtf ( descrim );
            period = newSpeed - speed;
            period /= accel;
            speed = newSpeed;

            period = floorf ( period * stepper->clock + 0.5 );
            time -= period / stepper->clock;

            if ( dir ) period = -period;
            sample = stepper->moveQueue[stepper->moveQueueHead++];
            ratio = ( sample - period ) / period;
            if (( ratio > 0.1 ) || ( ratio < -0.1 ))
                passed = FALSE;

            steps --;
        }

        if ( dir ) time = -time;
        time = floorf ( time * stepper->clock + 0.5 );
        sample = stepper->moveQueue[stepper->moveQueueHead++];
        ratio = ( sample - time ) / time;
        if (( ratio > 0.1 ) || ( ratio < -0.1 ))
        {
             passed = FALSE;
             SYSTEM_Halt ();
        }

        Nop ();
    }

    ////////////////////////////////////////////////////////////////////////////
    //  Exit Speed test
    ////////////////////////////////////////////////////////////////////////////
    {
        FLOAT steps;
        FLOAT ratio, speed;

        steps = floorf ( distance * stepper->stepsPerMM + 0.5 );
        speed = 2 * steps / travelTime - entrySpeed;
        ratio = ( stepper->speed - speed ) / speed;
        if (( ratio > 0.05 )
        || ( ratio < -0.05 ))
        {
            passed = FALSE;
            SYSTEM_Halt ();
        }

        Nop ();
    }

    ////////////////////////////////////////////////////////////////////////////
    //  Timing test
    ////////////////////////////////////////////////////////////////////////////
    {
        INT16 steps;
        INT32 timeCount = 0, diff;

        steps = floorf ( distance * stepper->stepsPerMM + 0.5 );
        if ( steps < 0 ) steps = -steps;

        stepper->moveQueueHead -= steps;

        while ( steps -- )
            timeCount += stepper->moveQueue[stepper->moveQueueHead++];

        if ( timeCount < 0 ) timeCount = -timeCount;
        diff = timeCount - floorf ( travelTime * stepper->clock + 0.5 );

        if (( diff > 5 ) || ( diff < -5 ))
        {
            passed = FALSE;
            SYSTEM_Halt ();
        }

        Nop ();
    }

    ////////////////////////////////////////////////////////////////////////////
    
    if ( passed == FALSE )
        SYSTEM_Halt ();


    return ( TRUE );
}
////////////////////////////////////////////////////////////////////////////////
VOID STEPPER_Interrupt ( STEPPER *stepper )
{
    INT16 period;

    // add step flag

    stepper->Step ();

    period = stepper->moveQueue[stepper->moveQueueTail++];
    if ( period > 0 )
    {
        stepper->DirForward ();
    }
    else
    {
        stepper->DirBackward ();
    }

    stepper->SetPeriod ( period );

    if ( --stepper->moveQueueCount == 0 )
    {
        stepper->TimerOff ();
    }

}
////////////////////////////////////////////////////////////////////////////////
