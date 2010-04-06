#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/* Returns 1 if double read, 0 otherwise
 * If it returns 1, the double is removed from the stream.
 * If it returns 0, the stream is as it was before the function was called.
 */

int rdbl(FILE * fd, double *d)
{
    int c, h;

    if ((c = getc(fd)) == EOF) {
        ungetc(c, fd);
        return 0;
    }

    if (isdigit(c) || (c == '.')) {
        ungetc(c, fd);
        if (scanf("%lg", d) != 1) {
            ungetc(c, fd);
            return 0;
        }

        return 1;
    } else if ((c == '+') || (c == '-')) {
        if ((h = getc(fd)) == EOF) {
            ungetc(h, fd);
            ungetc(c, fd);
            return 0;
        } else if (isdigit(h) || (h == '.')) {
            ungetc(h, fd);
            ungetc(c, fd);
            if (scanf("%lg", d) != 1) {
                ungetc(h, fd);
                ungetc(c, fd);
                return 0;
            }

            return 1;
        } else {
            ungetc(h, fd);
            ungetc(c, fd);
            return 0;
        }
    } else {
        ungetc(c, fd);
        return 0;
    }
}
