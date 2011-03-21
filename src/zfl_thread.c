/*  =========================================================================
    zfl_thread.c - work with operating system threads

    Provides a portable API for creating, killing, and waiting on operating
    system threads. Used instead of pthreads, which is not portable to all
    platforms. Does not provide a thread cancellation method since that leads
    to unstable code. Send 0MQ messages to tell a worker thread to end.

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
#include "../include/zfl_thread.h"

//  Structure of our class

struct _zfl_thread_t {
#if defined (__UNIX__)
    pthread_t
        thread;
#elif defined (__WINDOWS__)
    HANDLE handle;
    void *(*thread_fn) (void *);
    void *thread_args;
#else
#   error "Platform not supported by zfl_thread class"
#endif
};


#if defined (__WINDOWS__)
//  Thread shim for Windows that wraps a POSIX-style thread handler
//  and does the _endthreadex for us automatically.

unsigned __stdcall s_call_thread_fn (void *args)
{
    assert (args);
    zfl_thread_t *self = (zfl_thread_t *) args;
    void *rc = self->thread_fn (self->thread_args);
    _endthreadex (0);
    return 0;
}
#endif

//  --------------------------------------------------------------------------
//  Constructor - create a new thread
//
//  Takes the same arguments as the POSIX pthread_create call. Returns a new
//  zfl_thread_t object which you use for subsequent work with this thread.
//  Child threads are started with the same priority as the calling thread.
//  Returns NULL if it was not possible to create the thread.

zfl_thread_t *
zfl_thread_new (void *(*thread_fn) (void *), void *args)
{
    zfl_thread_t
        *self;

    self = (zfl_thread_t *) zmalloc (sizeof (zfl_thread_t));
#if defined (__UNIX__)
    int rc = pthread_create (&self->thread, NULL, thread_fn, args);
    if (rc == 0)
        //  Ensure thread memory is freed when thread exits
        pthread_detach (self->thread);
    else
        zfl_thread_destroy (&self);
#elif defined (__WINDOWS__)
    self->thread_fn = thread_fn;
    self->thread_args = args;
    self->handle = (HANDLE)_beginthreadex(
        NULL,                   //  Handle is private to this process
        0,                      //  Use a default stack size for new thread
        &s_call_thread_fn,      //  Start real thread function via this shim
        self,                   //  Which gets the current object as argument
        CREATE_SUSPENDED,       //  Set thread priority before starting it
        NULL);                  //  We don't use the thread ID

    if (self->handle) {
        //  Set child thread priority to same as current
        int priority = GetThreadPriority (GetCurrentThread ());
        SetThreadPriority (self->handle, priority);
        //  Now start thread
        ResumeThread (self->handle);
    }
    else                        //  Could not create child thread
        zfl_thread_destroy (&self);
#endif
    return self;
}


//  --------------------------------------------------------------------------
//  Destructor - destroy a thread
//
//  Waits for thread to complete if necessary.

void
zfl_thread_destroy (zfl_thread_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        zfl_thread_t *self = *self_p;
        //  If thread did not yet finish, wait for it to complete
        zfl_thread_wait (self);
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Wait for thread to complete. This method pauses execution of the calling
//  thread indefinitely, until the specified thread has finished. Returns
//  zero if successful, -1 if there was an error.

int
zfl_thread_wait (zfl_thread_t *self)
{
    assert (self);
#if defined (__UNIX__)
    int rc = pthread_join (self->thread, NULL);
#elif defined (__WINDOWS__)
    int rc = WaitForSingleObject (self->handle, INFINITE);
    if (rc != -1) {
        CloseHandle (self->handle);
        rc = 0;
    }
#endif
    return rc;
}


//  --------------------------------------------------------------------------
//  Selftest

//  We pass these arguments to the child thread
typedef struct {
    Bool verbose;               //  Display trace information?
    int number;                 //  Thread number for debugging
    int delay;                  //  How long to sleep for, in msecs
} s_thread_args_t;

static void *
s_test_thread (void *args_ptr)
{
    zfl_clock_t
        *clock = zfl_clock_new ();
    s_thread_args_t
        *args = (s_thread_args_t *) args_ptr;

    if (args->verbose) {
        printf ("Thread %d starts...\n", args->number);
        fflush (stdout);
    }
    zfl_clock_sleep (clock, args->delay);
    if (args->verbose) {
        printf ("Thread %d ends\n", args->number);
        fflush (stdout);
    }
    zfl_clock_destroy (&clock);
    return NULL;
}

int
zfl_thread_test (Bool verbose)
{
    zfl_thread_t
        *thread;
    zfl_clock_t
        *clock = zfl_clock_new ();
    int rc;

    printf (" * zfl_thread: ");

    //  Test a thread that just runs and finishes
    s_thread_args_t args1 = { verbose, 1, 100 };
    thread = zfl_thread_new (s_test_thread, &args1);
    assert (thread);
    rc = zfl_thread_wait (thread);
    assert (rc == 0);
    zfl_thread_destroy (&thread);
    assert (thread == NULL);

    //  Test wait method on a thread that's already finished
    s_thread_args_t args2 = { verbose, 2, 0 };
    thread = zfl_thread_new (s_test_thread, &args2);
    assert (thread);
    zfl_clock_sleep (clock, 100);
    rc = zfl_thread_wait (thread);
    assert (rc == 0);
    zfl_thread_destroy (&thread);
    assert (thread == NULL);

    //  Test destructor on thread that is still running
    s_thread_args_t args3 = { verbose, 3, 100 };
    thread = zfl_thread_new (s_test_thread, &args3);
    assert (thread);
    zfl_thread_destroy (&thread);
    assert (thread == NULL);

    //  Test destructor on thread that's already finished
    s_thread_args_t args4 = { verbose, 4, 0 };
    thread = zfl_thread_new (s_test_thread, &args4);
    assert (thread);
    zfl_clock_sleep (clock, 100);
    zfl_clock_destroy (&clock);

    //  Destructor should be safe to call twice
    zfl_thread_destroy (&thread);
    zfl_thread_destroy (&thread);
    assert (thread == NULL);


    printf ("OK\n");
    return 0;
}
