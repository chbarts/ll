#include <stdlib.h>
#include <stdio.h>
#include "rdbl.h"

int main(int argc, char *argv[])
{
    FILE *fp = stdin;
    double d;
    int c;

    if (argc == 2) {
        if ((fp = fopen(argv[1], "r")) == NULL) {
            perror("rdbl-test");
            exit(EXIT_FAILURE);
        }
    }

    while ((c = getc(fp)) != EOF) {
        ungetc(c, fp);

        if (rdbl(fp, &d)) {
            printf("Double: %lg\n", d * 2);
        } else {
            if ((c = getc(fp)) == EOF) {
                if (fp != stdin)
                    fclose(fp);

                exit(EXIT_SUCCESS);
            } else {
                putchar(c);
            }
        }
    }

    if (fp != stdin)
        fclose(fp);

    exit(EXIT_SUCCESS);
}
