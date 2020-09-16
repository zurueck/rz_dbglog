#include <stdio.h>
#include <assert.h>
#include "rz_dbglog.h"

void debugprintf(const char * buf, int len) {
    /* please implement your low level stdout here */
    printf("%s", buf);
}

int main(int argc, char **argv) {
    int a = 135;
    int b = 246;
    int rc;

    set_cate_name(0, "C0", 2);
    set_dbg_filter_level(7);
    //all function
    LOG_EMERG(0, "test all level\n");
    LOG_ALERT(0, "test all level\n");
    LOG_CRIT(0, "test all level\n");
    LOG_ERR(0, "test all level\n");
    LOG_WARNING(0, "test all level\n");
    LOG_NOTICE(0, "test all leve\n");
    LOG_INFO(0, "test all leve\n");
    LOG_DEBUG(0, "test all leve\n");


    //test filer
    printf("======== test filter ========\n");
    set_dbg_filter_level(2);
    LOG_EMERG(0, "test filter = 2\n");
    LOG_ALERT(0, "test filter = 2\n");
    LOG_CRIT(0, "test filter = 2\n");
    LOG_ERR(0, "test filter = 2\n");
    LOG_WARNING(0, "test filter = 2\n");
    LOG_NOTICE(0, "test filter = 2\n");
    LOG_INFO(0, "test filter = 2\n");
    LOG_DEBUG(0, "test filter = 2\n");


    //test filter cate
    printf("======== test filter cate ========\n");
    set_dbg_filter_level(7);
    set_cate_name(1, "C1", 2);
    LOG_EMERG(1, "test c1\n");
    del_dbg_category(1);
    LOG_EMERG(1, "C1 has been deleted, you shouldn't see this line\n");
    LOG_EMERG(1, "C1 has been deleted, you shouldn't see this line\n");
    LOG_EMERG(1, "C1 has been deleted, you shouldn't see this line\n");
    add_dbg_category(1);
    LOG_EMERG(1, "add C1 again, you may see this line\n");
    LOG_EMERG(1, "add C1 again, you may see this line\n");
    LOG_EMERG(1, "add C1 again, you may see this line\n");

    //test cate name leng
    printf("======== test cate name length ========\n");
    set_cate_name(1, "cate1_gg", 0);
    LOG_ALERT(1, "C1 name length = 0\n");

    rc = set_cate_name(1, "12345678901234567890", 20);
    assert(rc == 0);
    LOG_ALERT(1, "C1 name length = 20(too long)\n");

    //test cate num
    printf("======== test cate name length ========\n");
    rc = set_cate_name(100, "cate1_gg", 8);
    assert(rc != 0);

    //test printf functions
    printf("======== test printf functions ========\n");
    set_cate_name(2, "C2", 2);
    LOG_NOTICE(2, "test a = %d, b= %d\n", a, b);

    printf("======== test done ========\n");
    return 0;
}

