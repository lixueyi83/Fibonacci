/******************************************************************************
 * File Name: fibonacci.c
 * Author: Xueyi Li
 * Created Time: Tue 04 Feb 2020 01:55:06 PM PST
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <assert.h>

/* used for testing performance of each algorithm, and the runtime will increase 
 * exponentially with recursion solution, so better start with some small number 
 * like, 20 or 30. Tested on my PC, if NUM=50, the runtime could be more than 
 * minutes. */
const int NUM = 40;

/*****************************************************************************
 * Function: fibonacci(int n)
 * Description: recursive solution, top-down
 * Time Complexity: 
 * Space Complexity:
 */
int fib_recursive(int n)
{
    if(n < 2) return n;
    return fib_recursive(n-1) + fib_recursive(n-2);
}

void test_fib_recursive(void)
{
    printf("\tfib(%d): %d\n", NUM, fib_recursive(NUM));
}

/*****************************************************************************
 * Function: fibonacci(int n)
 * Description: iterative solution, dp[n] buffer used for iteration
 * Time Complexity: 
 * Space Complexity:
 */
int fib_iterative(int n)
{
    if(n < 2) return n;

    int dp[n+1];
    dp[0] = 0;
    dp[1] = 1;

    for(int i=2; i<n+1; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    
    return dp[n];
}


void test_fib_iterative(void)
{
    printf("\tfib(%d): %d\n", NUM, fib_iterative(NUM));
}

/*****************************************************************************
 * main entrance
 */
int main(int argc, char* argv[])
{
    test_fib_recursive();
    test_fib_iterative();

    return 0;
}
