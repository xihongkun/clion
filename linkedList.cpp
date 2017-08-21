//
// Created by xih on 8/3/2017.
//

#include <iostream>

using namespace std;
static void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

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

    //p1 p2都遍历完毕，需要看carry的值!!!!!!
    if (carry > 0) {
        ListNode *s = new ListNode(carry);
        p->next = s;
    }
    return dummy.next;
}


/**
 * [LeetCode]78. Remove Nth Node From end of List删除链表中倒数第N个节点
 * Given a linked list, remove the nth node from the end of list and return its head. For example,
 * Given linked list: 1->2->3->4->5, and n = 2. After removing the second node from the end, the linked list becomes 1->2->3->5.
 * Note: Given n will always be valid. Try to do this in one pass.
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
 */
void deleteNode(ListNode *node) {
    ListNode *del = node->next;
    node->val = del->val;
    node->next = del->next;
    delete del;
}


/**
 * [LeetCode]88. Swap Nodes in Pairs链表成对逆序
 */
ListNode *swapPairs(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return head;

    ListNode dummy(-1);
    dummy.next = head;
    ListNode *pre = &dummy, *pcur = head, *pnext = head->next;

    while (pnext != nullptr) {
        // 逆序
        pre->next = pnext;
        pcur->next = pnext->next;
        pnext->next = pcur;

        //更新
        pre = pcur;
        pcur = pcur->next;
        pnext = pcur ? pcur->next: nullptr; // 判断pcur是否为空
    }
    return dummy.next;
}

// remove duplicate from list
// 设置两个指针curr和next指向相邻两个节点，从头往后扫描，（1）如果某次指向的两个节点值相等，则删除next指向的节点，并且next前移；
// （2）如果指向的两个节点值不一样，则两个节点都向前移动。
ListNode *removeDupFromList(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode *pcur = head;
    ListNode *pnext = head->next;

    while (pnext) {
        if (pcur->val == pnext->val) {
            ListNode *del = pnext;
            pnext = pnext->next;
            pcur->next = pnext; //不要忘记设置pcur的后继节点
            delete del;
        } else {
            pcur = pnext;
            pnext = pnext->next;
        }
    }
    return head;
}


// 合并两个有序链表
ListNode *mergeTwoSortedList(ListNode *list1, ListNode *list2) {
    if (list1 == nullptr) return list2;
    if (list2 == nullptr) return list1;

    ListNode dummy(-1);
    ListNode *p = &dummy;
    ListNode *p1 = list1, *p2 = list2;

    while (p1 != nullptr && p2 != nullptr) {
        if (p1->val < p2->val) {
            p->next = p1;
            p1 = p1->next;
        } else {
            p->next = p2;
            p2 = p2->next;
        }
        p = p->next;
    }

    if (p1 != nullptr)  p->next = p1;   //不用再跟踪p和p1了，直接链接过来就可以了
    if (p2 != nullptr)  p->next = p2;

    return dummy.next;
}

//-----------------------------链表的快速排序 -------------------------------------------------------//

// 链表快速排序 分区
ListNode *quickSortListPartition(ListNode *start, ListNode *end) {
    int pivot = start->val;

    ListNode *p = start;  //用来遍历链表的指针
    ListNode *index = start; //

    while(p != end) {
        //如果遍历到的值小于pivot, index往前走，然后index/p交换数值
        if (p->val < pivot) {
            index = index->next;
            swap(p->val, index->val);
        }
        p = p->next;
    }
    //最后 将index/start的值交换.这样, index左侧链表的值都小于pivot
    if (index != start) {
        swap(index->val, start->val);
    }
    return index;
}

// 递归函数
void quickSortList(ListNode *start, ListNode *end) {
    if (start != end && start->next != end) {   //前闭后开区间
        ListNode *index = quickSortListPartition(start, end);
        quickSortList(start, index);  //前闭后开区间
        quickSortList(index->next, end);
    }
}

//快速排序的主函数 -- 因为交换的只是节点的值，所以不会改变原链表的头指针。返回类型void即可
void quickSortListMain(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return;
    quickSortList(head, nullptr);
}

// End -----------------------------链表的快速排序 -------------------------------------------------------//

// -----------------------链表的insert sort--------------------------------------------------------------//

// 在排好序的链表里寻找插入位置
ListNode *getInsertPos(ListNode *dummyHead, int x) {
    ListNode *pcur = dummyHead->next;
    ListNode *pre = dummyHead;

    while (pcur && pcur->val <= x) {
        pre = pcur;
        pcur = pcur->next;
    }
    return pre;
}

ListNode *insertSortList(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return head;
    // 这里不要设置dummy.next=head。dummy链表是已经排好序的链表。
    // 由于往dummy链表插入的时候，对于第一个插入的元素，一定会执行pcur->next = &dummy->next(nullptr), 这样就把pcur与后面原链表的节点断开了。
    // 因此，执行上面的getInsertPos函数 总是会在排好序的链表里寻找插入位置。
    ListNode dummy(INT8_MIN);
    ListNode *pcur = head;
    while (pcur) {
        ListNode *pos = getInsertPos(&dummy, pcur->val);

        //把pcur插入到pos之后。在这之前，需要先保存pcur的下一个节点
        ListNode *temp = pcur->next;

        pcur->next = pos->next;
        pos->next = pcur;

        pcur = temp;
    }
    return dummy.next;
}

// -----------------------  End  链表的insert sort--------------------------------------------------------------//

// ----------------------- 链表的归并排序-----------------------------------------------------------------------//
ListNode *mergeSort(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return head;

    ListNode *pSlow, *pFast;
    pSlow = pFast = head;

    while (pFast->next && pFast->next->next) {
        pSlow = pSlow->next;
        pFast = pFast->next->next;
    }

    // 将链表划分为两个链表，以便进行合并
    ListNode *head1 = head;
    ListNode *head2 = pSlow->next;
    // 将链表1的结尾设为空, 断开
    pSlow->next = nullptr;

    ListNode *merged1 = mergeSort(head1);
    ListNode *merged2 = mergeSort(head2);
    ListNode *merged = mergeTwoSortedList(merged1, merged2);
    return merged;
}

// End ----------------------- 链表的归并排序-----------------------------------------------------------------------//


/**
 * [LeetCode]91. Rotate List旋转链表
 * Given a list, rotate the list to the right by k places, where k is non-negative.
 * For example: Given 1->2->3->4->5->NULL and k = 2, return 4->5->1->2->3->NULL.
 * Idea:
 * @return head pointer of the new list
 */
ListNode *rotateList(ListNode *head, int k) {
    if (head == nullptr || head->next == nullptr || k == 0) return head;
    ListNode *p = head;
    //求链表长度
    int len = 1;
    while (p->next) {
        len++;
        p = p->next;
    }

    // p指向尾节点。将他与头节点连起来，形成一个环。
    p->next = head;

    //从尾节点开始，向前走len-k步，找到需要断开的节点
    for (int i = 1; i <= len - k; i++) {
        p = p->next;
    }

    head = p->next;
    p->next = nullptr;
    return head;
}

/** [LeetCode]89. Partition List链表划分
 * Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
 * You should preserve the original relative order of the nodes in each of the two partitions.
 * For example, Given 1->4->3->2->5->2 and x = 3, return 1->2->2->4->3->5.
 * 思路： 遍历一遍链表，分别将值小于x和值大于等于x的节点分为两个链表链接起来，然后再将后者链接在前者的末尾就可以了。
*/
ListNode *partitionList(ListNode *head, int x) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode *p = head;

    ListNode leftDummy(-1);
    ListNode rightDummy(-1);

    ListNode *leftpCur = &leftDummy;
    ListNode *rightpCur = &rightDummy;

    while (p != nullptr) {
        if (p->val < x) {
            leftpCur->next = p;
            leftpCur = leftpCur->next;
        } else {
            rightpCur->next = p;
            rightpCur = rightpCur->next;
        }
        p = p->next;
    }
    leftpCur->next = rightDummy.next;
    rightpCur->next = nullptr;  //不要忘记设置右子链表的尾节点!!!
    return leftDummy.next;
}


// 求链表的中间节点.如果有偶数个节点，返回中间两个节点的第二个;如果有奇数个节点，返回唯一一个
ListNode *getListMid(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return head;

    ListNode *pSlow, *pFast;
    pSlow = pFast = head;

    while (pFast && pFast->next) { //如果要返回中间结点的第一个节点: while (pFast && pFast->next->next)
        pSlow = pSlow->next;
        pFast = pFast->next->next;
    }
    return pSlow;
}

//判断链表是否有环
bool hasCycle(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return false;

    ListNode *slow, *fast;
    slow = fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// 求链表的环入口
ListNode *listCycleEntry(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return nullptr;

    ListNode *slow, *fast;
    slow = fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) { // 有环
            ListNode *slow2 = head;
            while (slow != slow2) {
                slow = slow->next;
                slow2 = slow2->next;
            }
            return slow2;
        }
    }
    return nullptr;
}


// 求两个链表的交点. Refer: http://www.cnblogs.com/aprilcheny/p/4968190.html
ListNode *getIntersectionNode(ListNode *head1, ListNode *head2) {
    if (head1 == nullptr || head2 == nullptr) return nullptr;

    int size1 = 0; int size2 = 0;
    ListNode *p1 = head1; ListNode *p2 = head2;
    while (p1){
        size1++;
        p1 = p1->next;
    }

    while (p2) {
        size2++;
        p2 = p2->next;
    }

    p1 = head1;
    p2 = head2;
    if (size1 != size2) {
        int diff = size1 - size2;
        while (diff > 0) {
            p1 = p1->next;
            diff--;
        }

        diff = size2 - size1;
        while (diff > 0) {
            p2 = p2->next;
            diff--;
        }
    }

    while (p1 != nullptr && p2 != nullptr && p1->val != p2->val) {
        p1 = p1->next;
        p2 = p2->next;
    }

    return p1;
}

/*
int main(){
    int valArray1[] = {20, 7, 2, 5, 1, 9, 10, 6, 100};
    int valArray1Len = sizeof(valArray1)/sizeof(valArray1[0]);
    ListNode *list1 = initLinkedList(valArray1, valArray1Len);

    int valArray2[] = {2, 8, 1, 5, 12, 0, 23, 4, 6, 13};
    int valArray2Len = sizeof(valArray2)/sizeof(valArray2[0]);
    ListNode *list2 = initLinkedList(valArray2, valArray2Len);

    cout << endl << "List 1:" << endl;
    iterateLinkedList(list1);
    cout << endl << "List 2:" << endl;
    iterateLinkedList(list2);

    //寻找中间节点
    ListNode *mid = getListMid(list1);
    cout << endl << "Middle node of list1: " << mid->val << endl;

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

    // rotate list
    int valArray3[] = {2, 8, 1, 5, 12, 0, 23, 4, 6, 13};
    int valArray3Len = sizeof(valArray3)/sizeof(valArray3[0]);
    ListNode *list3 = initLinkedList(valArray3, valArray3Len);
    cout << endl << "List 3:" << endl;
    iterateLinkedList(list3);

    ListNode *rotatedList = rotateList(list3, 4);
    cout << endl << "Rotate list3 from end index 4: " << endl;
    iterateLinkedList(rotatedList);

    // 将链表分区
    ListNode *partitedList = partitionList(rotatedList, 8);
    cout << endl << "Partition list compared with 8: " << endl;
    iterateLinkedList(partitedList);

    // 将链表4进行快速排序
    int valArray4[] = {2, 8, 1, 5, 12, 0, 23, 4, 6, 13};
    int valArray4Len = sizeof(valArray4)/sizeof(valArray4[0]);
    ListNode *list4 = initLinkedList(valArray4, valArray4Len);
    quickSortListMain(list4);
    cout << endl << "Now quick sort list 4: " << endl;
    iterateLinkedList(list4);

    // 将链表5进行归并排序
    int valArray5[] = {20, 7, 2, 5, 1, 9, 10, 6, 100, 34};
    int valArray5Len = sizeof(valArray5)/sizeof(valArray5[0]);
    ListNode *list5 = initLinkedList(valArray5, valArray5Len);
    ListNode *mergeSortList5 = mergeSort(list5);
    cout << endl << "Now merge sort list 5: " << endl;
    iterateLinkedList(mergeSortList5);


    // 合并两个有序链表
    ListNode *mergedList = mergeTwoSortedList(list4, mergeSortList5);
    cout << endl << "Merge list4 and list 5: " << endl;
    iterateLinkedList(mergedList);

    // remove dup from list
    ListNode *removeDup = removeDupFromList(mergedList);
    cout << endl << "Remove dup from merged list: " << endl;
    iterateLinkedList(removeDup);

    // swap node in pairs
    ListNode *swappedList = swapPairs(mergedList);
    cout << endl << "Swap node in pairs for merged list: " << endl;
    iterateLinkedList(swappedList);

    ListNode *insertSortedList = insertSortList(swappedList);
    cout << endl << "Now re-sort the list using insertion sort: " << endl;
    iterateLinkedList(insertSortedList);


    // 构造两个相交的链表
    ListNode *a1 = new ListNode(20); ListNode *a2 = new ListNode(7); ListNode *a3 = new ListNode(2);
    ListNode *a4 = new ListNode(5); ListNode *a5 = new ListNode(1); ListNode *a6 = new ListNode(9);
    a1->next = a2; a2->next = a3; a3->next = a4;
    a4->next = a5; a5->next = a6;

    ListNode *b1 = new ListNode(1);
    ListNode *b2 = new ListNode(8);
    b1->next = b2;
    b2->next = a4;

    // 判断两个链表是否相交
    ListNode *interSectionPointer = getIntersectionNode(a1, b1);
    if (interSectionPointer != nullptr)
        cout << endl << "The intersection node of list a1 and b1 is " << interSectionPointer->val << endl;

    // 判断链表是否有环;如果有，寻找环的入口
    a6->next = a3;
    bool cycleFlag = hasCycle(a1);
    if (cycleFlag)
        cout << endl << "There is cycle in list. The cycle begins at " << listCycleEntry(a1)->val << endl;

}
*/