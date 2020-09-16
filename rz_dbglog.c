#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "rz_dbglog.h"

static int s_dbgLv = CONFIG_DEFAULT_LEVEL;
static int s_dbgCate = CONFIG_DEFAULT_CATE;
static struct prefix_info s_cate_table[CONFIG_CATE_NUM] = {0};
static struct prefix_info s_logLevel_table[] = {
   {"[EMERG]", 7},
   {"[ALERT]", 7},
   {"[CRIT]", 6},
   {"[ERR]", 5},
   {"[WARNING]", 9},
   {"[NOTICE]", 8},
   {"[INFO]", 6},
   {"[DEBUG]", 7},
};

/* return copy length */
static int add_lv_string(char* buf, int level) {
    struct prefix_info *llTable;

    if (level > 7 || level < 0)
        return 0;

    llTable = &s_logLevel_table[level];
    strncpy(buf, llTable->name, llTable->len);
    return llTable->len;
}

/* return copy length */
static int add_cate_string(char* buf, char cate) {
    struct prefix_info *cTable;

    if (cate > CONFIG_CATE_NUM)
        return 0;

    cTable = &s_cate_table[cate];
    if (cTable->len > CONFIG_CATE_NAME_MAX_LEN) {
        cTable->len = CONFIG_CATE_NAME_MAX_LEN;
    }
    strncpy(buf, cTable->name, cTable->len);
    return cTable->len;
}

/* return copy length */
static int add_comma(char* buf) {

    strncpy(buf, ", ", 2);
    return 2;
}

void rz_dbgprintf(char level, char cate, const char *fmt, ...) {
    char logbuf[CONFIG_MSG_MAX_LEN] = {0};
    va_list ap;
    int len = 0;
    int total_len = 0;

    /* filter message by log level */
    if (!((0x1<<level) & s_dbgLv))
        return;

    /* filter message by category */
    if (!((0x1<<cate) & s_dbgCate))
        return;

#if CONFIG_OUTPUT_LEVEL
    /* add prefix log level into buffer */
    len += add_lv_string(logbuf, level);
#endif

#if CONFIG_OUTPUT_CATE
    /* add prefix cate into buffer */
    len += add_cate_string(logbuf + len, cate);
#endif

#if CONFIG_OUTPUT_LEVEL || CONFIG_OUTPUT_CATE
    /* add ", " */
    len += add_comma(logbuf + len);
#endif

    /* add user message */
    va_start(ap, fmt);
    total_len = len;
    total_len += vsnprintf(logbuf + len, sizeof(logbuf) - len, fmt, ap);
    va_end(ap);

    debugprintf(logbuf, total_len);
}

int set_dbg_filter_level(int level) {

    if (level < 0 || level > 7 )
        return -1;

    s_dbgLv = 0xFF >> (7-level);
    return 0;
}

void set_dbg_category(int cate) {

    s_dbgCate = cate;
}

void add_dbg_category(int cate) {

    s_dbgCate |= (1<<cate);
}

void del_dbg_category(int cate) {

    s_dbgCate &= ~(1<<cate);
}


int set_cate_name(int cate, char* str, int strLen) {
    struct prefix_info *cTable;

    if ((cate < 0) || (cate > (CONFIG_CATE_NUM-1)))
        return -1;

    cTable = &s_cate_table[cate];
    cTable->name = str;
    if (strLen > CONFIG_CATE_NAME_MAX_LEN) {
        cTable->len = CONFIG_CATE_NAME_MAX_LEN;
    } else {
        cTable->len = strLen;
    }
    return 0;
}

