# ifndef VBC_H
# define VBC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct s_node
{
    enum
    {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct s_node   *l;
    struct s_node   *r;
}               t_node;

t_node	*parse_expr(char **s);
t_node	*parse_term(char **s);
t_node	*parse_fact(char **s);

# endif