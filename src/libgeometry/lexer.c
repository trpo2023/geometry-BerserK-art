#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/lexer.h>

#define SKIP                             \
    while (i < strlen(a) && a[i] == ' ') \
    i++

int is_circle(char a[], int comments)
{
    char c[] = "circle(";
    for (int i = 0; i < strlen(a); i++) {
        a[i] = tolower(a[i]);
        if (i < 7 && c[i] != a[i]) {
            if (comments) {
                printf("%s\n", a);
                printf(" ^ \nNot a circle\n");
            }
            return 0;
        }
    }
    int i = 7, dot = 1, num = 0;
    SKIP;

    if (a[i] == '-')
        i++;
    while (i < strlen(a)) {
        if (!(isdigit(a[i]) || (dot && a[i] == '.'))) {
            if (!(a[i] == ' ' && num)) {
                if (comments) {
                    printf("%s\n", a);
                    for (int j = 0; j < i; j++)
                        printf(" ");
                    printf("^\nwrong symbol\n");
                }
                return 0;
            }
            break;
        } else {
            if (a[i] == '.')
                dot = 0;
            else
                num = 1;
        }
        i++;
    }

    dot = 1;
    num = 0;
    SKIP;

    if (a[i] == '-')
        i++;
    while (i < strlen(a)) {
        if (!(isdigit(a[i]) || (dot && a[i] == '.'))) {
            if (!((a[i] == ' ' || a[i] == ',') && num)) {
                if (comments) {
                    printf("%s\n", a);
                    for (int j = 0; j < i; j++)
                        printf(" ");
                    printf("^\nwrong symbol\n");
                }
                return 0;
            }
            break;
        } else {
            if (a[i] == '.')
                dot = 0;
            else
                num = 1;
        }
        i++;
    }
    dot = 1;
    num = 0;
    SKIP;
    if (a[i++] != ',') {
        if (comments) {
            printf("Have no \',\'\n");
        }
        return 0;
    }
    SKIP;
    if (a[i] == '-')
        i++;
    while (i < strlen(a)) {
        if (!(isdigit(a[i]) || (dot && a[i] == '.'))) {
            if (!((a[i] == ' ' || a[i] == ')') && num)) {
                if (comments) {
                    printf("%s\n", a);
                    for (int j = 0; j < i; j++)
                        printf(" ");
                    printf("^\nwrong symbol\n");
                }
                return 0;
            }
            break;
        } else {
            if (a[i] == '.')
                dot = 0;
            else
                num = 1;
        }
        i++;
    }
    SKIP;
    if (a[i++] != ')') {
        if (comments) {
            printf("%s\nHave no ended \')\'\n", a);
        }
        return 0;
    }
    return 1;
}
