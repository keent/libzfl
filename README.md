
<A name="toc1-3" title="libzfl - High-level C library for ØMQ" />
# libzfl - High-level C library for ØMQ

<A name="toc2-6" title="Contents" />
## Contents


**<a href="#toc2-11">Overview</a>**
&emsp;<a href="#toc3-14">Scope and Goals</a>
&emsp;<a href="#toc3-23">Ownership and License</a>
&emsp;<a href="#toc3-30">Contributing</a>

**<a href="#toc2-41">Using libzfl</a>**
&emsp;<a href="#toc3-44">Dependencies</a>
&emsp;<a href="#toc3-49">Building and Installing</a>
&emsp;<a href="#toc3-70">Linking with an Application</a>
&emsp;<a href="#toc3-81">API Summary</a>
&emsp;<a href="#toc4-84">zfl_base - libzfl base class</a>
&emsp;<a href="#toc4-95">zfl_bits - bitstring manipulation - in-progress</a>
&emsp;<a href="#toc4-106">zfl_blob - work with binary long objects (blobs)</a>
&emsp;<a href="#toc4-117">zfl_config - work with configuration files</a>
&emsp;<a href="#toc4-128">zfl_config_json - load JSON file into zfl_config structure</a>
&emsp;<a href="#toc4-139">zfl_config_zpl - load ZPL file into zfl_config structure</a>
&emsp;<a href="#toc4-150">zfl_device - configure ØMQ devices and their sockets</a>
&emsp;<a href="#toc4-161">zfl_thread - work with operating system threads</a>
&emsp;<a href="#toc3-172">The Class Model</a>
&emsp;<a href="#toc3-205">libzfl Classes</a>
&emsp;<a href="#toc3-218">Error Handling</a>

**<a href="#toc2-223">Design Ideology</a>**
&emsp;<a href="#toc3-226">The Problem with C</a>
&emsp;<a href="#toc3-235">A Simple Class Model</a>
&emsp;<a href="#toc3-262">Naming Style</a>
&emsp;<a href="#toc3-271">Portability</a>
&emsp;<a href="#toc3-297">Technical Aspects</a>

**<a href="#toc2-308">Under the Hood</a>**
&emsp;<a href="#toc3-311">Adding a New Class</a>
&emsp;<a href="#toc3-324">Coding Style</a>
&emsp;<a href="#toc3-343">Assertions</a>
&emsp;<a href="#toc3-361">Documentation</a>
&emsp;<a href="#toc3-388">Porting libzfl</a>
&emsp;<a href="#toc3-401">This Document</a>

<A name="toc2-11" title="Overview" />
## Overview

<A name="toc3-14" title="Scope and Goals" />
### Scope and Goals

libzfl is a thin portability & function library for ZeroMQ applications in C/C++. It is written as clear readable C classes, portable to all ØMQ platforms, and licensed under the LGPL.

The main goal is to allow the construction of industrial-scale ØMQ services and devices that integrate properly with the operating system, while staying 100% portable. libzfl acts as a primary abstraction layer on top of the ØMQ API, mainly for C applications but also for other languages. libzfl is inspired by the iMatix Standard Function Library (SFL), and borrows liberally from it. See http://legacy.imatix.com/html/sfl/.

libzfl is meant to be lightweight, consistent, class-based, minimalistic, highly efficient, and aimed at making it faster and easier to develop realistic, secure, and portable ØMQ devices and applications.

<A name="toc3-23" title="Ownership and License" />
### Ownership and License

libzfl is maintained by Pieter Hintjens and Martin Hurton (code) and Mikko Koppanen (build system). Its other authors and contributors are listed in the AUTHORS file. It is held by the ZeroMQ organization at github.com.

The authors of libzfl grant you use of this software under the terms of the GNU Lesser General Public License (LGPL). For details see the files `COPYING` and `COPYING.LESSER` in this directory.

<A name="toc3-30" title="Contributing" />
### Contributing

To submit an issue use the [issue tracker](http://github.com/zeromq/zfl/issues). All discussion happens on the [zeromq-dev](zeromq-dev@lists.zeromq.org) list or #zeromq IRC channel at irc.freenode.net.

The proper way to submit patches is to clone this repository, make your changes, and use git to create a patch. See http://www.zeromq.org/docs:contributing. All contributors are listed in AUTHORS.

All classes are maintained by a single person, who is the responsible editor for that class and who is named in the header as such. This is usually the originator of the class. When several people collaborate on a class, one single person is always the lead maintainer and the one to blame when it breaks.

The general rule is, if you contribute code to libzfl you must be willing to maintain it as long as there are users of it. Code with no active maintainer will in general be deprecated and/or removed.

<A name="toc2-41" title="Using libzfl" />
## Using libzfl

<A name="toc3-44" title="Dependencies" />
### Dependencies

libzfl depends on [CZMQ](http://czmq.zeromq.org). Please build and install CZMQ before building and installing libzfl.

<A name="toc3-49" title="Building and Installing" />
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

<A name="toc3-70" title="Linking with an Application" />
### Linking with an Application

Include `zfl.h` in your application and link with libzfl. Here is a typical gcc link command:

    gcc -lzfl -lzmq myapp.c -o myapp

You should read `zfl.h`. This file includes `zmq.h` and the system header files that typical ØMQ applications will need. The provided 'c' shell script lets you write simple portable build scripts:

    c -lzfl -lzmq -l myapp

<A name="toc3-81" title="API Summary" />
### API Summary

<A name="toc4-84" title="zfl_base - libzfl base class" />
#### zfl_base - libzfl base class

Provides manual template for new classes, and canonical style guidelines
for all ZFL source code.

This is the class interface:

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


<A name="toc4-95" title="zfl_bits - bitstring manipulation - in-progress" />
#### zfl_bits - bitstring manipulation - in-progress

Provides manual template for new classes, and canonical style guidelines
for all ZFL source code.

This is the class interface:

    //  Create a new bitstring object
    zfl_bits_t *
        zfl_bits_new (void);
    
    //  Destroy a bitstring object
    void
        zfl_bits_destroy (zfl_bits_t **self_p);
    
    //  Example method
    int
        zfl_bits_filler (zfl_bits_t *self);
    
    //  Example method
    void
        zfl_bits_filler_set (zfl_bits_t *self, int newvalue);
    
    //  Self test of this class
    int
        zfl_bits_test (Bool verbose);


<A name="toc4-106" title="zfl_blob - work with binary long objects (blobs)" />
#### zfl_blob - work with binary long objects (blobs)

Manipulates opaque binary objects including reading and writing from/to
files.  Example use case is for loading config data from stdin or file
for processing by zfl_config.

This is the class interface:

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


<A name="toc4-117" title="zfl_config - work with configuration files" />
#### zfl_config - work with configuration files

Loads a configuration file formatted in JSON or in ZPL format as defined
by rfc.zeromq.org/spec:4/zpl. Provides methods to navigate this data and
access property values. See zfl_config.c for examples of use.

This is the class interface:

    //  Function that executes config
    typedef int (zfl_config_fct) (zfl_config_t *self, void *arg, int level);
    
    //
    zfl_config_t *
        zfl_config_new (char *name, zfl_config_t *parent);
    
    //
    void
        zfl_config_destroy (zfl_config_t **self_p);
    
    //
    zfl_config_t *
        zfl_config_load (char *filename);
    
    //
    int
        zfl_config_save (zfl_config_t *self, char *filename);
    
    //
    zfl_config_t *
        zfl_config_child (zfl_config_t *self);
    
    //
    zfl_config_t *
        zfl_config_next (zfl_config_t *self);
    
    //
    zfl_config_t *
        zfl_config_locate (zfl_config_t *self, char *path);
    
    //
    char *
        zfl_config_resolve (zfl_config_t *self, char *path, char *default_value);
    
    //
    zfl_config_t *
        zfl_config_at_depth (zfl_config_t *self, int level);
    
    //
    char *
        zfl_config_name (zfl_config_t *self);
    
    //
    int
        zfl_config_set_name (zfl_config_t *self, char *name);
    
    //
    zfl_blob_t *
        zfl_config_value (zfl_config_t *self);
    
    //
    int
        zfl_config_set_value (zfl_config_t *self, zfl_blob_t *blob);
    
    //
    char *
        zfl_config_string (zfl_config_t *self);
    
    //
    int
        zfl_config_set_string (zfl_config_t *self, char *string);
    
    //
    int
        zfl_config_set_printf (zfl_config_t *self, char *format, ...);
    
    //
    int
        zfl_config_execute (zfl_config_t *self, zfl_config_fct handler, void *arg);
    
    //
    int
        zfl_config_dump (zfl_config_t *self);
    
    //  Self test of this class
    int
        zfl_config_test (Bool verbose);


<A name="toc4-128" title="zfl_config_json - load JSON file into zfl_config structure" />
#### zfl_config_json - load JSON file into zfl_config structure

Loads a JSON file into a zfl_config structure.  Does not provide detailed
error reporting.  To verify your JSON files use http://www.jsonlint.com.
This version uses the cJSON library.

This is the class interface:

    //  Create new zfl_config object from JSON string
    zfl_config_t *
        zfl_config_json (char *json_string);
    
    //  Create new zfl_config object from JSON file
    zfl_config_t *
        zfl_config_json_file (char *filename);
    
    //  Self test of this class
    int
        zfl_config_json_test (Bool verbose);


<A name="toc4-139" title="zfl_config_zpl - load ZPL file into zfl_config structure" />
#### zfl_config_zpl - load ZPL file into zfl_config structure

Loads a ZPL property set as defined at http://rfc.zeromq.org/spec:4 into
a new zfl_config_t structure. This code would be a LOT shorter in Perl.

This is the class interface:

    //  Create new zfl_config object from ZPL string
    zfl_config_t *
        zfl_config_zpl (char *zpl_string);
    
    //  Create new zfl_config object from ZPL file
    zfl_config_t *
        zfl_config_zpl_file (char *filename);
    
    //  Self test of this class
    int
        zfl_config_zpl_test (Bool verbose);


<A name="toc4-150" title="zfl_device - configure ØMQ devices and their sockets" />
#### zfl_device - configure ØMQ devices and their sockets

Used to configure ØMQ devices and their sockets. Takes configuration data
from a zfl_config object, and implements the rfc.zeromq.org/spec:5/zdcf
specification. Use this class to for stand-alone devices. Do not use for
built-in devices (i.e. which operate as threads of larger processes). See
examples/zdevice.c for a working example.

This is the class interface:

    //
    zfl_device_t *
        zfl_device_new (char *filename);
    
    //
    void
        zfl_device_destroy (zfl_device_t **self_p);
    
    //
    void *
        zfl_device_context (zfl_device_t *self);
    
    //
    Bool
        zfl_device_verbose (zfl_device_t *self);
    
    //
    char *
        zfl_device_locate (zfl_device_t *self, int index);
    
    //
    char *
        zfl_device_property (zfl_device_t *self, char *device_name, char *property);
    
    //
    void *
        zfl_device_socket (zfl_device_t *self, char *device, char *socket_name, int type);
    
    //  Self test of this class
    int
        zfl_device_test (Bool verbose);


<A name="toc4-161" title="zfl_thread - work with operating system threads" />
#### zfl_thread - work with operating system threads

Provides a portable API for creating, killing, and waiting on operating
system threads. Used instead of pthreads, which is not portable to all
platforms. Does not provide a thread cancellation method since that leads
to unstable code. Send ØMQ messages to tell a worker thread to end.

This is the class interface:

    zfl_thread_t *
        zfl_thread_new (void *(*thread_fn) (void *), void *args);
    
    //
    void
        zfl_thread_destroy (zfl_thread_t **self_p);
    
    //
    int
        zfl_thread_wait (zfl_thread_t *self);
    
    //  Self test of this class
    int
        zfl_thread_test (Bool verbose);


<A name="toc3-172" title="The Class Model" />
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

<A name="toc3-205" title="libzfl Classes" />
### libzfl Classes

These are the existing libzfl classes:

* zfl_base - base class for libzfl
* zfl_blob - binary long object
* zfl_config - work with configuration files
* zfl_config_json - work with JSON configuration files
* zfl_config_zpl - work with ZPL configuration files
* zfl_device - configure a device or device socket
* zfl_thread - work with operating system threads

<A name="toc3-218" title="Error Handling" />
### Error Handling

Functions that create or search objects return object references success and NULL on failure.  Functions that perform work return 0 on success and -1 on failure.

<A name="toc2-223" title="Design Ideology" />
## Design Ideology

<A name="toc3-226" title="The Problem with C" />
### The Problem with C

C has the significant advantage of being a small language that, if we take a little care with formatting and naming, can be easily interchanged between developers. Every C developer will use much the same 90% of the language. Larger languages like C++ provide powerful abstractions like STL containers but at the cost of interchange. Every C++ developer will use a different 20% of the language.

The huge problem with C is that any realistic application needs packages of functionality to bring the language up to the levels we expect for the 21st century. Much can be done by using external libraries but every additional library is a dependency that makes the resulting applications harder to build and port. While C itself is a highly portable language (and can be made more so by careful use of the preprocessor), most C libraries consider themselves part of the operating system, and as such do not attempt to be portable.

The answer to this, as we learned from building enterprise-level C applications at iMatix from 1995-2005, is to create our own fully portable, high-quality libraries of pre-packaged functionality, in C. Doing this right solves both the requirements of richness of the language, and of portability of the final applications.

<A name="toc3-235" title="A Simple Class Model" />
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

<A name="toc3-262" title="Naming Style" />
### Naming Style

libzfl aims for short, consistent names, following the theory that names we use most often should be shortest. Classes get one-word names, unless they are part of a family of classes in which case they may be two words, the first being the family name. Methods, similarly, get one-word names and we aim for consistency across classes (so a method that does something semantically similar in two classes will get the same name in both). So the canonical name for any method is:

    zfl_classname_methodname

And the reader can easily parse this without needing special syntax to separate the class name from the method name.

<A name="toc3-271" title="Portability" />
### Portability

Creating a portable C application can be rewarding in terms of maintaining a single code base across many platforms, and keeping (expensive) system-specific knowledge separate from application developers. In most projects (like ØMQ core), there is no portability layer and application code does conditional compilation for all mixes of platforms. This leads to quite messy code.

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

<A name="toc3-297" title="Technical Aspects" />
### Technical Aspects

* *Thread safety*: the use of opaque structures is thread safe, though ØMQ applications should not share state between threads in any case.
* *Name spaces*: we prefix class names with `zfl_`, which ensures that all exported functions are globally safe.
* *Library versioning*: we don't make any attempt to version the library at this stage. Classes are in our experience highly stable once they are built and tested, the only changes typically being added methods.
* *Performance*: for critical path processing, you may want to avoid creating and destroying classes. However on modern Linux systems the heap allocator is very fast. Individual classes can choose whether or not to nullify their data on allocation.
* *Self-testing*: every class has a `selftest` method that runs through the methods of the class. In theory, calling all selftest functions of all classes does a full unit test of the library. The `zfl_selftest` application does this.
* *Portability*: the libzfl library is aimed at becoming a portability layer (like Apache APR or the older iMatix SFL) but that depends on it actually being ported. See section on 'Porting libzfl' below.
* *Memory management*: libzfl classes do not use any special memory management techiques to detect leaks. We've done this in the past but it makes the code relatively complex. Instead, we do memory leak testing using tools like valgrind.

<A name="toc2-308" title="Under the Hood" />
## Under the Hood

<A name="toc3-311" title="Adding a New Class" />
### Adding a New Class

If you define a new libzfl class `myclass` you need to:

* Write the `zfl_myclass.c` and `zfl_myclass.h` source files, in `zfl/src` and `zfl/include` respectively.
* Add`#include <zfl_myclass.h>` to `zfl/include/zfl.h`.
* Add the myclass header and test call to `src/zfl_selftest.c`.
* Add a reference documentation to 'doc/zfl_myclass.txt'.
* Add myclass to 'src/Makefile.am` and `doc/Makefile.am`.

The `bin/newclass.sh` shell script will automate these steps for you.

<A name="toc3-324" title="Coding Style" />
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

<A name="toc3-343" title="Assertions" />
### Assertions

We use assertions heavily to catch bad argument values. The libzfl classes do not attempt to validate arguments and report errors; bad arguments are treated as fatal application programming errors.

We also use assertions heavily on calls to system functions that are never supposed to fail, where failure is to be treated as a fatal non-recoverable error (e.g. running out of memory).

Assertion code should always take this form:

    int rc = some_function (arguments);
    assert (rc == 0);

Rather than the side-effect form:

    assert (some_function (arguments) == 0);

Since assertions may be removed by an optimizing compiler.

<A name="toc3-361" title="Documentation" />
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

<A name="toc3-388" title="Porting libzfl" />
### Porting libzfl

When you try libzfl on an OS that it's not been used on (ever, or for a while), you will hit code that does not compile. In some cases the patches are trivial, in other cases (usually when porting to Windows), the work needed to build equivalent functionality may be quite heavy. In any case, the benefit is that once ported, the functionality is available to all applications.

Before attempting to patch code for portability, please read the `czmq_prelude.h` header file. There are several typical types of changes you may need to make to get functionality working on a specific operating system:

* Defining typedefs which are missing on that specific compiler: do this in czmq_prelude.h.
* Defining macros that rename exotic library functions to more conventional names: do this in czmq_prelude.h.
* Reimplementing specific methods to use a non-standard API: this is typically needed on Windows. Do this in the relevant class, using #ifdefs to properly differentiate code for different platforms.

The canonical 'standard operating system' for all libzfl code is Linux, gcc, POSIX.

<A name="toc3-401" title="This Document" />
### This Document

This document is originally at README.txt and is built using [gitdown](http://github.com/imatix/gitdown).
