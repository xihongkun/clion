//
// Created by xih on 8/3/2017.
//

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* initLinkedList(int valArray[], int size) {
    ListNode dummy(-1);
    ListNode *p = &dummy;
    for (int i=0; i<size; i++){
        ListNode *s = new ListNode(valArray[i]);
        p->next = s;
        p = s;
    }
    return dummy.next;
}

void iterateLinkedList(ListNode *head){
    ListNode *p = head;
    while(p){
        cout << p->val << " ";
        p = p->next;
    }
}


// 反转链表
ListNode* reverseList(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode *pCur = head;
    ListNode *pre = nullptr;
    ListNode *rHead = nullptr; //反转后新链表的头节点

    while (pCur != nullptr) {
        if (pCur->next == nullptr) {
            rHead = pCur;
        }

        //在pCur->next = pre 之前，需要保存下一个节点。否则以后用pCur = pCur->next 往后移的时候， 找不到下一个节点。
        ListNode *pNext = pCur->next;

        pCur->next = pre; //指向前驱节点
        //断链了，需要保存当前节点至pre
        pre = pCur;
        pCur = pNext;
    }
    return rHead;
}

/**
 * [LeetCode]90. Reverse Linked List II链表局部反转 Refer: http://www.jianshu.com/p/2e082ab35446
 * Reverse a linked list from position m to n. Do it in-place and in one-pass.
 * For example:
 * Given 1->2->3->4->5->NULL, m = 2 and n = 4, return 1->4->3->2->5->NULL.
 * Note: Given m, n satisfy the following condition: 1 ≤ m ≤ n ≤ length of list.
 * @param head
 * @param m
 * @param n
 * @return
 */

ListNode* reverseBetween(ListNode* head, int m, int n) {
    if (head == nullptr || head->next == nullptr ||  m == n ) return head;
    ListNode dummy(-1);
    dummy.next = head;
    ListNode *pre = &dummy;

    for (int i=1; i < m; i ++) {
        pre = pre->next;
    }

    ListNode *head2 = pre; //head2作为反转部分的头节点，每次反转都用头插法往head2后面插入
    ListNode *pCur = pre->next;

    // 每次将pCur之后的节点（move）移动到head2之后的节点，重复n-m次
    for (int j = m; j < n; j++) {
        ListNode *move = pCur->next;
        // pCur 指向move的下一个节点。这样在下一次循环的时候会用上面的语句 更新move
        pCur->next = move->next;
        //头插法
        move->next = head2->next;
        head2->next = move;
    }

    return dummy.next;
}

// 反转list的前m个元素
ListNode *reverseFrontM(ListNode *head, int m) {
    if (head == nullptr || head->next == nullptr || m == 1) return head;
    ListNode dummyHead(-1);
    dummyHead.next = head;

    ListNode *pCur = head;
    for (int i = 1; i < m; i++) {
        ListNode *move = pCur->next;
        pCur->next = move->next;

        //头插法
        move->next = dummyHead.next;
        dummyHead.next = move;
    }
    return dummyHead.next;
}

//两个链表逐位相加
ListNode* addTwoList(ListNode *list1, ListNode *list2) {
    ListNode *p1 = list1;
    ListNode *p2 = list2;

    ListNode dummy(-1);
    ListNode *p = &dummy;

    int carry = 0; //进位
    int val1, val2;
    while(p1 || p2) {

        val1 = 0;
        if (p1) {
            val1 = p1->val;
            p1 = p1->next;
        }

        val2 = 0;
        if (p2) {
            val2 = p2->val;
            p2 = p2->next;
        }

        int temp = val1 + val2 + carry;
        carry = temp/10;
        ListNode *s = new ListNode(temp%10);
        p->next = s;
        p = s;
    }
    return dummy.next;
}


/**
 * [LeetCode]78. Remove Nth Node From end of List删除链表中倒数第N个节点
 * Given a linked list, remove the nth node from the end of list and return its head. For example,
 * Given linked list: 1->2->3->4->5, and n = 2. After removing the second node from the end, the linked list becomes 1->2->3->5.
 * Note: Given n will always be valid. Try to do this in one pass.
 * @param head
 * @param n
 * @return head pointer of linked list
 */

// 方法1： 先求链表的长度，然后找到要删除的节点
ListNode *removeNthFromEnd(ListNode *head, int n) {
    if (head == nullptr) return head;
    ListNode dummy(-1);
    dummy.next = head;
    ListNode *p = &dummy;

    ListNode *temp = p->next;
    int len = 0;
    while (temp != nullptr) {
        len++;
        temp = temp->next;
    }

    for (int i = 0; i < len - n; i++) {   //只用一个前驱即可找到要删除的节点。不必用pre和del两个指针来跟踪
        p = p->next;
    }
    ListNode *del = p->next;
    p->next = del->next;
    delete del;

    return dummy.next;
}


//方法2：设置两个指针p q, q先走n步，然后p q一块走，这样当q走到链表尾的时候，由于p落后q n步，p指向的节点既是要删除的节点
ListNode *removeNthFromEnd2(ListNode *head, int n) {
    ListNode dummy(-1);
    dummy.next = head;

    ListNode *p = &dummy, *q = &dummy;
    //q先走n步
    for (int i = 0; i < n; i++) {
        q = q->next;
    }

    // p和q一块走，直到q->next为空. 注意： 由于我们要找的是删除节点的前一个节点，所以判断条件是q->next不为空。
    while (q->next != nullptr) {
        p = p->next;
        q = q->next;
    }

    ListNode *del = p->next;
    p->next = del->next;
    delete del;

    return dummy.next;
}

/**
 * [LeetCode]79. Delete Node in a Linked List删除链表节点
 * Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.
 * http://www.cnblogs.com/aprilcheny/p/4964895.html
 * Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are given the third node with value 3,
 * the linked list should become 1 -> 2 -> 4 after calling your function.
 * @param node: the node to be removed
 */
void deleteNode(ListNode *node) {
    ListNode *del = node->next;
    node->val = del->val;
    node->next = del->next;
    delete del;
}


int main(){
    int valArray1[] = {20, 7, 2, 5, 1, 9, 10, 6, 100, 34};
    int valArray1Len = sizeof(valArray1)/sizeof(valArray1[0]);
    ListNode *list1 = initLinkedList(valArray1, valArray1Len);

    int valArray2[] = {2, 8, 1, 5, 12, 0, 23, 4, 6, 13};
    int valArray2Len = sizeof(valArray2)/sizeof(valArray2[0]);
    ListNode *list2 = initLinkedList(valArray2, valArray2Len);

    cout << endl << "List 1:" << endl;
    iterateLinkedList(list1);
    cout << endl << "List 2:" << endl;
    iterateLinkedList(list2);

    // 删除某个节点
    //deleteNode(list1->next);
    //cout << "After removing 2nd element from List 1:" << endl;
    //iterateLinkedList(list1);

    // 链表逐位相加
    ListNode *addedList = addTwoList(list1, list2);
    cout << endl << "Adding List 1 and List 2:" << endl;
    iterateLinkedList(addedList);

    // 反转链表
    ListNode *list1Reverse = reverseList(list1);
    cout << endl << "Reverse List 1: " << endl;
    iterateLinkedList(list1Reverse);

    // 反转链表的m-n个元素
    cout << endl << "Reverse list1Reverse from index 2 to index 5: " << endl;
    ListNode* list1ReverseBetween = reverseBetween(list1Reverse, 2, 5);
    iterateLinkedList(list1ReverseBetween);

    // 反转链表的前m个元素
    ListNode *list2Reverse = reverseFrontM(list2, 4);
    cout << endl << "Reverse front 4 elements for List 2: " << endl;
    iterateLinkedList(list2Reverse);

    // 删除链表的倒数第n个元素
    ListNode *removeNthfromEndOflist = removeNthFromEnd(list2Reverse, 4);
    cout << endl << "Remove 4th from end of list2Reverse: " << endl;
    iterateLinkedList(removeNthfromEndOflist);

    // 删除链表的倒数第n个元素, 方法2
    ListNode *removeNthfromEnd2Oflist = removeNthFromEnd2(removeNthfromEndOflist, 4);
    cout << endl << "Remove 4th from end of list2Reverse: " << endl;
    iterateLinkedList(removeNthfromEnd2Oflist);
}