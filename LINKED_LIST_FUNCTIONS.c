#include <stdio.h>
#include "LINKED_LIST_FUNCTIONS.h"

struct node * create_node(FILE *fp)
{
    struct node *pn;
    fseek(fp, 0, SEEK_SET);
    pn = (struct node *)malloc(sizeof(struct node));
    fgets(pn->question, 300, fp);
    fgets(pn->decision_1, 200, fp);
    fscanf(fp, "%d%d%d", &(pn->impact_1.people), &(pn->impact_1.court), &(pn->impact_1.treasury));
    fseek(fp, 2, SEEK_CUR);
    fgets(pn->decision_2, 200, fp);
    fscanf(fp, "%d%d%d", &(pn->impact_2.people), &(pn->impact_2.court), &(pn->impact_2.treasury));
    pn->possibility = 3;
    pn->next = NULL;
    return pn;
}

void print_list(struct node *l_list)
{
    struct node *p_l_list = l_list;
    printf("%s%s%d\n%d\n%d\n%s%d\n%d\n%d\n\n%d\n\n", p_l_list->question, p_l_list->decision_1, p_l_list->impact_1.people, p_l_list->impact_1.court, p_l_list->impact_1.treasury, p_l_list->decision_2, p_l_list->impact_2.people, p_l_list->impact_2.court, p_l_list->impact_2.treasury, p_l_list->index);
    while(p_l_list->next != NULL)
    {
        p_l_list = p_l_list->next;
        printf("%s%s%d\n%d\n%d\n%s%d\n%d\n%d\n\n%d\n\n", p_l_list->question, p_l_list->decision_1, p_l_list->impact_1.people, p_l_list->impact_1.court, p_l_list->impact_1.treasury, p_l_list->decision_2, p_l_list->impact_2.people, p_l_list->impact_2.court, p_l_list->impact_2.treasury, p_l_list->index);
    }
}

void add_end(struct node **l_list ,FILE *fp)
{
    struct node *p_l_list = *l_list, *pn;
    fseek(fp, 0, SEEK_SET);
    if(*l_list == NULL)
    {
        pn = (struct node *)malloc(sizeof(struct node));
        fgets(pn->question, 300, fp);
        pn->question[strlen(pn->question) - 1] = '\0';
        fgets(pn->decision_1, 200, fp);
        pn->decision_1[strlen(pn->decision_1) - 1] = '\0';
        fscanf(fp, "%d%d%d", &(pn->impact_1.people), &(pn->impact_1.court), &(pn->impact_1.treasury));
        fseek(fp, 2, SEEK_CUR);
        fgets(pn->decision_2, 200, fp);
        pn->decision_2[strlen(pn->decision_2) - 1] = '\0';
        fscanf(fp, "%d%d%d", &(pn->impact_2.people), &(pn->impact_2.court), &(pn->impact_2.treasury));
        pn->possibility = 3;
        pn->next = NULL;
        *l_list = pn;
    }
    else
    {
        while(p_l_list->next != NULL)
            p_l_list = p_l_list->next;
        pn = (struct node *)malloc(sizeof(struct node));
        p_l_list->next = pn;
        pn->next = NULL;
        fgets(pn->question, 300, fp);
        pn->question[strlen(pn->question) - 1] = '\0';
        fgets(pn->decision_1, 200, fp);
        pn->decision_1[strlen(pn->decision_1) - 1] = '\0';
        fscanf(fp, "%d%d%d", &(pn->impact_1.people), &(pn->impact_1.court), &(pn->impact_1.treasury));
        fseek(fp, 2, SEEK_CUR);
        fgets(pn->decision_2, 200, fp);
        pn->decision_2[strlen(pn->decision_2) - 1] = '\0';
        fscanf(fp, "%d%d%d", &(pn->impact_2.people), &(pn->impact_2.court), &(pn->impact_2.treasury));
        pn->possibility = 3;
    }
}

void add_front(struct node **l_list, FILE *fp)
{
    struct node *pn;
    fseek(fp, 0, SEEK_SET);
    pn = (struct node *)malloc(sizeof(struct node));
    pn->next = *l_list;
    fgets(pn->question, 300, fp);
    fgets(pn->decision_1, 200, fp);
    fscanf(fp, "%d%d%d", &(pn->impact_1.people), &(pn->impact_1.court), &(pn->impact_1.treasury));
    fseek(fp, 2, SEEK_CUR);
    fgets(pn->decision_2, 200, fp);
    fscanf(fp, "%d%d%d", &(pn->impact_2.people), &(pn->impact_2.court), &(pn->impact_2.treasury));
    pn->possibility = 3;
    *l_list = pn;
}

void insert_next_node(struct node **l_list, int index, FILE *fp)
{
    struct node *pn, *p_l_list = *l_list;
    fseek(fp, 0, SEEK_SET);
    if(index > 0)
    {
        int i;
        for(i = 1; i < index; i++)
            p_l_list = p_l_list->next;
        pn = (struct node *)malloc(sizeof(struct node));
        pn->next = p_l_list->next;
        fgets(pn->question, 300, fp);
        fgets(pn->decision_1, 200, fp);
        fscanf(fp, "%d%d%d", &(pn->impact_1.people), &(pn->impact_1.court), &(pn->impact_1.treasury));
        fseek(fp, 2, SEEK_CUR);
        fgets(pn->decision_2, 200, fp);
        fscanf(fp, "%d%d%d", &(pn->impact_2.people), &(pn->impact_2.court), &(pn->impact_2.treasury));
        pn->possibility = 3;
        p_l_list->next = pn;
    }
    else if(index == 0)
    {
        pn = (struct node *)malloc(sizeof(struct node));
        pn->next = *l_list;
        fgets(pn->question, 300, fp);
        fgets(pn->decision_1, 200, fp);
        fscanf(fp, "%d%d%d", &(pn->impact_1.people), &(pn->impact_1.court), &(pn->impact_1.treasury));
        fseek(fp, 2, SEEK_CUR);
        fgets(pn->decision_2, 200, fp);
        fscanf(fp, "%d%d%d", &(pn->impact_2.people), &(pn->impact_2.court), &(pn->impact_2.treasury));
        pn->possibility = 3;
        *l_list = pn;
    }
}

void delete_end(struct node **l_list)
{
    struct node *p_l_list = *l_list;
    if(p_l_list->next != NULL)
    {
        while(p_l_list->next->next != NULL)
            p_l_list = p_l_list->next;
        free(p_l_list->next);
        p_l_list->next = NULL;
    }
    else
    {
        free(*l_list);
        *l_list = NULL;
    }
}

void delete_front(struct node **l_list)
{
    struct node *p_l_list = *l_list;
    *l_list = (*l_list)->next;
    free(p_l_list);
}

void delete_next(struct node **l_list, int index)
{
    if(index >= 1)
    {
        struct node *p_l_list = *l_list, *p;
        int i;
        for(i = 1; i <= index; i++)
        {
            p = p_l_list;
            p_l_list = p_l_list->next;
        }
        p->next = p_l_list->next;
        free(p_l_list);
    }
    else if(index == 0)
    {
        struct node *p_l_list = *l_list;
        *l_list = (*l_list)->next;
        free(p_l_list);
    }
}
