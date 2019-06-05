#ifndef ULOG_ULOG_H
#define ULOG_ULOG_H

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(ULOG_OUTPUT_LEVEL)
#define ULOG_OUTPUT_LEVEL ULOG_VERBOSE
#endif

typedef int (*OutputCb)(const char *ptr);

enum ULOG_LEVEL {
    ULOG_VERBOSE,
    ULOG_DEBUG,
    ULOG_INFO,
    ULOG_WARN,
    ULOG_ERROR,
    ULOG_ASSERT
};

#if !defined(ULOG_NO_COLOR)
#define _STR_COLOR(color) "\x1b[" #color "m"
#else
#define _STR_COLOR(color) ""
#endif

#define STR_RESET _STR_COLOR(0)
#define STR_BLACK _STR_COLOR(0;30)
#define STR_RED _STR_COLOR(0;31)
#define STR_GREEN _STR_COLOR(0;32)
#define STR_YELLOW _STR_COLOR(0;33)
#define STR_BLUE _STR_COLOR(0;34)
#define STR_PURPLE _STR_COLOR(0;35)
#define STR_SKYBLUE _STR_COLOR(0;36)
#define STR_WHITE _STR_COLOR(0;37)

#define STR_BOLD_BLACK _STR_COLOR(30;1)
#define STR_BOLD_RED _STR_COLOR(31;1)
#define STR_BOLD_GREEN _STR_COLOR(32;1)
#define STR_BOLD_YELLOW _STR_COLOR(33;1)
#define STR_BOLD_BLUE _STR_COLOR(34;1)
#define STR_BOLD_PURPLE _STR_COLOR(35;1)
#define STR_BOLD_SKYBLUE _STR_COLOR(36;1)
#define STR_BOLD_WHITE _STR_COLOR(37;1)

// Precompiler define to get only filename;
#if !defined(__FILENAME__)
#include <string.h>
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#if !defined(ULOG_DISABLE)
#define _uLogLog(level, ...) uLogLog(level, __FILENAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define _uLogLog(level, ...)
#endif

#define Log_verbose(fmt, ...) _uLogLog(ULOG_VERBOSE, fmt, ##__VA_ARGS__)
#define Log_debug(fmt, ...) _uLogLog(ULOG_DEBUG, fmt, ##__VA_ARGS__)
#define Log_info(fmt, ...) _uLogLog(ULOG_INFO, fmt, ##__VA_ARGS__)
#define Log_warn(fmt, ...) _uLogLog(ULOG_WARN, fmt, ##__VA_ARGS__)
#define Log_error(fmt, ...) _uLogLog(ULOG_ERROR, fmt, ##__VA_ARGS__)
#define Log_assert(fmt, ...) _uLogLog(ULOG_ASSERT, fmt, ##__VA_ARGS__)

#define __TYPE_CMP(X, Y) __builtin_types_compatible_p(typeof(X), Y)

#define Log_token(token) do { \
    char *fmt = "(none) %s = "; \
    if (__TYPE_CMP(token, float) || __TYPE_CMP(token, double)) { \
        fmt = "(float) %s => %f";\
    } else if (__TYPE_CMP(token, int) || __TYPE_CMP(token, unsigned int) \
        || __TYPE_CMP(token, short) || __TYPE_CMP(token, unsigned short) \
        || __TYPE_CMP(token, long) || __TYPE_CMP(token, unsigned long) \
        || __TYPE_CMP(token, long long) || __TYPE_CMP(token, unsigned long long) \
        ) { \
        fmt = "(int) %s => %d";\
    } else if (__TYPE_CMP(token, char) || __TYPE_CMP(token, unsigned char)) { \
        fmt = "(char) %s => %c";\
    } else if (__TYPE_CMP(token, char *) || __TYPE_CMP(token, unsigned char*) \
        || __TYPE_CMP(token, char[]) || __TYPE_CMP(token, unsigned char[]) \
        ) { \
        fmt = "(char*) %s => %s";\
    } else if (__TYPE_CMP(token, void *) \
        || __TYPE_CMP(token, float*) || __TYPE_CMP(token, double*) \
        || __TYPE_CMP(token, int*) || __TYPE_CMP(token, unsigned int*) \
        || __TYPE_CMP(token, short*) || __TYPE_CMP(token, unsigned short*) \
        || __TYPE_CMP(token, long*) || __TYPE_CMP(token, unsigned long*) \
        || __TYPE_CMP(token, long long*) || __TYPE_CMP(token, unsigned long long*) \
        ) { \
        fmt = "(void*) %s => %x";\
    } \
    Log_debug(fmt, #token, token); \
} while(0);

void uLogInit(OutputCb cb);
void uLogLog(enum ULOG_LEVEL level, const char *file, const char *func, int line, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif  //ULOG_ULOG_H
