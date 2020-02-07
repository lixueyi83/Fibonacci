/*************************************************************************
 * File Name: huge_num.c
 * Author: 
 * Mail: 
 * Created Time: Thu 06 Feb 2020 09:16:41 PM PST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <assert.h>
#include "debug.h"
#include "huge_num.h"

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

void testHugeNumbers(void)
{
    testConvertNumToList();
    testAddTwoNumbers();
}
