#ifndef RZ_DBGLOG_H
#define RZ_DBGLOG_H

#include <string.h>
/* ========== config ========== */
/* maximum length of single message */
#define CONFIG_MSG_MAX_LEN      512

/* default level filter 0xFF=all pass */
#define CONFIG_DEFAULT_LEVEL    0xFF

/* default catagory filter 0xFF=all pass */
#define CONFIG_DEFAULT_CATE     0xFF

/* category number, it consume stacks */
#define CONFIG_CATE_NUM         8

/* maximum length of category name */
#define CONFIG_CATE_NAME_MAX_LEN 12

/* level shown in output message or not */
#define CONFIG_OUTPUT_LEVEL     1

/* catagory shown in output message or not */
#define CONFIG_OUTPUT_CATE      1

/*
 * CONFIG_OUTPUT_FUNCTION, CONFIG_OUTPUT_FILE and CONFIG_OUTPUT_LINE
 * work only in GNU now,
 * set 000 will become 100
 */
/* function name shown in output message or not. Works in GNU only now */
#define CONFIG_OUTPUT_FUNCTION  1

/* file name shown in output message or not. Only Works in GNU only now */
#define CONFIG_OUTPUT_FILE      1

/* line number name shown in output message or not. Works in GNU only now */
#define CONFIG_OUTPUT_LINE      1

/* ======= end config ========== */


struct prefix_info{
    char *name;
    int len;
};

/**
 * @brief User need to implement this function
 *
 * low level stdout implement
 */
extern void debugprintf(const char *buf, int len);

/**
 * @brief It is recommand not call this function directly.
 *
 * dbgprintf add level and category field into fmt string. This function should not call by user directly. It will be called by micros. such as LOG_DEBUG(CATE, fmt, ...)
 *
 * @param [in] level message level
 * @param [in] cate  message category
 * @param [in] fmt   message string
 * @param [in] ...   arguments of fmt string
 */
void rz_dbgprintf(char level, char cate, const char *fmt, ...);

/**
 * set level filter. message lower than the level will not shown. It means the lower number the message is, the higher priority it has. set 7 => print all message. set 0 => print emerg message only.
 *
 * @param [in] level 0~7. level to be set.
 * @return 0 done \n
 *         -1 gg
 */
int set_dbg_filter_level(int level);

/**
 * set category filter. This is bit controlled parameter, any cate with bit 1 will be shown.
 *
 * @param [in] cate category
 */
void set_dbg_category(int cate);

/**
 * add category. Read and OR operation to parameter category.
 *
 * @param [in] cate Bit1 in this parameter will enable its category
 */
void add_dbg_category(int cate);

/**
 * remove category. Read and NOT OR operation to parameter category.
 *
 * @param [in] cate Bit1 in this parameter will enable its category
 */
void del_dbg_category(int cate);

/**
 * set category string. String length larger than CONFIG_CATE_NAME_MAX_LEN will be truncated
 *
 * @param [in] cate     category number
 * @param [in] str      string pointer
 * @param [in] strLen   string length.
 * @return 0 done \n
 *         -1 gg
 */
int set_cate_name(int cate, char* str, int strLen);

#define RZ_LOG_LEVEL_EMERG      0
#define RZ_LOG_LEVEL_ALERT      1
#define RZ_LOG_LEVEL_CRIT       2
#define RZ_LOG_LEVEL_ERR        3
#define RZ_LOG_LEVEL_WARNING    4
#define RZ_LOG_LEVEL_NOTICE     5
#define RZ_LOG_LEVEL_INFO       6
#define RZ_LOG_LEVEL_DEBUG      7

#define __D_FILE__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#if CONFIG_OUTPUT_FUNCTION
    #if CONFIG_OUTPUT_FILE
        #if CONFIG_OUTPUT_LINE
            #define OUTPUT_OPTION "%s(%s):(%d) "
            #define OUTPUT_ARG    __FUNCTION__,__D_FILE__,__LINE__
        #else
            #define OUTPUT_OPTION "%s(%s) "
            #define OUTPUT_ARG    __FUNCTION__,__D_FILE__
        #endif
    #else
        #if CONFIG_OUTPUT_LINE
            #define OUTPUT_OPTION "%s:(%d) "
            #define OUTPUT_ARG    __FUNCTION__,__LINE__
        #else
            #define OUTPUT_OPTION "%s "
            #define OUTPUT_ARG    __FUNCTION__
        #endif
    #endif
#else
    #if CONFIG_OUTPUT_FILE
        #if CONFIG_OUTPUT_LINE
            #define OUTPUT_OPTION "(%s):(%d) "
            #define OUTPUT_ARG    __D_FILE__,__LINE__
        #else
            #define OUTPUT_OPTION "(%s) "
            #define OUTPUT_ARG    __D_FILE__
        #endif
    #else
        #if CONFIG_OUTPUT_LINE
            #define OUTPUT_OPTION "(%d) "
            #define OUTPUT_ARG    __LINE__
        #else
            #define OUTPUT_OPTION "%s "
            #define OUTPUT_ARG    __FUNCTION__
        #endif
    #endif
#endif


#if defined (__GNUC__)
#define DBG_LOG(lvl, cate, fmt, ...)     \
                    {rz_dbgprintf(lvl, cate, OUTPUT_OPTION fmt, OUTPUT_ARG ,##__VA_ARGS__);}
//                    {rz_dbgprintf(lvl, cate, "%s(%s):(%d) " fmt, __FUNCTION__, __D_FILE__, __LINE__ ,##__VA_ARGS__);}
#elif defined (__STDC__)
#define DBG_LOG(lvl, cate, fmt, ...)     \
                    {rz_dbgprintf(lvl, cate, "%s(%s):(%d) " fmt, __func__, __FILE__, __LINE__ ,##__VA_ARGS__);}
#else
#define DBG_LOG(lvl, cate, fmt, ...)
//#define DBG_LOG(lvl, cate, fn, fmt, ...)     \
//                    {rz_dbgprintf(lvl, cate, "%s(%s):(%d) " fmt, __func__, __FILE__, __LINE__ ,##__VA_ARGS__);}
#endif

#define LOG_EMERG(CATE, fmt, ...)      {DBG_LOG((RZ_LOG_LEVEL_EMERG), (CATE), fmt, ##__VA_ARGS__)}
#define LOG_ALERT(CATE, fmt, ...)      {DBG_LOG((RZ_LOG_LEVEL_ALERT), (CATE), fmt, ##__VA_ARGS__)}
#define LOG_CRIT(CATE, fmt, ...)      {DBG_LOG((RZ_LOG_LEVEL_CRIT), (CATE), fmt, ##__VA_ARGS__)}
#define LOG_ERR(CATE, fmt, ...)      {DBG_LOG((RZ_LOG_LEVEL_ERR), (CATE), fmt, ##__VA_ARGS__)}
#define LOG_WARNING(CATE, fmt, ...)      {DBG_LOG((RZ_LOG_LEVEL_WARNING), (CATE), fmt, ##__VA_ARGS__)}
#define LOG_NOTICE(CATE, fmt, ...)      {DBG_LOG((RZ_LOG_LEVEL_NOTICE), (CATE), fmt, ##__VA_ARGS__)}
#define LOG_INFO(CATE, fmt, ...)      {DBG_LOG((RZ_LOG_LEVEL_INFO), (CATE), fmt, ##__VA_ARGS__)}
#define LOG_DEBUG(CATE, fmt, ...)      {DBG_LOG((RZ_LOG_LEVEL_DEBUG), (CATE), fmt, ##__VA_ARGS__)}

#endif //RZ_DBGLOG_H
