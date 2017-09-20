//
// Created by xih on 8/4/2017.
//

#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

const int sortedArray[] = {1,3,4,6,8,9,12};

// 二分查找，非递归
int binarySearch(const int A[], int n, int value){
    int first = 0;
    int last = n-1;

    while (first <= last) {
        int mid = (first+last)/2;
        if (value == A[mid]) return mid;
        if (value > A[mid]) {
            first = mid + 1;
        }
        else if (value < A[mid]) {
            last = mid - 1;
        }
    }

    return -1;
}

/* 数字在排序数组中出现的次数
 * 如：输入{1,2,3,3,3,3,4,5}和数字3，输出4
 */
int getFirstK(const int A[], int n, int k) {
    int start = 0;
    int end = n - 1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (A[mid] == k) {
            if( (mid > 0 && A[mid - 1] != k) || mid == 0) return mid;
            else end = mid - 1;
        } else if (A[mid] > k) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }

    return -1;
}

int getLastK(const int A[], int n, int k) {
    int start = 0, end = n - 1;
    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (A[mid] == k) {
            if ( (mid < n - 1 && A[mid + 1] !=k) || mid == n - 1) return mid;
            else start = mid + 1;
        } else if (A[mid] > k) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }

    return -1;
}

int getNumberOfK(const int A[], int length, int k) {
    int number = 0;
    int first = getFirstK(A, length, k);
    int last = getLastK(A, length, k);

    if (first != -1 && last != -1) number = last - first + 1;
    return number;
}

/* 0~n-1中缺失的数字。递增排序数组，且没有重复值。求缺失的那个数字
 */
int getMissingNumber(const int A[], int n) {
    int start = 0, end = n - 1;
    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (A[mid] == mid) {
            start = mid + 1; // 数字与下标一样，则缺失的数字一定在右半边
        } else {
            if ((mid > 0 && A[mid - 1] == mid - 1) || mid == 0) return mid; //数字与下标不一致，但是前一个元素一致。已经找到
            else end = mid - 1; //否则，说明还在左边。继续找
        }
    }
    return -1;
}

/*数组中数值和下标相等的数字。 -- 单调递增且没有重复值的数组里，找出数值和下标相等的数字。
 */
int getNumberSameAsIndex(const int A[], int n) {
    if (A == nullptr || n <= 0) return -1;
    int start = 0, end = n - 1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (A[mid] == mid) return mid;
        else if (A[mid] > mid) {  //如果A[i]>i,由于数组单调增且没有重复值，则必有A[i+k]>=A[i]+k>i+k, 即后面的数字也大于下标
            end = mid - 1;
        } else {   //同理，如果A[i]<i, 则前面的数字也一样
            start = mid + 1;
        }
    }
    return -1;
}

/*
int main(){
    // 二分查找
    int size = sizeof(sortedArray)/sizeof(sortedArray[0]);
    int target = 9;
    int index = binarySearch(sortedArray, size, target);

    cout << "Index of target " << target << " is " << index << endl;

    //数字在排序数组中出现次数
    int A[] = {1,2,3,3,3,3,4,5}, length = 8;
    int number3 = getNumberOfK(A, length, 3);
    int number5 = getNumberOfK(A, length, 5);
    assert(number3 == 4 && number5 == 1);

    //缺失的数字
    int B[] = {0,1,2,3,4,6,7,8};
    int missingNumber = getMissingNumber(B,8);
    assert(missingNumber == 5);

    //下标和数值相等的元素
    int C[] = {-3, -1, 1, 3, 5};
    int number = getNumberSameAsIndex(C, 5);
    assert(number == 3);
}
*/
