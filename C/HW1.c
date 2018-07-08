#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void lottery(int);
int checkPassword(int);
int isElement(int[], int, int);
int numbers[6]; //To hold the numbers generated.
int frequency[49]; //To count all number how many times occur.

int main()
{
    int password;
    int i, j; //Counter variables
    int max=0, lastMaxIndex[6], temp=0, *sortingPointer; //Temporary variables to keep each maximum-so-far element.
    int loopCount;
    int guess[6];

    printf("Enter password: ");
    scanf("%d", &password);
    if(checkPassword(password)==1)//If the password is true, then the program will start the actual process.
    {
        for(i=0; i<49; i++)
        {
            frequency[i]=0; /*Frequency array counts how many times each number occurred.
                              The index of i holds information about how many times number of (i+1) occurred.*/
            if(i<6)
                lastMaxIndex[i]=0;
        }

        printf("Enter loop count: ");
        scanf("%d", &loopCount);
        lottery(loopCount);
        printf("Result for %d random generations:\n", loopCount);

        for(i=0; i<49; i++)
            printf("%d->%d\t", i+1,frequency[i]);
        printf("\n----------------MOST FREQUENT SIX NUMBERS----------------\n");
        for(j=0; j<6; j++)
        {
            for(i=0; i<49; i++)//The loop search for the maximum element of the array
            {
                if(frequency[i]>=max && isElement(lastMaxIndex,i,j+1)==0)//Since the index of array is important on my algorithm
                {                                                        //I could not jut delete the maximum item
                    max=frequency[i];                                    //so I used isElement function to ignore the
                    lastMaxIndex[j]=i;                                   //elements found before
                }
            }
            printf("%d->%d\n", lastMaxIndex[j]+1,max);//After the calculations we can print the value of maximum-so-far element.
            guess[j]=lastMaxIndex[j]+1;               //And the value of the maximum-so-far element goes into the guess array.
            max=0;                                    //We have to initialize maximum-so-far element to 0 because we need to find
                                                      //the next maximum element and we don't know its value.
        }

        printf("\n----------------GUESS----------------\n");
        for(i=0; i<5; i++)//Bubble sort algorithm using pointer arithmetics
            for(sortingPointer=guess; sortingPointer < guess+5-i; sortingPointer++)
            {
                if(*sortingPointer>*(sortingPointer+1))
                {
                    temp = *sortingPointer;
                    *sortingPointer=*(sortingPointer+1);
                    *(sortingPointer+1)=temp;
                }
            }
        for(i=0; i<6; i++)
            printf("%d\t", *(guess+i));
    }
    else
        printf("Wrong password!\n");
    return 0;
}

void lottery(int loopCount)
{
    int i, j, num;
    srand(time(NULL));
    for(i=0; i<loopCount; i++)//We have to generate 6 random numbers for each loop so I used 2 nested "for loops".
        for(j=0; j<6; j++)
        {
            num =(rand()%49)+1;
            if(isElement(numbers,num,6)==0)//We need to generate unique 6 six values;
            {                              //If the number we just generated is not already in the array, we can add it.
                numbers[j] = num;
                frequency[numbers[j]-1]++;
            }
            else     //If it is not, we should decrease the value of the counter, j, to make it stay same as before.
                j--; //Because we did not add anything to array and index number should stay same at the and of the loop.

        }
}

int checkPassword(int password)
{
    if(password==220201013)
        return 1;
    else
        return 0;
}

int isElement(int array[], int number, int size)//Searches the whole array if the number is in the array or not.
{
    int i;
    for(i=0; i<size; i++)
        if(array[i] == number)
            return 1;
    return 0;
}
