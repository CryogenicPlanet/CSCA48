/*
 * CSC A48 - Exercise 11 - Sudoku Solver
 * 
 * Your goal in this exercise is to practice recursion and
 * to see how a properly written recursive solution can
 * take care of fairly complicated tasks with a few lines
 * of (well thought out) code.
 * 
 * We will be solving Sudoku puzzles. In case you have never
 * solved or seen a Sudoku, you can learn more about them
 * here:
 * 
 * https://en.wikipedia.org/wiki/Sudoku
 * 
 * Your task if to write a function that takes an input
 * Sudoku in the form of a 9x9 array of integers. the
 * array will have a few entries filled with numbers in
 * [1, 9], and the remaining entries set to zero.
 * 
 * For the example in the wiki, the input array will
 * be
 * 
 * 5 3 0 0 7 0 0 0 0
 * 6 0 0 1 9 5 0 0 0
 * 0 9 8 0 0 0 0 6 0
 * 8 0 0 0 6 0 0 0 3
 * 4 0 0 8 0 3 0 0 1
 * 7 0 0 0 2 0 0 0 6
 * 0 6 0 0 0 0 2 8 0 
 * 0 0 0 4 1 9 0 0 5
 * 0 0 0 0 8 0 0 7 9
 * 
 * Your code should find the values that correctly
 * complete the Sudoku. 
 * 
 * As a brief reminder, a correctly solved Sudoku is
 * one in which there are no repeated digits in any
 * row, any column, or any of the 3x3 sub-arrays that
 * make up the large 9x9 grid. Another way to think
 * about it is, every row, column, and 3x3 subgrid
 * uses all of the different digits.
 * 
 * How to solve this?
 * 
 * * RECURSIVELY!
 * 
 * (hint) - Solving a Sudoku with N unknown values
 * may involve trying something, then solving an
 * easier Sudoku problem.
 * 
 * * How to approach this?
 * 
 * - As noted in class:
 * 	a) Determine the base case(s)
 * 	b) Figure out the recursive case
 * 	c) Determine what needs to happen to
 * 	   the solution for the entire problem
 * 	   is returned once the recursion hits
 * 	   the base case(s)
 * 
 * - Conditions on the input Sudoku
 * 	- It will have AT LEAST ONE DIGIT in each
 * 	  3x3 subgrid. Likely there will be several
 * 	  3x3 subgrids with several digits already
 * 	  set to some value.
 * 
 * - Conditions on your solution
 * 	- It should return a solution if there
 * 	  exists one.
 * 	- If no solution can be found, return the
 * 	  original input array
 * 	- If multiple solutions exist, any one of
 *        them is valid
 * 
 * - Can I use helper functions?
 * 	- Yes, by all means!
 * 
 * - Can I add extra libraries?
 * 	- No, they won't be needed.
 * 
 * - Can I change the 'print_sudoku()' function?
 * 	- Please don't, we may need it for testing!
 * 
 * (c) F. Estrada, March 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

void print_sudoku(int sudoku[9][9])
{
  printf("The Sudoku contains:\n");
  //printf("0  1  2  3  4  5  6  7  8\n-  -  -  -  -  -  -  -  -\n");
  for (int j = 0; j < 9; j++)
  {
    for (int i = 0; i < 9; i++)
    {
      printf("%d  ", sudoku[j][i]);
    }
    printf("\n");
  }
}

int check_row(int sudoku[9][9], int element, int column)
{
  int count = 0;
  for (int i = 0; i < 9; i++)
  {
    if (sudoku[column][i] == element)
    { // Iterating through each element in a single row
      count++;
    }
  }
  if (count != 1)
  { // Only one of each element in a row
    //printf("Failed Row\n");
    return 1;
  }
  return 0;
}
int check_columm(int sudoku[9][9], int element, int row)
{
  int count = 0;
  for (int i = 0; i < 9; i++)
  {
    if (sudoku[i][row] == element)
    { // Iterating through each element in a single column
      count++;
    }
  }
  if (count != 1)
  { // Only one of each element in a collumn
    //printf("Failed Column\n");
    return 1;
  }
  return 0;
}
int check_3x3(int sudoku[9][9], int element, int row_sector, int column_sector)
{ // Sector 0 - 2
  int count = 0;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (sudoku[i + column_sector * 3][j + row_sector * 3] == element)
      {
        count++;
      } // Checks that there is only one element in any 3x3 Sector
    }
  }
  if (count != 1)
  {
    //printf("Failed 3x3\n");
    return 1;
  }
  return 0;
}

int check_sudoku(int sudoku[9][9])
{
  /*
   *  This function checks whether a Sudoku is properly
   * solved. That means that each row, column, and
   * 3x3 subgrid uses each digit only once.
   * 
   *  If *ignores* zeros, so you can use it to check
   * that a partial solution is valid
   */

  /*****
   * TO DO:
   * Complete this function
   *   -- BUT ONLY IF YOU WANT TO!
   * Our testing script only checks your Sudoku
   * solution, if you want to solve it without
   * using this function, or if you want to write
   * your own helper functions, that's ok!
   * *****/

  int row_sector, column_sector = 0;
  for (int i = 0; i < 9; i++)
  {
    if (i > 2)
    {
      column_sector = 1;
    }
    if (i > 5)
    {
      column_sector = 2;
    }
    for (int j = 0; j < 9; j++)
    {
      row_sector = 0;
      if (j > 2)
      {
        row_sector = 1;
      }
      if (j > 5)
      {
        row_sector = 2;
      }
      if (sudoku[i][j] != 0)
      {
        if (check_row(sudoku, sudoku[i][j], i) == 1 || check_columm(sudoku, sudoku[i][j], j) == 1 || check_3x3(sudoku, sudoku[i][j], row_sector, column_sector) == 1)
        {
          // Fails Either Row Check or Column Check or 3x3 Check and is not 0
          //printf("Failed at Point (%d,%d) in Sector(%d,%d)\n",i,j,column_sector,row_sector);
          return 1;
        }
      }
    }
  }

  return 0;
}

int solved(int sudoku[9][9])
{
  /*
   * This function checks whether a given Sudoku is
   * completely solved (it has no zeros, all digits
   * are used once per row, column, and sub-grid.
   * It returns 1 if the Sudoku is solved, zero
   * otherwise
   */

  /*****
   * TO DO
   * Complete this function
   * BUT ONLY IF YOU WANT TO!
   *   You can solve the Sudoku without using this function,
   * or you can write a different helper function, whatever
   * makes more sense to yoU! our checker won't look at this
   * function, 
   * ****/
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (sudoku[i][j] == 0)
      {
        return 1;
      }
    }
  }
  return 0;
}

int valid_input(int sudoku[9][9], int element, int i, int j)
{
  sudoku[i][j] = element;
  if (check_sudoku(sudoku) == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int solver(int sudoku[9][9], int depth, int original[9][9])
{
  if (solved(sudoku) == 0)
  { // Input Sudoku is solved
    return 0;
  }
  if (check_sudoku(sudoku) == 1)
  { // Input Sudoku is Invalid
    return 1;
  }
  //printf("Recursive depth %d\n", depth);
  int zeroI,zeroJ;
  zeroI = -1;
  zeroJ = -1;

  for (int i = 0; i < 9; i++)
  {
    // Column Step

    for (int j = 0; j < 9; j++)
    {
      // Row Step
      if (sudoku[i][j] == 0)
      {
        // Check Non Zero
        //printf("Found zero at Depth %d at (%d,%d)\n", depth, i, j);
        zeroI = i;
        zeroJ = j;
      }
    }
  }
  for (int k = 1; k <= 9; k++)
  {

    if (valid_input(sudoku, k, zeroI, zeroJ) == 0)
    {
      sudoku[zeroI][zeroJ] = k;
      // Check Insert is true
      //printf("Procedding to next recursive depth from %d with valid input %d at (%d,%d)\n", depth, k, i, j);
      if (solver(sudoku, depth + 1, sudoku) == 0)
      { // Recursively execute and check validity
        //printf("Exiting Recursive Depth with success %d\n", depth + 1);
        return 0;
      }
      else
      {
        //printf("Exiting Recursive Depth of %d FAILED to insert %d at (%d,%d)\n", depth + 1, k, i, j);
        sudoku[zeroI][zeroJ] = 0;
      }
    }
    else
    {
      sudoku[zeroI][zeroJ] = 0;
    }
  }
  //printf("Exited New Element Loop \n");

  //printf("Exiting final for loop at depth %d\n", depth);
  if (solved(sudoku) == 0)
  {
    return 0;
  }
  return 1;
}

void solve_sudoku(int sudoku[9][9], int depth)
{
  /*
   * This function solves an input Sudoku, the
   * input has a value of 0 for any entries that
   * are not yet decided. If no solution exists
   * the function returns the input array *exactly
   * as it was* when the function was called.
   * 
   * The 'depth' parameter is provided in case you
   * want to use it to help debug and trace your
   * code. You do not need to use it if you don't
   * want to, and the problem can be solved without
   * using the depth value at all. 
   * 
   * The automated checker won't look at the depth
   * either.
   */

  if (solved(sudoku) == 0)
  { // Input Sudoku is solved
    return;
  }
  if (check_sudoku(sudoku) == 1)
  { // Input Sudoku is Invalid
    return;
  }
//#pragma omp parallel num_threads(6)
  solver(sudoku, depth, sudoku);
  // if(solved(sudoku) == 1){
  //   solve_sudoku(sudoku,depth+1);
  // }

  //printf("Exited solver \n");
}

#ifndef __testing

int main()
{
  // We'll provide you with the same test case
  // from the Wiki, so you can check your output.
  // But as always, be aware we will test your
  // solution on different Sudoku puzzles.

  int Sudoku[9][9] = {{5, 3, 0, 0, 7, 0, 0, 0, 0},
                      {6, 0, 0, 1, 9, 5, 0, 0, 0},
                      {0, 9, 8, 0, 0, 0, 0, 6, 0},
                      {8, 0, 0, 0, 6, 0, 0, 0, 3},
                      {4, 0, 0, 8, 0, 3, 0, 0, 1},
                      {7, 0, 0, 0, 2, 0, 0, 0, 6},
                      {0, 6, 0, 0, 0, 0, 2, 8, 0},
                      {0, 0, 0, 4, 1, 9, 0, 0, 5},
                      {0, 0, 0, 0, 8, 0, 0, 7, 9}};

  printf("Input puzzle is:\n");
  print_sudoku(Sudoku);

  //printf("Check input sudoku %d \n", check_sudoku(Sudoku));
  //printf("Check if it is solved %d \n", solved(Sudoku));
  solve_sudoku(Sudoku, 0);

  printf("Solution is:\n");

  print_sudoku(Sudoku);
}

#endif