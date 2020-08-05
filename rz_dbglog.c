#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "rz_dbglog.h"

int g_lv = CONFIG_DEFAULT_LEVEL;
int g_cata = CONFIG_DEFAULT_CATA;

#if CONFIG_DBGLOG_SELFTEST
void debugprintf(const char * buf) {
    printf("%s", buf);
}
#endif

static struct logLevel g_logLevel_table[] = {
   {"[EMERG]", 7}, 
   {"[ALERT]", 7}, 
   {"[CRIT]", 6}, 
   {"[ERR]", 5}, 
   {"[WARNING]", 9}, 
   {"[NOTICE]", 8}, 
   {"[INFO]", 6}, 
   {"[DEBUG]", 7}, 
};

static int add_level(char* buf, char level) {
    struct logLevel *llTable;

    if (level > 7) {return 0;}
    llTable = &g_logLevel_table[level];
    strncpy(buf, llTable->name, llTable->len);

    return llTable->len;
}

static int add_cata(char* buf, char cata) {
    struct logLevel *llTable;

    if (cata > 7) {return 0;}
    sprintf(buf, "0x%02X ", 0x1<<cata);

    return 5;
}

void rz_dbgprintf(char level, char cata, const char *fmt, ...) {
    char logbuf[CONFIG_LOG_BUF_LENGTH];
    va_list ap;
    int len;

    //global setting for log level
    if (!((0x1<<level) & g_lv)) {return;}

    //global setting for cata
    if (!((0x1<<cata) & g_cata)) {return;}

    //add log level into buffer
    len = add_level(logbuf, level);
    //add cata into buffer
    len = len + add_cata(logbuf + len, cata);

    //add user message
    va_start(ap, fmt);
    vsnprintf (logbuf + len, sizeof(logbuf) - len, fmt, ap);
    va_end(ap);

    debugprintf(logbuf);
}

#if CONFIG_DBGLOG_SELFTEST
int main(int argc, char **argv) {
    int a = 12300;
    
    LOG_EMERG(1, "test\n");
    LOG_ALERT(1, "test\n");
    LOG_CRIT(1, "test\n");
    LOG_ERR(1, "test\n");
    LOG_WARNING(1, "test\n");
    LOG_NOTICE(2, "test a = %d\n", a);
    LOG_INFO(2, "test a = %d\n", a);
    LOG_DEBUG(0, "test a = %d\n", a);

    return 0;
}
#endif
