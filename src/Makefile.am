lib_LTLIBRARIES = libzfl.la

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libzfl.pc

include_HEADERS = \
    ../include/zfl.h \
    ../include/zfl_base.h \
    ../include/zfl_bits.h \
    ../include/zfl_config.h \
    ../include/zfl_config_json.h \
    ../include/zfl_config_zpl.h \
    ../include/zfl_blob.h \
    ../include/zfl_device.h \
    ../include/zfl_thread.h \
    import/cJSON/cJSON.h

libzfl_la_SOURCES = \
    zfl_base.c \
    zfl_bits.c \
    zfl_blob.c \
    zfl_config.c \
    zfl_config_json.c \
    zfl_config_zpl.c \
    zfl_device.c \
    zfl_thread.c

EXTRA_libzfl_la_SOURCES = import/cJSON/cJSON.c

INCLUDES = -I$(top_srcdir)/include
bin_PROGRAMS = zfl_selftest
zfl_selftest_LDADD = libzfl.la
zfl_selftest_SOURCES = zfl_selftest.c

if ON_MINGW
libzfl_la_LDFLAGS = -no-undefined -avoid-version -version-info @LTVER@
else
libzfl_la_LDFLAGS = -version-info @LTVER@
endif

TESTS = zfl_selftest


