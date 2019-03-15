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

#define DEBUG_TAG "[DEBUG]"
#define ERROR_TAG "[ERROR]"
#define WARN_TAG "[WARN]"
#define INFO_TAG "[INFO]"

#define OPERATION_SUCCESS 0
#define OPERATION_FAILURE 1

#define base_log(S, H, M, ...) fprintf(S, H " (%s:%d): " M "\r\n",\
        __FILE__, __LINE__, ##__VA_ARGS__); fflush(S);


#define base_log_err(S, H, M, ...) fprintf(S,\
        H " (%s:%d: errno: %s) " M "\r\n", __FILE__, __LINE__,\
        clean_errno(), ##__VA_ARGS__);\
	fflush(S);\

#ifdef NDEBUG
#define debug(M, ...)
#else
/*
#define debug(M, ...) fprintf(get_dbg_out(), "[DEBUG] (%s:%d): " M "\r\n",\
        __FILE__, __LINE__, ##__VA_ARGS__); flush_dbg_out();
*/
#define debug(M, ...) base_log(get_dbg_out(), DEBUG_TAG, M, ##__VA_ARGS__);
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))
/*
#define log_err(M, ...) fprintf(stderr,\
        "[ERROR] (%s:%d: errno: %s) " M "\r\n", __FILE__, __LINE__,\
        clean_errno(), ##__VA_ARGS__);\
*/
#define log_err(M, ...) base_log_err(stderr, ERROR_TAG, M, ##__VA_ARGS__);\
	if (get_dbg_out() != stderr) base_log_err(get_dbg_out(), ERROR_TAG, M, ##__VA_ARGS__);
/*
#define log_warn(M, ...) fprintf(stderr,\
        "[WARN] (%s:%d: errno: %s) " M "\r\n",\
        __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
*/
#define log_warn(M, ...) base_log_err(stderr, WARN_TAG, M, ##__VA_ARGS__);\
	if (get_dbg_out() != stderr) base_log_err(get_dbg_out(), WARN_TAG, M, ##__VA_ARGS__);
/*
#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\r\n",\
        __FILE__, __LINE__, ##__VA_ARGS__);
*/
#define log_info(M, ...) base_log(stderr, INFO_TAG, M, ##__VA_ARGS__);\
	if (get_dbg_out() != stderr) base_log(get_dbg_out(), INFO_TAG, M, ##__VA_ARGS__);
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
