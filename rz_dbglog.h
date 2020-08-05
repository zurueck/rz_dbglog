#ifndef RZ_DBGLOG_H
#define RZ_DBGLOG_H

/* ========== config ========== */
#define CONFIG_LOG_BUF_LENGTH   512
#define CONFIG_DBGLOG_SELFTEST  1
#define CONFIG_DEFAULT_LEVEL    0xFF
#define CONFIG_DEFAULT_CATA     0xFF

/* ======= end config ========== */
struct logLevel {
    char *name;
    int len;
};

extern int g_dbglog_lv;
extern int g_dbglog_cata;

/**
 * user need to implement this function
 */
extern void debugprintf(const char *buf);

void rz_dbgprintf(char level, char cata, const char *fmt, ...);


#define RZ_LOG_LEVEL_EMERG      0
#define RZ_LOG_LEVEL_ALERT      1
#define RZ_LOG_LEVEL_CRIT       2
#define RZ_LOG_LEVEL_ERR        3
#define RZ_LOG_LEVEL_WARNING    4
#define RZ_LOG_LEVEL_NOTICE     5
#define RZ_LOG_LEVEL_INFO       6
#define RZ_LOG_LEVEL_DEBUG      7

#define __D_FILE__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#if defined (__GNUC__)
#define DBG_LOG(lvl, cata, fmt, ...)     \
                    {rz_dbgprintf(lvl, cata, "%s(%s):(%d) " fmt, __FUNCTION__, __D_FILE__, __LINE__ ,##__VA_ARGS__);}
#elif defined (__STDC__)
#define DBG_LOG(lvl, cata, fmt, ...)     \
                    {rz_dbgprintf(lvl, cata, "%s(%s):(%d) " fmt, __func__, __FILE__, __LINE__ ,##__VA_ARGS__);}
#else
#define DBG_LOG(lvl, cata, fmt, ...)
//#define DBG_LOG(lvl, cata, fn, fmt, ...)     \
                    {rz_dbgprintf(lvl, cata, "%s(%s):(%d) " fmt, __func__, __FILE__, __LINE__ ,##__VA_ARGS__);}
#endif


#define LOG_EMERG(CATA, fmt, ...)      {DBG_LOG((RZ_LOG_LEVEL_EMERG), (CATA), fmt, ##__VA_ARGS__)}
#define LOG_ALERT(CATA, fmt, ...)      {DBG_LOG((RZ_LOG_LEVEL_ALERT), (CATA), fmt, ##__VA_ARGS__)}
#define LOG_CRIT(CATA, fmt, ...)      {DBG_LOG((RZ_LOG_LEVEL_CRIT), (CATA), fmt, ##__VA_ARGS__)}
#define LOG_ERR(CATA, fmt, ...)      {DBG_LOG((RZ_LOG_LEVEL_ERR), (CATA), fmt, ##__VA_ARGS__)}
#define LOG_WARNING(CATA, fmt, ...)      {DBG_LOG((RZ_LOG_LEVEL_WARNING), (CATA), fmt, ##__VA_ARGS__)}
#define LOG_NOTICE(CATA, fmt, ...)      {DBG_LOG((RZ_LOG_LEVEL_NOTICE), (CATA), fmt, ##__VA_ARGS__)}
#define LOG_INFO(CATA, fmt, ...)      {DBG_LOG((RZ_LOG_LEVEL_INFO), (CATA), fmt, ##__VA_ARGS__)}
#define LOG_DEBUG(CATA, fmt, ...)      {DBG_LOG((RZ_LOG_LEVEL_DEBUG), (CATA), fmt, ##__VA_ARGS__)}

#endif //RZ_DBGLOG_H
