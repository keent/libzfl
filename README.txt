.set GIT=https://github.com/zeromq/zfl
.sub 0MQ=ØMQ

# libzfl - High-level C library for ØMQ

## Contents

.toc

## Overview

### Scope and Goals

libzfl is a thin portability & function library for ZeroMQ applications in C/C++. It is written as clear readable C classes, portable to all 0MQ platforms, and licensed under the LGPL.

The main goal is to allow the construction of industrial-scale 0MQ services and devices that integrate properly with the operating system, while staying 100% portable. libzfl acts as a primary abstraction layer on top of the 0MQ API, mainly for C applications but also for other languages. libzfl is inspired by the iMatix Standard Function Library (SFL), and borrows liberally from it. See http://legacy.imatix.com/html/sfl/.

libzfl is meant to be lightweight, consistent, class-based, minimalistic, highly efficient, and aimed at making it faster and easier to develop realistic, secure, and portable 0MQ devices and applications.

### Ownership and License

libzfl is maintained by Pieter Hintjens and Martin Hurton (code) and Mikko Koppanen (build system). Its other authors and contributors are listed in the AUTHORS file. It is held by the ZeroMQ organization at github.com.

The authors of libzfl grant you use of this software under the terms of the GNU Lesser General Public License (LGPL). For details see the files `COPYING` and `COPYING.LESSER` in this directory.

### Contributing

To submit an issue use the [issue tracker](http://github.com/zeromq/zfl/issues). All discussion happens on the [zeromq-dev](zeromq-dev@lists.zeromq.org) list or #zeromq IRC channel at irc.freenode.net.

The proper way to submit patches is to clone this repository, make your changes, and use git to create a patch. See http://www.zeromq.org/docs:contributing. All contributors are listed in AUTHORS.

All classes are maintained by a single person, who is the responsible editor for that class and who is named in the header as such. This is usually the originator of the class. When several people collaborate on a class, one single person is always the lead maintainer and the one to blame when it breaks.

The general rule is, if you contribute code to libzfl you must be willing to maintain it as long as there are users of it. Code with no active maintainer will in general be deprecated and/or removed.

## Using libzfl

### Dependencies

libzfl depends on [CZMQ](http://czmq.zeromq.org). Please build and install CZMQ before building and installing libzfl.

### Building and Installing

libzfl uses autotools for packaging. To build from git (all example commands are for Linux):

    git clone git://github.com/zeromq/libzfl.git
    cd libzfl
    sh autogen.sh
    ./configure
    make all
    sudo make install
    sudo ldconfig

You will need the libtool and autotools packages. On FreeBSD, you may need to specify the default directories for configure:

    ./configure --with-zeromq=/usr/local

After building, you can run the libzfl selftests:

    make check

### Linking with an Application

Include `zfl.h` in your application and link with libzfl. Here is a typical gcc link command:

    gcc -lzfl -lzmq myapp.c -o myapp

You should read `zfl.h`. This file includes `zmq.h` and the system header files that typical 0MQ applications will need. The provided 'c' shell script lets you write simple portable build scripts:

    c -lzfl -lzmq -l myapp

### API Summary

#### zfl_base - libzfl base class

.pull src/zfl_base.c@header,left

This is the class interface:

.pull include/zfl_base.h@interface,code

.pull src/zfl_base.c@discuss,left

#### zfl_bits - bitstring manipulation - in-progress

.pull src/zfl_bits.c@header,left

This is the class interface:

.pull include/zfl_bits.h@interface,code

.pull src/zfl_bits.c@discuss,left

#### zfl_blob - work with binary long objects (blobs)

.pull src/zfl_blob.c@header,left

This is the class interface:

.pull include/zfl_blob.h@interface,code

.pull src/zfl_blob.c@discuss,left

#### zfl_config - work with configuration files

.pull src/zfl_config.c@header,left

This is the class interface:

.pull include/zfl_config.h@interface,code

.pull src/zfl_config.c@discuss,left

#### zfl_config_json - load JSON file into zfl_config structure

.pull src/zfl_config_json.c@header,left

This is the class interface:

.pull include/zfl_config_json.h@interface,code

.pull src/zfl_config_json.c@discuss,left

#### zfl_config_zpl - load ZPL file into zfl_config structure

.pull src/zfl_config_zpl.c@header,left

This is the class interface:

.pull include/zfl_config_zpl.h@interface,code

.pull src/zfl_config_zpl.c@discuss,left

#### zfl_device - configure 0MQ devices and their sockets

.pull src/zfl_device.c@header,left

This is the class interface:

.pull include/zfl_device.h@interface,code

.pull src/zfl_device.c@discuss,left

#### zfl_thread - work with operating system threads

.pull src/zfl_thread.c@header,left

This is the class interface:

.pull include/zfl_thread.h@interface,code

.pull src/zfl_thread.c@discuss,left

### The Class Model

libzfl consists of classes, each class consisting of a .h and a .c. Classes may depend on other classes.

`zfl.h` includes all classes header files, all the time. For the user, libzfl forms one single package. All classes start by including `zfl.h`. All applications that use libzfl start by including `zfl.h`. `zfl.h` also defines a limited number of small, useful macros and typedefs that have proven useful for writing clearer C code.

The canonical example for libzfl style is the zfl_base class, which defines the template for all other classes. The nomenclature for all classes is consistent. We use zfl_base as an example:

* Source files: zfl_base.c, zfl_base.h
* Methods: zfl_base_test, zfl_base_print, ...

All classes are based on a flat C class system and follow these rules:

* Class typedef: `zfl_base_t`
* Constructor: `zfl_base_new`
* Destructor: `zfl_base_destroy`
* Property methods: `zfl_base_property_set`, `zfl_base_property`
* Class structures are private (defined in the .c source but not the .h)
* Properties are accessed only via methods named as described above.
* In the class source code the object is always called `self`.
* The constructor may take arbitrary arguments, and returns NULL on failure, or a new object.
* The destructor takes a pointer to an object reference and nullifies it.

Return values for methods are:

* For methods that return an object reference, either the reference, or NULL on failure.
* For methods that signal success/failure, a return value of 0 means sucess, -1 failure.

Private/static functions in a class are named `s_functionname` and are not exported via the header file.

All classes have a test method called `zfl_classname_test`.

### libzfl Classes

These are the existing libzfl classes:

* zfl_base - base class for libzfl
* zfl_blob - binary long object
* zfl_config - work with configuration files
* zfl_config_json - work with JSON configuration files
* zfl_config_zpl - work with ZPL configuration files
* zfl_device - configure a device or device socket
* zfl_thread - work with operating system threads

### Error Handling

Functions that create or search objects return object references success and NULL on failure.  Functions that perform work return 0 on success and -1 on failure.

## Design Ideology

### The Problem with C

C has the significant advantage of being a small language that, if we take a little care with formatting and naming, can be easily interchanged between developers. Every C developer will use much the same 90% of the language. Larger languages like C++ provide powerful abstractions like STL containers but at the cost of interchange. Every C++ developer will use a different 20% of the language.

The huge problem with C is that any realistic application needs packages of functionality to bring the language up to the levels we expect for the 21st century. Much can be done by using external libraries but every additional library is a dependency that makes the resulting applications harder to build and port. While C itself is a highly portable language (and can be made more so by careful use of the preprocessor), most C libraries consider themselves part of the operating system, and as such do not attempt to be portable.

The answer to this, as we learned from building enterprise-level C applications at iMatix from 1995-2005, is to create our own fully portable, high-quality libraries of pre-packaged functionality, in C. Doing this right solves both the requirements of richness of the language, and of portability of the final applications.

### A Simple Class Model

C has no standard API style. It is one thing to write a useful component, but something else to provide an API that is consistent and obvious across many components. We learned from building [OpenAMQ](http://www.openamq.org), a messaging client and server of 0.5M LoC, that a consistent model for extending C makes life for the application developer much easier.

The general model is that of a class (the source package) that provides objects (in fact C structures). The application creates objects and then works with them. When done, the application destroys the object. In C, we tend to use the same name for the object as the class, when we can, and it looks like this (to take a fictitious libzfl class):

    zfl_regexp_t *regexp = zfl_regexp_new (regexp_string);
    if (!regexp)
        printf ("E: invalid regular expression: %s\n", regexp_string);
    else
    if (zfl_regexp_match (regexp, input_buffer))
        printf ("I: successful match for %s\n", input buffer);
    zfl_regexp_destroy (&regexp);

As far as the C program is concerned, the object is a reference to a structure (not a void pointer). We pass the object reference to all methods, since this is still C. We could do weird stuff like put method addresses into the structure so that we can emulate a C++ syntax but it's not worthwhile. The goal is not to emulate an OO system, it's simply to gain consistency. The constructor returns an object reference, or NULL if it fails. The destructor nullifies the class pointer, and is idempotent.

What we aim at here is the simplest possible consistent syntax.

No model is fully consistent, and classes can define their own rules if it helps make a better result. For example:

* Some classes may not be opaque. For example, we have cases of generated serialization classes that encode and decode structures to/from binary buffers. It feels clumsy to have to use methods to access the properties of these classes.

* While every class has a new method that is the formal constructor, some methods may also act as constructors. For example, a "dup" method might take one object and return a second object.

* While every class has a destroy method that is the formal destructor, some methods may also act as destructors. For example, a method that sends an object may also destroy the object (so that ownership of any buffers can passed to background threads). Such methods take the same "pointer to a reference" argument as the destroy method.

### Naming Style

libzfl aims for short, consistent names, following the theory that names we use most often should be shortest. Classes get one-word names, unless they are part of a family of classes in which case they may be two words, the first being the family name. Methods, similarly, get one-word names and we aim for consistency across classes (so a method that does something semantically similar in two classes will get the same name in both). So the canonical name for any method is:

    zfl_classname_methodname

And the reader can easily parse this without needing special syntax to separate the class name from the method name.

### Portability

Creating a portable C application can be rewarding in terms of maintaining a single code base across many platforms, and keeping (expensive) system-specific knowledge separate from application developers. In most projects (like 0MQ core), there is no portability layer and application code does conditional compilation for all mixes of platforms. This leads to quite messy code.

libzfl is explicitly meant to become a portability layer, similar to but thinner than libraries like the [Apache Portable Runtime](http://apr.apache.org) (APR).

These are the places a C application is subject to arbitrary system differences:

* Different compilers may offer slightly different variants of the C language, often lacking specific types or using neat non-portable names. Windows is a big culprit here. We solve this by 'patching' the language in czmq_prelude.h, e.g. defining int64_t on Windows.
* System header files are inconsistent, i.e. you need to include different files depending on the OS type and version. We solve this by pulling in all necessary header files in czmq_prelude.h. This is a proven brute-force approach that increases recompilation times but eliminates a major source of pain.
* System libraries are inconsistent, i.e. you need to link with different libraries depending on the OS type and version. We solve this with an external compilation tool, 'C', which detects the OS type and version (at runtime) and builds the necessary link commands.
* System functions are inconsistent, i.e. you need to call different functions depending, again, on OS type and version. We solve this by building small abstract classes that handle specific areas of functionality, and doing conditional compilation in these.

An example of the last:

    #if (defined (__UNIX__))
        pid = GetCurrentProcessId();
    #elif (defined (__WINDOWS__))
        pid = getpid ();
    #else
        pid = 0;
    #endif

libzfl uses the GNU autotools system, so non-portable code can use the macros this defines. It can also use macros defined by the czmq_prelude.h header file.

### Technical Aspects

* *Thread safety*: the use of opaque structures is thread safe, though 0MQ applications should not share state between threads in any case.
* *Name spaces*: we prefix class names with `zfl_`, which ensures that all exported functions are globally safe.
* *Library versioning*: we don't make any attempt to version the library at this stage. Classes are in our experience highly stable once they are built and tested, the only changes typically being added methods.
* *Performance*: for critical path processing, you may want to avoid creating and destroying classes. However on modern Linux systems the heap allocator is very fast. Individual classes can choose whether or not to nullify their data on allocation.
* *Self-testing*: every class has a `selftest` method that runs through the methods of the class. In theory, calling all selftest functions of all classes does a full unit test of the library. The `zfl_selftest` application does this.
* *Portability*: the libzfl library is aimed at becoming a portability layer (like Apache APR or the older iMatix SFL) but that depends on it actually being ported. See section on 'Porting libzfl' below.
* *Memory management*: libzfl classes do not use any special memory management techiques to detect leaks. We've done this in the past but it makes the code relatively complex. Instead, we do memory leak testing using tools like valgrind.

## Under the Hood

### Adding a New Class

If you define a new libzfl class `myclass` you need to:

* Write the `zfl_myclass.c` and `zfl_myclass.h` source files, in `zfl/src` and `zfl/include` respectively.
* Add`#include <zfl_myclass.h>` to `zfl/include/zfl.h`.
* Add the myclass header and test call to `src/zfl_selftest.c`.
* Add a reference documentation to 'doc/zfl_myclass.txt'.
* Add myclass to 'src/Makefile.am` and `doc/Makefile.am`.

The `bin/newclass.sh` shell script will automate these steps for you.

### Coding Style

In general the zfl_base class defines the style for the whole library. The overriding rules for coding style are consistency, clarity, and ease of maintenance. We use the C99 standard for syntax including principally:

* The // comment style.
* Variables definitions placed in or before the code that uses them.

So while ANSI C code might say:

    zfl_blob_t *file_buffer;       /*  Buffer for our file */
    ... (100 lines of code)
    file_buffer = zfl_blob_new ();
    ...

The style in libzfl would be:

    zfl_blob_t *file_buffer = zfl_blob_new ();

### Assertions

We use assertions heavily to catch bad argument values. The libzfl classes do not attempt to validate arguments and report errors; bad arguments are treated as fatal application programming errors.

We also use assertions heavily on calls to system functions that are never supposed to fail, where failure is to be treated as a fatal non-recoverable error (e.g. running out of memory).

Assertion code should always take this form:

    int rc = some_function (arguments);
    assert (rc == 0);

Rather than the side-effect form:

    assert (some_function (arguments) == 0);

Since assertions may be removed by an optimizing compiler.

### Documentation

Man pages are generated from the class header and source files via the doc/mkman tool, and similar functionality in the gitdown tool (http://github.com/imatix/gitdown). The header file for a class must wrap its interface as follows:

    //  @interface
    ... prototypes and public typedefs
    //  @end

The source file for a class must provide documentation as follows:

    /*
    @header
    ...short explanation of class...
    @discuss
    ...longer discussion of how it works...
    @end
    */

The source file for a class then provides the self test example as follows:

    //  @selftest
    ...test code and functions
    //  @end

The template for man pages is in doc/mkman.

### Porting libzfl

When you try libzfl on an OS that it's not been used on (ever, or for a while), you will hit code that does not compile. In some cases the patches are trivial, in other cases (usually when porting to Windows), the work needed to build equivalent functionality may be quite heavy. In any case, the benefit is that once ported, the functionality is available to all applications.

Before attempting to patch code for portability, please read the `czmq_prelude.h` header file. There are several typical types of changes you may need to make to get functionality working on a specific operating system:

* Defining typedefs which are missing on that specific compiler: do this in czmq_prelude.h.
* Defining macros that rename exotic library functions to more conventional names: do this in czmq_prelude.h.
* Reimplementing specific methods to use a non-standard API: this is typically needed on Windows. Do this in the relevant class, using #ifdefs to properly differentiate code for different platforms.

The canonical 'standard operating system' for all libzfl code is Linux, gcc, POSIX.

### This Document

This document is originally at README.txt and is built using [gitdown](http://github.com/imatix/gitdown).
