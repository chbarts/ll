#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "rdbl.h"
#include "ll2.h"

int n = 0;

ll *push(double num, ll * tos)
{
    ll *tmp;
    double *data;

    if (!(data = malloc(sizeof(double)))) {
        fprintf(stderr, "stack die, everybody cry\n");
        tos = free_all_data(tos);
        free_all_nodes(tos);
        exit(EXIT_FAILURE);
    }

    *data = num;

    if (!(tmp = new_node(1, data, tos))) {
        fprintf(stderr, "stack die, everybody cry\n");
        tos = free_all_data(tos);
        free_all_nodes(tos);
        exit(EXIT_FAILURE);
    }

    n++;
    return tmp;
}

ll *add(ll * tos)
{
    ll *nxt;
    double *nd, *td;

    if (!tos || !(nxt = get_next(tos))) {
        fprintf(stderr, "add: stack too shallow\n");
        return tos;
    }

    nd = (double *) get_data(nxt);
    td = (double *) get_data(tos);
    *nd += *td;
    free(td);
    free(tos);
    n--;
    return nxt;
}

ll *sub(ll * tos)
{
    ll *nxt;
    double *nd, *td;

    if (!tos || !(nxt = get_next(tos))) {
        fprintf(stderr, "sub: stack too shallow\n");
        return tos;
    }

    nd = (double *) get_data(nxt);
    td = (double *) get_data(tos);
    *nd -= *td;
    free(td);
    free(tos);
    n--;
    return nxt;
}

ll *mul(ll * tos)
{
    ll *nxt;
    double *nd, *td;

    if (!tos || !(nxt = get_next(tos))) {
        fprintf(stderr, "mul: stack too shallow\n");
        return tos;
    }

    nd = (double *) get_data(nxt);
    td = (double *) get_data(tos);
    *nd *= *td;
    free(td);
    free(tos);
    n--;
    return nxt;
}

ll *ddiv(ll * tos)
{
    ll *nxt;
    double *td, *nd;

    if (!tos || !(nxt = get_next(tos))) {
        fprintf(stderr, "div: stack too shallow\n");
        return tos;
    }

    nd = (double *) get_data(nxt);
    td = (double *) get_data(tos);

    if (*td == 0.0) {
        fprintf(stderr, "div: divide by zero\n");
        return tos;
    }

    *nd /= *td;
    free(td);
    free(tos);
    n--;
    return nxt;
}

ll *neg(ll * tos)
{
    double *td;

    if (!tos) {
        fprintf(stderr, "neg: stack too shallow\n");
        return tos;
    }

    td = (double *) get_data(tos);

    *td = -(*td);
    return tos;
}

ll *srt(ll * tos)
{
    double *td;

    if (!tos) {
        fprintf(stderr, "neg: stack too shallow\n");
        return tos;
    }

    td = (double *) get_data(tos);

    if (*td < 0.0) {
        fprintf(stderr,
                "sqrt: argument is negative (imagine the result)\n");
        return tos;
    }

    *td = sqrt(*td);
    return tos;
}

void print_tos(ll * tos)
{
    double *de;

    if (!tos) {
        fprintf(stderr, ".: stack too shallow\n");
        return;
    }

    de = (double *) get_data(tos);
    printf("%lg\n", *de);
}

void print_stack(ll * tos)
{
    double *de;

    while (tos) {
        de = (double *) get_data(tos);
        printf("%lg\n", *de);
        tos = get_next(tos);
    }
}

ll *drop(ll * tos)
{
    ll *nxt;

    if (!tos)
        return NULL;

    nxt = get_next(tos);
    free(get_data(tos));
    free(tos);
    n--;
    return nxt;
}

ll *dup(ll * tos)
{
    if (!tos)
        return NULL;

    return push(*((double *) get_data(tos)), tos);
}

ll *swap(ll * tos)
{
    ll *nxt;

    if (!tos)
        return NULL;

    if (!(nxt = get_next(tos))) {
        fprintf(stderr, "swap: stack too shallow\n");
        return tos;
    }

    set_next(tos, get_next(nxt));
    set_next(nxt, tos);
    return nxt;
}

ll *rot(ll * tos)
{
    ll *nxt1, *nxt2;

    if (!tos)
        return NULL;

    if (!(nxt1 = get_next(tos)) || !(nxt2 = get_next(nxt1))) {
        fprintf(stderr, "rot: stack too shallow\n");
        return tos;
    }

    set_next(nxt1, get_next(nxt2));
    set_next(nxt2, tos);
    set_next(tos, nxt1);
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
            tos = free_all_data(tos);
            free_all_nodes(tos);
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
            tos = free_all_data(tos);
            free_all_nodes(tos);
            return 0;
        case '.':
            print_tos(tos);
            break;
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

    tos = free_all_data(tos);
    free_all_nodes(tos);
    return 0;
}
