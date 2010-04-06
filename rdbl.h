/* Returns 1 if double read, 0 otherwise
 * If it returns 1, the double is removed from the stream.
 * If it returns 0, the stream is as it was before the function was called.
 */

int rdbl(FILE * fd, double *d);
