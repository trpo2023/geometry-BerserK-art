#include <stdlib.h>

#include <ctest.h>

#include <libgeometry/figures.h>
#include <libgeometry/lexer.h>
#include <libgeometry/parser.h>

// basic test without setup/teardown
CTEST(suite1, test1)
{
    ASSERT_EQUAL(1, 1);
}

CTEST(correct_circle, intparse_test)
{
    char a[] = "circle(15 14, 13)";
    Circle c1 = get_circle(a);
    ASSERT_DBL_NEAR(15.0, c1.p.x);
    ASSERT_DBL_NEAR(14.0, c1.p.y);
    ASSERT_DBL_NEAR(13.0, c1.R);
}

CTEST(correct_circle, doubleparse_test)
{
    char a[] = "circle(15.8 14.9, 13.3)";
    Circle c1 = get_circle(a);
    ASSERT_DBL_NEAR(15.8, c1.p.x);
    ASSERT_DBL_NEAR(14.9, c1.p.y);
    ASSERT_DBL_NEAR(13.3, c1.R);
}

CTEST(correct_circle, negativeparse_test)
{
    char a[] = "circle(-15.8 -14.9, 13.3)";
    Circle c1 = get_circle(a);
    ASSERT_DBL_NEAR(-15.8, c1.p.x);
    ASSERT_DBL_NEAR(-14.9, c1.p.y);
    ASSERT_DBL_NEAR(13.3, c1.R);
}

CTEST(correct_circle, dotparse_test)
{
    char a[] = "circle(.8 -.9, 13.3)";
    Circle c1 = get_circle(a);
    ASSERT_DBL_NEAR(0.8, c1.p.x);
    ASSERT_DBL_NEAR(-0.9, c1.p.y);
    ASSERT_DBL_NEAR(13.3, c1.R);
}

CTEST(correct_circle, spase_test)
{
    char a[] = "circle(0.8  -0.9    ,     13.3)";
    Circle c1 = get_circle(a);
    ASSERT_DBL_NEAR(0.8, c1.p.x);
    ASSERT_DBL_NEAR(-0.9, c1.p.y);
    ASSERT_DBL_NEAR(13.3, c1.R);
}

CTEST(uncorrect_circle, triangle_test)
{
    char a[] = "triangle(15 14, 13)";
    Circle c1 = get_circle(a);
    ASSERT_DBL_NEAR(0.0, c1.p.x);
    ASSERT_DBL_NEAR(0.0, c1.p.y);
    ASSERT_DBL_NEAR(0.0, c1.R);
}

CTEST(uncorrect_circle, only_dot_test)
{
    char a[] = "circle(. 14, 13)";
    Circle c1 = get_circle(a);
    ASSERT_DBL_NEAR(0.0, c1.p.x);
    ASSERT_DBL_NEAR(0.0, c1.p.y);
    ASSERT_DBL_NEAR(0.0, c1.R);
}
