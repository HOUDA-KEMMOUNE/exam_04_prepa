#include "../header.h"
t_tree  *parse_expr(char **s);
#include <ctype.h>


t_tree  *new_node(t_tree node)
{
    t_tree *ptr = gc_malloc(sizeof(node));
    if(!ptr)
    {
        gc_free_all();
        exit(1);
    }
    *ptr = node;
    return(ptr);
}

void    unexpected(char c)
{
    if (c)
        printf("unexpected token '%c'\n", c);
    else
        printf("unexpected end of input\n");
    gc_free_all();
    exit(1);
}

t_tree  *parse_factor(char **s)
{
    if(isdigit(**s))
    {
        t_tree node = {VAL, **s - '0', NULL, NULL};
        (*s)++;
        return(new_node(node));
    }
    if(**s == '(')
    {
        (*s)++;
        t_tree *node = parse_expr(s);
        if(**s != ')')
            unexpected(**s);
        (*s)++;
        return(node);
    }
    unexpected(**s);
    return NULL;
}


t_tree *parse_term(char **s)
{
    t_tree *left = parse_factor(s);
    while(*s && **s == '*')
    {
        (*s)++;
        t_tree *right = parse_factor(s);
        t_tree node = {MULTI, 0, left, right};
        left = new_node(node);
    }
    return(left);
}

t_tree *parse_expr(char **s)
{
    t_tree *left = parse_term(s);
    while(**s == '+')
    {
        (*s)++;
        t_tree *right = parse_term(s);
        t_tree node = {ADD, 0, left, right};
        left = new_node(node);
    }
    return(left);
}
#include "ctype.h"

void    unexpected(char c)
{
    if(c)
        printf("unexpected token %c\n", c);
    else
        printf("unexpected end of file\n");
    exit (1);
}

t_tree *new_node(t_tree node)
{
    t_tree *ptr = gc_malloc(sizeof(node));
    *ptr = node;
    return ptr;
}

t_tree *parse_factor(char **s)
{
    if(isdigit(**s))
    {
        t_tree node = {VAL, **s - '0', NULL, NULL};
        (*s)++;
        return(new_node(node));
    }
    if(**s == '(')
    {
        (*s)++;
        t_tree *node = parse_expr(s);
        if(**s != ')')
            unexpected(**s);
        (*s)++;
        return(node);
    }
    unexpected(**s);
    return(NULL);
}

t_tree *parse_term(char **s)
{
    t_tree *left = parse_factor(s);
    while(**s == '*')
    {
        (*s)++;
        t_tree *right = parse_factor(s);
        t_tree node = {MULTI, '*', left, right};
        left = new_node(node);
    }
    return(left);
}


t_tree *parse_expr(char **s)
{
    t_tree *left = parse_term(s);
    while(**s == '+')
    {
        (*s)++;
        t_tree *right = parse_term(s);
        t_tree node = {ADD, '+', left, right};
        left = new_node(node);
    }
    return(left);
}