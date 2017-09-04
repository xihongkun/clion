//
// Created by hongkun on 2017/9/4.
//

#include <iostream>
#include <vector>
#include <unordered_set>
#include <assert.h>

using namespace std;

// 三角矩阵求最小路径和。每次都只能移动至下一行的相邻元素
// 状态转移方程： f[i][j]表示从位置[i,j] 出发到bottom的最小路径和，则f[i][j] = min (f[i+1][j], f[i+i][j+1]) + S[i][j]
int minTotal(vector<vector<int>> triangle) {
    int size = triangle.size();

    for (int i = size - 2; i >= 0; i--) {
        for (int j = 0; j < triangle[i].size(); j++)
            triangle[i][j]  += min(triangle[i+1][j], triangle[i+1][j+1]);
    }
    return triangle[0][0];
}

/* 最大连续子序列之和
 * 设状态f[i]表示以A[i]结尾的最大连续子序列的和， 则状态转移方程为：
 * f[i] = max(f[i-1]+A[i], A[i]),   0=< i <= n-1,
 * target = max(f[i])
 */
int maxSubArray(int A[], int n) {
    int f[n] = {0};
    f[0] = A[0]; // 边界
    int target = f[0]; // 每次循环都取target和f[i]中的大者.

    for (int i = 1; i < n; i++) {
        f[i] = max(f[i-1] + A[i], A[i]);
        target = max(f[i], target);
    }
    return target;
}


/* m*n 矩阵从左上角到右下角的最小路径和, 每次只能下移或者右移
 * 设f[i][j]表示从f[0][0]出发到grid[i][j]的最小路径和，则：
 * f[i][j] = min(f[i-1][j], f[i][j-1]) + grid[i][j]    1=< i <= n-1,  1=< j <= n-1,
 * target = f[m-1][n-1]
 */
int minPathSumGrid(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();
    int f[m][n] = {0};

    f[0][0] = grid[0][0]; // 边界条件
    for (int j = 1; j < n; j++)
        f[0][j] = f[0][j-1] + grid[0][j];
    for (int i = 1; i < m; i++)
        f[i][0] = f[i-1][0] + grid[i][0];

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            f[i][j] = min(f[i-1][j], f[i][j-1]) + grid[i][j];
        }
    }
    return f[m-1][n-1];
}


/* 最小编辑距离。Minimum steps to convert word1 to word2.
 * 设状态f[i][j]表示A[0,i]到B[0][j]的最小编辑距离。设A[0,i]的形式是str1c，B[0,j]的形式是str2d。
 * 1. 如果c==d, 则 f[i,j] = f[i-1][j-1]
 * 2. 如果c!=d, 则:
 * a) 把c替换成d： f[i][j] = f[i-1][j-1] + 1
 * b) c后面插入d: f[i][j] = f[i][j-1] + 1
 * c) 将c删除: f[i][j] = f[i-1][j] + 1   // 删除c后，将str1转换为str2d
 */
int minDistance(const string &word1, const string &word2) {
    int m = word1.size();
    int n = word2.size();

    // 长度为n的字符串有n+1个隔板。第一个隔板视为空字符，这样可以方便设置dp的边界值。
    // 注意，使用这种方法，f[i,j]表示的A[0, i-1] 到B[0, j-1]的编辑距离。因此，在比较字符时，要比较A[i-1]和B[j-1]
    int f[m+1][n+1] = {0};

    // 设置边界. 表示从A[o,i]转换为空字符需要的操作数
    for (int i = 0; i <= m; i++)
        f[i][0] = i;
    for (int j =0; j <= n; j++)  // 从空字符转换为B[0,j]需要的操作数
        f[0][j] = j;

    for (int i = 1; i <= m; i++){
        for (int j =1; j <= m; j++) {
            if (word1[i-1] == word2[j-1]) {
                f[i][j] = f[i-1][j-1];
            } else {
                f[i][j] = min(f[i-1][j-1], f[i][j-1]) + 1;
                f[i][j] = min(f[i][j], f[i-1][j] + 1);
            }
        }
    }

    return f[m][n]; // n+1个隔板，最大下标为n
}

/* Given a string S and a string T, count the number of distinct subsequences of T in S.
 * A subsequence of a string is a new string which is formed from the original string by deleting some (can be none)
 * of the characters without disturbing the relative positions of the remaining characters.
 * (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).
 * Here is an example: S = "rabbbit", T = "rabbit" Return 3.
 * 思路： 设f[i,j]表示 T[0,j] 在 S[0,i]中匹配到的个数。通过题目解释，还可以理解为从S[0,i]通过删除字符变换到T[0,j]有多少种方法。
 * 1. 如果T[j] == S[i], 则S[i]可以保留，也可以舍弃。f[i,j] = f[i-1, j-1] + f[i-1, j]
 * 2. 如果T[j] != S[i], 则只能舍弃S[i]. f[i, j] = f[i-1, j]
 */
int numDistinct(const string &S, const string &T) {
    int m = S.size();
    int n = T.size();

    int f[m+1][n+1]; // 多一个隔板。这样f[i,j]表示S[0, i-1] 和 T[0, j-1]的匹配
    for (int i = 0; i <= m; i++)
        f[i][0] = 1;
    for (int j = 1; j <= n; j++)
        f[0][j] = 0;

    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= n; j++) {
            if (S[i-1] == T[j-1]) {
                f[i][j] = f[i-1][j-1] + f[i-1][j];
            } else {
                f[i][j] = f[i-1][j];
            }
        }
    }
    return f[m][n];
}

/* Word Break: Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated
 * sequence of one or more dictionary words.
 * For example, given s = "leetcode", dict = ["leet", "code"].
 * Return true because "leetcode" can be segmented as "leet code".
 * 思路： 设f[i]表示S[0,i-1]是否可以分词（多一个隔板表示开头的空字符），则状态转移方程为：
 * f[i] = anyof(f[j] && S[j, i-1]}属于dict) j<i
 */
bool wordBreak(const string &s, unordered_set<string> &dict) {
    int len = s.size();

    bool f[len+1];
    f[0] = false; //空字符
    for (int i = 1; i <= len; i++) {
        for (int j = 0; j < i; j++) {
            string subStr = s.substr(j, i-j);
            if (f[j] && dict.find(subStr) != dict.end()) {
                f[i] = true;
                break;
            }
        }
    }

    return f[len];
}

int main() {
    // minimum path sum from top to bottom
    vector<vector<int>> v = {{2}, {3,4}, {6,5,7}, {4,1,8,3}};
    cout << endl << "Minimum path sum is " << minTotal(v) << endl;

    // 最大连续子序列之和
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int sizeA = sizeof(A) / sizeof(A[0]);
    cout << endl << "Max sub array sum: " << maxSubArray(A, sizeA) << endl;

    // m*n 矩阵从左上角到右下角的最小路径和
    vector<vector<int>> grid = {{1,2,3}, {4,5,6}};
    cout << endl << "Minimum path sum of grid from top-left to right-bottom is " << minPathSumGrid(grid) << endl;

    // 最小编辑距离
    int steps = minDistance("word1", "ward2");
    cout << endl << "Convert word1 to ward2 need " << steps << " steps." << endl;

    // distinct subsequence
    int num = numDistinct("rabbbit", "rabbit");
    cout << endl << "Distinct subsequence rabbit in rabbbit: " << num << endl;

    // Word break.
    unordered_set<string> dict = {"leet", "code"};
    bool result1 = wordBreak("leetcode", dict);
    bool result2 = wordBreak("letcode", dict);
    assert(result1);
    assert(!result2);
}




