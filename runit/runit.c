#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define RUNIT_ATTACH_COUNT          10
#define RUNIT_CHECK_FIRST_FAILURE   ru_count_failure != 1 ? true : printf("\nFailures:\n\n")
#define RUNIT_ERROR_TEXT            printf("%d) %s\n\tError %s(%d): ", ru_count_failure, ru_err_buf, __FILE__, __LINE__)

#define describe(text)              ru_tmp_str[ru_namespace] = text;
#define context(text)               describe(text)
#define it(text)                    describe(text) ru_is_it = 1;

#define to_eq(x)                    == x ? \
                                    true : \
                                    (    ru_count_failure++, \
                                         RUNIT_CHECK_FIRST_FAILURE, \
                                         RUNIT_ERROR_TEXT, \
                                         printf("Expected to equal to %d\n", x) \
                                    ); \
                                    ru_test++;

#define not_to_eq(x)                != x ? \
                                    true : \
                                    (   ru_count_failure++, \
                                        RUNIT_CHECK_FIRST_FAILURE, \
                                        RUNIT_ERROR_TEXT, \
                                        printf("Expected to not to equal to %d\n", x) \
                                    ); \
                                    ru_test++;

#define arr_to_eq(_a, _b, _s)       for (int i = 0; i < _s; i++) \
                                    { \
                                        if (_a[i] != _b[i]) \
                                        { \
                                            ru_count_failure++; \
                                            RUNIT_CHECK_FIRST_FAILURE; \
                                            RUNIT_ERROR_TEXT; \
                                            printf("Elemets with %d index not equal (0x%x != 0x%x)\n", i, _a[i], _b[i]); \
                                        } \
                                    } \
                                    ru_test++;

#define assert_false                (   ru_count_failure++, \
                                        RUNIT_CHECK_FIRST_FAILURE, \
                                        RUNIT_ERROR_TEXT, \
                                        printf("Failure stub\n") \
                                    ); \
                                    ru_test++;

#define do                          { \
                                        if (ru_before_each_func != NULL && ru_is_it) ru_before_each_func(); \
                                        sprintf(ru_err_buf, "%s", ru_tmp_str[0]); \
                                        for (int i = 1; i <= ru_namespace; i++) { strcat(ru_err_buf, "\n\t"); strcat(ru_err_buf, ru_tmp_str[i]); } \
                                        ru_namespace++; \
                                        if (ru_namespace > RUNIT_ATTACH_COUNT) \
                                        { \
                                            printf("\nError (%d): There can only be %d levels attachment it()do...end\n\n", __LINE__, RUNIT_ATTACH_COUNT); \
                                            exit(1); \
                                        }
#define end                         } \
                                    sprintf(ru_err_buf, "%s", ""); \
                                    ru_namespace--; \
                                    if (ru_is_it) ru_is_it = 0;

#define source(_str)

#define before_each  void ru_before_each_func()

__attribute__((weak)) void ru_before_each_func();

unsigned int    ru_test = 0;
unsigned int    ru_count_failure = 0;
char           *ru_tmp_str[RUNIT_ATTACH_COUNT];
char            ru_err_buf[1024];
unsigned int    ru_namespace = 0;
char            ru_is_it = 0;

int main(void)
{
    #include "includes"
    printf("\n%d examples, %d failures\n", ru_test, ru_count_failure);
    return 0;
}
