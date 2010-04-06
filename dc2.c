#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "rdbl.h"
#include "ll.h"

int n = 0;

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

    n++;
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
    n--;
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
    n--;
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
    n--;
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
    n--;
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

ll *srt(ll * tos)
{
    if (!tos) {
        fprintf(stderr, "neg: stack too shallow\n");
        return tos;
    }

    if ((*((double *) tos->data)) < 0.0) {
        fprintf(stderr,
                "sqrt: argument is negative (imagine the result)\n");
        return tos;
    }

    *((double *) tos->data) = sqrt((*((double *) tos->data)));
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
    n--;
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
        ungetc(c, stdin);

        if (rdbl(stdin, &d)) {
            tos = push(d, tos);
            continue;
        }

        if ((c = getchar()) == EOF) {
            free_all_nodes(tos, 1);
            return 0;
        }

        switch (c) {
        case '+':
            tos = add(tos);
            break;
        case '-':
            tos = sub(tos);
            break;
        case '*':
            tos = mul(tos);
            break;
        case '/':
            tos = ddiv(tos);
            break;
        case 'f':
            print_stack(tos);
            break;
        case 's':
            tos = swap(tos);
            break;
        case 'r':
            tos = rot(tos);
            break;
        case 'D':
            tos = drop(tos);
            break;
        case 'd':
            tos = dup(tos);
            break;
        case 'z':
            tos = neg(tos);
            break;
        case '=':
            printf("%d\n", n);
            break;
        case 'Q':
            tos = srt(tos);
            break;
        case 'q':
            free_all_nodes(tos, 1);
            return 0;
        case ' ':
        case '\n':
        case '\t':
        case '\f':
            break;
        default:
            fprintf(stderr, "unrecognized command %c\n", c);
            break;
        }
    }

    free_all_nodes(tos, 1);
    return 0;
}
