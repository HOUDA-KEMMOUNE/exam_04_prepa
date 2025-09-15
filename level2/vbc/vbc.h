#ifndef VBC_H
#define VBC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// ghadiri dik enum struct
typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;

node *parse_expr(char **s);
node *parse_factor(char **s);
node *parse_term(char **s);
// wfcts diyalk 3adi
// node *parse_expr(char **s);
// node *parse_term(char **s);
// node *parse_factor(char **s);

#endif