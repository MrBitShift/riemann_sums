#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

FILE *dbg_out = NULL;

FILE *get_dbg_out()
{
	return (dbg_out == NULL) ? stderr : dbg_out;
}

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(get_dbg_out(), "[DEBUG] %s:%d: " M "\r\n",\
        __FILE__, __LINE__, ##__VA_ARGS__); flush_dbg_out();
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr,\
        "[ERROR] (%s:%d: errno: %s) " M "\r\n", __FILE__, __LINE__,\
        clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr,\
        "[WARN] (%s:%d: errno: %s) " M "\r\n",\
        __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\r\n",\
        __FILE__, __LINE__, ##__VA_ARGS__);

#define check(A, M, ...) if(!(A)) {\
    log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__);\
    errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__);\
    errno=0; goto error; }

#define flush_dbg_out() fflush(get_dbg_out());

#define close_dbg_out() fprintf(get_dbg_out(), "\r\n"); flush_dbg_out(); fclose(get_dbg_out());


#endif
