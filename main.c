#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include "LINKED_LIST_FUNCTIONS.h"

struct save_format
{
    char username[100];
    bool is_middle;
    int question[100];
    char ans_question[300][300];
    char choice[300][200];
    struct the_three parameter;
    int age;
};

int question_cnt;
int questions_left;
int questions_answered;
int node_left;
bool is_campaign;
struct save_format save;
struct save_format save_arr[100];
struct node *list = NULL;
void (*f)();

void delay(int mili_sec);
void main_menu();
void campaign_menu();
void endless_menu();
void input_keys_page();
void tutorial_page();
void load_menu();
void new_menu();
bool are_you_sure();
void loading_and_play();
struct node * get_question();
void print_screen(struct node * quest, FILE *face, int pointer);
int give_index(struct node *quest);
struct node * give_question(int index);
void refresh_list();
void yes_animation(struct node *quest);
void no_animation(struct node *quest);
void lost_load(char username[100]);
void put_cam_top();
void put_end_top();
int save_cmp_cms(void *s1, void *s2);
int save_cmp_ens(void *s1, void *s2);

int main()
{
    time_t t = time(NULL);
    srand(t);
    refresh_list();
    f = main_menu;
    while(1)
        f();
    return 0;
}

void delay(int mili_sec)
{
    clock_t t = clock();
    while(clock() < t + mili_sec);
    return;
}

void main_menu()
{
    system("cls");
    int pointer = 0, i;
    char input;
    char original_option[5][20] = {" Campaign", " Endless mode", " Input keys", " Tutorial", " Quit"};
    char option[5][20] = {" Campaign", " Endless mode", " Input keys", " Tutorial", " Quit"};
    while(1)
    {
        printf("\n");
        strcat(option[pointer], "  <<");
        for(i = 0; i < 5; i++)
            puts(option[i]);
        printf("\n\n Tip = 'W' and 'S' to move the cursor, 'O' to choose option.");
        strcpy(option[pointer], original_option[pointer]);
        fflush(stdin);
        input = getch();
        if(input == 's' || input == 'S')
        {
            if(pointer == 4)
                pointer = 0;
            else
                pointer++;
        }
        else if(input == 'w' || input == 'W')
        {
            if(pointer == 0)
                pointer = 4;
            else
                pointer--;
        }
        else if(input == 'o' || input == 'O')
        {
            if(pointer == 0)
                f = campaign_menu;
            else if(pointer == 1)
                f = endless_menu;
            else if(pointer == 2)
                f = input_keys_page;
            else if(pointer == 3)
                f = tutorial_page;
            else if(pointer == 4)
            {
                system("cls");
                exit(0);
            }
            system("cls");
            return;
        }
        system("cls");
    }
}

void campaign_menu()
{
    system("cls");
    int pointer = 0, i, j;
    char input;
    char original_option[3][50] = {" New game", " Load game", " Top 10 Players"};
    char option[3][50] = {" New game", " Load game", " Top 10 Players"};
    is_campaign = true;
    while(1)
    {
        printf("\n");
        strcat(option[pointer], "  <<");
        for(i = 0; i < 3; i++)
            puts(option[i]);
        printf("\n\n Tip = 'W' and 'S' to move the cursor, 'O' to choose option, 'P' to go back.");
        strcpy(option[pointer], original_option[pointer]);
        input = getch();
        if(input == 's' || input == 'S')
        {
            if(pointer == 2)
                pointer = 0;
            else
                pointer++;
        }
        else if(input == 'w' || input == 'W')
        {
            if(pointer == 0)
                pointer = 2;
            else
                pointer--;
        }
        else if(input == 'o' || input == 'O')
        {
            if(pointer == 0)
                f = new_menu;
            else if(pointer == 1)
                f = load_menu;
            else
            {
                system("cls");
                FILE *top = fopen("top_cms.bin", "r");
                int lines;
                for(lines = 0; fread(&save_arr[lines], sizeof(save), 1, top) == 1; lines++);
                qsort(save_arr, lines, sizeof(save), save_cmp_cms);
                for(j = 0; j < (int)round(fmin(lines, 10)); j++)
                {
                    save_arr[j].username[strlen(save_arr[j].username) - 4] = '\0';
                    printf("\n %d. %-20sPeople:%2d Court:%2d Treasury:%2d", (j + 1), save_arr[j].username, save_arr[j].parameter.people, save_arr[j].parameter.court, save_arr[j].parameter.treasury);
                }
                fclose(top);
                getch();
            }
            system("cls");
            return;
        }
        else if(input == 'p' || input == 'P')
        {
            f = main_menu;
            system("cls");
            return;
        }
        system("cls");
    }
}

void endless_menu()
{
    system("cls");
    int pointer = 0, i, j;
    char input;
    char original_option[3][50] = {" New game", " Load game", " Top 10 Players"};
    char option[3][50] = {" New game", " Load game", " Top 10 Players"};
    is_campaign = false;
    while(1)
    {
        printf("\n");
        strcat(option[pointer], "  <<");
        for(i = 0; i < 3; i++)
            puts(option[i]);
        printf("\n\n Tip = 'W' and 'S' to move the cursor, 'O' to choose option, 'P' to go back.");
        strcpy(option[pointer], original_option[pointer]);
        input = getch();
        if(input == 's' || input == 'S')
        {
            if(pointer == 2)
                pointer = 0;
            else
                pointer++;
        }
        else if(input == 'w' || input == 'W')
        {
            if(pointer == 0)
                pointer = 2;
            else
                pointer--;
        }
        else if(input == 'o' || input == 'O')
        {
            if(pointer == 0)
                f = new_menu;
            else if(pointer == 1)
                f = load_menu;
            else
            {
                system("cls");
                FILE *top = fopen("top_ens.bin", "r");
                int lines;
                for(lines = 0; fread(&save_arr[lines], sizeof(save), 1, top) == 1; lines++);
                qsort(save_arr, lines, sizeof(save), save_cmp_ens);
                for(j = 0; j < (int)round(fmin(lines, 10)); j++)
                {
                    save_arr[j].username[strlen(save_arr[j].username) - 4] = '\0';
                    printf("\n %d. %-20sAge:%3d", (j + 1), save_arr[j].username, save_arr[j].age);
                }
                fclose(top);
                getch();
            }
            system("cls");
            return;
        }
        else if(input == 'p' || input == 'P')
        {
            f = main_menu;
            system("cls");
            return;
        }
        system("cls");
    }
}

void input_keys_page()
{
    system("cls");
    char input = 0;
    printf("\n W\tMove cursor up\n S\tMove cursor down\n A\tMove cursor left\n D\tMove cursor right\n O\tConfirm\n P\tBack/Pause\n\n");
    while(input != 'o' && input != 'O' && input != 'p' && input != 'P')
        input = getch();
    f = main_menu;
    system("cls");
    return;
}

void tutorial_page()
{
    system("cls");
    int i = 0;
    char input = 0;
    char text[1000] = "You are the king of an imaginary land, As a king you must make the right choices to keep your throne. There are three parameters; People, Court and Treasury. In order to stay in power, you must manage these three by making the right chices. Watch out! Avoid making one of the parameters reach zero and avoid making the average of the three parameters reach lower than 10! There are 2 modes for this game; Campaign and Endless. In Campaign mode, you answer to all the questions in the game three times, if you survive! if you managed to do that, it's a win for you! In Endless mode, you have to survive for as long as you can! In both modes, your score will be saved. In campaign, it's based on the sum of the three parameters, and in endless, it's based on your age, which represents the number of questions you managed to answer.";
    printf("\n ");
    while(text[i] != '\0')
    {
        if(i % 50 == 0 && i != 0)
        {
            while(text[i - 1] != '.' && text[i - 1] != '!' && text[i - 1] != ';' && text[i - 1] != ',')
            {
                putchar(text[i]);
                i++;
                delay(20);
            }
            printf("\n");
        }
        else
        {
            putchar(text[i]);
            i++;
            delay(18);
        }
    }
    delay(1000);
    printf("\n Good Luck!\n\n Press 'P' or 'O' to go to main menu.");
    fflush(stdin);
    while(input != 'o' && input != 'O' && input != 'p' && input != 'P')
        input = getch();
    f = main_menu;
    system("cls");
    return;
}

void load_menu()
{
    system("cls");
    char username[100];
    int pointer = 0, i, j;
    char input;
    char original_option[2][50] = {" Retry", " Back to main menu"};
    char option[2][50] = {" Retry", " Back to main menu"};
    printf("\n Enter your username:\n ");
    gets(username);
    if(is_campaign)
        strcat(username, ".cms");
    else
        strcat(username, ".ens");
    FILE *save_file = fopen(username, "rb");
    while(save_file == NULL)
    {
        system("cls");
        printf("\n There is no save file for this username!\n\n");
        strcat(option[pointer], "  <<");
        for(i = 0; i < 2; i++)
            puts(option[i]);
        strcpy(option[pointer], original_option[pointer]);
        input = getch();
        if(input == 's' || input == 'S')
        {
            if(pointer == 1)
                pointer = 0;
            else
                pointer++;
        }
        else if(input == 'w' || input == 'W')
        {
            if(pointer == 0)
                pointer = 1;
            else
                pointer--;
        }
        else if(input == 'o' || input == 'O')
        {
            if(pointer == 0)
            {
                system("cls");
                printf("\n Enter your username:\n ");
                gets(username);
                if(is_campaign)
                    strcat(username, ".cms");
                else
                    strcat(username, ".ens");
                fclose(save_file);
                save_file = fopen(username, "rb");
            }
            else if(pointer == 1)
            {
                f = main_menu;
                system("cls");
                return;
            }
            system("cls");
        }
        else if(input == 'p' || input == 'P')
        {
            system("cls");
            printf("\n Enter your username:\n ");
            gets(username);
            if(is_campaign)
                strcat(username, ".cms");
            else
                strcat(username, ".ens");
            fclose(save_file);
            save_file = fopen(username, "rb");
        }
    }
    fread(&save, sizeof(save), 1, save_file);
    fclose(save_file);
    if(save.is_middle)
    {
        questions_answered = (save.age - 20) / 2;
        questions_left = 0;
        for(i = 0; i < 100; i++)
        {
            if(save.question[i] == -1)
                break;
            else
                questions_left += save.question[i];
        }
        for(j = 0; j < question_cnt - i; j++)
        {
            save.question[i + j] = 3;
            questions_left += 3;
        }
        f = loading_and_play;
    }
    else
        lost_load(username);
    system("cls");
    return;
}

void new_menu()
{
    system("cls");
    char username[100];
    int pointer = 0, i;
    char input;
    char original_option[3][50] = {" Choose another username", " Overwrite save", " Back to main menu"};
    char option[3][50] = {" Choose another username", " Overwrite save", " Back to main menu"};
    printf("\n Please choose your username:\n ");
    gets(username);
    if(is_campaign)
        strcat(username, ".cms");
    else
        strcat(username, ".ens");
    while(fopen(username, "r") != NULL)
    {
        system("cls");
        printf("\n Sorry! This username is already taken!\n\n");
        strcat(option[pointer], "  <<");
        for(i = 0; i < 3; i++)
            puts(option[i]);
        strcpy(option[pointer], original_option[pointer]);
        input = getch();
        if(input == 's' || input == 'S')
        {
            if(pointer == 2)
                pointer = 0;
            else
                pointer++;
        }
        else if(input == 'w' || input == 'W')
        {
            if(pointer == 0)
                pointer = 2;
            else
                pointer--;
        }
        else if(input == 'o' || input == 'O')
        {
            if(pointer == 0)
            {
                system("cls");
                printf("\n Please choose your username:\n ");
                gets(username);
                if(is_campaign)
                    strcat(username, ".cms");
                else
                    strcat(username, ".ens");
            }
            else if(pointer == 1)
            {
                if(are_you_sure() == true)
                    break;
            }
            else if(pointer == 2)
            {
                f = main_menu;
                system("cls");
                return;
            }
            system("cls");
        }
        else if(input == 'p' || input == 'P')
        {
            system("cls");
            printf("\n Please choose your username:\n ");
            gets(username);
            if(is_campaign)
                strcat(username, ".cms");
            else
                strcat(username, ".ens");
        }
    }
    FILE *save_file = fopen(username, "wb");
    save.age = 20;
    for(i = 0; i < 100; i++)
    {
        if(i < question_cnt)
            save.question[i] = 3;
        else
            save.question[i] = -1;
    }
    save.is_middle = true;
    save.parameter.people = save.parameter.court = save.parameter.treasury = 50;
    strcpy(save.username, username);
    fwrite(&save, sizeof(save), 1, save_file);
    questions_left = 3 * question_cnt;
    questions_answered = 0;
    fclose(save_file);
    f = loading_and_play;
    system("cls");
    return;
}

bool are_you_sure()
{
    system("cls");
    int pointer = 0, i;
    char input;
    char original_option[2][50] = {" Yes", " No"};
    char option[2][50] = {" Yes", " No"};
    while(1)
    {
        system("cls");
        strcat(option[pointer], "  <<");
        printf("\n Are you sure?\n\n");
        for(i = 0; i < 2; i++)
            puts(option[i]);
        strcpy(option[pointer], original_option[pointer]);
        input = getch();
        if(input == 's' || input == 'S')
        {
            if(pointer == 1)
                pointer = 0;
            else
                pointer++;
        }
        else if(input == 'w' || input == 'W')
        {
            if(pointer == 0)
                pointer = 1;
            else
                pointer--;
        }
        else if(input == 'o' || input == 'O')
        {
            if(pointer == 0)
                return true;
            else if(pointer == 1)
                return false;
            system("cls");
            break;
        }
        else if(input == 'p' || input == 'P')
        {
            system("cls");
            return false;
        }
    }
    return false;
}

void loading_and_play()
{
    char input;
    bool change_question = true;
    int random_mili_sec, i,  pointer = 0;
    time_t t = time(NULL);
    struct node *quest;
    FILE *face;
    srand(t);
    random_mili_sec = 1000 + (rand() % 1001);
    system("cls");
    printf("\n Loading");
    for(i = 0; i < 4; i++)
    {
        delay(random_mili_sec / 4);
        if(i != 3)
            printf(".");
    }
    while(save.is_middle)
    {
        system("cls");
        if(change_question)
        {
            quest = get_question(save);
            change_question = false;
        }
        if(save.age < 40)
        {
            if(pointer == 0)
                face = fopen("faces\\0\\0\\0\\2.txt", "r");
            else
                face = fopen("faces\\0\\0\\4\\2.txt", "r");
            if(face == NULL)
            {
                system("cls");
                printf("\n A text file from faces is missing!");
                exit(-1);
            }
        }
        else if(save.age >= 60)
        {
            if(pointer == 0)
                face = fopen("faces\\1\\0\\0\\2.txt", "r");
            else
                face = fopen("faces\\1\\0\\4\\2.txt", "r");
            if(face == NULL)
            {
                system("cls");
                printf("\n A text file from faces is missing!");
                exit(-1);
            }
        }
        else
        {
            if(pointer == 0)
                face = fopen("faces\\2\\0\\0\\2.txt", "r");
            else
                face = fopen("faces\\2\\0\\4\\2.txt", "r");
            if(face == NULL)
            {
                system("cls");
                printf("\n A text file from faces is missing!");
                exit(-1);
            }
        }
        print_screen(quest, face, pointer);
        fclose(face);
        fflush(stdin);
        input = getch();
        if(input == 'd' || input == 'D')
        {
            if(pointer == 1)
                pointer = 0;
            else
                pointer++;
        }
        else if(input == 'a' || input == 'A')
        {
            if(pointer == 0)
                pointer = 1;
            else
                pointer = 0;
        }
        else if(input == 'o' || input == 'O')
        {
            if(pointer == 0)
            {
                yes_animation(quest);
                strcpy(save.choice[questions_answered], quest->decision_1);
            }
            else
            {
                no_animation(quest);
                strcpy(save.choice[questions_answered], quest->decision_2);
            }
            questions_left--;
            quest->possibility--;
            strcpy(save.ans_question[questions_answered], quest->question);
            save.question[quest->index]--;
            if(save.question[quest->index] == 0)
            {
                delete_next(&list, give_index(quest));
                node_left--;
            }
            if(node_left == 0)
            {
                list = NULL;
                refresh_list();
                for(i = 0; i < question_cnt; i++)
                    save.question[i] = 3;
                questions_left = 3 * question_cnt;
            }
            change_question = true;
            questions_answered++;
            if(save.parameter.people == 0 || save.parameter.court == 0 || save.parameter.treasury == 0 || (save.parameter.people + save.parameter.court + save.parameter.treasury) / 3 < 10)
                save.is_middle = false;
        }
        else if(input == 'p' || input == 'P')
        {
            int tmp = pointer;
            pointer = 0;
            char original_option[4][50] = {" Resume", " See previous decisions", " Save", " Main menu"};
            char option[4][50] = {" Resume", " See previous decisions", " Save", " Main menu"};
            while(1)
            {
                system("cls");
                printf("\n Paused\n");
                printf("\n");
                strcat(option[pointer], "  <<");
                for(i = 0; i < 4; i++)
                    puts(option[i]);
                printf("\n\n Tip = Remember to \"save\" before going to the \"Main menu\"");
                strcpy(option[pointer], original_option[pointer]);
                input = getch();
                if(input == 's' || input == 'S')
                {
                    if(pointer == 3)
                        pointer = 0;
                    else
                        pointer++;
                }
                else if(input == 'w' || input == 'W')
                {
                    if(pointer == 0)
                        pointer = 3;
                    else
                        pointer--;
                }
                else if(input == 'o' || input == 'O')
                {
                    if(pointer == 0)
                        break;
                    else if(pointer == 1)
                    {
                        system("cls");
                        for(i = 0; i < questions_answered; i++)
                        {
                            printf("\n Question %d:\n ", i + 1);
                            puts(save.ans_question[i]);
                            printf("\n Decision:\n ");
                            puts(save.choice[i]);
                            printf("\n_______________________________________________________\n");
                        }
                        getch();
                    }
                    else if(pointer == 2)
                    {
                        system("cls");
                        FILE *fp = fopen(save.username, "wb");
                        fwrite(&save, sizeof(save), 1, fp);
                        fclose(fp);
                        printf("\n Game Saved!");
                        getch();
                    }
                    else if(pointer == 3)
                    {
                        if(are_you_sure() == true)
                        {
                            f = main_menu;
                            return;
                        }
                    }
                    system("cls");
                }
                else if(input == 'p' || input == 'P')
                {
                    break;
                }
                system("cls");
            }
            pointer = tmp;
        }
        if(is_campaign && questions_answered == 3 * question_cnt)
        {
            system("cls");
            if(save.age < 40)
            {
                face = fopen("faces\\w0.txt", "r");
                if(face == NULL)
                {
                    system("cls");
                    printf("\n A text file from faces is missing!");
                    exit(-1);
                }
            }
            else if(save.age >= 60)
            {
                face = fopen("faces\\w1.txt", "r");
                if(face == NULL)
                {
                    system("cls");
                    printf("\n A text file from faces is missing!");
                    exit(-1);
                }
            }
            else
            {
                face = fopen("faces\\w2.txt", "r");
                if(face == NULL)
                {
                    system("cls");
                    printf("\n A text file from faces is missing!");
                    exit(-1);
                }
            }
            put_cam_top();
            struct node *win_menu;
            win_menu = (struct node *)malloc(sizeof(struct node));
            strcpy(win_menu->decision_1, " ");
            strcpy(win_menu->decision_2, " ");
            strcpy(win_menu->question, "Congratulations! You beat the game! Your name shall not be forgotten. Your score is now saved. You may be able to see yourself in the top ten rankings, if you played well enough! \n Long Live the king!");
            questions_left = 0;
            print_screen(win_menu, face, -1);
            questions_left = 3 * question_cnt;
            delay(3000);
            fflush(stdin);
            getch();
            f = main_menu;
            fclose(face);
            return;
        }
    }
    if(save.age < 40)
    {
        face = fopen("faces\\d01.txt", "r");
        if(face == NULL)
        {
            system("cls");
            printf("\n A text file from faces is missing!");
            exit(-1);
        }
    }
    else if(save.age >= 60)
    {
        face = fopen("faces\\d11.txt", "r");
        if(face == NULL)
        {
            system("cls");
            printf("\n A text file from faces is missing!");
            exit(-1);
        }
    }
    else
    {
        face = fopen("faces\\d21.txt", "r");
        if(face == NULL)
        {
            system("cls");
            printf("\n A text file from faces is missing!");
            exit(-1);
        }
    }
    print_screen(quest, face, -1);
    struct node *dead_menu;
    fclose(face);
    delay(3000);
    system("cls");
    if(!is_campaign)
        put_end_top();
    dead_menu = (struct node *)malloc(sizeof(struct node));
    strcpy(dead_menu->decision_1, "            Save & Main menu");
    strcpy(dead_menu->decision_2, "            Main menu");
    strcpy(dead_menu->question, "\n                                        You have fallen...");
    pointer = 0;
    while(1)
    {
        system("cls");
        if(save.age < 40)
        {
            if(pointer == 0)
                face = fopen("faces\\d00.txt", "r");
            else
                face = fopen("faces\\d02.txt", "r");
            if(face == NULL)
            {
                system("cls");
                printf("\n A text file from faces is missing!");
                exit(-1);
            }
        }
        else if(save.age >= 60)
        {
            if(pointer == 0)
                face = fopen("faces\\d10.txt", "r");
            else
                face = fopen("faces\\d12.txt", "r");
            if(face == NULL)
            {
                system("cls");
                printf("\n A text file from faces is missing!");
                exit(-1);
            }
        }
        else
        {
            if(pointer == 0)
                face = fopen("faces\\d20.txt", "r");
            else
                face = fopen("faces\\d22.txt", "r");
            if(face == NULL)
            {
                system("cls");
                printf("\n A text file from faces is missing!");
                exit(-1);
            }
        }
        print_screen(dead_menu, face, pointer);
        fclose(face);
        input = getch();
        if(input == 'd' || input == 'D')
        {
            if(pointer == 1)
                pointer = 0;
            else
                pointer++;
        }
        else if(input == 'a' || input == 'A')
        {
            if(pointer == 0)
                pointer = 1;
            else
                pointer = 0;
        }
        else if(input == 'o' || input == 'O')
        {
            if(pointer == 0)
            {
                FILE *fp = fopen(save.username, "wb");
                fwrite(&save, sizeof(save), 1, fp);
                fclose(fp);
                f = main_menu;
                system("cls");
                return;
            }
            else
            {
                f = main_menu;
                system("cls");
                return;
            }
        }
    }
    f = main_menu;
    system("cls");
    return;
}

struct node * get_question()
{
    int random;
    struct node *quest = list;
    random = (rand() % questions_left) + 1;
    while(quest->next != NULL)
    {
        random -= save.question[quest->index];
        if(random > 0)
            quest = quest->next;
        else
            break;
    }
    return quest;
};

void print_screen(struct node *quest, FILE *face, int pointer)
{
    int i, j, k, l;
    bool flag = false, flag1 = false, flag2 =false;
    char str[27];
    fseek(face, 0, SEEK_SET);
    printf("\n ");
    i = 0;
    while(i < 300)
    {
        if(quest->question[i] == '\0')
            flag = true;
        if(!flag)
        {
            if(i % 100 == 0 && i != 0)
            {
                while(quest->question[i] != ' ')
                {
                    putchar(quest->question[i]);
                    i++;
                }
                printf("\n ");
            }
            else
            {
                putchar(quest->question[i]);
                i++;
            }
        }
        else
        {
            if(i % 100 == 0 && i != 0)
            {
                printf("\n");
                putchar(' ');
                i++;
            }
            else
            {
                putchar(' ');
                i++;
            }
        }
    }
    for(l = 0; l < 7; l++)
    {
        printf("\n ");
        for(k = 0; k < 37; k++)
            putchar(' ');
        fgets(str, 27, face);
        str[25] = '\0';
        printf("%s", str);
    }
    i = 0;
    j = 0;
    for(l = 0; l < 6; l++)
    {
        printf("\n ");
        while(i < (l + 1) * 30)
        {
            if(quest->decision_1[i] == '\0')
                flag1 = true;
            if(!flag1)
            {
                putchar(quest->decision_1[i]);
                i++;
            }
            else
            {
                putchar(' ');
                i++;
            }
        }
        if(l == 0 && pointer == 0)
            printf(" <<    ");
        else
            printf("       ");
        fgets(str, 27, face);
        str[25] = '\0';
        printf("%s", str);
        if(l == 0 && pointer == 1)
            printf("    >> ");
        else
            printf("       ");
        while(j < (l + 1) * 30)
        {
            if(quest->decision_2[j] == '\0')
                flag2 = true;
            if(!flag2)
            {
                putchar(quest->decision_2[j]);
                j++;
            }
            else
            {
                putchar(' ');
                j++;
            }
        }
    }
    printf("\n ");
    while(i < 200)
    {
        if(quest->decision_1[i] == '\0')
            flag1 = true;
        if(!flag1)
        {
            putchar(quest->decision_1[i]);
            i++;
        }
        else
        {
            putchar(' ');
            i++;
        }
    }
    printf("                 ");
    fgets(str, 27, face);
    str[25] = '\0';
    printf("%s", str);
    printf("       ");
    while(j < 200)
    {
        if(quest->decision_2[j] == '\0')
            flag2 = true;
        if(!flag2)
        {
            putchar(quest->decision_2[j]);
            j++;
        }
        else
        {
            putchar(' ');
            j++;
        }
    }
    printf("\n\n\n           People:%2d Court:%2d Treasury:%2d", save.parameter.people, save.parameter.court, save.parameter.treasury);
    printf("                   Age:%3d   ", save.age);
    if(is_campaign)
        printf("Questions left:%3d", questions_left);
    else
        printf("Questions Answered:%3d", questions_answered);
    printf("\n\n                                             ");
    if(is_campaign)
        printf("Mode:Campaign");
    else
        printf("Mode:Endless");
}

int give_index(struct node *quest)
{
    struct node *current = list;
    int index = 0;
    while(current != quest)
    {
        current = current->next;
        index++;
    }
    return index;
}

struct node * give_question(int index)
{
    struct node *current = list;
    while(current != NULL && current->index != index)
        current = current->next;
    return current;
};

void refresh_list()
{
    char file_name[100][50];
    int i = 0, j;
    struct node *current;
    FILE *fp = fopen("CHOICES.txt", "r"), *fp_list;
    if(fp == NULL)
    {
        printf("The file CHOICES.txt is missing!");
        exit(-1);
    }
    while(fgets(file_name[i], 50, fp) != NULL)
    {
        for(j = 0; j < 50; j++)
        {
            if(file_name[i][j] == '\n')
            {
                file_name[i][j] = '\0';
                break;
            }
        }
        fp_list = fopen(file_name[i], "r");
        if(fp_list == NULL)
        {
            printf("The file %s is missing!", file_name[i]);
            exit(-1);
        }
        add_end(&list, fp_list);
        if(i == 0)
            current = list;
        else
            current = current->next;
        current->index = i;
        i++;
    }
    node_left = question_cnt = i;
    fclose(fp);
    fclose(fp_list);
}

void yes_animation(struct node *quest)
{
    int i;
    char files[5][100];
    FILE *fp;
    system("cls");
    if(save.age < 40)
    {
        strcpy(files[0], "faces\\0\\0\\5\\2.txt");
        strcpy(files[1], "faces\\0\\0\\5\\s2.txt");
        strcpy(files[2], "faces\\0\\1\\5\\2.txt");
        strcpy(files[3], "faces\\0\\0\\1\\2.txt");
        strcpy(files[4], "faces\\0\\0\\3\\2.txt");
    }
    else if(save.age >= 60)
    {
        strcpy(files[0], "faces\\1\\0\\5\\2.txt");
        strcpy(files[1], "faces\\1\\0\\5\\s2.txt");
        strcpy(files[2], "faces\\1\\1\\5\\2.txt");
        strcpy(files[3], "faces\\1\\0\\1\\2.txt");
        strcpy(files[4], "faces\\1\\0\\3\\2.txt");
    }
    else
    {
        strcpy(files[0], "faces\\2\\0\\5\\2.txt");
        strcpy(files[1], "faces\\2\\0\\5\\s2.txt");
        strcpy(files[2], "faces\\2\\1\\5\\2.txt");
        strcpy(files[3], "faces\\2\\0\\1\\2.txt");
        strcpy(files[4], "faces\\2\\0\\3\\2.txt");
    }
    fp = fopen(files[0], "r");
    if(fp == NULL)
    {
        system("cls");
        printf("\n A text file from faces is missing!");
        exit(-1);
    }
    print_screen(quest, fp, -1);
    delay(400);
    system("cls");
    fclose(fp);
    fp = fopen(files[2], "r");
    if(fp == NULL)
    {
        system("cls");
        printf("\n A text file from faces is missing!");
        exit(-1);
    }
    print_screen(quest, fp, -1);
    delay(400);
    system("cls");
    fclose(fp);
    fp = fopen(files[0], "r");
    print_screen(quest, fp, -1);
    delay(400);
    system("cls");
    fclose(fp);
    for(i = 0; i < 3; i++)
    {
        fp = fopen(files[1], "r");
        if(fp == NULL)
        {
            system("cls");
            printf("\n A text file from faces is missing!");
            exit(-1);
        }
        print_screen(quest, fp, -1);
        delay(150);
        system("cls");
        fclose(fp);
        fp = fopen(files[0], "r");
        print_screen(quest, fp, -1);
        delay(150);
        system("cls");
        fclose(fp);
    }
    fp = fopen(files[3], "r");
    if(fp == NULL)
    {
        system("cls");
        printf("\n A text file from faces is missing!");
        exit(-1);
    }
    save.parameter.people += quest->impact_1.people;
    save.parameter.court += quest->impact_1.court;
    save.parameter.treasury += quest->impact_1.treasury;
    if(save.parameter.people < 0)
        save.parameter.people = 0;
    if(save.parameter.court < 0)
        save.parameter.court = 0;
    if(save.parameter.treasury < 0)
        save.parameter.treasury = 0;
    if(save.parameter.people > 100)
        save.parameter.people = 100;
    if(save.parameter.court > 100)
        save.parameter.court = 100;
    if(save.parameter.treasury > 100)
        save.parameter.treasury = 100;
    print_screen(quest, fp, -1);
    delay(500);
    system("cls");
    fclose(fp);
    fp = fopen(files[4], "r");
    if(fp == NULL)
    {
        system("cls");
        printf("\n A text file from faces is missing!");
        exit(-1);
    }
    save.age += 2;
    print_screen(quest, fp, -1);
    delay(500);
    system("cls");
    fclose(fp);
    return;
}

void no_animation(struct node *quest)
{
    int i;
    char files[9][100];
    FILE *fp;
    system("cls");
    if(save.age < 40)
    {
        strcpy(files[0], "faces\\0\\1\\5\\0.txt");
        strcpy(files[1], "faces\\0\\1\\5\\1.txt");
        strcpy(files[2], "faces\\0\\1\\5\\2.txt");
        strcpy(files[3], "faces\\0\\1\\5\\3.txt");
        strcpy(files[4], "faces\\0\\1\\5\\4.txt");
        strcpy(files[5], "faces\\0\\0\\5\\2.txt");
        strcpy(files[6], "faces\\0\\0\\5\\s2.txt");
        strcpy(files[7], "faces\\0\\0\\1\\2.txt");
        strcpy(files[8], "faces\\0\\0\\3\\2.txt");
    }
    else if(save.age >= 60)
    {
        strcpy(files[0], "faces\\1\\1\\5\\0.txt");
        strcpy(files[1], "faces\\1\\1\\5\\1.txt");
        strcpy(files[2], "faces\\1\\1\\5\\2.txt");
        strcpy(files[3], "faces\\1\\1\\5\\3.txt");
        strcpy(files[4], "faces\\1\\1\\5\\4.txt");
        strcpy(files[5], "faces\\1\\0\\5\\2.txt");
        strcpy(files[6], "faces\\1\\0\\5\\s2.txt");
        strcpy(files[7], "faces\\1\\0\\1\\2.txt");
        strcpy(files[8], "faces\\1\\0\\3\\2.txt");
    }
    else
    {
        strcpy(files[0], "faces\\2\\1\\5\\0.txt");
        strcpy(files[1], "faces\\2\\1\\5\\1.txt");
        strcpy(files[2], "faces\\2\\1\\5\\2.txt");
        strcpy(files[3], "faces\\2\\1\\5\\3.txt");
        strcpy(files[4], "faces\\2\\1\\5\\4.txt");
        strcpy(files[5], "faces\\2\\0\\5\\2.txt");
        strcpy(files[6], "faces\\2\\0\\5\\s2.txt");
        strcpy(files[7], "faces\\2\\0\\1\\2.txt");
        strcpy(files[8], "faces\\2\\0\\3\\2.txt");
    }
    for(i = 2; i >= 0; i--)
    {
        fp = fopen(files[i], "r");
        if(fp == NULL)
        {
            system("cls");
            printf("\n A text file from faces is missing!");
            exit(-1);
        }
        print_screen(quest, fp, -1);
        delay(50);
        system("cls");
        fclose(fp);
    }
    for(i = 1; i <= 4; i++)
    {
        fp = fopen(files[i], "r");
        if(fp == NULL)
        {
            system("cls");
            printf("\n A text file from faces is missing!");
            exit(-1);
        }
        print_screen(quest, fp, -1);
        delay(50);
        system("cls");
        fclose(fp);
    }
    for(i = 3; i >= 2; i--)
    {
        fp = fopen(files[i], "r");
        if(fp == NULL)
        {
            system("cls");
            printf("\n A text file from faces is missing!");
            exit(-1);
        }
        print_screen(quest, fp, -1);
        delay(50);
        system("cls");
        fclose(fp);
    }
    fp = fopen(files[5], "r");
    if(fp == NULL)
    {
        system("cls");
        printf("\n A text file from faces is missing!");
        exit(-1);
    }
    print_screen(quest, fp, -1);
    delay(400);
    system("cls");
    fclose(fp);
    for(i = 0; i < 3; i++)
    {
        fp = fopen(files[6], "r");
        if(fp == NULL)
        {
            system("cls");
            printf("\n A text file from faces is missing!");
            exit(-1);
        }
        print_screen(quest, fp, -1);
        delay(150);
        system("cls");
        fclose(fp);
        fp = fopen(files[5], "r");
        print_screen(quest, fp, -1);
        delay(150);
        system("cls");
        fclose(fp);
    }
    fp = fopen(files[7], "r");
    if(fp == NULL)
    {
        system("cls");
        printf("\n A text file from faces is missing!");
        exit(-1);
    }
    save.parameter.people += quest->impact_2.people;
    save.parameter.court += quest->impact_2.court;
    save.parameter.treasury += quest->impact_2.treasury;
    if(save.parameter.people < 0)
        save.parameter.people = 0;
    if(save.parameter.court < 0)
        save.parameter.court = 0;
    if(save.parameter.treasury < 0)
        save.parameter.treasury = 0;
    if(save.parameter.people > 100)
        save.parameter.people = 100;
    if(save.parameter.court > 100)
        save.parameter.court = 100;
    if(save.parameter.treasury > 100)
        save.parameter.treasury = 100;
    print_screen(quest, fp, -1);
    delay(500);
    system("cls");
    fclose(fp);
    fp = fopen(files[8], "r");
    if(fp == NULL)
    {
        system("cls");
        printf("\n A text file from faces is missing!");
        exit(-1);
    }
    save.age += 2;
    print_screen(quest, fp, -1);
    delay(500);
    system("cls");
    fclose(fp);
    return;
}

void lost_load(char username[100])
{
    system("cls");
    int pointer = 0, i;
    char input;
    char original_option[2][50] = {" Start a new game", " See previous decisions"};
    char option[2][50] = {" Start a new game", " See previous decisions"};
    is_campaign = false;
    while(1)
    {
        printf("\n You have lost in your last game.\n\n");
        strcat(option[pointer], "  <<");
        for(i = 0; i < 2; i++)
            puts(option[i]);
        strcpy(option[pointer], original_option[pointer]);
        input = getch();
        if(input == 's' || input == 'S')
        {
            if(pointer == 1)
                pointer = 0;
            else
                pointer++;
        }
        else if(input == 'w' || input == 'W')
        {
            if(pointer == 0)
                pointer = 1;
            else
                pointer--;
        }
        else if(input == 'o' || input == 'O')
        {
            if(pointer == 0)
            {
                FILE *save_file = fopen(username, "wb");
                save.age = 20;
                for(i = 0; i < 100; i++)
                {
                    if(i < question_cnt)
                        save.question[i] = 3;
                    else
                        save.question[i] = -1;
                }
                save.is_middle = true;
                save.parameter.people = save.parameter.court = save.parameter.treasury = 50;
                strcpy(save.username, username);
                fwrite(&save, sizeof(save), 1, save_file);
                questions_left = 3 * question_cnt;
                questions_answered = 0;
                fclose(save_file);
                f = loading_and_play;
                system("cls");
                return;
            }
            else if(pointer == 1)
            {
                system("cls");
                for(i = 0; i < questions_answered; i++)
                {
                    printf("\n Question %d:\n ", i + 1);
                    puts(save.ans_question[i]);
                    printf("\n Decision:\n ");
                    puts(save.choice[i]);
                    printf("\n_______________________________________________________\n");
                }
                getch();
            }
            system("cls");
            return;
        }
        else if(input == 'p' || input == 'P')
        {
            f = load_menu;
            system("cls");
            return;
        }
        system("cls");
    }
}

void put_cam_top()
{
    FILE *top = fopen("top_cms.bin", "a+b");
    struct save_format tmp_save;
    bool flag = false;
    fseek(top, 0, SEEK_SET);
    while(fread(&tmp_save, sizeof(save), 1, top) == 1)
    {
        if(strcmp(tmp_save.username, save.username) == 0)
        {
            flag = true;
            if(save.parameter.people > tmp_save.parameter.people)
            {
                fseek(top, -sizeof(save), SEEK_CUR);
                fwrite(&save, sizeof(save), 1, top);
            }
            else if(save.parameter.people == tmp_save.parameter.people)
            {
                if(save.parameter.court > tmp_save.parameter.court)
                {
                    fseek(top, -sizeof(save), SEEK_CUR);
                    fwrite(&save, sizeof(save), 1, top);
                }
                else if(save.parameter.court == tmp_save.parameter.court)
                {
                    if(save.parameter.treasury > tmp_save.parameter.treasury)
                    {
                        fseek(top, -sizeof(save), SEEK_CUR);
                        fwrite(&save, sizeof(save), 1, top);
                    }
                }
            }
        }
    }
    if(flag == false)
    {
        fseek(top, 0, SEEK_END);
        fwrite(&save, sizeof(save), 1, top);
    }
    fclose(top);
    return;
}

void put_end_top()
{
    FILE *top = fopen("top_ens.bin", "a+b");
    struct save_format tmp_save;
    bool flag = false;
    fseek(top, 0, SEEK_SET);
    while(fread(&tmp_save, sizeof(save), 1, top) == 1)
    {
        if(strcmp(tmp_save.username, save.username) == 0)
        {
            flag = true;
            if(save.age > tmp_save.age)
            {
                fseek(top, -sizeof(save), SEEK_CUR);
                fwrite(&save, sizeof(save), 1, top);
            }
        }
    }
    if(flag == false)
    {
        fseek(top, 0, SEEK_END);
        fwrite(&save, sizeof(save), 1, top);
    }
    fclose(top);
    return;
}

int save_cmp_cms(void *s1, void *s2)
{
    struct save_format save1 = *((struct save_format *) s1);
    struct save_format save2 = *((struct save_format *) s2);
    if(save1.parameter.people > save2.parameter.people)
    {
        return -1;
    }
    else if(save1.parameter.people == save2.parameter.people)
    {
        if(save1.parameter.court > save2.parameter.court)
        {
            return -1;
        }
        else if(save1.parameter.court == save2.parameter.court)
        {
            if(save1.parameter.treasury > save2.parameter.treasury)
            {
                return -1;
            }
            else if(save1.parameter.treasury == save2.parameter.treasury)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 1;
    }
}

int save_cmp_ens(void *s1, void *s2)
{
    struct save_format save1 = *((struct save_format *) s1);
    struct save_format save2 = *((struct save_format *) s2);
    if(save1.age > save2.age)
        return -1;
    else if(save1.age == save2.age)
        return 0;
    else
        return 1;
}
