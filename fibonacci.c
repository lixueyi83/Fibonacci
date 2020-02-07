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
int NUM = 300;

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
    for(int i=0; i<50; i++){
        printf("\tfib(%d): %10lld", i, fibRecursiveForSmallNums(i));
        MEAS_RUNTIME(fibRecursiveForSmallNums, i); 
    }
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
    for(int i=0; i<93; i+=2){
        printf("\tfib(%d): %20lld", i, fibRecursiveMemoForSmallNums(i));
        MEAS_RUNTIME(fibRecursiveMemoForSmallNums, i); 
    }
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
    for(int i=0; i<93; i+=2){
        printf("\tfib(%d): %20lld", i, fibIterativeForSmallNums(i));
        MEAS_RUNTIME(fibIterativeForSmallNums, i); 
    }
}

/*****************************************************************************
 * Function: fibIterativeForSmallNumsDP(int n)
 * Description: iterative solution, dp[n] buffer used for iteration
 * Time Complexity: O(N)
 * Space Complexity: O(1)
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
    for(int i=0; i<93; i+=2){
        printf("\tfib(%d): %20lld", i, fibIterativeForSmallNumsDP(i));
        MEAS_RUNTIME(fibIterativeForSmallNumsDP, i); 
    }
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
 * Space Complexity: O(1)
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

void testFibRecursiveMemo(void)
{
    print_func_name();
    for(int i=0; i<NUM; i+=5){
        ListNode* head = fibRecursiveMemo(i);
        printf("\tfib(%d): ", i); printNumOfList(head);
        MEAS_RUNTIME(fibRecursiveMemo, i); 
    }
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
    for(int i=0; i<NUM; i+=5){
        ListNode* head = fibIterativeDP(i);
        printf("\tfib(%d): ", i); printNumOfList(head);
        MEAS_RUNTIME(fibIterativeDP, i); 
    }
}

/*****************************************************************************
 * main entrance
 */
int main(int argc, char* argv[])
{
    testFibRecursiveForSmallNums();
    testFibRecursiveMemoForSmallNums();
    testFibIterativeForSmallNums();
    testFibIterativeForSmallNumsDP();
    testFibRecursiveMemo();
    testFibIterativeDP();

    return 0;
}

/******************************************************************************
 * 1. Which algorithm would you use in an actual release?
 *    Given Time Complexity and Space Complexity, I would rather choose iterative
 *    version with time O(n) and space O(1). And the reason I would not choose
 *    the bruteforce one is clearly that its consumption if huge time and space
 *    complexity. However, the recursive bruteforce solution does has its use
 *    case, for example we want to show to the students how bad it is compared
 *    to other algorithm, and those students might have a very clear picture
 *    and understanding about the cost of different algorithms.
 *
 * 2. Can we make current solution better or can we make further optimization?
 *    The answer is yes. We have already taken into consideration that how to
 *    deal with storing huge numbers, bigger than long long int built-in data 
 *    types, by using a linked list to store each digit into a node and it did
 *    work pretty well. And the next step optimization might be focusing on
 *    calculating fib(n) itself, and mainly focuses on reducing time complexity.
 *    Cause current space complexity is already O(1), nothing further we can do.
 *
 *    Actually, there is a formula to calculate fib(n) 
 *      Fn = {[(√5 + 1)/2] ^ n} / √5
 *
 *    With this fomular the time complexith will be just O(1) which shall be
 *    the best so far solution for calculating Fibonacci numbers. However, we 
 *    we have to keep in mind that we have to implement sqrt(n) and pow(phi, n)
 *    utility function if there is no such libary/api ready to use.
 *
 *    For details regarding this formular, check below link:
 *    http://www.maths.surrey.ac.uk/hosted-sites/R.Knott/Fibonacci/fibFormula.html
 *
 *
 *****************************************************************************/
