#include <stdlib.h>

#include <ctest.h>

#include <libgeometry/lexer.h>

// basic test without setup/teardown
CTEST(suite1, test1)
{
    ASSERT_EQUAL(1, 1);
}

CTEST(correct_circle, simple_test)
{
    char a[] = "circle(10 10, 10)";
    ASSERT_EQUAL(1, is_circle(a, 0));
}

CTEST(correct_circle, toLower)
{
    char a[] = "CIRCLE(10 10, 10)";
    ASSERT_EQUAL(1, is_circle(a, 0));
}

CTEST(correct_circle, dif_reg)
{
    char a[] = "cIrcLe(10 10, 10)";
    ASSERT_EQUAL(1, is_circle(a, 0));
}

CTEST(correct_circle, double_test)
{
    char test1[] = "circle(10.0 10.0, 10.0)";
    ASSERT_EQUAL(1, is_circle(test1, 0));
    char test2[] = "circle(10.3281 10, 10)";
    ASSERT_EQUAL(1, is_circle(test2, 0));
    char test3[] = "circle(10. 10., 10)";
    ASSERT_EQUAL(1, is_circle(test3, 0));
    char test4[] = "circle(-10 -10, 10.122)";
    ASSERT_EQUAL(1, is_circle(test4, 0));
}

CTEST(correct_circle, space_test)
{
    char test1[] = "circle(  10.0    10.0,    10.0)";
    ASSERT_EQUAL(1, is_circle(test1, 0));
    char test2[] = "circle(10.3281 10,10)";
    ASSERT_EQUAL(1, is_circle(test2, 0));
    char test3[] = "circle(10 10, 10)";
    ASSERT_EQUAL(1, is_circle(test3, 0));
    char test4[] = "cIrcLe(10 10                          , 10)";
    ASSERT_EQUAL(1, is_circle(test4, 0));
}

CTEST(uncorrect_circle, uncorrect_circle)
{
    char test1[] = "circcle(10.0 10.0, 10.0)";
    ASSERT_EQUAL(0, is_circle(test1, 0));
    char test2[] = "ircle(10.3281 10, 10)";
    ASSERT_EQUAL(0, is_circle(test2, 0));
    char test3[] = "circle (10. 10., 10)";
    ASSERT_EQUAL(0, is_circle(test3, 0));
    char test4[] = "triangle(10 10, 10.122)";
    ASSERT_EQUAL(0, is_circle(test4, 0));
}

CTEST(uncorrect_circle, empty_test)
{
    char a[] = "CIRCLE(  , )";
    ASSERT_EQUAL(0, is_circle(a, 0));
}

CTEST(uncorrect_circle, last_empty_test)
{
    char a[] = "CIRCLE(1  1, )";
    ASSERT_EQUAL(0, is_circle(a, 0));
}

CTEST(uncorrect_circle, mid_empty_test)
{
    char a[] = "CIRCLE(1  , 1)";
    ASSERT_EQUAL(0, is_circle(a, 0));
}

CTEST(uncorrect_circle, two_empty_numbers_test)
{
    char a[] = "CIRCLE(  , 1)";
    ASSERT_EQUAL(0, is_circle(a, 0));
}

CTEST(uncorrect_circle, uncorrect_numbers)
{
    char test1[] = "circle(a 10, 10)";
    ASSERT_EQUAL(0, is_circle(test1, 0));
    char test2[] = "circle(10 1e0, 10)";
    ASSERT_EQUAL(0, is_circle(test2, 0));
    char test3[] = "circle (10 10, 10 as)";
    ASSERT_EQUAL(0, is_circle(test3, 0));
    char test4[] = "circle(10 10, ten)";
    ASSERT_EQUAL(0, is_circle(test4, 0));
}

CTEST(uncorrect_circle, uncorrect_double)
{
    char test1[] = "circle(10.. 10, 10)";
    ASSERT_EQUAL(0, is_circle(test1, 0));
    char test2[] = "circle(. 10, 10)";
    ASSERT_EQUAL(0, is_circle(test2, 0));
    char test3[] = "circle(10 .10., 10)";
    ASSERT_EQUAL(0, is_circle(test3, 0));
    char test4[] = "circle(1,0 1,0 , 1,0)";
    ASSERT_EQUAL(0, is_circle(test4, 0));
}

CTEST(uncorrect_circle, free_mistakes_test)
{
    char test1[] = "circle(10 10, 10";
    ASSERT_EQUAL(0, is_circle(test1, 0));
    char test2[] = "circle(10, 10, 10)";
    ASSERT_EQUAL(0, is_circle(test2, 0));
    char test3[] = "circle(10 10. 10)";
    ASSERT_EQUAL(0, is_circle(test3, 0));
    char test4[] = "circle(10 - 10 , 10)";
    ASSERT_EQUAL(0, is_circle(test4, 0));
}

CTEST(uncorrect_circle, negative_radius_test)
{
    char test1[] = "circle(10 10, -10)";
    ASSERT_EQUAL(0, is_circle(test1, 0));
    char test2[] = "circle(10 10, -10.9)";
    ASSERT_EQUAL(0, is_circle(test2, 0));
    char test3[] = "circle(-10 -10, 10)";
    ASSERT_EQUAL(1, is_circle(test3, 0));
    char test4[] = "circle(10 10 , 10-)";
    ASSERT_EQUAL(0, is_circle(test4, 0));
}
