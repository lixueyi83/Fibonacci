/*************************************************************************
 * File Name: huge_num.h
 * Author: 
 * Mail: 
 * Created Time: Thu 06 Feb 2020 09:16:56 PM PST
 ************************************************************************/
#ifndef PROJECT_PATH_HUGE_NUM_H
#define PROJECT_PATH_HUGE_NUM_H

/*****************************************************************************
 * ListNode data structure for storing the digits of a number, and the number
 * can be a very huge number that the built-in storage data type can not hold
 */
typedef struct ListNode
{
    int val;
    struct ListNode* next;
}ListNode;


void printList(ListNode* head);
void printListBackward(ListNode* head);
void AppendDigitToList(ListNode** head, int digit);
void appendNode(ListNode** head, int n);
ListNode* convertNumtoList(long long num);
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
void testHugeNumbers(void);

#endif
