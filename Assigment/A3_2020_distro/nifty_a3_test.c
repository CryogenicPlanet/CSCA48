#include<stdio.h>
#include<stdlib.h>
#include"ingredient_graph.c"


int output_check(intNode *head, intNode *checkAgainst){
	// Function aims to autocheck the printed outputs
	if(head == NULL){
		return 1; // Failed
	}
	intNode *cur = head;
	intNode *checker = checkAgainst;
	int found = 1; // False
	while (checker != NULL)
	{
		found = 1; // False
		cur = head;
		while (cur != NULL)
		{
			if(checker->x == cur->x){
				//printf("Found %s in output\n",ingredients[checker->x]);
				found = 0;// True
				break;
			}
			cur = cur ->next;
		}
		if (found == 1)
		{
			printf("Did not find %s in output\n",ingredients[checker->x]);
			return 1; // Failed Didn't find desired output
		}
		checker = checker ->next;	
		
		
	}
	return 0;
	
}
intNode * insertIngredients(intNode * head,char toBeInserted[MAT_SIZE][MAX_STR_LEN], int count){
	for(int i = 0; i < count; i++){
		//printf("Inserting Ingredient %s with index %d\n",toBeInserted[i],ingredient_index(toBeInserted[i]));
		head = insertInt(head,ingredient_index(toBeInserted[i]));
	}
	return head;
}

int main()
{
// _______________________________________ PUT TESTS BELOW HERE(10x10 Matrix) ______________________________________-

int tests_passed= 0;
intNode *checkAgainst = NULL;

printf("\n\n\n ~~~~~~~~ The following are using the 10x10 matrix ~~~~~~~~~~\n\n\n");
load_ingredients();

printf("------- The available ingredients should appear above this line -------\n");
printf("\n");
printf("_________________________________________________\n");
printf("Test 1: Find correct ingredient index(gruyere cheese):\n\n");
if(ingredient_index("gruyere cheese") == 7){
	printf("Test 1 Passed. good for you! this is a truly amazing achievement. go celebrate.\n");
	tests_passed++;
}else{
	printf("Test 1 Failed, ingredient_index(\"gruyere cheese\") returned %d instead of 7.\n", ingredient_index("gruyere cheese"));
}

printf("_________________________________________________\n");
printf("Test 2: Attempt to find ingredient index for item not in ingredients (onion):\n\n");
if(ingredient_index("onion") == -1){
	printf("Test 2 Passed. wow! go tell all your friends!\n");
	tests_passed++;
}else{
	printf("Test 2 Failed, ingredient_index(\"onion\") returned %d instead of -1.\n", ingredient_index("onion"));
}

printf("_________________________________________________\n");
printf("Test 3: Related ingredients for Artichoke hearts:\n\n");
printf("Your program printed:\n\n");
related_ingredients("artichoke hearts");
printf("\nShould have printed:\n\nmedium shrimp\nturkey\ngruyere cheese\nquinoa\n");

printf("_________________________________________________\n");
printf("Test 4: Related ingredients for Onions (item not in ingredient list):\n\n");
printf("Your program returned:\n\n");
related_ingredients("Onions");
printf("\nThis test should not print anything.\n");


printf("_________________________________________________\n");
printf("Test 5: Related ingredients to medium shrimp with k = 0 distance:\n\n");
printf("Your program returned the following linked list:\n\n");
intNode *h = NULL;
h = related_k_dist(h, "medium shrimp", 0, 0);
print_ingredients(h);
checkAgainst = NULL;
char output[MAT_SIZE][MAX_STR_LEN] = {"prepared horseradish","artichoke hearts"};
checkAgainst = insertIngredients(checkAgainst,output,2);
if(output_check(h,checkAgainst) == 1){
	printf("Failed Test Case 5, Did not get desired output\n");
	printf("\nThe linked list should contain:\n\nprepared horseradish\nartichoke hearts\n");
	return 1;
}
tests_passed++;
h = deleteList(h);
printf("Passed Test Case 5 \n");
printf("_________________________________________________\n");

printf("Test 6: Related ingredients to turkey with k = 1 distance:\n\n");
printf("Your program returned the following linked list:\n\n");
h = NULL;
h = related_k_dist(h, "turkey", 1, 0);
print_ingredients(h);
checkAgainst = NULL;
char t6[MAT_SIZE][MAX_STR_LEN] = {"medium shrimp","artichoke hearts","turkey","gruyere cheese","quinoa"};
checkAgainst = insertIngredients(checkAgainst,t6,5);
if(output_check(h,checkAgainst) == 1){
	printf("Failed Test Case 6, Did not get desired output\n");
	printf("\nThe linked list should contain:\n\nartichoke hearts\nmedium shrimp\nturkey\ngruyere cheese\nquinoa\n");
	return 1;
}
tests_passed++;
h = deleteList(h);
printf("Passed Test Case 6\n");
printf("_________________________________________________\n");

printf("Test 7: Related ingredients to soymilk with k = 2 distance:\n\n");
printf("Your program returned the following linked list:\n\n");
h = NULL;
h = related_k_dist(h, "soymilk", 2, 0);
print_ingredients(h);
checkAgainst = NULL;
char t7[MAT_SIZE][MAX_STR_LEN] = {"sunflower seeds","artichoke hearts","soymilk","quinoa"};
checkAgainst = insertIngredients(checkAgainst,t7,4);
if(output_check(h,checkAgainst) == 1){
	printf("Failed Test Case 7, Did not get desired output\n");
	printf("\nThe linked list should contain:\n\nsunflower seeds\nsoymilk\nquinoa\nartichoke hearts\n");
	return 1;
}
tests_passed++;
h = deleteList(h);
printf("Passed Test case 7");
printf("_________________________________________________\n");

printf("Test 8: Related ingredients to tomato juice with k = 6 distance:\n\n");
printf("Your program returned the following linked list:\n\n");
h = NULL;
h = related_k_dist(h, "tomato juice", 6, 0);
print_ingredients(h);
checkAgainst = NULL;
char t8[MAT_SIZE][MAX_STR_LEN] = {"sunflower seeds","artichoke hearts","soymilk","quinoa","medium shrimp",
"prepared horseradish","fresh breadcrumbs","gruyere cheese","tomato juice","turkey"};
checkAgainst = insertIngredients(checkAgainst,t8,10);
if(output_check(h,checkAgainst) == 1){
	printf("Failed Test Case 8, Did not get desired output\n");
	printf("\nThe linked list should contain all ten foods.\n");
	return 1;
}
tests_passed++;
h = deleteList(h);
printf("Passed Test Case 8\n");
printf("_________________________________________________\n");

printf("Test 9: Related ingredients to item not in list (onion) with k = 3 distance:\n\n");

h = NULL;
h = related_k_dist(h, "onion", 3, 0);
if(h == NULL){
	printf("Test 9 Passed. woah, you passed test 9? you must have big pp\n");
	tests_passed++;
} else {
	printf("Test 9 Failed, the link list was non empty.");
}
h = deleteList(h);

printf("_________________________________________________\n");

printf("Test 10: Related ingredients to artichoke hearts with restrictions from medium shrimp k = 0 avoid k = 0:\n\n");
printf("Your program returned the following linked list:\n\n");
h = NULL;
h = related_with_restrictions("artichoke hearts", "medium shrimp", 0, 0);
checkAgainst = NULL;
char t10[MAT_SIZE][MAX_STR_LEN] = {"quinoa","gruyere cheese","turkey"};
checkAgainst = insertIngredients(checkAgainst,t10,3);
if(output_check(h,checkAgainst) == 1){
	printf("Failed Test Case 10, Did not get desired output\n");
	printf("\nThe linked list should contain:\n\ngruyere cheese\nquinoa\nturkey\n");
	return 1;
}
tests_passed++;
print_ingredients(h);
h = deleteList(h);
printf("Passed Test 10\n");
printf("_________________________________________________\n");

printf("Test 11: Related ingredients to soymilk with restrictions from quinoa k = 2 avoid k = 1:\n\n");
h = NULL;
h = related_with_restrictions("soymilk", "quinoa", 2, 1);
if(h == NULL){
	printf("Test 11 Failed. just kidding! you passed test 11 no problem.\n");
	tests_passed++;
} else {
	printf("Test 11 Failed, the link list was non empty.");
}
h = deleteList(h);

printf("_________________________________________________\n");

printf("Test 12: Related ingredients with restrictions with items not on the list k = 5 avoid k = 0:\n\n");
h = NULL;
h = related_with_restrictions("carrots", "beef jerkey", 5, 0);
print_ingredients(h);
if(h == NULL){
	printf("Test 12 Passed. Im really happy for you.\n");
	tests_passed++;
} else {
	printf("Test 12 Failed, the link list was non empty.");
}
h = deleteList(h);
printf("_________________________________________________\n");

printf("Test 13: Related ingredients to tomato juice with restrictions from soymilk k = 3 avoid k = 2:\n\n");
printf("Your program returned the following linked list:\n\n");
h = NULL;
h = related_with_restrictions("tomato juice", "soymilk", 3, 2);
print_ingredients(h);
checkAgainst = NULL;
char t13[MAT_SIZE][MAX_STR_LEN] = {"medium shrimp",
"prepared horseradish","fresh breadcrumbs","gruyere cheese","tomato juice","turkey"};
checkAgainst = insertIngredients(checkAgainst,t13,6);
if(output_check(h,checkAgainst) == 1){
	printf("Failed Test Case 13, Did not get desired output\n");
	printf("\nThe linked list should contain:\n\ngruyere cheese\ntomato juice\nfresh breadcrumbs\nmedium shrimp\nprepared horseradish\nturkey\n");
	return 1;
}
tests_passed++;
h = deleteList(h);
printf("Passed Test Case 13\n");
printf("_________________________________________________\n");



printf("\n\n     =========== SUMMARY ============\n\n");
printf("     Passed %d/11 automatically ran tests.\n", tests_passed);
printf("     make sure test cases 3 and 4 output, they are not autochecked. also wash your hands.\n\n\n");
  return 0;   
}
