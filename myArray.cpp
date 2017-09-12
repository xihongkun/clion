//
// Created by xih on 8/3/2017.
//

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>
#include <algorithm>

using namespace std;

/* Remove Element.
 * Given an array and a value, remove all instances of the value in place and return the new length.
 */
int removeElement(int A[], int n, int elem) {
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (A[i] != elem) {
            A[index] = A[i];
            index++;
        }
    }
    return index;
}

/* Remove duplicates from Sorted Array
 * Example: Given A = [1,1,2], return length = 2, and A is now [1,2]
 * 思路： 类似链表删除duplicates，设置两个指针，如果相等，前面指针往前走；否则，两个都往前走.
 * 注意：由于数组删除中间元素的操作比较麻烦，我们可以直接移动元素，而不删除该元素。
 */
 int removeDup(int A[], int n) {
    if (n == 0) return 0;
    int index = 0;
    for (int i = 1; i < n; i++) {
        if (A[i] != A[index]) {
            index++;
            A[index] = A[i];
        }
    }
    return index + 1;
}

/* Remove dup 2 -- Duplicates are allowed at most twice.
 * 思路： 使用index记录新的A数组的下一个位置，使用i扫描原始A数组。
 * 如果i扫描到的当前元素在index之前已经存在两个，那么i继续前进；否则将i指向的元素放入index，index与i一起前进。
 */
int removeDup2(int A[], int n) {
    if (n < 3) return n;
    int index = 2; // “新"数组下一个位置

    for (int i = 2; i < n; i++) {
        if (A[i] != A[index-2]) {
            A[index] = A[i];
            index++;
        }
    }
    return index;
}

// Two sums. 返回下标
vector<int> two_sums(vector<int> nums, int target) {
    unordered_map<int, int> mapping;
    vector<int> result;
    for (int j=0; j<nums.size(); j++){
        const int gap = target - nums[j];

        if (mapping.find(gap) != mapping.end()) {

            result.push_back(mapping[gap]);
            result.push_back(j);
            return result;
        }

        else {
            mapping[nums[j]] = j;
        }
    }
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

/* Longest Consecutive Sequence
 * Given {100, 4, 200, 1, 3, 2}, the longest consecutive sequence is [1,2,3,4], return length as 4
 * 用一个哈希，表示该数字是否已经访问过。如果没有访问过，以该数字为中心，往两扩张，直到该数字不属于原数组。
 */
int longestConsecutive(vector<int> &num) {
    unordered_map<int, bool> visited;
    for (auto i: num)  visited[i] = false;

    int longest = 0;

    for (auto i : num) {
        if (visited[i]) continue;

        int length = 1; //每轮开始， 设length = 1；
        visited[i] = true;
        for (int j = i + 1; find(num.begin(), num.end(), j) != num.end(); j++) { // include <algorithm> to make 'find' usable
            length++;
            visited[j] = true;
        }

        for (int k = i -1; find(num.begin(), num.end(), k) != num.end(); k--) {
            length++;
            visited[k] = true;
        }
        longest = max(longest, length);
    }
    return longest;
}

/* 3Sum which equals a target. Find all unique triplets which sums zero.(a+b+c=0)
 * 注意这道题与dfs题目里找所有和为target的combination区别：本题限定三个数的sum为target
 * 思路： 先排序!!!!! 然后左右夹逼
 */
vector<vector<int>> threeSum(vector<int> &num) {
    vector<vector<int>> result;

    if (num.size() < 3) return result;

    sort(num.begin(), num.end()); //一定要先排序!!!!
    int n = num.size();
    int target = 0; //这里target可以换成任何值

    for (int i = 0; i < n -2; i++) {
        int j = i + 1;
        int k = n - 1;

        while (j < k) {
            if (num[i] + num[j] + num[k] < target) {
                j++;
            } else if (num[i] + num[j] + num[k] > target) {
                k--;
            } else {
                result.push_back({num[i], num[j], num[k]});
                j++;
                k--;    //不要忘了，将j k同时改变
            }
        }
    }
    return result;
}

/* Find kth largest element in array.
 */
int partition(vector<int> &nums, int low, int high) {
    int pivot = nums[low];
    int i = low, j = high;

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

int select (vector<int> &nums, int low, int high, int k) {
    if (low == high) return nums[low];

    int pos = partition(nums, low, high);
    if (pos == k - 1) return nums[pos];
    if (pos > k - 1) return select(nums, low, pos - 1, k);
    if (pos < k - 1) return select(nums, pos + 1, high, k);
}

int findKthLargest(vector<int>& nums, int k) {
    return select(nums, 0, nums.size() - 1, k);
}


int main(){
    // remove elements.
    int elementArray[] = {1,2,1,1,4,5,6,2};
    int afterRemovedLength = removeElement(elementArray, 8, 1);
    assert(afterRemovedLength == 5);

    // Two sum
    vector<int> nums = {3,2,4};
    int target = 6;
    vector<int> result = two_sums(nums, target);
    for (int i=0; i<result.size(); i++)
        cout << result[i];

    // Search in rotated sorted Array
    int A[] = {4,5,6,7,0,1,2};
    int targetArray[4] = {5, 7, 2, 8};
    int indexResult[4];
    for (int i = 0; i < 4; i++) {
        indexResult[i] = searchRotated(A, 7, targetArray[i]);
    }
    assert(indexResult[0] == 1 && indexResult[1] == 3 && indexResult[2] == 6 && indexResult[3] == -1);

    // longest consecutive sequence
    vector<int> num = {100,4,200,1,3,2};
    int length = longestConsecutive(num);
    assert(length == 4);

    // 3 Sum
    vector<int> test = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> result3sum = threeSum(test);
    for (auto answer : result3sum) {
        cout << endl << "One solution set: ";
        for (auto i : answer) {
            cout << i << ",";
        }
    }

    // Kth largest
    vector<int> testArray = {9,3,2,4,8};
    int thirdLargest = findKthLargest(testArray, 3);
    assert(thirdLargest == 4);
}

