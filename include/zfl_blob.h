/*  =========================================================================
    zfl_blob.h - ZFL blob class

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

#ifndef __ZFL_BLOB_H_INCLUDED__
#define __ZFL_BLOB_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

//  Opaque class structure
typedef struct _zfl_blob_t zfl_blob_t;

//  @interface
//  Create a new blob object
zfl_blob_t *
    zfl_blob_new (byte *data, size_t size);

//  Destroy a blob object
void
    zfl_blob_destroy (zfl_blob_t **self_p);

//  Create a blob object loaded from a file
zfl_blob_t *
    zfl_blob_load (FILE *file);

//  Set a blob's content, copying from a memory block
int
    zfl_blob_set_data (zfl_blob_t *self, byte *data, size_t size);

//  Set a blob's content, not copying
int
    zfl_blob_set_dptr (zfl_blob_t *self, byte *data, size_t size);

//  Return blob content reference
byte *
    zfl_blob_data (zfl_blob_t *self);

//  Return size of blob content
size_t
    zfl_blob_size (zfl_blob_t *self);

//  Self test of this class
int
    zfl_blob_test (Bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif

