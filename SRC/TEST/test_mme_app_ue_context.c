#include <check.h>
#include <stdlib.h>
#include <stdint.h>

#include "mme_app_ue_context.h"
#include "3gpp_23.003.h"

#define TEST_CASE_COMMON_CONVERT_MAX 10

START_TEST(imsi_empty_test)
{
    mme_app_imsi_t imsi_mme = {.length = 0};
    char imsi_str[] = "001012234567890";

    /* Check if imsi_mme is empty */
    ck_assert(mme_app_is_imsi_empty(&imsi_mme) == true);

    /* Check if imsi_mme is not empty */
    mme_app_string_to_imsi((&imsi_mme), imsi_str);
    ck_assert( mme_app_is_imsi_empty(&imsi_mme) == false);
}
END_TEST


START_TEST(imsi_convert_to_uint_test)
{
    int i;
    mme_app_imsi_t imsi_mme_test;
    uint64_t imsi_uint64;

    char imsi_compare[TEST_CASE_COMMON_CONVERT_MAX][IMSI_BCD_DIGITS_MAX + 1] = {
        "001012234567890",
        "262011234567890",
        "262010000043448",
        "26201943210",
        "262019876543210",
        "41004123456789",
        "310150123456789",
        "460001357924680",
        "520031234567890",
        "470010171566423"
    };

    uint64_t imsi_cmp[TEST_CASE_COMMON_CONVERT_MAX] = {
        1012234567890,
        262011234567890,
        262010000043448,
        26201943210,
        262019876543210,
        41004123456789,
        310150123456789,
        460001357924680,
        520031234567890,
        470010171566423,
    };

    for(i = 0; i < TEST_CASE_COMMON_CONVERT_MAX; i++){
        mme_app_string_to_imsi(&imsi_mme_test, imsi_compare[i]);
        imsi_uint64 = mme_app_imsi_to_u64(imsi_mme_test);
        printf("Convert %"PRIu64" and assert %"PRIu64"\n", imsi_uint64, imsi_cmp[i]);
        ck_assert_uint_eq(imsi_uint64, imsi_cmp[i]);
    }

}
END_TEST

START_TEST(imsi_convert_common_struct_test)
{
    int i;
    mme_app_imsi_t imsi_mme;
    imsi_t imsi_structs[TEST_CASE_COMMON_CONVERT_MAX] = {
        {.u.num.digit1 = 0, .u.num.digit2 = 0, .u.num.digit3 = 1, .u.num.digit4 = 0, .u.num.digit5 = 1, .u.num.digit6 = 1, .u.num.digit7 = 2, .u.num.digit8 = 3,
         .u.num.digit9 = 4, .u.num.digit10 = 5, .u.num.digit11 = 6, .u.num.digit12 = 7, .u.num.digit13 = 8, .u.num.digit14 = 9, .u.num.digit15 = 0},
        {.u.num.digit1 = 2, .u.num.digit2 = 6, .u.num.digit3 = 2, .u.num.digit4 = 0, .u.num.digit5 = 1, .u.num.digit6 = 1, .u.num.digit7 = 2, .u.num.digit8 = 3,
         .u.num.digit9 = 4, .u.num.digit10 = 5, .u.num.digit11 = 6, .u.num.digit12 = 7, .u.num.digit13 = 8, .u.num.digit14 = 9, .u.num.digit15 = 0},
        {.u.num.digit1 = 3, .u.num.digit2 = 1, .u.num.digit3 = 0, .u.num.digit4 = 1, .u.num.digit5 = 5, .u.num.digit6 = 0, .u.num.digit7 = 1, .u.num.digit8 = 2,
         .u.num.digit9 = 3, .u.num.digit10 = 4, .u.num.digit11 = 5, .u.num.digit12 = 6, .u.num.digit13 = 7, .u.num.digit14 = 8, .u.num.digit15 = 9},
        {.u.num.digit1 = 4, .u.num.digit2 = 6, .u.num.digit3 = 0, .u.num.digit4 = 0, .u.num.digit5 = 0, .u.num.digit6 = 1, .u.num.digit7 = 3, .u.num.digit8 = 5,
         .u.num.digit9 = 7, .u.num.digit10 = 9, .u.num.digit11 = 2, .u.num.digit12 = 4, .u.num.digit13 = 6, .u.num.digit14 = 8, .u.num.digit15 = 0},
        {.u.num.digit1 = 5, .u.num.digit2 = 2, .u.num.digit3 = 0, .u.num.digit4 = 0, .u.num.digit5 = 3, .u.num.digit6 = 1, .u.num.digit7 = 2, .u.num.digit8 = 3,
         .u.num.digit9 = 4, .u.num.digit10 = 5, .u.num.digit11 = 6, .u.num.digit12 = 7, .u.num.digit13 = 8, .u.num.digit14 = 9, .u.num.digit15 = 0},
        {.u.num.digit1 = 4, .u.num.digit2 = 7, .u.num.digit3 = 0, .u.num.digit4 = 0, .u.num.digit5 = 1, .u.num.digit6 = 0, .u.num.digit7 = 1, .u.num.digit8 = 7,
         .u.num.digit9 = 1, .u.num.digit10 = 5, .u.num.digit11 = 6, .u.num.digit12 =6, .u.num.digit13 = 4, .u.num.digit14 = 2, .u.num.digit15 = 3},
        {.u.num.digit1 = 4, .u.num.digit2 = 1, .u.num.digit3 = 0, .u.num.digit4 = 0, .u.num.digit5 = 4, .u.num.digit6 = 1, .u.num.digit7 = 2, .u.num.digit8 = 3,
         .u.num.digit9 = 4, .u.num.digit10 = 5, .u.num.digit11 = 6, .u.num.digit12 =7, .u.num.digit13 = 8, .u.num.digit14 = 9, .u.num.digit15 = 0xf},
        {.u.num.digit1 = 4, .u.num.digit2 = 1, .u.num.digit3 = 0, .u.num.digit4 = 0, .u.num.digit5 = 4, .u.num.digit6 = 1, .u.num.digit7 = 2, .u.num.digit8 = 3,
         .u.num.digit9 = 4, .u.num.digit10 = 5, .u.num.digit11 = 6, .u.num.digit12 =7, .u.num.digit13 = 8, .u.num.digit14 = 0xf, .u.num.digit15 = 0xf},
        {.u.num.digit1 = 4, .u.num.digit2 = 1, .u.num.digit3 = 0, .u.num.digit4 = 0, .u.num.digit5 = 4, .u.num.digit6 = 1, .u.num.digit7 = 2, .u.num.digit8 = 3,
         .u.num.digit9 = 4, .u.num.digit10 = 5, .u.num.digit11 = 6, .u.num.digit12 =7, .u.num.digit13 = 0xf, .u.num.digit14 = 0xf, .u.num.digit15 = 0xf},
        {.u.num.digit1 = 4, .u.num.digit2 = 1, .u.num.digit3 = 0, .u.num.digit4 = 0, .u.num.digit5 = 4, .u.num.digit6 = 1, .u.num.digit7 = 2, .u.num.digit8 = 0xf,
         .u.num.digit9 = 0xf, .u.num.digit10 = 0xf, .u.num.digit11 = 0xf, .u.num.digit12 = 0xf, .u.num.digit13 = 0xf, .u.num.digit14 = 0xf, .u.num.digit15 = 0xf},
    };


    char imsi_compare[TEST_CASE_COMMON_CONVERT_MAX][IMSI_BCD_DIGITS_MAX + 1] = {
        "001011234567890",
        "262011234567890",
        "310150123456789",
        "460001357924680",
        "520031234567890",
        "470010171566423",
        "41004123456789",
        "4100412345678",
        "410041234567",
        "4100412",
    };

    for(i = 0; i < TEST_CASE_COMMON_CONVERT_MAX; i++){
        mme_app_convert_imsi_to_imsi_mme(&imsi_mme, &imsi_structs[i]);
        printf("IMSI mme %"IMSI_FORMAT" %d compare %s \n", IMSI_DATA(imsi_mme), imsi_mme.length, imsi_compare[i]);
        ck_assert_str_eq(IMSI_DATA(imsi_mme), imsi_compare[i]);
    }
}
END_TEST

START_TEST(imsi_equal_test)
{
    mme_app_imsi_t imsi_mme_a;
    mme_app_imsi_t imsi_mme_b;
    const char imsi_str_a[] = "001011234567890";
    const char imsi_str_b[] = "262011234567890";

    mme_app_string_to_imsi(&imsi_mme_a, imsi_str_a);
    mme_app_string_to_imsi(&imsi_mme_b, imsi_str_b);

    ck_assert(mme_app_imsi_compare(&imsi_mme_a, &imsi_mme_b) == false);
    ck_assert(mme_app_imsi_compare(&imsi_mme_a, &imsi_mme_a) == true);
    ck_assert(mme_app_imsi_compare(&imsi_mme_b, &imsi_mme_a) == false);
    ck_assert(mme_app_imsi_compare(&imsi_mme_a, &imsi_mme_a) == true);
}
END_TEST

Suite * imsi_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("IMSI tests");

    /* Core test case */
    tc_core = tcase_create("IMSI test");
    tcase_add_test(tc_core, imsi_empty_test);
    tcase_add_test(tc_core, imsi_convert_common_struct_test);
    tcase_add_test(tc_core, imsi_convert_to_uint_test);
    tcase_add_test(tc_core, imsi_equal_test);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    /* Create SQR Test Suite */
    s = imsi_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
