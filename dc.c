#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "ll.h"

ll *push(double num, ll * tos)
{
    ll *tmp;
    double *data;

    if (!(data = malloc(sizeof(double)))) {
        fprintf(stderr, "stack die, everybody cry\n");
        free_all_nodes(tos, 1);
        exit(EXIT_FAILURE);
    }

    *data = num;

    if (!(tmp = new_node(1, data, tos))) {
        fprintf(stderr, "stack die, everybody cry\n");
        free_all_nodes(tos, 1);
        exit(EXIT_FAILURE);
    }

    return tmp;
}

ll *add(ll * tos)
{
    ll *nxt;

    if (!tos || !(tos->nxt)) {
        fprintf(stderr, "add: stack too shallow\n");
        return tos;
    }

    nxt = tos->nxt;
    *((double *) nxt->data) += *((double *) tos->data);
    free(tos->data);
    free(tos);
    return nxt;
}

ll *sub(ll * tos)
{
    ll *nxt;

    if (!tos || !(tos->nxt)) {
        fprintf(stderr, "sub: stack too shallow\n");
        return tos;
    }

    nxt = tos->nxt;
    *((double *) nxt->data) -= *((double *) tos->data);
    free(tos->data);
    free(tos);
    return nxt;
}

ll *mul(ll * tos)
{
    ll *nxt;

    if (!tos || !(tos->nxt)) {
        fprintf(stderr, "mul: stack too shallow\n");
        return tos;
    }

    nxt = tos->nxt;
    *((double *) nxt->data) *= *((double *) tos->data);
    free(tos->data);
    free(tos);
    return nxt;
}

ll *ddiv(ll * tos)
{
    ll *nxt;

    if (!tos || !(tos->nxt)) {
        fprintf(stderr, "div: stack too shallow\n");
        return tos;
    }

    if ((*((double *) tos->data)) == 0.0) {
        fprintf(stderr, "div: divide by zero\n");
        return tos;
    }

    nxt = tos->nxt;
    *((double *) nxt->data) /= *((double *) tos->data);
    free(tos->data);
    free(tos);
    return nxt;
}

ll *neg(ll * tos)
{
    if (!tos) {
        fprintf(stderr, "neg: stack too shallow\n");
        return tos;
    }

    *((double *) tos->data) = -(*((double *) tos->data));
    return tos;
}

void print_stack(ll * tos)
{
    while (tos) {
        printf("%lg\n", *((double *) tos->data));
        tos = tos->nxt;
    }
}

ll *drop(ll * tos)
{
    ll *nxt;

    if (!tos)
        return NULL;

    nxt = tos->nxt;
    free(tos->data);
    free(tos);
    return nxt;
}

ll *dup(ll * tos)
{
    return push(*((double *) tos->data), tos);
}

ll *swap(ll * tos)
{
    ll *nxt;

    if (!tos)
        return NULL;

    if (!(tos->nxt)) {
        fprintf(stderr, "swap: stack too shallow\n");
        return tos;
    }

    nxt = tos->nxt;
    tos->nxt = nxt->nxt;
    nxt->nxt = tos;
    return nxt;
}

ll *rot(ll * tos)
{
    ll *nxt1, *nxt2;

    if (!tos)
        return NULL;

    if (!(tos->nxt) || !((tos->nxt)->nxt)) {
        fprintf(stderr, "rot: stack too shallow\n");
        return tos;
    }

    nxt1 = tos->nxt;
    nxt2 = nxt1->nxt;
    nxt1->nxt = nxt2->nxt;
    nxt2->nxt = tos;
    tos->nxt = nxt1;
    return nxt2;
}

int main(void)
{
    int c, h;
    double d;
    ll *tos = NULL;

    while ((c = getchar()) != EOF) {
        if (isdigit(c) || (c == '.')) {
            ungetc(c, stdin);
            scanf("%lg", &d);
            tos = push(d, tos);
            continue;
        }

        if ((c == '+') || (c == '-')) {
            if ((h = getchar()) == EOF) {
                if (c == '+') {
                    tos = add(tos);
                    continue;
                } else if (c == '-') {
                    tos = sub(tos);
                    continue;
                }
            } else if (isdigit(h) || (h == '.')) {
                ungetc(h, stdin);
                ungetc(c, stdin);
                scanf("%lg", &d);
                tos = push(d, tos);
                continue;
            } else {
                if (c == '+') {
                    tos = add(tos);
                    continue;
                } else if (c == '-') {
                    tos = sub(tos);
                    continue;
                }
            }
        }

        if (c == '*') {
            tos = mul(tos);
            continue;
        }

        if (c == '/') {
            tos = ddiv(tos);
            continue;
        }

        if (c == 'f') {
            print_stack(tos);
            continue;
        }

        if (c == 's') {
            tos = swap(tos);
            continue;
        }

        if (c == 'r') {
            tos = rot(tos);
            continue;
        }

        if (c == 'D') {
            tos = drop(tos);
            continue;
        }

        if (c == 'd') {
            tos = dup(tos);
            continue;
        }

        if (c == 'z') {
            tos = neg(tos);
            continue;
        }

        if (c == 'q') {
            free_all_nodes(tos, 1);
            return 0;
        }
    }

    free_all_nodes(tos, 1);
    return 0;
}
