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
    ll *beg = NULL, *tmp;
    int i;

    for (i = 0; i < 10; i++) {
        if (!(tmp = new_node(0, &(lst[i]), beg))) {
            perror("malloc()");
            free_all_nodes(beg);
            exit(EXIT_FAILURE);
        } else {
            beg = tmp;
        }
    }

    free_all_nodes(map(reverse(map(beg, print)), print));

    return 0;
}
