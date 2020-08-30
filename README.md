# Rz_dbglog

## Introduction
Rz_dbglog is a simple dynamic debug message feature. It is designed for bare metal MCU system with hardware indepent fucntions. User has to implement their own low level stdout funcions. Log level can be changed at runtime to filter the print out message.

## How to Use
1. implement your own low level output function
   `void debugprintf(const char * buf)`
2. set "config" part in header file
3. call APIs in source code

* change "g_lv" "g_cata" anytime to filter the message

## APIs
    LOG_EMERG(CATA, fmt, ...)  
    LOG_ALERT(CATA, fmt, ...)  
    LOG_CRIT(CATA, fmt, ...)  
    LOG_ERR(CATA, fmt, ...)  
    LOG_WARNING(CATA, fmt, ...)  
    LOG_NOTICE(CATA, fmt, ...)  
    LOG_INFO(CATA, fmt, ...)  
    LOG_DEBIG(CATA, fmt, ...)  

### e.g.
    LOG_ERR(1, "test\n");

## To do 
1. Seperate test fucntion into test.c
2. add doxygen style comment
3. make output format optional
4. support catagory name
5. add APIs: change level, change cata
6. more readme: memory usage
7. support used in interrupt function
8. support RTOS

## Reference


