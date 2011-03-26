/*  =========================================================================
    zfl_config_json - load JSON file into zfl_config structure

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

#ifndef __ZFL_CONFIG_JSON_H_INCLUDED__
#define __ZFL_CONFIG_JSON_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

//  @interface
//  Create new zfl_config object from JSON string
zfl_config_t *
    zfl_config_json (char *json_string);

//  Create new zfl_config object from JSON file
zfl_config_t *
    zfl_config_json_file (char *filename);

//  Self test of this class
int
    zfl_config_json_test (Bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif

