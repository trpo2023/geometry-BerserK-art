#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/lexer.h>
#include <libgeometry/parser.h>

int main(int argc, char* argv[])
{
    FILE* fp;
    if (argc != 1) {
        if ((fp = freopen(argv[1], "r", stdin)) == NULL)
            printf("No such file or directory");
    } else
        printf("введите количество фигур:\n");
    char num[255];
    gets(num);
    int size = atoi(num);
    char str[size][255];
    int count_with_no_errors = 0;
    for (int i = 0; i < size; i++) {
        gets(str[i]);
        count_with_no_errors += is_circle(str[i], 1);
    }
    Circle masc[count_with_no_errors];
    printf("\n");
    int da = 0;
    for (int i = 0; i < size; i++) {
        if (is_circle(str[i], 0))
            masc[da++] = get_circle(str[i]);
    }
    for (int i = 0; i < count_with_no_errors; i++) {
        printf("%d.", i);
        print_crc(masc[i]);
        printf("perimetr: %lf\n", perimetr(&masc[i]));
        printf("area: %lf\n", area(&masc[i]));
        printf("intersects:\n");
        for (int j = 0; j < count_with_no_errors; j++) {
            if (i != j && is_intersect(&masc[i], &masc[j])) {
                printf("%d. circle\n", j);
            }
        }
        printf("\n");
    }
    if (fp) {
        fclose(fp);
    }
    return 0;
}
