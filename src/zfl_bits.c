/*  =========================================================================
    zfl_bits - bitstring manipulation - in-progress

    -------------------------------------------------------------------------
    Copyright (c) 1991-2011 iMatix Corporation <www.imatix.com>
    Copyright other contributors as noted in the AUTHORS file.

    This file is part of libzfl, http://libzfl.zeromq.org.

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

/*
@header
    Provides manual template for new classes, and canonical style guidelines
    for all ZFL source code.
@discuss
@end
*/

#include <czmq.h>
#include "../include/zfl_bits.h"

//  Structure of our class

struct _zfl_bits_t {
    int
        filler;                         //  An example property
};

//  Private functions

static int
s_private_function_example (void)
{
    return 0;
}


//  --------------------------------------------------------------------------
//  Constructor

zfl_bits_t *
zfl_bits_new (void)
{
    zfl_bits_t
        *self;

    self = (zfl_bits_t *) zmalloc (sizeof (zfl_bits_t));
    s_private_function_example();
    return self;
}


//  --------------------------------------------------------------------------
//  Destructor

void
zfl_bits_destroy (zfl_bits_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        zfl_bits_t *self = *self_p;
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Filler property
//  Does nothing special but if it did, we'd explain that here

int
zfl_bits_filler (zfl_bits_t *self)
{
    assert (self);
    return self->filler;
}

void
zfl_bits_filler_set (zfl_bits_t *self, int newvalue)
{
    assert (self);
    self->filler = newvalue;
}


//  --------------------------------------------------------------------------
//  Selftest

int
zfl_bits_test (Bool verbose)
{
    printf (" * zfl_bits: ");

    //  @selftest
    zfl_bits_t *bits = zfl_bits_new ();
    assert (bits);

    zfl_bits_filler_set (bits, 123);
    assert (zfl_bits_filler (bits) == 123);

    //  Destructor should be safe to call twice
    zfl_bits_destroy (&bits);
    zfl_bits_destroy (&bits);
    assert (bits == NULL);
    //  @end

    printf ("OK\n");
    return 0;
}
