#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"
#include "cmocka.h"

#include "vectors.h"

void verify_vec3_addition() {
    vec3 a = {.x = 1, .y = 1, .z = 1}, b = {.x = 1, .y = 1, .z = 1};

    vec3 result = vec3_add(&a, &b);
    vec3 expected = {2, 2, 2};
    assert_memory_equal(&result, &expected, sizeof(vec3));
}

void verify_vec3_cross() {
    vec3 a = {1, 2, 3}, b = {1, 5, 7};
    vec3 result = vec3_cross(&a, &b);
    vec3 expected = {-1, -4, 3};
    assert_memory_equal(&result, &expected, sizeof(vec3));
    a.x = -1, a.y = -2, a.z = 3;
    b.x = 4, b.y = 0, b.z = -8;
    result = vec3_cross(&a, &b);
    expected.x = 16, expected.y = 4, expected.z = 8;
    assert_memory_equal(&result, &expected, sizeof(vec3));
}

void verify_vec3_unit(){
    vec3 a = {1, 2, 3}, b = {1, 5, 7};
    vec3 result = vec3_unit(&a);
    vec3 expected = {0.26726, 0.53452, 0.80178};
    assert_float_equal(result.x, expected.x, 0.0001);
    assert_float_equal(result.y, expected.y, 0.0001);
    assert_float_equal(result.z, expected.z, 0.0001);
}