#include <stdlib.h>
#include "ll.h"

ll *get_next(ll * node)
{
    if (!node)
        return NULL;

    if (!(node->nxt))
        return NULL;

    return node->nxt;
}

int get_tag(ll * node)
{
    if (!node)
        return -1;

    return node->tag;
}

void *get_data(ll * node)
{
    if (!node)
        return NULL;

    return node->data;
}

ll *get_end(ll * node)
{
    if (!node)
        return NULL;

    if (!(node->nxt))
        return node;

    while (node->nxt)
        node = get_next(node);

    return node;
}

ll *append_node(ll * cur, ll * new)
{
    if (!cur || !new)
        return NULL;

    if (!(cur->nxt)) {
        cur->nxt = new;
        return cur;
    }

    cur = get_end(cur);
    cur->nxt = new;
    return cur;
}

ll *prepend_node(ll * cur, ll * new)
{
    if (!cur || !new)
        return NULL;

    new->nxt = cur;
    return new;
}

ll *new_node(int tag, void *data, ll * next)
{
    ll *new;

    if (!(new = malloc(sizeof(ll))))
        return NULL;

    new->tag = tag;
    new->data = data;
    new->nxt = next;

    return new;
}

void free_all_nodes(ll * beg, int d)
{
    ll *tmp;

    if (!beg)
        return;

    while (beg) {
        tmp = beg->nxt;
        if (d)
            free(beg->data);
        free(beg);
        beg = tmp;
    }

    return;
}
