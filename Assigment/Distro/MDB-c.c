/**
 *  CSC A48 - Winter 2020 - Assignment 1 starter
 *
 *  (c) 2020 Francisco Estrada & Joe Armitage 
 *  - No part of this code may be reproduced without written authorization
 *
 * This is the file where you will be doing most of your work. The
 * functionality you must provide for part 1 of the assignment is described
 * in the handout, and given in detail in the comments at the head of each
 * function below.
 *
 * Plan your work carefully, review the notes for Unit 3, and work carefully
 * to complete the functions in this file. At any point you can bring
 * questions to your TAs or instructors during office hours. But please
 * remember:
 *
 * - You should not post any assignment code on Piazza
 * - You should not share any part of your solution in any form
 * - You should definitely *help* other understand any ideas and
 *   concepts regarding linked lists that you have already mastered,
 *   but being careful not to give away parts of the solution, or
 *   descriptions of how to implement functions below.
 * - If you are not sure whether you can or can not discuss some
 *   particular aspect of the work to be done, remember it's always
 *   safe to talk with your TAs.
 * - Obtaining external 'help' including being given code by an
 *   external party, or being tutored on what to write to solve
 *   the assignment constitutes an academic offence.
 *
 * All tasks to be completed by you are clearly labeled with a
 * TODO:
 * comment block, which also gives you details about what you have to implement.
 * Look carefully and make sure you don't miss a thing!
 *
 * NOTE: This file contains no main() function! you can not compile
 * it on its own to create an executable. It's meant to be used
 * together with A1_driver.c - be sure to read that file carefully
 * to understand how to use the tests there - Any additional tests
 * you want to run on the code below should be added to A1_driver.c
 *
 * Before you even get starter implementing, please complete the
 * student identification section below, and check that you are aware
 * of the policy on academic honesty and plagiarism.
 */

/**
 * TODO: STUDENT IDENTIFICATION
 *
 * Student Name (Last name, First name):
 * Student Number:
 * UTORid:
 * Your instructor's name is:
 */

/**
 * TODO:
 * Academic Integrity Statement:
 *
 * I hereby certify that the work contained in this file is my own, and
 * that I have not received any parts of my solution from other sources
 * including my fellow students, external tutoring services, the internet,
 * or algorithm implementations found online.
 *
 * Sign here with your name:
 *
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 1024

/* Compound data type declarations */
/***************************************************************************/
/******                         TODO                               *********/
/****** In the space below, complete the definitions of the compound *******/
/****** data types that will be needed to implement the movie review *******/
/****** linked list. This includes the MovieReview type, and the     *******/
/****** ReviewNode. Details about the contents of these can be       *******/
/****** found in the assignment handout. Read them carefully!        *******/
/******                                                              *******/
/***************************************************************************/

// Used to store information about the cast of a movie (Implement AFTER everything else)
typedef struct castList_struct
{
        
} CastList;

// Used to store information about a movie
typedef struct movieReview_struct
{

  char movie_title[1024];
  char movie_studio[1024];
  int year;
  double BO_total;
  int score;
  CastList *cast;
    
} MovieReview;

// Used to store a linked list of MovieReview nodes
typedef struct reviewNode_struct
{

  MovieReview review;
  struct reviewNode_struct* next;
    
} ReviewNode;

/**
 * Allocates a new, empty ReviewNode, and initializes its contents with the given values.
 *
 * INPUT:
 *  - title: the title of the movie
 *  - studio: the studio where the movie was produced
 *  - year: the year in which the movie was produced
 *  - BO_total: the amount of money this movie grossed at the box office
 *  - score: the average review score given to this movie
 *
 * NOTE: - The *next pointer for the new node MUST be set to NULL
 *
 * RETURN:
 *  - if something goes wrong, return NULL,
 *  - else:
 *      - the newly allocated node, initialized with:
 *          - node.next <- NULL
 *          - node.review:
 *              - movie_title <- title
 *              - movie_studio <- studio
 *              - year <- year
 *              - BO_total <- BO_total
 *              - score <- score
 *              - cast <- NULL
 */
ReviewNode *newMovieReviewNode(char *title, char *studio, int year, double BO_total, int score)
{
    
    MovieReview review;
    strcpy(review.movie_title,title);
    strcpy(review.movie_studio,studio);
    review.year = year;
    review.BO_total = BO_total;
    review.score =  score;
    ReviewNode *MovieReviewNode;
    MovieReviewNode =(ReviewNode *)calloc(1, sizeof(ReviewNode));
    MovieReviewNode->review = review;
    //printf("----\nFrom new Review function using review object\n %s,%s,%d\n---\n",review.movie_title,review.movie_studio,year);
    MovieReviewNode->next = NULL;
    return MovieReviewNode;
}

/**
 * Finds and returns a ReviewNode containing information that matches the input query:
 *      - title
 *      - studio
 *      - year
 * but if no such ReviewNode exists, returns NULL.
 *
 * INPUT:
 *  - title: the title of the movie
 *  - studio: the studio where the movie was produced
 *  - year: the year in which the movie was produced
 *
 * RETURN:
 *  - if a review matching the query is found:
 *      the node that contains that review.
 *  - else:
 *      NULL
 */
ReviewNode *findMovieReview(char *title, char *studio, int year, ReviewNode *head)
{
    ReviewNode *current = NULL;
    current = head;
    int checker = 0;
    while(current !=  NULL){
        checker = 0;
        if(strcmp(current->review.movie_title,title) == 0){
            checker += 1;
            if(strcmp(current->review.movie_studio,studio)==0){
                checker += 1;
                if(current->review.year == year){
                    checker += 1;
                    //printf("FOUND %s,%s at %d,%d\n",title,studio,year,current->review.year);
                    //checker = NULL;
                    return current;
                }
            }
        }
    current = current->next;
    }

    return NULL;  // Remove this before you implement your solution!
}

/**
 * Inserts a new movie review into the linked list, if it does not exist already.
 *
 * INPUT:
 *  - title: the title of the movie
 *  - studio: the studio where the movie was produced
 *  - year: the year in which the movie was produced
 *  - BO_total: the amount of money this movie grossed at the box office
 *  - score: the average review score given to this movie
 *
 * OUTPUT: - head: the (potentially new) head of the linked list of reviews
 *
 * RETURN: - the (potentially new) head node of the linked list
 *
 * NOTE:
 *  - If head == NULL, then the list is still empty
 *  - Inserts the new movie review *at the head* of the linked list
 *  - MUST check that the movie is not already in the list before inserting (there should be no
 *      duplicate entries). If a movie with matching title, studio, and year is already in the list,
 *      nothing is inserted and the function returns the current list head.
 */
ReviewNode *insertMovieReview(char *title, char *studio, int year, double BO_total, int score,
                              ReviewNode *head)
{
    /***************************************************************************/
    /**********  TODO: Complete this function **********************************/
    /***************************************************************************/
    
    if(findMovieReview(title,studio,year,head) != NULL){
        printf("Sorry, movie alreadt exists\n");
        return head;
    }
    ReviewNode *newNode = NULL;        
    newNode = newMovieReviewNode(title,studio,year,BO_total,score);
    newNode->next = head;
    //printf("Just added %s\n",newNode->review.movie_title);
    return newNode;  // Remove this before you implement your solution!
}

/**
 * Returns the length of the linked list that begins at head.
 *
 * INPUT: - head: the start of a linked list
 *
 * RETURN: - the number of elements in this linked list
 */
int countReviews(ReviewNode *head)
{
    int count = 0;
    ReviewNode *current;
    current = head;
    while(current != NULL){
        count++;
    current = current->next;
    }

    return count;  // Remove this before you implement your solution
}

/**
 * Updates the review matching the input query:
 *  - title
 *  - studio
 *  - year
 * with new BO_total and score.
 *
 * If no such review is found, the function prints out: "Sorry, no such movie exists at this point"
 *
 * INPUT:
 *  - title: the title of the movie
 *  - studio: the studio where the movie was produced
 *  - year: the year in which the movie was produced
 *  - BO_total: the amount of money this movie grossed at the box office
 *  - score: the average review score given to this movie
 *
 * OUTPUT:
 *  - head: the (potentially new) head of the linked list of reviews
 *  - error message to the terminal, if no node is found matching given [title, studio, year] query
 */
void updateMovieReview(char *title, char *studio, int year, double BO_total, int score,
                       ReviewNode *head)
{
    ReviewNode *match;
    match = findMovieReview(title,studio,year,head);
    if(match != NULL){
        match->review.BO_total = BO_total;
        match->review.score = score;
        //printf("Updating Match where match title %s\n ",match->review.movie_title);
    }

}

/**
 * Removes a review matching the input query from the linked list, if such review can be found.
 *
 * INPUT:
 *  - title: the title of the movie
 *  - studio: the studio where the movie was produced
 *  - year: the year in which the movie was produced
 *
 * OUTPUT: - head: the (potentially new) head node of the linked list
 * RETURN: - the (potentially new) head node of the linked list
 */
ReviewNode *deleteMovieReview(char *title, char *studio, int year, ReviewNode *head)
{
    ReviewNode *prev;
    ReviewNode *current;
    ReviewNode *next;
    prev = NULL;
    current = head;
    int checker = 0;
    next = current->next;
    while (current!= NULL){
        next = current->next;
        checker = 0;
        if(strcmp(current->review.movie_title,title) == 0){
            checker +=1;
            if(strcmp(current->review.movie_studio,studio)==0){
                checker +=1;
                if(current->review.year == year){
                    checker +=1;
                    if(prev != NULL){
                        prev->next = next;
                        free(current);
                        //return head;
                    } else{
                        head = next;
                        free(current);
                        //eturn head;
                    }
                }
            }
        }
    prev = current;
    current = next;
    }

    return head;  // Remove this before implementing your solution
}
double printReviews(ReviewNode *head, int condition,char *studio,int score){
    double totalBoxOffice = 0.0;
    ReviewNode *current;
    current = head;
    while(current != NULL){
        if(condition == 1){
            if(strcmp(current->review.movie_studio,studio) != 0){
                current = current->next;
            } // Checks if the studio is not equal and skips that node
        }
        if(condition == 2){
            if(current->review.score < score){
                current = current->next;
            } // Check if the score is lesser than and then skips that node
        }
        if(current != NULL){
        printf("%s\n",current->review.movie_title);
        printf(current->review.movie_studio);
        printf("\n%d\n",current->review.year);
        printf("%f\n",current->review.BO_total);
        totalBoxOffice += current->review.BO_total;
        printf("%d\n",current->review.score);
        printf("**********************\n");
        current = current->next;
    }}
    return totalBoxOffice;
}
/**
 * Prints out all the reviews in the linked list and returns the sum of all the box office totals
 * for all stored movie reviews.
 *
 * INPUT: - the head node of the linked list
 *
 * RETURN: - the BOX OFFICE TOTAL, for all movies
 *
 * NOTE:
 *  - Each field in the review is printed in a separate line, with *no additional text*
 *  - The only thing printed is the value of the corresponding field
 *  - Reviews are separated from each other by a line of "*******************"
 *    whose length is irrelevant, as long as it is >= 2
 *  - See the Assignment handout for a sample of the output that should be produced by this function
 */
double printMovieReviews(ReviewNode *head)
{
    char* temp = NULL;
    return printReviews(head,0,temp,-1);  // Remove this before you implement your solution
}

/**
 * Prints out all the reviews in the linked list which share the production studio given by studio
 * and then returns the sum of all the box office totals for these such stored movie reviews.
 *
 * INPUT: - the head node of the linked list
 *
 * RETURN:
 *  - the BOX OFFICE TOTAL, for all the movies that match the query
 *  - the studio attribute of the query: only print and count nodes matching this studio
 *
 * NOTE:
 *  - Each field in the review is printed in a separate line, with *no additional text*
 *  - The only thing printed is the value of the corresponding field
 *  - Reviews are separated from each other by a line of "*******************"
 *    whose length is irrelevant, as long as it is >= 2
 *  - See the Assignment handout for a sample of the output that should be produced by this function
 */
double queryReviewsByStudio(char *studio, ReviewNode *head)
{
    /***************************************************************************/
    /**********  TODO: Complete this function *********************************/
    /***************************************************************************/

    return printReviews(head,1,studio,-1);  // Remove this before you implement your solution
}

/**
 * Prints out the contents of all reviews whose score is greater than, or equal to min_score.
 *
 * INPUT: - the head node of the linked list
 *
 * RETURN:
 *  - the BOX OFFICE TOTAL, for all the movies that match the query
 *  - the minimum score attribute of the query: only print and count nodes above this score
 *
 * NOTE:
 *  - Each field in the review is printed in a separate line, with *no additional text*
 *  - The only thing printed is the value of the corresponding field
 *  - Reviews are separated from each other by a line of "*******************"
 *    whose length is irrelevant, as long as it is >= 2
 *  - See the Assignment handout for a sample of the output that should be produced by this function
 */
double queryReviewsByScore(int min_score, ReviewNode *head)
{
    /***************************************************************************/
    /**********  TODO: Complete this function *********************************/
    /***************************************************************************/
    char* temp = NULL;
    return printReviews(head,2,temp,min_score);  // Remove this before you implement your solution
}

/**
 * Deletes the linked list of movie reviews, releasing the memory allocated to each node.
 *
 * INPUT: - the head node of the linked list
 *
 * RETURN: - a NULL pointer (so that the head of the list can be set to NULL after deletion)
 */
ReviewNode *deleteReviewList(ReviewNode *head)
{
    /***************************************************************************/
    /**********  TODO: Complete this function *********************************/
    /***************************************************************************/
    ReviewNode *current = head;
    ReviewNode *next = current;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    return NULL;  // Remove this before you implement your solution
}

/////////////////////////////////////////////////////////////////////////////////////////////
// CRUNCHY SECTION!
// Do not work on the functions below until your A1 is working properly and is fully tested!
/////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Sorts the list of movie reviews in ascending order of movie title.
 * If duplicate movie titles exist, the order is arbitrary (i.e. you choose which one goes first).
 *
 * INPUT: - the head of the unsorted list.
 * OUTPUT: - the head of the sorted list.
 * RETURN: - the head of the sorted list.
 */
ReviewNode *sortReviewsByTitle(ReviewNode *head)
{
    /***************************************************************************/
    /**********  TODO: Complete this function *********************************/
    /***************************************************************************/
    
    return NULL;  // Remove this before you implement your solution
}

/**
 * Inserts the name of a cast member into the linked list of cast members, matching the input query:
 *  - title
 *  - studio
 *  - year
 * if a match is found; else, does nothing.
 *
 * INPUT:
 *  - title: the title of the movie
 *  - studio: the studio where the movie was produced
 *  - year: the year in which the movie was produced
 *  - head: the head node of the linked list
 *  - name: the name of the cast member being inserted
 *
 * OUTPUT: - the (internally modified) linked list of ReviewNodes, starting at head
 *
 * NOTE:
 *  - Duplicate names are allowed - this time!
 */
void insertCastMember(char *title, char *studio, int year, ReviewNode *head, char *name)
{
    /***************************************************************************/
    /**********  TODO: Complete this function *********************************/
    /***************************************************************************/

}

/**
 * Counts how many actors have names containing the input parameter "name".
 *
 * INPUT:
 *  - movie: the movie from which the cast is to be searched
 *  - name: the name to be searched for in the cast list of this movie
 *
 * RETURN: - number of cast members of this movie that contain the substring "name".
 *
 * EXAMPLE:
 * If the input name is "Joe", and the cast list contains
 * - Joe Cool
 * - Notajoe Jones
 * - OneJoe Smith
 * - Last Name Joe
 * then the function will return 3 (actor names 1, 3, and 4 contain 'Joe').
 *
 * NOTE: The case of each character MUST match (the J must be a capital letter in the above example
 * for the match to count)
 */
int countNames(MovieReview *movie, char *name)
{
    /***************************************************************************/
    /**********  TODO: Complete this function *********************************/
    /***************************************************************************/

    return 0;  // Remove this when you start working on your solution
}

 //Prints out names of cast members for this movie - use it to help you debug
 //UN-COMMENT this function AFTER you've implemented the cast list CDT, or
 //you will get compiler errors!
 void printNames(ReviewNode *head){
     printf("Temp\n");
 }
/*
 void printNames(ReviewNode *head)
 {
     if (NULL == head || NULL == head->review.cast) return;
    printf("The cast for this movie are:\n");
     for (CastList *p = head->review.cast; NULL != p; p = p->next) printf("%s\n", p->name);
 } */
