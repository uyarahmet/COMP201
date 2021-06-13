#include <stdio.h>
#include <string.h>
#include <math.h>

int reviewRateFinder(char *ch)
{
    if (*ch == '1')
    {
        return 1;
    }
    if (*ch == '2')
    {
        return 2;
    }
    if (*ch == '3')
    {
        return 3;
    }
    if (*ch == '4')
    {
        return 4;
    }
    if (*ch == '0')
    {
        return 0;
    }
}


int main()
{

    /*****************OPENING FILES***************************/

    FILE *wordListP;
    wordListP = fopen("wordList.txt", "r");

    if (wordListP == NULL)
    { // check for opening word list
        printf("Could not open word list file.\n");
        return 1;
    }

    FILE *reviewListP;
    reviewListP = fopen("movieReviews.txt", "r");

    if (reviewListP == NULL)
    { // check for opening review
        printf("Could not open word review file.\n");
        return 1;
    }

    /********************************************************/

    /************************TASK1***************************/

    char word[50];

    printf("Enter a word: ");
    fgets(word, 50, stdin);
    int len = strlen(word);
    if (word[len - 1] == '\n') // removing new line character.
        word[len - 1] = 0;

    char buffer[1000];
    int reviewPoints = 0;
    int apperance = 0;

    while (fgets(buffer, 1000, reviewListP) != NULL)
    {
        char *token = strtok(buffer, " "); // first token is review rate
        int reviewRate = reviewRateFinder(token);
        // int seen = 0;

        while (token != NULL)
        {
            if (strncasecmp(word, token, 50) == 0)
            {
                reviewPoints += reviewRate;
                apperance += 1;
                break; // 1 occurence is enough according to BB thread. 
            }
            token = strtok(NULL, " ");
        }
    }

    printf("%s appears %d times.\n", word, apperance);
    double average = (double)reviewPoints /apperance;
    printf("The average score for reviews containing the word %s is %1.4f",word, average);
    

    /********************************************************/

    // printf("Starting to read wordList.txt...\n");

    // while(fgets(buffer, bufferVal, wordListP) != NULL){
    //     printf("%s",buffer);

    // }

    /************ CLosing files *****************************/
    printf("\nclosing\n");
    fclose(wordListP);
    fclose(reviewListP);
    printf("exiting\n");
    return 0;
}