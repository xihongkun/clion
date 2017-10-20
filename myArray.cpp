//
// Created by xih on 8/3/2017.
//

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>
#include <algorithm>

using namespace std;

/* Median of Two Sorted Arrays
 * 中位数的定义是，如果一个集合有奇数2k + 1个元素，那排序后第k个数就是中位数，如果有偶数2k个元素，那么中位数的定义为排序后第k个数和第k+1个数的平均值。
 * 思路：假设A和B的长度都大于k/2，那么我们将A的第k/2个元素(即A[k/2-1])和B的第k/2个元素比较，有以下三种情况：
 * 如果A[k/2 - 1] == B[k/2 - 1]， 那么A[k/2 - 1] 即所求的第k大的元素
 * 如果A[k/2 - 1] < B[k/2 -1], 那么A的前k/2个元素可以放心的删除(A[0], A[1]...A[k/2-1]肯定在top-K的范围内)
 * 如果A[k/2 - 1] > B[k/2 -1], 那么B的前k/2个元素可以放心的删除
 */
int findKth(int A[], int m, int B[], int n, int k) {
    //always assume that m is equal or smaller than n
    // 如果 m>n, 将两个数组互换即可
    if (m > n) return findKth(B, n, A, m, k);
    // 递归终止条件1： 如果m==0, 返回 B[k-1]
    if (m == 0) return B[k-1];
    // 递归终止条件2: 如果k==1, 返回min(A[0], B[0])
    if (k == 1) return min(A[0], B[0]);

    int pa = min(k/2, m), pb = k - pa; //从A中选pa个元素的话，需要从B中选k-pa个元素
    if (A[pa - 1] == B[pb - 1]) return A[pa -1];
    if (A[pa - 1] < B[pb - 1]) {
        return findKth(A + pa, m - pa, B, n, k - pa); //注意： 删除A的前pa个元素后, 递归查找第k-pa大的元素
    } else {
        return findKth(A, m, B + pb, n - pb, k - pb);
    }
}

double findMedianSortedArrays(int A[], int m, int B[], int n) {
    int total = m + n;
    if (total & 1) {
        return findKth(A, m, B, n, total/2 + 1);
    } else {
        return (findKth(A, m, B, n, total/2) + findKth(A, m, B, n, total/2 + 1)) / 2.0;
    }
}


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

/* 数组循环右移k位 (相同的问法： Rotate an array of n elements to the right by k steps)
 *
 * 方法一： 开辟一个临时数组B, i->(i+k)%len的映射到B数组，然后再交换回来. 时间复杂度和空间复杂度均为o(n)
 * 方法二： 每次右移一位. 重复K次. 时间复杂度o(n*k), 空间复杂度o(n)
 */
void rotateArray1(int A[], int n, int k) {
    k = k % n;
    if (k == 0) return;
    int B[n];
    for (int i = 0; i < n; i++) {
        B[(i + k) % n] = A[i];
    }

    for (int j = 0; j < n; j++) {
        A[j] = B[j];
    }
}

void rotateArray2(int A[], int n, int k) {
    k = k % n;
    if (k == 0) return;

    for (int i = 1; i <= k; i++) {
        // 每次右移之前，先把最后一位保存起来
        int temp = A[n - 1];
        for (int j = n - 2; j >= 0; j--) {
            A[j + 1] = A[j];
        }
        // 保存的值赋给A[0]即可
        A[0] = temp;
    }
}

/*
int main(){
    // 两个有序数组的中位数
    int testA[] = {1,3,5,7,9}, testB[] = {2,4,6};
    double testMedian = findMedianSortedArrays(testA, 5, testB, 3);
    cout << "Median: " << testMedian << endl;

    int testA2[] = {1,3,5,7,9}, testB2[] = {2, 4};
    double testMedian2 = findMedianSortedArrays(testA2, 5, testB2, 2);
    cout << "Midian 2: " << testMedian2 << endl;

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

    // 顺时针打印矩阵
    vector<vector<int>> matrix= {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};
    vector<int> matrixClockwiseResult = clockWiseOrder(matrix);
    cout << endl;
    for (auto i : matrixClockwiseResult) cout << i << ",";
    cout << endl;
}
*/

