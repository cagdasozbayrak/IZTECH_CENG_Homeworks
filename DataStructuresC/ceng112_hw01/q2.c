#include <stdio.h>
#include <ctype.h>

int firstCharOfSentence(char current, char last);

int main()
{
	int next=0, last=0, current=0;
	while((next=getchar()) != EOF)
	{
		if(firstCharOfSentence(current, last)) 
			printf("%c", toupper(next));			     
		else							      
			printf("%c", next);
		last = current;
		current = next;
	}
}

int firstCharOfSentence(char current, char last)
{
	return (current == ' ' || current == 0) &&
		   (last == '.' || last == '?' || last == '!' || last == 0);
}
