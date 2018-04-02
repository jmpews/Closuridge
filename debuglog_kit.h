#ifndef debuglog_kit_h
#define debuglog_kit_h

#include <errno.h>
#include <stdio.h>

/*======= Debug Log Toolkit =======*/
#define EnablePrintErrnoString 1

#define COMMON_ERROR_LOG()                                                                                             \
    do {                                                                                                               \
        fprintf(stderr, "======= ERROR LOG ======= \n");                                                               \
        fprintf(stderr, "[!]error occur at %s:%d:%s()\n", __FILE__, __LINE__, __func__);                               \
        if (EnablePrintErrnoString) {                                                                                  \
            fprintf(stderr, "======= Errno [%d] String ======= \n", errno);                                            \
            perror(strerror(errno));                                                                                   \
        }                                                                                                              \
        fprintf(stderr, "======= Error Log End ======= \n");                                                           \
    } while (0)

#endif