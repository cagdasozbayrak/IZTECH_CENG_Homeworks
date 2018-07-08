#include <stdio.h>
#include <string.h>

//Linked list implementation
struct Node
{
    char word[30];
    struct Node *next;
};

struct Node *head=NULL, *tail=NULL;

void addItem(char *word) //Adds the given word end of the linked list.
{
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    strcpy(temp->word,word);
    temp->next = NULL;
    if(head==NULL)
    {
        head=temp;
        tail=temp;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }
}
//End of linked list implementation

int searchCaseInsensitive(char str1[], char str2[]); /*Searches second string in the end of first string
                                                        if found returns 1 else 0*/

void applyRulesOnWords(struct Node *head);
void applyRule(char *word, char *rule, char *changeOfRule);

int main(int argc, char* argv[])
{
    FILE *inputFile, *outputFile;
    struct Node *temp;
    char str[30];

    inputFile = fopen(argv[2], "r");//Since the 3rd argument is the input file name, it will be in argv[2]
    while(!feof(inputFile))
    {
        fscanf(inputFile, "%s", str);
        addItem(str);
    }
    fclose(inputFile);

    outputFile = fopen(argv[4], "w");
    applyRulesOnWords(head);
    for(temp=head; temp!=NULL; temp=temp->next)
        fprintf(outputFile, "%s\n", temp->word);
    fclose(outputFile);

    free(head);
    free(tail);
    free(temp);
}

int searchCaseInsensitive(char str1[], char str2[])
{
    int found = 0;
    int size1 = strlen(str1);
    int size2 = strlen(str2);
    char tempStr[size1+1];
    char compareStr[size2+1]; //To hold the string portion to compare
    int i, j; //Counter variables
    for(i=0; i<size1; i++)
        tempStr[i]=tolower(str1[i]); //Since our function need to be case insensitive, we have to make all string upper case.
    tempStr[size1]='\0';//Last character of a string must be NULL
    i=size1-size2;
    for(j=0; j<size2; j++) //Adds size2 characters of str1 to check if it is equal to str2
        compareStr[j] = tempStr[i+j];
    compareStr[size2]='\0';
    if(strcmp(compareStr, str2) == 0)
        found = 1;
    return found;
}

void applyRulesOnWords(struct Node *head)
{
    struct Node *temp;
    for(temp=head; temp!=NULL; temp=temp->next)
    {
        if(searchCaseInsensitive(temp->word, "sses"))
            applyRule(temp->word, "sses", "ss");
        else if(searchCaseInsensitive(temp->word, "ies"))
            applyRule(temp->word, "ies", "i");
        else if(searchCaseInsensitive(temp->word, "ss"))
            applyRule(temp->word, "ss", "ss");
        else if(searchCaseInsensitive(temp->word, "s"))
            applyRule(temp->word, "s", "");
        else
            continue;
    }
}

void applyRule(char *word, char *rule, char *changeOfRule)
{
    int ruleLength=strlen(rule);
    int wordLength=strlen(word);
    int location=wordLength-ruleLength;//The location we put \0 character so that add changeOfRule end of it
    *(word+(location))='\0';//Deletes the part that the rule will be applied on.
    strcat(word,changeOfRule);
}
