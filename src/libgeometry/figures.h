#pragma once

typedef struct {
    double x;
    double y;
} Point;
typedef struct {
    Point p;
    double R;
} Circle;

double perimetr(Circle* c);
double area(Circle* c);
int is_intersect(Circle* c1, Circle* c2);
