# Rz_dbglog

## Introduction
Rz_dbglog is a simple dynamic debug message implement. It is designed for bare metal MCU system with hardware indepent fucntions. User has to implement their own low level stdout funcions. Log level can be changed at runtime to filter the print out message.

## How to Use
1. implement your own low level output function
   `void debugprintf(const char * buf)`
2. set "configuration" part in header file
3. call APIs in source code
4. change level and category at runtime to filter the message

## Configurations
### Log level
There are 8 printf-like APIs with 8 log levels, 0~7, 0 is the highest level. Log level can be controlled by set_dbg_filter_level(). Message with the level <= filter level will be shown. For example, If we set log level = 2 now, messages with log level = 0, 1, 2 will go to output.
### Category
Category helps users to categorize their message. It is also can be filtered by users. Users can set category name by APIs. Name will shown in output message later
###

## APIs
    LOG_EMERG(CATA, fmt, ...)
    LOG_ALERT(CATA, fmt, ...)
    LOG_CRIT(CATA, fmt, ...)
    LOG_ERR(CATA, fmt, ...)
    LOG_WARNING(CATA, fmt, ...)
    LOG_NOTICE(CATA, fmt, ...)
    LOG_INFO(CATA, fmt, ...)
    LOG_DEBIG(CATA, fmt, ...)

    void rz_dbgprintf(char level, char cate, const char *fmt, ...);
    int set_dbg_filter_level(int level);
    void set_dbg_category(int cate);
    void add_dbg_category(int cate);
    void del_dbg_category(int cate);

### Example
    Please refer to test.c

## To do
1. make output format optional
2. readme: memory usage

