/*  =========================================================================
    zfl_clock.h - use timers and dates

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

#ifndef __ZFL_CLOCK_H_INCLUDED__
#define __ZFL_CLOCK_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

//  Opaque class structure
typedef struct _zfl_clock_t zfl_clock_t;

zfl_clock_t *
    zfl_clock_new (void);
void
    zfl_clock_destroy (zfl_clock_t **self_p);
void
    zfl_clock_sleep (zfl_clock_t *self, uint msecs);
uint64_t
    zfl_clock_now (zfl_clock_t *self);
int
    zfl_clock_test (Bool verbose);

#ifdef __cplusplus
}
#endif

#endif
