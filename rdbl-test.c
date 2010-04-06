#include <stdlib.h>
#include <stdio.h>
#include "rdbl.h"

int main(void)
{
    double d;
    int c;

    while ((c = getchar()) != EOF) {
        ungetc(c, stdin);

        if (rdbl(stdin, &d)) {
            printf("Double: %lg\n", d * 2);
            continue;
        } else {
            if ((c = getchar()) == EOF) {
                exit(EXIT_SUCCESS);
            } else {
                putchar(c);
            }

            continue;
        }
    }

    exit(EXIT_SUCCESS);
}
