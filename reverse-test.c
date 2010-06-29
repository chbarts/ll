#include <stdlib.h>
#include <stdio.h>
#include "ll3.h"

static int lst[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

static void *print(int tag, void *data)
{
    int *i = data;
    (void) tag;
    printf("%d\n", *i);
    return data;
}

int main(void)
{
    ll *beg = NULL;
    int i;

    for (i = 0; i < 10; i++) {
        if (!(beg = new_node(0, &(lst[i]), beg))) {
            perror("malloc()");
            exit(EXIT_FAILURE);
        }
    }

    beg = map(reverse(map(beg, print)), print);
    free_all_nodes(beg);

    return 0;
}
