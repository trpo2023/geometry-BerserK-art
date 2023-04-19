#include <stdlib.h>

#include <ctest.h>

#include <libgeometry/figures.h>
#include <libgeometry/lexer.h>
#include <libgeometry/parser.h>

// basic test without setup/teardown
CTEST(suite1, test1) {
    ASSERT_EQUAL(1, 1);
}
