/*  =========================================================================
    zfl_base - libzfl base class

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

#ifndef __ZFL_BASE_H_INCLUDED__
#define __ZFL_BASE_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

//  Opaque class structure
typedef struct _zfl_base_t zfl_base_t;

//  @interface
//  Constructor
zfl_base_t *
    zfl_base_new (void);

//  Destructor
void
    zfl_base_destroy (zfl_base_t **self_p);

//  Example method returning property
int
    zfl_base_filler (zfl_base_t *self);

//  Example method setting property
void
    zfl_base_filler_set (zfl_base_t *self, int newvalue);

//  Self test of this class
int
    zfl_base_test (Bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
