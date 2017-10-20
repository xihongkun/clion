//
// Created by xih on 8/4/2017.
//

#include <iostream>
#include <vector>
#include <assert.h>
#include <queue>
#include <algorithm>

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

/* Search in rotated Sorted Array
 * Example, [0,1,2,4,5,6,7] might be rotated to [4,5,6,7,0,1,2]. If found return index, otherwise return -1.
 * Assume there is no duplicates in array.
 * 二分查找.
 */
int searchRotated(int A[], int n, int target) {
    int first = 0, last = n - 1;

    while (first <= last) {
        int mid = first + (last - first) / 2;
        if (A[mid] == target) return mid;

        if (A[first] < A[mid]) {    //[first, mid]是有序区
            if (target >= A[first] && target <= A[mid])
                last = mid;
            else
                first = mid + 1;
        } else {                    // [mid, last]是有序区
            if (target >= A[mid] && target <= A[last])
                first = mid;
            else
                last = mid - 1;
        }
    }
    return -1;
}

/* Find Minimum in Rotated Sorted Array 寻找旋转有序数组的最小值. 假设数组中没有重复值
 * A[start] < A[mid], 那么最小值一定在右半区间，譬如[4,5,6,7,0,1,2]，中间元素为7，7 > 4，最小元素一定在[7,0,1,2]这边，于是我们继续在这个区间查找。
 * A[start] > A[mid] ，那么最小值一定在左半区间，譬如[7,0,1,2,4,5,6]，这件元素为2，2 < 7，我们继续在[7,0,1,2]这个区间查找。
 * 注意： 1. 这里不要取start = mid + 1 或者 end = mid - 1, 因为如果mid元素是两个有序数组分界点的话，
 *          取mid+1会导致二分后的数组变成单调的数组，无法再次利用循环判断。例如第一个例子里，取mid+1的话，搜索范围会定在[0,1,2].
 *          即： 总是要保证二分后的数组还是旋转数组!!!
 *       2. 最后结束循环时, start 指向前一个数组最后一个值，end指向后一个数组的第一个元素. 因此num[end]就是最小值
 */
int findMin(int A[], int n) {
    if (A[0] < A[n - 1]) return A[0]; // 如果没有旋转

    int start = 0, end = n - 1;
    while (start != end - 1) { // 结束条件
        int mid = start + (end - start) / 2;
        if (A[start] < A[mid]) {
            start = mid;
        } else {
            end = mid;
        }
    }
    return A[end];
}
/* 允许重复元素存在. 如果遇到A[start] == A[end]的情况， start++即可， 因为前面还有重复值，不会出现丢失的问题。
 * 这里在每次while循环里，都要检测if (A[start] < A[mid])，因为跟上面没有重复值的情况不同，start++不能保证每次二分后的数组还是旋转数组。
 * */
int findMinDup(int A[], int n) {
    if (A[0] < A[n - 1])  return A[0];
    int start = 0, end = n - 1;

    while (start != end - 1) {
        if (A[start] < A[end]) return A[start];  //检查二分后的数组是否已经是单调数组
        int mid = start + (end - start) / 2;
        if (A[start] < A[mid]) start = mid;
        else if (A[start] > A[mid]) end = mid;
        else start++;
    }
    return min(A[start], A[end]);  // 返回最小值
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

/* Find kth largest element in array.
 * 方法1：用快排里的partition方法
 */
int partition(vector<int> &nums, int start, int end) {  //partition函数的复杂度为O(n)
    int pivot = nums[start];
    int i = start, j = end;

    while (i < j) {
        while (i < j && nums[j] <= pivot) j--;   //从右往左找比pivot大的，换到左边
        nums[i] = nums[j];
        while (i < j && nums[i] >= pivot) i++;   //从左往右找比pivot小的，换到右边
        nums[j] = nums[i];
    }
    // 此时i=j, 填充pivot
    nums[i] = pivot;
    return i;
}

int findKthLargest(vector<int> &nums, int k) {
    int start = 0, end = nums.size() - 1;

    int index = partition(nums, 0, end);

    while (index != k - 1) {
        if (index > k - 1) {
            end = index - 1;
            index = partition(nums, start, end);
        } else {
            start = index + 1;
            index = partition(nums, start, end);
        }
    }
    return nums[index];
}

/* /* Find kth largest element in array.
 * 方法2：最小堆(因为是最小堆，所以每次更新的时候都能把最小的元素pop出来;最后队头的元素是K个元素里最小的，也就是第K大的元素)
 */
int findKthLargest2(vector<int> &nums, int k) {
    priority_queue<int, vector<int>, greater<int>> q;
    int i = 0;
    for (; i < k; i++) {
        q.push(nums[i]);
    }

    for (; i < nums.size(); i++) {
        if (nums[i] > q.top()) {
            q.pop();
            q.push(nums[i]);
        }
    }
    return q.top();
}

/* 数组中出现次数超过一半的数字
 * 思路： 如果该数组出现次数超过一半，那么排序后位于数组中间的数字一定就是该数字。
 */
int getMoreThanHalf(vector<int> nums) {
    int start = 0, end = nums.size() - 1;
    int middle = start + (end - start) / 2;

    int index = partition(nums, start, end);
    while (index != middle) {
        if (index > middle) {
            end = index - 1;
            index = partition(nums, start, end);
        } else {
            start = index + 1;
            index = partition(nums, start, end);
        }
    }
    return nums[index];
}


/* Single Number. 一个数组中，每个元素都出现偶数次，except one. Find the single one.
 * 思路： 用异或的方法.
 */
int getSingleNumber(int A[], int n) {
    int x = 0;
    for (int i = 0; i < n; i++) {
        x ^= A[i];
    }
    return x;
}

/* Get 2 Single Numbers. 找出出现次数为一次的两个数
 * 思路： 先计算异或结果。然后根据结果中第一个1比特位的index，把数组划分为2部分。在每个部分中分别找出single number
 */
vector<int> get2SingleNumbers(int A[], int n) {
    int x = 0;
    for (int i = 0; i < n; i++) {
        x ^= A[i];
    }

    int size = sizeof(int) * 8;
    int index = 0; //记录首个1 bit出现的index
    for (; index < size; index++) {
        if ((x >> index) & 1) break;
    }

    int num1 = 0, num2 = 0; //按照index位置是否为1， 把原数组分为两部分
    for (int i = 0; i < n; i++) {
        if ((A[i] >> index) & 1) {
            num1 ^= A[i];
        } else {
            num2 ^= A[i];
        }
    }
    vector<int> result;
    result.push_back(num1);
    result.push_back(num2);
    return result;
}

/* Single Number II
 * Given an array of integers, every element appears three times except for one. Find that single one.
 */
int getSingleNumber2(int A[], int n) {
    int size = sizeof(int) * 8; // 存放int的每一位运算结果
    int W[size];
    fill_n(&W[0], size, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < size; j++) {
            W[j] += (A[i] >> j) & 1;
        }
    }
    for (int j = 0; j < size; j++) {
        W[j] %= 3;
    }

    int result = 0;
    for (int j = 0; j < size; j++) {
        result += (W[j] << j);
    }

    return result;
}


int main(){
    // 二分查找
    int size = sizeof(sortedArray)/sizeof(sortedArray[0]);
    int target = 9;
    int index = binarySearch(sortedArray, size, target);

    cout << "Index of target " << target << " is " << index << endl;

    // Search in rotated sorted Array
    int A[] = {4,5,6,7,0,1,2};
    int targetArray[4] = {5, 7, 2, 8};
    int indexResult[4];
    for (int i = 0; i < 4; i++) {
        indexResult[i] = searchRotated(A, 7, targetArray[i]);
    }
    // 旋转数组最小值
    int minRotated = findMin(A, 7);

    int A2[8] = {7,0,1,2,3,4,5,6};
    int minRotated2 = findMin(A2, 8);

    int Adup[5] = {1,0,1,1,1}, Adup2[5] = {1,1,1,0,1};
    int dupMinRotate = findMinDup(Adup, 5);
    int dupMinRotate2 = findMinDup(Adup2, 5);

    assert(indexResult[0] == 1 && indexResult[1] == 3 && indexResult[2] == 6 && indexResult[3] == -1 && minRotated == 0
           && minRotated2 == 0 && dupMinRotate == 0 && dupMinRotate2 == 0);

    // Kth largest
    vector<int> testArray = {9,3,2,4,8,0,1};
    int thirdLargest = findKthLargest(testArray, 3);
    int thirdLargest2 = findKthLargest2(testArray, 3);
    assert(thirdLargest == 4 && thirdLargest2 == 4);

    // 出现次数超过一半的数字
    vector<int> moreThanHalfArray = {4,5,2,4,2,4,4,9,4};
    int moreThanHalfInt = getMoreThanHalf(moreThanHalfArray);
    assert(moreThanHalfInt == 4);

    //Single Number
    int singleNumberArray[] = {1,2,2,3,3,4,4,4,4};
    int singleNumber = getSingleNumber(singleNumberArray, sizeof(singleNumberArray)/sizeof(singleNumberArray[0]));
    assert(singleNumber == 1);

    // Two single numbers
    int twoSingleNumberArray[] = {1,2,3,3,4,4,5,5};
    vector<int> resultSingleNumbers = get2SingleNumbers(twoSingleNumberArray, sizeof(twoSingleNumberArray)/ sizeof(twoSingleNumberArray[0]));
    cout << endl;
    for (auto i : resultSingleNumbers) {
        cout << i << " , " << endl;
    }

    // Single number 2
    int singleNumberArray2[] = {2,2,2,3,4,4,4};
    int singleNumber2 = getSingleNumber2(singleNumberArray2, sizeof(singleNumberArray2)/sizeof(singleNumberArray2[0]));
    assert(singleNumber2 == 3);

    //数字在排序数组中出现次数
    int A1[] = {1,2,3,3,3,3,4,5}, length = 8;
    int number3 = getNumberOfK(A1, length, 3);
    int number5 = getNumberOfK(A1, length, 5);
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
