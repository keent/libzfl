
<A name="toc1-3" title="ZFL - ØMQ Function Library" />
# ZFL - ØMQ Function Library

<A name="toc2-6" title="Contents" />
## Contents


**<a href="#toc2-11">Overview</a>**
&emsp;<a href="#toc3-14">Scope and Goals</a>
&emsp;<a href="#toc3-23">Ownership and License</a>
&emsp;<a href="#toc3-30">Contributing</a>

**<a href="#toc2-41">Using ZFL</a>**
&emsp;<a href="#toc3-44">Building and Installing</a>
&emsp;<a href="#toc3-65">Linking with an Application</a>
&emsp;<a href="#toc3-76">API Summary</a>
&emsp;<a href="#toc4-79">zfl_xxx  - yyy</a>
&emsp;<a href="#toc3-90">The Class Model</a>
&emsp;<a href="#toc3-123">ZFL Classes</a>
&emsp;<a href="#toc3-136">Error Handling</a>

**<a href="#toc2-141">Design Ideology</a>**
&emsp;<a href="#toc3-144">The Problem with C</a>
&emsp;<a href="#toc3-153">A Simple Class Model</a>
&emsp;<a href="#toc3-180">Naming Style</a>
&emsp;<a href="#toc3-189">Portability</a>
&emsp;<a href="#toc3-215">Technical Aspects</a>

**<a href="#toc2-226">Under the Hood</a>**
&emsp;<a href="#toc3-229">Adding a New Class</a>
&emsp;<a href="#toc3-242">Coding Style</a>
&emsp;<a href="#toc3-261">Assertions</a>
&emsp;<a href="#toc3-279">Documentation</a>
&emsp;<a href="#toc3-284">Porting ZFL</a>
&emsp;<a href="#toc3-297">This Document</a>

<A name="toc2-11" title="Overview" />
## Overview

<A name="toc3-14" title="Scope and Goals" />
### Scope and Goals

ZFL is the ØMQ Function Library, a thin portability & function library for ZeroMQ applications in C/C++. It is written as clear readable C classes, portable to all ØMQ platforms, and licensed under the LGPL.

The main goal is to allow the construction of industrial-scale ØMQ services and devices that integrate properly with the operating system, while staying 100% portable. ZFL acts as a primary abstraction layer on top of the ØMQ API, mainly for C applications but also for other languages. ZFL is inspired by the iMatix Standard Function Library (SFL), and borrows liberally from it. See http://legacy.imatix.com/html/sfl/.

ZFL is meant to be lightweight, consistent, class-based, minimalistic, highly efficient, and aimed at making it faster and easier to develop realistic, secure, and portable ØMQ devices and applications.

<A name="toc3-23" title="Ownership and License" />
### Ownership and License

ZFL is maintained by Pieter Hintjens and Martin Hurton (code) and Mikko Koppanen (build system). Its other authors and contributors are listed in the AUTHORS file. It is held by the ZeroMQ organization at github.com.

The authors of ZFL grant you use of this software under the terms of the GNU Lesser General Public License (LGPL). For details see the files `COPYING` and `COPYING.LESSER` in this directory.

<A name="toc3-30" title="Contributing" />
### Contributing

To submit an issue use the [issue tracker](http://github.com/zeromq/zfl/issues). All discussion happens on the [zeromq-dev](zeromq-dev@lists.zeromq.org) list or #zeromq IRC channel at irc.freenode.net.

The proper way to submit patches is to clone this repository, make your changes, and use git to create a patch. See http://www.zeromq.org/docs:contributing. All contributors are listed in AUTHORS.

All classes are maintained by a single person, who is the responsible editor for that class and who is named in the header as such. This is usually the originator of the class. When several people collaborate on a class, one single person is always the lead maintainer and the one to blame when it breaks.

The general rule is, if you contribute code to ZFL you must be willing to maintain it as long as there are users of it. Code with no active maintainer will in general be deprecated and/or removed.

<A name="toc2-41" title="Using ZFL" />
## Using ZFL

<A name="toc3-44" title="Building and Installing" />
### Building and Installing

ZFL uses autotools for packaging. To build from git (all example commands are for Linux):

    git clone git://github.com/zeromq/zfl.git
    cd zfl
    sh autogen.sh
    ./configure
    make all
    sudo make install
    sudo ldconfig

You will need the libtool and autotools packages. On FreeBSD, you may need to specify the default directories for configure:

    ./configure --with-zeromq=/usr/local

After building, you can run the ZFL selftests:

    make check

<A name="toc3-65" title="Linking with an Application" />
### Linking with an Application

Include `zfl.h` in your application and link with libzfl. Here is a typical gcc link command:

    gcc -lzfl -lzmq myapp.c -o myapp

You should read `zfl.h`. This file includes `zmq.h` and the system header files that typical ØMQ applications will need. The provided 'c' shell script lets you write simple portable build scripts:

    c -lzfl -lzmq -l myapp

<A name="toc3-76" title="API Summary" />
### API Summary

<A name="toc4-79" title="zfl_xxx  - yyy" />
#### zfl_xxx  - yyy

