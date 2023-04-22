#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/lexer.h>
#include <libgeometry/parser.h>

#define SKIP                             \
    while (i < strlen(a) && a[i] == ' ') \
    i++
#define pi 3.14159265358979

void print_crc(Circle c)
{
    printf("circle(%lf %lf, %lf)\n", c.p.x, c.p.y, c.R);
}

Circle get_circle(char a[])
{
    Point p1 = {0, 0};
    Circle circle = {p1, 0};
    if (is_circle(a, 0) == 0)
        return circle;
    int i = 7, k = 0, dot = 1;
    char fl1[255], fl2[255], fl3[255];

    SKIP;

    if (a[i] == '-')
        fl1[k++] = a[i++];

    while (i < strlen(a)) {
        if (isdigit(a[i]) || (dot && a[i] == '.')) {
            fl1[k++] = a[i];
            if (a[i] == '.')
                dot = 0;
        } else {
            if (a[i] != ' ') {
                return circle;
            }
            break;
        }
        i++;
    }
    fl1[k] = '\0';
    k = 0;
    dot = 1;
    SKIP;

    if (a[i] == '-')
        fl2[k++] = a[i++];
    while (i < strlen(a)) {
        if (isdigit(a[i]) || (dot && a[i] == '.')) {
            fl2[k++] = a[i];
            if (a[i] == '.')
                dot = 0;
        } else {
            if (a[i] != ' ' && a[i] != ',') {
                return circle;
            }
            break;
        }
        i++;
    }
    SKIP;
    if (a[i++] != ',') {
        return circle;
    }
    while (i < strlen(a) && a[i] == ' ') {
        i++;
    }
    fl2[k] = '\0';
    k = 0;
    dot = 1;
    if (a[i] == '-')
        fl3[k++] = a[i++];
    while (i < strlen(a)) {
        if (isdigit(a[i]) || (dot && a[i] == '.')) {
            fl3[k++] = a[i];
            if (a[i] == '.')
                dot = 0;
        } else {
            if (a[i] != ' ' && a[i] != ')') {
                return circle;
            }
            break;
        }
        i++;
    }
    SKIP;
    if (a[i++] != ')') {
        return circle;
    }
    fl3[k] = '\0';

    circle.p.x = atof(fl1);
    circle.p.y = atof(fl2);
    circle.R = atof(fl3);
    return circle;
}
