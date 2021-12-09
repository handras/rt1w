#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"

extern void verify_vec3_addition();
extern void verify_vec3_cross();
void verify_vec3_unit();

int main(void) {
    const struct CMUnitTest vector_tests[] = {
        cmocka_unit_test(verify_vec3_addition),
        cmocka_unit_test(verify_vec3_cross),
        cmocka_unit_test(verify_vec3_unit),
    };
    cmocka_run_group_tests(vector_tests, NULL, NULL);
}