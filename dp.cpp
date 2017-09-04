//
// Created by hongkun on 2017/9/4.
//

#include <iostream>
#include <vector>

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
}




