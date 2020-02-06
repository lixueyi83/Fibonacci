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

/* used for testing performance of each algorithm, and the runtime will increase 
 * exponentially with recursion solution, so better start with some small number 
 * like, 20 or 30. Tested on my PC, if NUM=50, the runtime could be more than 
 * minutes. */
const int NUM = 30;


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
    ListNode* curr = head;
    while(curr != NULL){
        printf("%d -> ", curr->val);
        curr = curr->next;
    }
    printf("null\n");
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
}

/*****************************************************************************
 * Function: addTwoNumbersNew
 * Description: add/combine number from l2 to l1 and return l1
 * Time Complexity: 
 * Space Complexity:
 */
ListNode* addTwoNumbersCombine(ListNode* l1, ListNode* l2) 
{
    ListNode* head = l1;
    
    /* 1. add-merge value from l2 to l1, when both l1 and l2 are valid */
    ListNode *prev = NULL, *prev2 = NULL;
    while(l1 && l2){
        l1->val += l2->val;
        /* keep track of previous node which will be used to connect remain
         * part of l2 */
        prev = l1, prev2 = l2;
        l1 = l1->next;
        l2 = l2->next;
    }
    
    /* 2. adding remain part of l2 to l1 if l2 is longer than l1, and if l1 is
     * longer l2 nothing needs to be done */
    if(l1 == NULL){
        prev->next = l2;
    }
    
    /* 3. 2nd traverse to add carry from curr node to next node */
    ListNode* curr = head;
    prev = NULL;
    while(curr->next!= NULL){
        if(curr->val >= 10){
            curr->next->val += 1;
            curr->val -= 10;
        }
        curr = curr->next;
    }
    
    /* 4. handling special case for the last node only when l1 and l2 have
     * same number of nodes and also when sum of two last nodes is >= 10 */
    if(curr->val >= 10){
        curr->val -= 10;
        ListNode* node = (ListNode*)malloc(sizeof(ListNode));
        node->val = 1;
        node->next = NULL;
        curr->next = node;
    }
    
    return head;
}

/*****************************************************************************
 * Function: addTwoNumbersNew
 * Description: add number from l1 and l2 to a new linked list and return it
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

ListNode* addTwoNumbersNew(ListNode* l1, ListNode* l2) 
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

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
    return addTwoNumbersNew(l1, l2);
    return addTwoNumbersCombine(l1, l2);
}
void testAddTwoNumbers(void)
{
    testConvertNumToList();

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
long long A[10];
long long fib_recursive_memo(int n)
{
    if(n < 2) return A[n] = n;
    if(A[n] > 0) return A[n];
    return A[n] = fib_recursive_memo(n-1) + fib_recursive_memo(n-2);
}

void test_fib_recursive_memo(void)
{
    print_func_name();
    printf("\tfib(%d): %lld\n", NUM, fib_recursive_memo(NUM));
    MEAS_RUNTIME(fib_recursive_memo, NUM); 
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
    print_func_name();
    printf("\tfib(%d): %lld\n", NUM, fib_iterative(NUM));
    MEAS_RUNTIME(fib_iterative, NUM); 
}

/*****************************************************************************/
ListNode* dp[100];

ListNode* fib(int n)
{
    if(dp[n] != NULL) return dp[n];

    if(n<2) return dp[n] = convertNumtoList(n);

    /* dp[n] = addTwoNumbers(fib(n-1), fib(n-2)); */
    /* printList(dp[n]); */
    ListNode* l1 = fib(n-1); printList(l1);
    ListNode* l2 = fib(n-2); printList(l2);
    addTwoNumbersNew(l1, l2);

    return dp[n];
}

void testFib(void)
{
    print_func_name();
    ListNode* head = fib(4);

    printf("\n\n");
    for(int i=0; i<5; i++)
        printList(head);
}

/*****************************************************************************
 * main entrance
 */
int main(int argc, char* argv[])
{
    testAddTwoNumbers();
    /* test_fib_recursive(); */
    /* test_fib_recursive_memo(); */
    /* test_fib_iterative(); */
    /* testFib(); */

    return 0;
}
