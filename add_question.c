#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fp1, *fp2;
    char name[20];
    char question[300];
    char decision1[200];
    int people1, court1, treasury1;
    char decision2[200];
    int people2, court2, treasury2;
    printf("\n Enter the name of the question file (Without the \".txt\" and not more than 15 characters):\n ");
    scanf("%s", name);
    strcat(name, ".txt");
    while(fopen(name, "r") != NULL)
    {
        printf("\n Sorry but this text file already exists! Enter another name please:\n ");
        scanf("%s", name);
        strcat(name, ".txt");
    }
    printf("\n Now Please write the question:\n\n ");
    getchar();
    gets(question);
    printf("\n Now Please write the first decision:\n\n ");
    getchar();
    gets(decision1);
    printf("\n Enter it's impact on parameters (People, Court and Treasury in order):\n\n ");
    scanf("%d%d%d", &people1, &court1, &treasury1);
    printf("\n Now Please write the second decision:\n\n ");
    getchar();
    gets(decision2);
    printf("\n Enter it's impact on parameters (People, Court and Treasury in order):\n\n ");
    scanf("%d%d%d", &people2, &court2, &treasury2);
    fp1 = fopen(name, "w");
    fp2 = fopen("CHOICES.txt", "a");
    fprintf(fp2, "\n%s", name);
    fclose(fp2);
    fprintf(fp1, "%s\n", question);
    fprintf(fp1, "%s\n", decision1);
    fprintf(fp1, "%d\n%d\n%d\n", people1, court1, treasury1);
    fprintf(fp1, "%s\n", decision2);
    fprintf(fp1, "%d\n%d\n%d", people2, court2, treasury2);
    printf("\n The question is added to the game. Thank you!\n ");
    fclose(fp1);
    getch();
    return 0;
}
