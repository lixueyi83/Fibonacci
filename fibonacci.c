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

typedef struct ListNode
{
    int val;
    struct ListNode* next;
}ListNode;

/*****************************************************************************
 * Function: printList
 * Description: print number from least significant digit to most significant
 *              digit, in linked list format
 * Time Complexity: 
 * Space Complexity:
 */
void printList(ListNode* head)
{
    printf("\t");
    ListNode* curr = head;
    while(curr != NULL){
        printf("%d -> ", curr->val);
        curr = curr->next;
    }
    printf("null\n");
}

void printListBackward(ListNode* head)
{
    if(head == NULL) return;
    printListBackward(head->next);
    printf("%d", head->val);
}

/*****************************************************************************
 * Function: AppendDigitToList
 * Description: append digit to the end of linked list
 * Time Complexity: 
 * Space Complexity:
 */
void AppendDigitToList(ListNode** head, int digit)
{
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->val = digit;
    newNode->next = NULL;

    ListNode** localRef = head;
    while(*localRef != NULL)
        localRef = &(*localRef)->next;
    *localRef = newNode;
}

ListNode* convertNumtoList(long long num)
{
    ListNode* head = NULL;

    while(num){
        int digit = num%10;
        AppendDigitToList(&head, digit);
        num /= 10;
    };
    return head;
}

void testConvertNumToList(void)
{
    print_func_name();
    long long num = 112233445566778899;
    ListNode* head = convertNumtoList(num);
    printList(head);
    num = 111111111;
    ListNode* l1 = convertNumtoList(num);
    printList(l1);
    num = 222222222;
    ListNode* l2 = convertNumtoList(num);
    printList(l2);
    num = 333333333;
    ListNode* l3 = convertNumtoList(num);
    printList(l3);
}

/*****************************************************************************
 * Function: appendNode
 * Description: append digit to linked list, we store the digit of number
 *              backwards, for example, 12345 will be stored in linked list
 *              as: head -> 5 -> 4 -> 3 -> 2 -> 1 -> null
 * Time Complexity: 
 * Space Complexity:
 */
void appendNode(ListNode** head, int n)
{
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->val = n;
    newNode->next = NULL;

    ListNode** localRef = head;
    while(*localRef != NULL)
        localRef = &(*localRef)->next;
    *localRef = newNode;
}

/*****************************************************************************
 * Function: addTwoNumbers
 * Description: add number from l1 and l2 to a new linked list and return it
 * Time Complexity: 
 * Space Complexity:
 */
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
{ 
    if(!l1 && !l2) return NULL;
    if(l1 && !l2) return l1;
    if(!l1 && l2) return l2;
  
    ListNode* head = NULL;
    /* 1. add-merge value from l2 to l1, when both l1 and l2 are valid */
    while(l1 && l2){
        appendNode(&head, l1->val + l2->val);
        l1 = l1->next;
        l2 = l2->next;
    }
    
    /* 2. adding remain part of l2 to l1 if l2 is longer than l1, and if l1 is
     * longer l2 nothing needs to be done */
    while(l1){
        appendNode(&head, l1->val);
        l1 = l1->next;
    }

    while(l2){
        appendNode(&head, l2->val);
        l2 = l2->next;
    }

    /* 3. 2nd traverse to add carry from curr node to next node */
    ListNode* curr = head;
    while(curr->next != NULL){
        if(curr->val >= 10){
            curr->val -= 10;
            curr->next->val += 1;
        }
        curr = curr->next;
    }
    
    /* 4. handling special case for the last node only when l1 and l2 have
     * same number of nodes and also when sum of two last nodes is >= 10 */
    if(curr->val >= 10){
        curr->val -= 10;
        appendNode(&head, 1);
    }
    
    return head;
}

void testAddTwoNumbers(void)
{
    print_func_name();
    ListNode* l1 = NULL;
    ListNode* l2 = NULL;

    for(int i=0; i<20; i++){
        AppendDigitToList(&l1, 8);
        AppendDigitToList(&l2, 9);
    }
    printList(l1); printf("\n");
    printList(l2); printf("\n");

    ListNode* l3 = NULL;
    l3 = addTwoNumbers(l1, l2);
    printList(l3); 
}

/*****************************************************************************
 * Function: fib_recursive(int n)
 * Description: recursive solution, top-down
 * Time Complexity: O(2^N) 
 * Space Complexity: O(2^N)
 */
/* long long fib_recursive(ListNode* head, int n) */
long long fib_recursive(int n)
{
    if(n < 2) return n;
    return fib_recursive(n-1) + fib_recursive(n-2);
}

void test_fib_recursive(void)
{
    print_func_name();
    printf("\tfib(%d): %lld\n", NUM, fib_recursive(NUM));
    MEAS_RUNTIME(fib_recursive, NUM); 
}

/*****************************************************************************
 * Function: fib_recursive_memo(int n)
 * Description: recursive solution, top-down with memoriation
 * Time Complexity: O(N) 
 * Space Complexity: O(N)
 */
long long A[100];
long long fib_recursive_memo(int n)
{
    if(n < 2) return A[n] = n;
    if(A[n] > 0) return A[n];
    return A[n] = fib_recursive_memo(n-1) + fib_recursive_memo(n-2);
}

void test_fib_recursive_memo(void)
{
    print_func_name();
    printf("\tfib_recursive_memo(%d): %lld\n", NUM, fib_recursive_memo(NUM));
    MEAS_RUNTIME(fib_recursive_memo, NUM); 
}

/*****************************************************************************
 * Function: hugeFib_recursive(int n)
 * Description: recursion with memorization, and to deal with huge numbers that 
 *              has more than 19 digits which is maximum length of long long 
 *              storage type, we have to use some other data structures, and
 *              here we chose linked list, each node will keep one digit of
 *              the huge number and the first node is the least significant
 *              digit and last node is the most significant digit.
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
ListNode* dp[100];
ListNode* hugeFib_recursive(int n)
{
    if(dp[n] != NULL) 
        return dp[n];
    if(n<2) 
        return dp[n] = convertNumtoList(n);
    return 
        dp[n] = addTwoNumbers(hugeFib_recursive(n-1), hugeFib_recursive(n-2));
}

void testFibHuge(void)
{
    print_func_name();
    ListNode* head = hugeFib_recursive(NUM);
    printf("\tfib(%d): ", NUM); printListBackward(head);
}

/*****************************************************************************
 * Function: fibonacci(int n)
 * Description: iterative solution, dp[n] buffer used for iteration
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
long long fib_iterative(int n)
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

void test_fib_iterative(void)
{
    print_func_name();
    printf("\tfib(%d): %lld\n", NUM, fib_iterative(NUM));
    MEAS_RUNTIME(fib_iterative, NUM); 
}

/*****************************************************************************
 * main entrance
 */
int main(int argc, char* argv[])
{
    /* testConvertNumToList(); */
    /* testAddTwoNumbers(); */
    /* test_fib_recursive(); */
    /* test_fib_recursive_memo(); */
    test_fib_iterative();
    testFibHuge();

    return 0;
}
