#include <math.h>
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

CTEST(perimetr, test2)
{
    Point p1 = {0, 0};
    Circle c = {p1, 0};
    ASSERT_DBL_NEAR(0.0, perimetr(&c));
}

CTEST(perimetr, test3)
{
    Point p1 = {10, 10};
    Circle c = {p1, 0};
    ASSERT_DBL_NEAR(0.0, perimetr(&c));
}

CTEST(perimetr, test4)
{
    Point p1 = {10, 10};
    Circle c = {p1, 1};
    ASSERT_DBL_NEAR(M_PI * 2, perimetr(&c));
}

CTEST(perimetr, test5)
{
    Point p1 = {10, 10};
    Circle c = {p1, 1.577};
    ASSERT_DBL_NEAR(M_PI * 2 * 1.577, perimetr(&c));
}

CTEST(area, zero_area)
{
    Point p1 = {10, 10};
    Circle c = {p1, 0};
    ASSERT_DBL_NEAR(0.0, area(&c));
}

CTEST(area, area_test)
{
    Point p1 = {10, 10};
    Circle c = {p1, 1};
    ASSERT_DBL_NEAR(M_PI, area(&c));
}

CTEST(area, irrational_area)
{
    Point p1 = {10, 10};
    Circle c = {p1, M_PI};
    ASSERT_DBL_NEAR(M_PI * M_PI * M_PI, area(&c));
}

CTEST(intersect, same_circle)
{
    Point p1 = {10, 10};
    Circle c1 = {p1, 1};
    ASSERT_EQUAL(1, is_intersect(&c1, &c1));
}

CTEST(intersect, intersection_same)
{
    Point p1 = {10, 10};
    Circle c1 = {p1, 1};
    Point p2 = {10, 10};
    Circle c2 = {p2, 1};
    ASSERT_EQUAL(1, is_intersect(&c1, &c2));
}

CTEST(intersect, intersection_dif_r)
{
    Point p1 = {10, 10};
    Circle c1 = {p1, 1};
    Point p2 = {10, 10};
    Circle c2 = {p2, 10};
    ASSERT_EQUAL(1, is_intersect(&c1, &c2));
}

CTEST(intersect, intersection_dif_pos)
{
    Point p1 = {0, 0};
    Circle c1 = {p1, 10};
    Point p2 = {10, 10};
    Circle c2 = {p2, 10};
    ASSERT_EQUAL(1, is_intersect(&c1, &c2));
}

CTEST(intersect, intersection_in_one_dot)
{
    Point p1 = {-10, 0};
    Circle c1 = {p1, 10};
    Point p2 = {10, 0};
    Circle c2 = {p2, 10};
    ASSERT_EQUAL(1, is_intersect(&c1, &c2));
}

CTEST(intersect, no_intersections)
{
    Point p1 = {-10, 0};
    Circle c1 = {p1, 5};
    Point p2 = {10, 0};
    Circle c2 = {p2, 5};
    ASSERT_EQUAL(0, is_intersect(&c1, &c2));
}
