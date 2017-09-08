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

/* Longest Palindromic Substring
 * 思路： 设状态f(i,j)表示区间[i,j]是否为回文串，则状态转移方程为：
 * 1. 如果i==j， 则f(i,j)=true -- 对角线元素全部为true
 * 2. 如果j=i+1, 则f(i,j)=(S[i]==S[j])
 * 3. 如果j>i+1, 则f(i,j)=(S[i]==S[j] && f(i+1, j-1))
 */
string longestPalindrome(const string &s) {
    int n = s.size();
    bool f[n][n];
    fill_n(&f[0][0], n*n, false); // f[0][0]={false}在不同的编译器上可能有不同的结果。
    int max_len = 1; // 初值。任何一个字符都可以构成回文串，赋初值1
    int start = 0; //记录回文串的长度和起始位置

    for (int j = 0; j < n; j++) {
        for (int i = 0; i <= j; i++) {
            if (j == i || ( j == i + 1 && s[i] == s[j]) ||
                    (j > i + 1 && s[i] == s[j] && f[i+1][j-1])) {

                f[i][j] = true;
            }
            if (f[i][j] && (j - i + 1) > max_len) {
                max_len = j - i + 1;
                start = i;
            }
        }

    }
    return s.substr(start, max_len);
}

/* Palindrome Partitioning
 * Return all possible palindrome partitioning of s.
 */
void dfsPalindrome(string &s, vector<vector<bool>> &f, vector<string> &path, vector<vector<string>> &result, int start) {
    if (start == s.size()){
        result.push_back(path);
        return;
    }

    for (int i = start; i < s.size(); i++) {
        if (f[start][i]) {
            path.push_back(s.substr(start, i-start+1));
            dfsPalindrome(s, f, path, result, i+1);
            path.pop_back();
        }
    }
}

vector<vector<string>> partition(string s) {
    int n = s.size();
    vector<vector<bool>> f(n, vector<bool>(n, false));

    //f[i][j]表示[i,j]是否为回文串，先求f
    for (int j = 0; j < n; j++) {
        for (int i = 0; i <=j; i++) {
            if (i == j || (j == i + 1 && s[i] == s[j]) || j > i + 1 && s[i] == s[j] && f[i+1][j-1]) {
                f[i][j] = true;
            }
        }
    }

    vector<vector<string>> result;
    vector<string> path;
    dfsPalindrome(s, f, path, result, 0);
    return  result;
}

/* Palindrome Partitioning II
 * Given a string s, partition s such that every substring of the partition is a palindrome.
 * Return the minimum cuts needed for a palindrome partitioning of s.
 * For example, given s = ”aab”,
 * Return 1 since the palindrome partitioning [”aa”,”b”] could be produced using 1 cut.
 * 思路：设状态f[i,j]表示S[i,j]是否为回文串。则可以用上面一题的方法得到f矩阵的值。
 * 设count[j+1]表示区间[0,j]的最小分割, 如果[i,j]是回文串，则count[j+1] = min(count[i]+1) 0=<i<=j
 */
int minCut(const string &s) {
    int n = s.size();

    bool f[n][n]; //dp: 记录[i,j]是否为回文串
    fill_n(&f[0][0], n*n, false);

    int count[n+1]; // 状态count[i]表示[0，i-1]的最小cut数
    // count[i]的边界条件
    count[0] = -1; //
    for (int i = 1; i < n + 1; i++) {
        count[i] = i; //最差情况，每一个字符都分割
    }

    for (int j = 0; j < n; j++){
        for (int i = 0; i <= j; i++) {
            if ( i == j || ( j == i + 1 && s[i] == s[j] ) || (j > i + 1 && s[i] == s[j] && f[i+1][j-1])) {
                f[i][j] = true;
                count[j+1] = min(count[j+1], count[i] + 1);
            }
        }
    }

    return count[n];
}


/* Decode Ways
 * A message containing letters from A-Z is being encoded to numbers using the following mapping:
 * 'A' -> 1, 'B' -> 2, ... 'Z' -> 26
 * Given an encoded message containing digits, determine the total number of ways to decode it.
 * For example, Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12). The number of ways decoding "12" is 2.
 * 思路：设状态f[i]表示[0,i-1](或者理解为前i个字符)的解码方法。则状态转移方程可以通过分析[i-2,i-1]的值得出：
 * 1. 如果 10 <= [i-2,i-1] <= 26： (s[i-2] == '1 || s[i-2] == '2'')
 *    1.1 如果为10，或20， 则f[i] = f[i-2]
 *    1.2 否则，f[i] = f[i-1] + f[i-2]
 * 2. 如果 s[i-2] == '0'
 *    2.1 '00'  直接return 0
 *    2.2 '01'-'09' f[i] = f[i-1]
 * 3. 其他情况，如27-99, 则f[i] = f[i-1] (s[i-1]== 0除外)
 */
int numDecodings(const string &s) {
    if (s.empty() || s[0] == '0') return 0;
    int n = s.size();
    int f[n+1];
    fill_n(&f[0], n, 0);

    f[1] = 1; //初始状态
    f[0] = 1; //注意： f[2]的最大可能值是2.所以这里设置f[0]=1
    for (int i = 2; i < n + 1; i++) {
        if (s[i-2] == '0') {
            if (s[i-1] == '0') return 0; // 00
            f[i] = f[i-1];   // 01-09
        } else if (s[i-2] == '1') {
            if (s[i - 1] == '0') f[i] = f[i - 2]; // 10
            else f[i] = f[i - 1] + f[i - 2]; // 11-19
        } else if (s[i-2] == '2') {
            if (s[i-1] == '0') f[i] = f[i-2]; // 20
            else if (s[i-1] >= '1' && s[i-1] <= '6') f[i] = f[i-1] + f[i-2]; //21-26
            else f[i] = f[i-1]; // 27-29
        } else {
            if (s[i-1] == '0') return 0;
            f[i] = f[i-1]; //其他
        }
    }
    return f[n];
}

/* Unique paths
 * 输入矩阵的维数，How many possible unique paths are there?
 * 注意这道题与minimum path summary的区别，这道题是求路径数。
 */
int uniquePaths(int m, int n) {
    int f[m][n] = {0};
    for (int i = 0; i < m; i++) f[i][0] = 1; //第一列，只能从上往下走，任何一个节点只有一条路
    for (int j = 1; j < n; j++) f[0][j] = 1; //第一行

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            f[i][j] = f[i-1][j] + f[i][j-1];
        }
    }
    return f[m-1][n-1];
}

/* Unique paths with obstacles
 * Now consider if some obstacles are added to the grids. How many unique paths would there be?
 * An obstacle and empty space is marked as 1 and 0 respectively in the grid.
 * 注意：1. 边界的状态f[i][0]和f[0][j]
 * 2. 中间值的状态：如果S[i][j] == 1, f[i][j]直接为0；否则f[i][j] = f[i-1][j] = f[i][j-1]
 */
int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();
    int f[m][n] = {0};
    for (int i = 0; i < m; i++){
        if (obstacleGrid[i][0] == 0) f[i][0] = 1;
        else break; //直接跳出循环，因为后面的元素因为障碍的存在都不可达了
    }

    for (int j = 1; j < n; j++) {
        if (obstacleGrid[0][j] == 0) f[0][j] = 1;
        else break;
    }

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (obstacleGrid[i][j] == 1)  f[i][j] = 0;
            else f[i][j] = f[i-1][j] = f[i][j-1];
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

    // 最长回文子串
    string test = "aba12321";
    string result = longestPalindrome(test);
    cout << endl << "The longest palindrome substr in " << test << " is " << result << endl;

    // min cut
    int minCutNum = minCut(test);
    cout << endl << "Min cut number for " << test << " is " << minCutNum << endl;

    // 输出所有的回文串组合
    string s = "aab";
    vector<vector<string>> output = partition(s);
    for (auto v : output) {
        cout << "One possible cut: ";
        for (auto s: v) {
            cout << s << ",";
        }
        cout << endl;
    }

    // Decode ways
    string string1 = "1213";
    int numWays = numDecodings(string1);
    cout << endl << "Number of decoding " << string1 << " is " << numWays << endl;

    //Unique paths
    int paths = uniquePaths(3, 3); //3*3的矩阵应该有6条路径
    assert(paths == 6);
}