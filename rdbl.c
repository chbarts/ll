/* By Chris Barts */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/* Returns 1 if double read, 0 otherwise
 * If it returns 1, the double is removed from the stream.
 * If it returns 0, the stream is as it was before the function was called.
 */

int rdbl(FILE * fd, double *d)
{
    int c, h, e;

    if ((c = getc(fd)) == EOF) {
        ungetc(c, fd);
        return 0;
    }

    if (isdigit(c)) {
        ungetc(c, fd);
        return fscanf(fd, "%lg", d);
    } else if ((c == '+') || (c == '-') || (c == '.')) {
        h = getc(fd);

        if (h == EOF) {
            ungetc(h, fd);
            ungetc(c, fd);
            return 0;
        } else if (isdigit(h)) {
            ungetc(h, fd);
            ungetc(c, fd);
            return fscanf(fd, "%lg", d);
        } else if ((h == '.') && (c != '.')) {
            e = getc(fd);
            ungetc(e, fd);
            ungetc(h, fd);
            ungetc(c, fd);

            if (isdigit(e)) {
                return fscanf(fd, "%lg", d);
            } else {
                return 0;
            }
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
