#include "MDB-c_1005934198.c" // <--- This will import your code so we can
                   //	use your solution to create a linked
                   //	list of movie reviews for testing!

int main()
{
    ReviewNode *MDB_head = NULL;
    ReviewNode *temp = NULL;

    printf("Custom Tester Assuming you have passed all tests in A1_driver \n");

    // Inserting Moives
    MDB_head = insertMovieReview("Alien", "20th Century Fox", 1979, 203630630.0, 85, MDB_head);
    MDB_head = insertMovieReview("Endgame", "Marvel", 2019, 1, 84, MDB_head);
    MDB_head = insertMovieReview("Birds of Prey", "Warner Bros", 2020, 203630630.0, 78, MDB_head);
    MDB_head = insertMovieReview("Parasite", "Neon", 2019, 10000.0, 99, MDB_head);
    MDB_head = insertMovieReview("Dollittle", "Universal Pictures", 2020, 1000.0, 14, MDB_head);

    // //Test 1 Sorting Test
    // printf("Pre Sorted Reviews\n------------------------\n");
    // printMovieReviews(MDB_head);
    // temp = sortReviewsByTitle(MDB_head);
    // printf("--------------------\nPost Sorted Reviews\n");
    // printMovieReviews(temp);
    // printf("Passed Sorting Test?\n");

    //Add Duplicate Title

    /// ONLY TEST 1 or 2 can be open at once both cannot be uncommented at the same time

    MDB_head = insertMovieReview("Birds of Prey", "Warner Bros", 2019, 203630630.0, 78, MDB_head);
    MDB_head = insertMovieReview("Alien", "20th Century Fox", 1978, 203630630.0, 85, MDB_head);

    // Test 2 Duplicate Sorting Test
    printf("Pre Sorted Reviews\n------------------------\n");
    printMovieReviews(MDB_head);
    temp = sortReviewsByTitle(MDB_head);
    printf("--------------------\nPost Sorted Reviews\n");
    printMovieReviews(temp);
    printf("Passed Duplicate Sorting Test?\n");

    // Test 3 Invalid Data Entry Test
    // Test 3 a) Invalid Score Input
    temp = insertMovieReview("Birds of Prey", "Warner Bros", 2018, 203630630.0, -1, MDB_head);
    if(temp != MDB_head){
        printf("Failed Test 3 Invalid Score Input\n");
        return 1;
        }
    printf("Passed Test 3 a) Invalid Score Input\n");
    // Test 3 b) Invalid Year Input
    temp = insertMovieReview("Birds of Prey", "Warner Bros", 100, 203630630.0, 78, MDB_head);
    if(temp != MDB_head){
        printf("Failed Test 3 Invalid Year Input\n");
        return 1;
        }
    printf("Passed Test 3 b) Invalid Year Input\n");

    printf("-----------------------\n All Reviews\n -----------------\n");
    printMovieReviews(MDB_head);
    printf("----------------\n");

    double score;
    // Test 4 Query Test
    MDB_head = insertMovieReview("Infinity War", "Marvel", 2018, 1.0, 93, MDB_head);
    MDB_head = insertMovieReview("Civil War", "Marvel", 2016, 1.0, 87, MDB_head);
    // Test 4 a) Marvel Studio Query
    score = queryReviewsByStudio("Marvel",MDB_head);
    if(score != 3.0){
        printf("Failed Test 4 Query Studio Marvel, with score %f \n", score);
        return 1;
    }
    printf("Passed Test 4 a) Marvel Query Test \n");
    // Test 4 b) Score Query Test
    score = queryReviewsByScore(85, MDB_head);
    if(score != 407271262.000000 && score!= 203640632.000000){
        printf("Failed Test 4 Query Score with score %f \n",score);
        return 1;
    }
    printf("Passed Test 4 b) Score Query Test? Check that the number of printed elements are five(if test case 1 is disabled) and four(if test case 1 is enabled)\n");

    // Test 5 Update Invalid Node
    updateMovieReview("Civil War","Marvel", 2019, 1, 90,MDB_head);
    temp = findMovieReview("Civil War","Marvel",2016,MDB_head);
    if(temp->review.score != 87 && temp->review.BO_total != 173630630.0){
        printf("Failed Test 5, Updated an Invalid Node");
        return 1;
    }
    printf("Passed Test 5? Check for error message above\n");

    // // Test Case 6 Insert Case Test

    MovieReview *rv = NULL;
    rv = (MovieReview *)calloc(1, sizeof(MovieReview));
    strcpy(rv->movie_title, "Civil War");
    strcpy(rv->movie_studio, "Marvel");
    rv->year = 2019;
    CastList *t = NULL;
    t = (CastList *)calloc(1, sizeof(CastList));
    strcpy(t->name, "Arnold Nolde");
    CastList *tx = NULL;
    tx = (CastList *)calloc(1, sizeof(CastList));
    strcpy(tx->name, "Arnold Nolde");
    t->next = tx;
    rv->cast = t;

    int name_count = countNames(rv, "old");
    if (name_count != 2)
    {
        printf("(TEST RESULT) Failed Test 6. Got %d instead of 2, since 'old' appears in Arnold Nolde and Arnold Nolde is inserted twice.\n", name_count);
        return 1;
    }
    printf("(TEST RESULT) Passed Test 6.\n");

    // Test Case 7 Small Sort Test
    ReviewNode *smallTest = NULL;
    smallTest = insertMovieReview("Alien", "20th Century Fox", 1979, 203630630.0, 85, smallTest);
    smallTest = insertMovieReview("Back to the Future", "Universal Studios", 1985, 381189762.00, 85,
                                 smallTest);
    printf("Pre Sorted Reviews\n------------------------\n");
    printMovieReviews(smallTest);
    temp = sortReviewsByTitle(smallTest);
    printf("--------------------\nPost Sorted Reviews\n");
    printMovieReviews(temp);
    printf("Passed Sorting Test?\n");
    
    
    // Test Case 8 Small Delete Node Case
    int count = 0;
    //printf("Before Insertion count: %d\n",countReviews(smallTest));
    //printf("----------- Test 8 ----------- \n");
    //printMovieReviews(temp);
    smallTest = insertMovieReview("Civil War", "Marvel", 2016, 1.0, 87, temp);
    count = countReviews(smallTest);
    //printMovieReviews(smallTest);
    //printf("Before Deletion count : %d\n",count);
    smallTest = deleteMovieReview("Back to the Future", "Universal Studios", 1985,smallTest);
    //printMovieReviews(smallTest);
    count = countReviews(smallTest);
    if(count != 2){
        printf("Failed Test Case 8 Small Delete Node Test Case with %d instead of 2\n", count);
        return 1;
    }
    printf("Passed Test Case 8\n");

}
