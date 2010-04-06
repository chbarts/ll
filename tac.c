#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handle_ferr.h"
#include "ggets.h"
#include "ll3.h"

static void *print(int tag, void *lp)
{
    char *ln = lp;

    printf("%d: %s\n", tag, ln);

    return lp;
}

static void dofile(char *pname, char *fname, FILE * inf)
{
    ll *beg = NULL;
    char *ln;

    while (fggets(&ln, inf) != EOF) {
        if (!(beg = new_node((int) strlen(ln), ln, beg))) {
            free_all_nodes(free_all_data(beg));
            fprintf(stderr, "%s: new_node() failed on %s\n", pname, fname);
            exit(EXIT_FAILURE);
        }
    }

    puts(fname);

    free_all_nodes(free_all_data(map(beg, print)));
}

int main(int argc, char *argv[])
{
    FILE *inf;
    int i;

    if (argc == 1) {
        dofile(argv[0], "stdin", stdin);

        if (ferror(stdin)) {
            handle_ferr("stdin", argv[0]);
        }

        return 0;
    }

    for (i = 1; i < argc; i++) {
        if (!(inf = fopen(argv[i], "r"))) {
            handle_ferr(argv[i], argv[0]);
            continue;
        }

        dofile(argv[0], argv[i], inf);

        if (ferror(inf)) {
            handle_ferr(argv[i], argv[0]);
        }

        if (fclose(inf)) {
            handle_ferr(argv[i], argv[0]);
        }
    }

    return 0;
}
