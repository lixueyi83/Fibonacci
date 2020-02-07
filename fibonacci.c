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
#include "debug.h"
#include "huge_num.h"

/* fib(92) = 7540113804746346429, which is maximum number that a long long int
 * storage type can hold, if we want to store fib(93) or beyond we have to put
 * it into a special data structure to store those huge numbers. This is exactly 
 * why we introduce linkedlist here below. 
 *
 * Here below is the corresponding fib number that we are expecting and the
 * bigger the number the more memory it is required for storing those numbers
 * in memory which are allocated from heap:
 * fib(100): 354224848179261915075 
 * fib(200): 280571172992510140037611932413038677189525 
 * fib(300): 222232244629420445529739893461909967206666939096499764990979600
 */
const int NUM = 300;
const int NUM_SMALL = 92;

/*****************************************************************************
 * Function: fibRecursiveForSmallNums(int n)
 * Description: recursive solution, top-down
 * Time Complexity: O(2^N) 
 * Space Complexity: O(2^N)
 */
/* long long fibRecursiveForSmallNums(ListNode* head, int n) */
long long fibRecursiveForSmallNums(int n)
{
    if(n < 2) return n;
    return fibRecursiveForSmallNums(n-1) + fibRecursiveForSmallNums(n-2);
}

void testFibRecursiveForSmallNums(void)
{
    print_func_name();
    printf("\tfib(%d): %lld\n", NUM_SMALL, fibRecursiveForSmallNums(NUM_SMALL));
    MEAS_RUNTIME(fibRecursiveForSmallNums, NUM_SMALL); 
}

/*****************************************************************************
 * Function: fibRecursiveMemoForSmallNums(int n)
 * Description: recursive solution, top-down with memoriation
 * Time Complexity: O(N) 
 * Space Complexity: O(N)
 */
long long A[100];
long long fibRecursiveMemoForSmallNums(int n)
{
    if(n < 2) return A[n] = n;
    if(A[n] > 0) return A[n];
    return A[n] = fibRecursiveMemoForSmallNums(n-1) + 
                  fibRecursiveMemoForSmallNums(n-2);
}

void testFibRecursiveMemoForSmallNums(void)
{
    print_func_name();
    printf("\tfib(%d): %lld\n", NUM_SMALL, fibRecursiveMemoForSmallNums(NUM_SMALL));
    MEAS_RUNTIME(fibRecursiveMemoForSmallNums, NUM_SMALL); 
}

/*****************************************************************************
 * Function: fibRecursiveMemo(int n)
 * Description: recursion with memorization, and to deal with huge numbers that 
 *              has more than 19 digits which is maximum length of long long 
 *              storage type, we have to use some other data structures, and
 *              here we chose linked list, each node will keep one digit of
 *              the huge number and the first node is the least significant
 *              digit and last node is the most significant digit.
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
ListNode* dp[2];
ListNode* fibRecursiveMemo(int n)
{
    if(dp[n] != NULL) 
        return dp[n];
    if(n<2) 
        return dp[n] = convertNumtoList(n);
    return 
        dp[n] = addTwoNumbers(fibRecursiveMemo(n-1), fibRecursiveMemo(n-2));
}

void testFibRecursive(void)
{
    print_func_name();
    ListNode* head = fibRecursiveMemo(NUM);
    printf("\tfib(%d): ", NUM); printNumOfList(head);
}

/*****************************************************************************
 * Function: fibIterativeForSmallNums(int n)
 * Description: iterative solution, dp[n] buffer used for iteration
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
long long fibIterativeForSmallNums(int n)
{
    if(n < 2) return n;

    long long dp[n+1];
    dp[0] = 0;
    dp[1] = 1;

    for(int i=2; i<n+1; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    
    return dp[n];
}

void testFibIterativeForSmallNums(void)
{
    print_func_name();
    printf("\tfib(%d): %lld\n", NUM_SMALL, fibIterativeForSmallNums(NUM_SMALL));
    MEAS_RUNTIME(fibIterativeForSmallNums, NUM_SMALL); 
}

/*****************************************************************************
 * Function: fibIterativeForSmallNumsDP(int n)
 * Description: iterative solution, dp[n] buffer used for iteration
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
long long fibIterativeForSmallNumsDP(int n)
{
    if(n < 2) return n;

    long long prev2 = 0, prev1 = 1, curr;
    for(int i=2; i<n+1; i++){
        curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}

void testFibIterativeForSmallNumsDP(void)
{
    print_func_name();
    printf("\tfib(%d): %lld\n", NUM_SMALL, fibIterativeForSmallNumsDP(NUM_SMALL));
    MEAS_RUNTIME(fibIterativeForSmallNumsDP, NUM_SMALL); 
}

ListNode* fibIterativeDP(int n)
{
    if(n < 2)
        return convertNumtoList(n);

    ListNode *prev2 = convertNumtoList(0);
    ListNode* prev1 = convertNumtoList(1);
    ListNode* curr = NULL;
    for(int i=2; i<n+1; i++){
        ListNode* l1 = deepCopyList(prev1);
        ListNode* l2 = deepCopyList(prev2);
        curr = addTwoNumbers(l1, l2);
        prev2 = prev1; 
        prev1 = curr;
    }
    return curr;
}

void testFibIterativeDP(void)
{
    print_func_name();
    ListNode* head = fibIterativeDP(NUM);
    printf("\tfib(%d): ", NUM); printNumOfList(head);
}

/*****************************************************************************
 * main entrance
 */
int main(int argc, char* argv[])
{
    /* testFibRecursiveForSmallNums(); */
    testFibRecursiveMemoForSmallNums();
    testFibIterativeForSmallNums();
    testFibIterativeForSmallNumsDP();
    testFibRecursive();
    testFibIterativeDP();

    return 0;
}
