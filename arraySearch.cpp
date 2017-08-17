//
// Created by xih on 8/4/2017.
//

#include <iostream>
using namespace std;

const int sortedArray[] = {1,3,4,6,8,9,12};

// 二分查找，非递归
int binarySearch(const int A[], int n, int value){
    int first = 0;
    int last = n-1;
    int mid = (first+last)/2;

    while (first <= last) {
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

/**
int main(){
    int size = sizeof(sortedArray)/sizeof(sortedArray[0]);
    int target = 6;
    int index = binarySearch(sortedArray, size, target);

    cout << "Index of target " << target << " is " << index << endl;
}
*/