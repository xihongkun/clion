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

/* 顺时针打印矩阵
 */
vector<int> clockWiseOrder(vector<vector<int>> &matrix) {
    vector<int> result;
    if (matrix.empty()) return result;

    int beginX = 0, beginY = 0;
    int endX = matrix[0].size() - 1, endY = matrix.size() - 1;

    while (true) {
        for (int j = beginX; j <= endX; j++) result.push_back(matrix[beginY][j]); // 从左至右
        if (++beginY > endY) break;

        for (int i = beginY; i <= endY; i++) result.push_back(matrix[i][endX]);  // 从上至下
        if (--endX < beginX) break;

        for (int j = endX; j >= beginX; j--) result.push_back(matrix[endY][j]);  // 从右至左
        if (--endY < beginY) break;

        for (int i = endY; i >= beginY; i--) result.push_back(matrix[i][beginX]);  // 从下至上
        if (++beginX > endX) break;
    }
    return result;
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

    // 顺时针打印矩阵
    vector<vector<int>> matrix= {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};
    vector<int> matrixClockwiseResult = clockWiseOrder(matrix);
    for (auto i : matrixClockwiseResult) cout << i << ",";
    cout << endl;
}

