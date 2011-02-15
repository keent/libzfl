/*  =========================================================================
    zfl_clock.c - use timers and dates

    Provides a portable API to non-portable date and time functions such as
    sub-second sleeping and sub-second precision clocks.

    -------------------------------------------------------------------------
    Copyright (c) 1991-2011 iMatix Corporation <www.imatix.com>
    Copyright other contributors as noted in the AUTHORS file.

    This file is part of the ZeroMQ Function Library: http://zfl.zeromq.org

    This is free software; you can redistribute it and/or modify it under the
    terms of the GNU Lesser General Public License as published by the Free
    Software Foundation; either version 3 of the License, or (at your option)
    any later version.

    This software is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABIL-
    ITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General
    Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
    =========================================================================
*/

#include "../include/zfl_prelude.h"
#include "../include/zfl_clock.h"

//  Structure of our class

struct _zfl_clock_t {
    int
        _none;                  //  Clock object has no data
};


//  --------------------------------------------------------------------------
//  Constructor

zfl_clock_t *
zfl_clock_new (void)
{
    zfl_clock_t
        *self;

    self = (zfl_clock_t *) zmalloc (sizeof (zfl_clock_t));
    return self;
}


//  --------------------------------------------------------------------------
//  Destructor

void
zfl_clock_destroy (zfl_clock_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        zfl_clock_t *self = *self_p;
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Sleep for a specified number of milliseconds. This method is meant for
//  testing delays, not system level precision. For high speed message I/O
//  loops you should use zmq_poll which has microsecond resolution and is
//  interruptible.

void
zfl_clock_sleep (zfl_clock_t *self, uint msecs)
{
    assert (self);
#if defined (__UNIX__)
    struct timespec t;
    t.tv_sec = msecs / 1000;
    t.tv_nsec = msecs * 1000000;
    nanosleep (&t, NULL);
#elif defined (__WINDOWS__)
    Sleep (msecs);
#else
#   error "Platform not supported by zfl_clock class"
#endif
}


//  --------------------------------------------------------------------------
//  Return current system time in microseconds. Returns the date and time in
//  a 64-bit integer that can be used in calculations. You can use this for
//  system level work. The actual resolution of the system clock depends on
//  the OS. For Linux, it is microseconds. For Windows, milliseconds.

uint64_t
zfl_clock_now (zfl_clock_t *self)
{
    assert (self);
#if (defined (__UNIX__))
    struct timeval tv;
    int rc = gettimeofday (&tv, NULL);
    assert (rc == 0);
    return (uint64_t) tv.tv_sec * 1000000 + tv.tv_usec;
#elif (defined (__WINDOWS__))
    SYSTEMTIME st;
    GetSystemTime (&st);
    return (uint64_t) st.wSecond * 1000000 + st.wMilliseconds * 1000;
#endif
}


//  --------------------------------------------------------------------------
//  Selftest

int
zfl_clock_test (Bool verbose)
{
    zfl_clock_t
        *clock;

    printf (" * zfl_clock: ");
    clock = zfl_clock_new ();
    assert (clock);

    //  Sleep for various msec pauses
    zfl_clock_sleep (clock, 0);
    uint64_t before = zfl_clock_now (clock);
    zfl_clock_sleep (clock, 100);
    zfl_clock_sleep (clock, 1);
    uint64_t after = zfl_clock_now (clock);
    assert (after - before > 100);

    zfl_clock_destroy (&clock);
    assert (clock == NULL);

    printf ("OK\n");
    return 0;
}
