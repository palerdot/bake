/* Copyright (c) 2010-2018 Sander Mertens
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/** @file
 * @section base Corto base platform definitions.
 * @brief Provide a stable platform/compiler independent set of definitions
 */

#ifndef UT_BASE_H
#define UT_BASE_H

#if UT_IMPL && defined _MSC_VER
#define UT_EXPORT __declspec(dllexport)
#elif UT_IMPL
#define UT_EXPORT __attribute__((__visibility__("default")))
#elif defined _MSC_VER
#define UT_EXPORT __declspec(dllimport)
#else
#define UT_EXPORT
#endif


/* Standard C library */
#include <alloca.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* OS-specific headers */
#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#else
#include <fnmatch.h>
#include <inttypes.h>
#include <execinfo.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <ftw.h>
#include <fcntl.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif
#endif

#ifdef __cplusplus
#ifndef UT_CPP_H

/* Cpp headers */
#include <utility>
#endif
extern "C" {
#endif

#ifndef NDEBUG
#define UT_MAGIC (0x6B6F7274)
#define UT_MAGIC_DESTRUCT (0x74726F6B)
#endif

/*
 * Configuration parameters
 *   Increasing these numbers will increase memory usage of Corto in various
 *   scenario's.
 */

/* The maximum nesting level of objects in the hierarchy. There are in total
 * 62 orders of magnitude in the universe, so 64 should be adequate to organize
 * most information sets.
 */
#define UT_MAX_SCOPE_DEPTH (64)

/* The maximum inheritance depth. Think 16 is too small? The Java world record
 * is set at 12 levels of inheritance:
 * http://www.javaspecialists.eu/records/index.jsp
 *
 * Please don't use 16 levels of inheritance.
 */
#define UT_MAX_INHERITANCE_DEPTH (16)

/* The maximum number of languages you can construct to a single Corto process. */
#define UT_MAX_BINDINGS (16)

/* The maximum number of threads that can make use of the Corto
 * API simultaneously. */
#define UT_MAX_THREADS (64)

/* The maximum number of nested notifications. */
#define UT_MAX_NOTIFY_DEPTH (16)

/* The max length of a scoped identifier (incl \0). When combining this with the
 * MAX_SCOPE_DEPTH, and taking into consideration the scope separator (/) you
 * can have a tree that is 64 levels deep, where each object has a 7-character
 * name, and one object with 6, to compensate for \0. Or, you can have an object
 * in the root with a 510 character name with no children. */
#define UT_MAX_PATH_LENGTH (512)

/* The maximum number of objects that a thread can wait for simultaneously */
#define UT_MAX_WAIT_FOR_OBJECTS (32)

/* Corto can't load files with extensions longer than 16 characters */
#define UT_MAX_FILE_EXTENSION (16)

/* Maximum number of OLS extensions that is supported by the core */
#define UT_MAX_OLS_KEY (256)

/* Maximum number of TLS keys that is supported by the core */
#define UT_MAX_THREAD_KEY (256)

/* The maximum number of arguments that can be passed to the Corto arg parser */
#define UT_ARG_MAX (256)

/* The maximum number of TLS strings that can exist simultaneously */
#define UT_MAX_TLS_STRINGS (5)

/* Maximum retained buffer length for TLS string. This ensures that when a very
 * large string is stored in TLS, it will be cleaned up eventually. Keeping it
 * around would be wasteful since chances are low that a string of similar
 * length will take advantage of the memory. */
#define UT_MAX_TLS_STRINGS_MAX (1024)

/* Maximum number of arguments for command */
#define UT_MAX_CMD_ARGS (256)

/* Maximum number of operations in an id expression */
#define UT_EXPR_MAX_OP (32)

/* Maximum number of content types in a process */
#define UT_MAX_CONTENTTYPE (32)

/* Maximum number of simultaneous benchmarks */
#define UT_MAX_BENCHMARK (64)

/* Maximum number of categories in logmsg, like: "comp1: comp2: comp3: msg" */
#define UT_MAX_LOG_CATEGORIES (24)

/* Maximum number of code frames in logmsg */
#define UT_MAX_LOG_CODEFRAMES (16)

#ifndef __cplusplus
/* Boolean definitions (compatible with C++ and C99 stdbool) */
#undef bool
#undef true
#undef false
#define bool char
#define false 0
#define true !false
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (!FALSE)
#endif

/* NULL pointer value */
#ifndef NULL
#define NULL (0x0)
#endif


/* Color constants */
#define UT_BLACK   "\033[1;30m"
#define UT_RED     "\033[0;31m"
#define UT_GREEN   "\033[0;32m"
#define UT_YELLOW  "\033[0;33m"
#define UT_BLUE    "\033[0;34m"
#define UT_MAGENTA "\033[0;35m"
#define UT_CYAN    "\033[0;36m"
#define UT_WHITE   "\033[1;37m"
#define UT_GREY    "\033[0;37m"
#define UT_NORMAL  "\033[0;49m"
#define UT_BOLD    "\033[1;49m"

#define UT_FUNCTION __func__

/* Macro's used to prevent type checking macro's from expanding */
#define ___

/* Macro used to annotate parameters in bootstrap.h */
#define _(txt)

/* Corto string representing null */
#define UT_NULL_STRING ("null")

/* String type that is large enough to hold any corto identifier */
typedef char ut_id[UT_MAX_PATH_LENGTH];

/* Builtin collection-implementation definitions */
typedef struct ut_rb_s* ut_rb;
typedef struct ut_ll_s* ut_ll;

/* Builtin procedure kinds */
#define UT_PROCEDURE_STUB (0)
#define UT_PROCEDURE_CDECL (1)

/* C language binding type definition macro's */
#define UT_ANY(__type) typedef struct __type {ut_type type; void *value; uint8_t owner;} __type
#define UT_SEQUENCE(type, subtype, postexpr) typedef struct type {uint32_t length; subtype _()(*buffer) postexpr;} type
#define UT_SEQUENCE_EMPTY(type) (type){0}

/* Iterator type */
typedef struct ut_iter ut_iter;
struct ut_iter {
    void *ctx;
    void *data;
    bool (*hasNext)(ut_iter*);
    void* (*next)(ut_iter*);
    void* (*nextPtr)(ut_iter*);
    void (*release)(ut_iter*);
};

/* Callback used to compare values */
typedef int (*ut_compare_cb)(void* o1, void* o2);

/* Callback used to walk elements in collection */
typedef int (*ut_elementWalk_cb)(void* o, void* userData);

/* Callback used to determine if value is smaller/larger/equal */
typedef int (*ut_equals_cb)(void *context, const void* o1, const void* o2);

/* Type for traversing a tree */
#ifndef HEIGHT_LIMIT
#define HEIGHT_LIMIT (24) /* 16M nodes in a single tree */
#endif

typedef struct jsw_rbtrav jsw_rbtrav_t;
typedef struct jsw_rbtree jsw_rbtree_t;
typedef struct jsw_rbnode jsw_rbnode_t;

struct jsw_rbtrav {
  jsw_rbtree_t *tree;               /* Paired tree */
  jsw_rbnode_t *it;                 /* Current node */
  jsw_rbnode_t *path[HEIGHT_LIMIT]; /* Traversal path */
  size_t        top;                /* Top of stack */
  int32_t       changes;            /* Check if tree has changed since last */
};

/* Global variables */
UT_EXPORT extern int8_t UT_APP_STATUS;
UT_EXPORT extern int8_t UT_LOG_BACKTRACE;

UT_EXPORT
void ut_init(
    char *appName);

UT_EXPORT
void ut_deinit(void);

UT_EXPORT
const char* ut_appname();

#ifdef __cplusplus
}
#endif

/* Base includes */
#include "parson.h"
#include "os.h"
#include "strbuf.h"
#include "iter.h"
#include "ll.h"
#include "rb.h"
#include "string.h"
#include "os.h"
#include "time.h"
#include "dl.h"
#include "fs.h"
#include "posix_thread.h"
#include "thread.h"
#include "file.h"
#include "env.h"
#include "memory.h"
#include "log.h"
#include "proc.h"
#include "expr.h"
#include "jsw_rbtree.h"
#include "path.h"
#include "load.h"
#include "version.h"

#endif /* UT_BASE_H */
