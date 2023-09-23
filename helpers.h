#ifndef __HELPERS_H__
#define __HELPERS_H__

#define NULL ((void*)0)

#define SOFTFP __attribute__((pcs("aapcs")))

#define STRINGIFY(x) #x

#define assert(x) do { if(!(x)) { glibc_fprintf(*glibc_stderr, "assertion failed: %s\n", STRINGIFY(x)); abort(); } } while(0);

#ifdef DEBUG
#define SHOW_FUNCTION(f, ptr) \
    if(!glibc_fprintf) glibc_fprintf = (int (*)(void*, const char*, ...))dlsym(glibc_handle, "fprintf"); \
    if(!glibc_stderr) glibc_stderr = (void**)dlsym(glibc_handle, "stderr"); \
    glibc_fprintf(*glibc_stderr, "%s is at %p called from %s\n", #f, ptr, __FUNCTION__);
#define FPRINTF_STDERR(fmt, ...) \
    if(!glibc_fprintf) glibc_fprintf = (int (*)(void*, const char*, ...))dlsym(glibc_handle, "fprintf"); \
    if(!glibc_stderr) glibc_stderr = (void**)dlsym(glibc_handle, "stderr"); \
    glibc_fprintf(*glibc_stderr, fmt, __VA_ARGS__);
#else
#define SHOW_FUNCTION(...)
#define FPRINTF_STDERR(...)
#endif

#define LOAD_GLIBC() \
    if(glibc_handle == NULL) \
    { \
        glibc_handle = dlopen("libc-2.31.so", RTLD_LAZY); \
    }

#define LOAD_RT() \
    if(rt_handle == NULL) \
    { \
        rt_handle = dlopen("librt-2.31.so", RTLD_LAZY); \
    }

#define LOAD_PTHREAD() \
    if(pthread_handle == NULL) \
    { \
        pthread_handle = dlopen("libpthread-2.31.so", RTLD_LAZY); \
    }

#define LOAD_GCC() \
    if(gcc_handle == NULL) \
    { \
        gcc_handle = dlopen("libgcc_s.so.1", RTLD_LAZY); \
    }

#define LOAD_SETJMP() \
    if(setjmp_handle == NULL) \
    { \
        setjmp_handle = lopen("libsetjmp.so", RTLD_LAZY); \
    }

#endif

