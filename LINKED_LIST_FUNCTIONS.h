#ifndef __LINKEDLIST_FUNCS__
#define __LINKEDLIST_FUNCS__
#include <stdio.h>

struct the_three
{
    int people;
    int court;
    int treasury;
};

struct node
{
    char question[300];
    char decision_1[200];
    struct the_three impact_1;
    char decision_2[200];
    struct the_three impact_2;
    int possibility;
    int index;
    struct node *next;
};

struct node * create_node(FILE *fp);
void print_list(struct node *l_list);
void add_end(struct node **l_list ,FILE *fp);
void add_front(struct node **l_list, FILE *fp);
void insert_next_node(struct node **l_list, int index, FILE *fp);
void delete_end(struct node **l_list);
void delete_front(struct node **l_list);
void delete_next(struct node **l_list, int index);
#endif
