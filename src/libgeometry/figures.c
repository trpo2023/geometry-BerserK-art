#include <math.h>

#include <libgeometry/figures.h>

double perimetr(Circle* c)
{
    return M_PI * 2 * c->R;
}

double area(Circle* c)
{
    return M_PI * c->R * c->R;
}

int is_intersect(Circle* c1, Circle* c2)
{
    double bet
            = sqrt(pow(c1->p.x - c2->p.x, 2.0) + pow(c1->p.y - c2->p.y, 2.0));
    return bet <= (c1->R + c2->R);
}
