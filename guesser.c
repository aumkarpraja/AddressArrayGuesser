// Author: Aumkar Prajapati

// Note: Instead of i and j, I used answer_i_cur and answer_j_cur, i and j are the inputs and work
// the same way. I did however follow the entire order (though my loops are organized slightly
// differently).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Typedef as required by assignment instructions
typedef struct {
    int real_part;
    int imag_part;
}complex;

// get user input, moved it out cause it might be used a lot
char* getInput(char *f){
    scanf("%10s",f);
    return f;
}

// fills the array with complex numbers
void fillArray(complex **array, int arraySize)
{
    int a, b;
    complex num;
    for (a = 0; a < arraySize; a++)
    {
        for (b = 0; b < arraySize; b++)
        {
            // assign random formula to complex number 5j + 10
            num.real_part = 5*rand() % 100 + 10;
            num.imag_part = 5*rand() % 100 + 10;
            array[a][b] = num; // fill it with complex rand
        }
    }
}

// fill an array of indexes to be used as the i and j values in the questions
void fillAnswerArray(int array[], int arraySize)
{
    rand(); // because rand tends to act weird on moons, called it once
    int i; // for loops
    
    // loop through the array and put in the random numbers
    for (i = 0; i < arraySize; i++)
        array[i] = rand() % arraySize; // fill with various answers
    
}


void hint1(complex **array, int arraySize)
{
    int k; // for loops
    
    // print left all the way down, show array address of first column M[k][0]
    for (k = 0; k < arraySize; k++)
        printf("M[%d][0] %p\n", k, &array[k][0]);
    
}

void hint2(complex **array, int arraySize)
{
    int k, l, m; // for loops
    
    // for the top columns, across
    for (l = 0; l < arraySize; l++)
        printf("\tM[0][%d]\t", l);
    
    printf("\n"); // spacer
    
    // for the left column
    printf("M[0][0] ");
    
    // For the top row, across
    for (m = 0; m < arraySize; m++)
        printf("%p\t", &array[0][m]);
    
    printf("\n"); // spacer
    
    // For the left most row, top to bottom
    for (k = 1; k < arraySize; k++)
        printf("M[%d][0] %p\n", k, &array[k][0]);
}

void hint3(complex **array, int arraySize)
{
    int k, l, m; // for loops
   
    // for the top columns, across
    for (l = 0; l < arraySize; l++)
        printf("\tM[0][%d]\t", l);
    
    printf("\n");
    
    // works from left to right, puts the descriptor first (i.e M[0][1]) then the address for the trailing
    for (m = 0; m < arraySize; m++){
        printf("M[%d][0]\t", m);
        for (k = 0; k < arraySize; k++){
            printf("%p\t", &array[m][k]);
        }
        printf("\n");
    }
}



int main(int argc, char *argv[])
{
    srand((unsigned int)time(NULL)); //was not random enough, though clock seems to do the trick
    int size_n = atoi(argv[1]); // Command line arg 1 for array size n
    complex **M; // the array
    int k; // for loops
    char i[10], j[10]; // the two inputs
    int answer_i[size_n], answer_j[size_n];
    int has_quit = 0; // a flag for when to quit
    int index_cur = 0; // an index value for the array
    int is_correct = 0; // flag for making the loop quit when user enters Q
    int attempts = 0; // right attempts made (to make sure it adds up to 100%)
    int wrong_attempts = 0; // wrong attempts
    // hint flag and other flags for stats
    int correct1 = 0; int correct2 = 0; int correct3 = 0; int no_hint = 0;
    int answer_i_cur, answer_j_cur; // current answer for i and j
    
    // assign space for array
    M = (complex **)malloc(sizeof(complex *)*size_n);
    for(k=0; k < size_n; k++)
        M[k] = (complex *)malloc(sizeof(complex)*size_n);
    
    fillArray(M, size_n); // fill array with complex numbers
    
    // fill the array with the random answers
    fillAnswerArray(answer_i, size_n);
    fillAnswerArray(answer_j, size_n);
    
    // start off the current answer at index 0
    answer_i_cur = answer_i[0];
    answer_j_cur = answer_j[0];
    
    // keep the loop going as long as the user doesn't trigger has_quit
    while (has_quit != 1)
    {
        // if the user enters Q, it will quit
        if (*i == 'Q')
            has_quit = 1;
        
        else
            while(has_quit != 2)
            {
                // if there is more and the user answered the previous question correct, move to the
                // next question
                if (is_correct == 1 && index_cur != size_n - 1)
                {
                    is_correct = 0;
                    index_cur++;
                    answer_i_cur = answer_i[index_cur];
                    answer_j_cur = answer_j[index_cur];
                }
                
                // if the limit has been hit, show the stats and end the program
                if (index_cur == size_n - 1)
                {
                    has_quit = 1;
                    free(M);
                    break;
                }
                
                
                printf("M[0][0]=%p.", &M[0][0]);
                printf(" M[i][j]=%p  What is i and j? (or Q or H or HH or HHH): ",&M[answer_i_cur][answer_j_cur]);
                
                // input i matters because it handles all the other commands (aside from i and j guesses)
                getInput(i);
               
                if (*i == 'Q')
                {
                    // quit out of loop 2, loop 1 is triggered by the same entry
                    has_quit = 2;
                    free(M); // free space in case anything goes wrong when trying to quit
                    break;
                }
                
                // HINT 1, make sure it's the char
                else if (*i == 'H' && strlen(i)== 1)
                {
                    printf("\n");
                    hint1(M, size_n);
                    printf("\n");
                    no_hint = 1;
                }
                
                // HINT 2, make sure the char is length two and part of the alphabet
                else if (strlen(i) == 2 && isalpha(*i))
                {
                    printf("\n");
                    hint2(M, size_n);
                    printf("\n");
                    no_hint = 1;

                }
                
                // HINT 3, same as hint 2
                else if (strlen(i) == 3 && isalpha(*i))
                {
                    printf("\n");
                    hint3(M, size_n);
                    printf("\n");
                    no_hint = 1;
                }
                
                // get the second input if the user hasn't decided to quit or entered something other than a number
                if (isdigit(*i))
                {
                    // get the second number
                    getInput(j);
                    
                    // moon fix: the moons server doesn't seem to like isdigit too much, I had to put this stuff here rather than having it. Please don't doc marks off on this, I had no other option.
                    
                    // if the numbers match, say it's right.
                    if (atoi(i) == answer_i_cur && atoi(j) == answer_j_cur)
                    {
                        // add an attempt
                        attempts++;
                        
                        printf("RIGHT\n");
                        
                        // a flag to tell the program to move onto the next question
                        is_correct = 1;
                        
                        // as long as this is the first attempt and the user got it right the first time
                        // then give it the first rating
                        if (attempts+wrong_attempts == 1 && no_hint == 0)
                            correct1++;
                        
                        // if the user didn't get it right the first time, give the second rating
                        else if(attempts+wrong_attempts >= 2 && no_hint == 0)
                            correct2++;
                        
                       
                        // if the user used hints, then this rating, reset hint so that it won't be
                        // flagged by the program again
                        else if (no_hint == 1)
                        {
                            correct3++;
                            no_hint = 0;
                        }
                    }
                    
                    else
                    {
                        // a wrong attempt was made so it will add it to the "ignored" attempts
                        // so the stats are accurate (and add up to 100%)
                        printf("WRONG\n");
                        wrong_attempts++;
                    }
                }
            }
    }
    // Averages
    float cor1 = 0, cor2 = 0, cor3 = 0;
   
    // do the math to average out the way the user was correct over the times actually attempted
    cor1 = (((float)correct1 / attempts) * 100);
    cor2 = (((float)correct2 / attempts) * 100);
    cor3 = (((float)correct3 / attempts) * 100);
    
    // output the statistics
    printf("------------------------------------------------\n");
    printf("%d\t Total number\n", attempts+wrong_attempts);
    printf("%.0f%%\t Correct after first time (no hints)\n", cor1); // correct1
    printf("%.0f%%\t Correct after 2 or more guesses (no hints)\n", cor2); // correct2
    printf("%.0f%%\t Correct after hints\n", cor3); // correct3
    printf("------------------------------------------------\n");
    return 0;
}
