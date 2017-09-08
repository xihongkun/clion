//
// Created by hongkun on 2017/9/6.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* Permutations.
 * Given a collection of numbers, return all possible permutations. You may assume there is no duplicates.
 */
void dfsPermute(vector<int> &num, vector<int> &path, vector<vector<int>> &result, bool visited[]) { //visited数组名即是指针，不用引用传递
    if (path.size() == num.size()) {
        result.push_back(path);
        return;
    }

    for (int i = 0; i < num.size(); i++) {
        if (!visited[i]) {
            visited[i] = true;
            path.push_back(num[i]); // 扩展状态
            dfsPermute(num, path, result, visited);

            visited[i] = false;
            path.pop_back(); // 恢复状态
        }
    }
}

vector<vector<int>> permute(vector<int> &num) {
    sort(num.begin(), num.end());
    vector<int> path; //存放中间结果
    vector<vector<int>> result; //存放最终结果

    bool visited[num.size()]; // 保存num[i]是否在当前的path中出现过
    fill_n(&visited[0], num.size(), false);

    dfsPermute(num, path, result, visited);
    return result;
}


/* Permutations II. There is duplicates in input vector<int>.
 * Return all possible unique permutations.
 * 思路：跟上面类似，唯一不同的地方是需要在每一次新的路径开始时，判断当前元素跟前面元素是否相等，即path是否重复；
 * 如果相等，并且visited[i-1] == false(表示前面的path已经结束了，当前是一条新的path)，则跳过该次递归。
 */
void dfsPermuteUnique(vector<int> &num, vector<int> &path, vector<vector<int>> &result, bool visited[]) {
    if (path.size() == num.size()) {
        result.push_back(path);
        return;
    }

    for (int i = 0; i < num.size(); i++) {
        if (i > 0 && num[i] == num[i-1] && !visited[i-1]) continue;
        if (!visited[i]) {
            visited[i] = true;
            path.push_back(num[i]); // 扩展状态
            dfsPermuteUnique(num, path, result, visited);
            visited[i] = false;
            path.pop_back(); // 恢复状态
        }
    }
}

vector<vector<int>> permuteUnique(vector<int> &num) {
    sort(num.begin(), num.end()); // 一定要先排序！否则递归里面的num[i] == num[i-1]不成立
    vector<int> path; //中间结果
    vector<vector<int>> result; //最终结果

    bool visited[num.size()];
    fill_n(&visited[0], num.size(), false); //num[i]是否被访问过

    dfsPermuteUnique(num, path, result, visited);
    return result;
}

/* Next Permutations。 例如，given [6,8,7,4,3,2], 输出[7,2,3,4,6,8]
 * Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
 * If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).
 * The replacement must be in-place, do not allocate extra memory.
 * 思路：1. 从右向左，找到第一个打破升序排列的元素，称之为partitionNum
 * 2. 从右向左， 找到第一个大于partitionNumber的元素，称之为changeNum
 * 3. 交换partitionNum 和 changeNum
 * 4. reverse(partitionIndex+1, end)
 */
void mySwap(int &a, int &b) {
    int temp = a;
    a = b;
    b= temp;
}

bool nextPermutation(vector<int> &num) { //如果找到下一个排列，返回true；否则返回false
    int n = num.size();

    int i = n - 2; // partition Index.
    while (i>=0 && num[i] >= num[i+1]) i--;
    if (i == -1) { ////全部降序排列，已经是最后一个排列了。按题目要求，re-arrange it as the lowest order.
        reverse(num.begin(), num.end());
        return false;
    }

    int j = n - 1; // changeNum Index
    while (j>=0 && num[j] <= num[i]) j--;

    mySwap(num[i], num[j]);
    reverse(num.begin()+i+1, num.end());

    return true;
}


/* Subsets.
 * Given a set of distinct integers, S, return all possible subsets.
 * Note: 1. Elements in a subset must be in non-descending order. 2. The solution set must not contain duplicate subsets.
 * 思路：DFS.对于每个元素，先一条路走到黑，然后换下一个元素. 例如对：[1,2,3]，
 * 首先选取1进入path， 则一条路走到黑：[1], [1,2],[1,2,3]
 *                                    [1,3]
 *                               [2], [2,3]
 *                               [3]
 * 即每一层i的节点数为i.
 */
void dfsSubnets(vector<int> &S, vector<int> &path, vector<vector<int>> &result, int start) {
    result.push_back(path);
    for (int i = start; i < S.size(); i++) { //收敛条件由start控制
        path.push_back(S[i]);
        dfsSubnets(S, path, result, i + 1); // 注意：是i+1，不是start+1 !!!
        path.pop_back();
    }
}

vector<vector<int>> subsets(vector<int> &S) {
    sort(S.begin(), S.end()); //先排序
    vector<int> path;
    vector<vector<int>> result;

    dfsSubnets(S, path, result, 0);
    return result;
}


/* Subsets with duplicates. 把上题改成有重复值存在， 如[1,1,2]
 * 思路：观察上面的递归，发现当i>start时,必然是下一层递归返回，开始选取下一个元素时。此时，如果s[i]==s[i-1]则跳出该次递归。
 */
void dfsSubsetWithDup(vector<int> &S, vector<int> &path, vector<vector<int>> &result, int start) {
    result.push_back(path);

    for (int i = start; i < S.size(); i++) {
        if (i > start && S[i] == S[i-1]) continue; //重复元素，跳过该层递归
        path.push_back(S[i]);
        dfsSubsetWithDup(S, path, result, i+1);
        path.pop_back();
    }
}

vector<vector<int>> subsetsWithDup(vector<int> &S) {
    sort(S.begin(), S.end());
    vector<int> path;
    vector<vector<int>> result;

    dfsSubsetWithDup(S, path, result, 0);
    return  result;
}

/*
int main() {
    // Permutations
    vector<int> v = {1,2,3,4};
    vector<vector<int>> p = permute(v);
    cout << endl << "Total number of permustaions: " << p.size() << endl;
    for (auto s : p) {
        cout << "One possible permutation: ";
        for (auto i: s) {
            cout << i << ",";
        }
        cout << endl;
    }

    // unique permutations
    vector<int> dupV = {1,1,2,2};
    vector<vector<int>> dupP = permuteUnique(dupV);
    cout << endl << "Total number of permustaions: " << dupP.size() << endl;

    for (auto s : dupP) {
        cout << "One possible permutation: ";
        for (auto i : s) {
            cout << i << ",";
        }
        cout << endl;
    }

    //next permutation
    vector<int> num = {6,8,7,4,3,2}, num1 = {5,4,3,2,1};
    nextPermutation(num);
    nextPermutation(num1);
    cout << endl << "Next permutation is " ;
    for (auto i : num)  cout << i << ",";
    cout << endl;

    for (auto j : num1) cout << j << ",";
    cout << endl;

    // Subsets
    vector<int> set = {1,2,3};
    vector<vector<int>> allSubsets = subsets(set);
    for (auto s : allSubsets) {
        cout << endl << "One subset: ";
        for (auto i: s) {
            cout << i << ",";
        }
    }

    // Subsets with duplicates
    vector<int> set2 = {1,1,2};
    vector<vector<int>> allSubsets2 = subsetsWithDup(set2);
    for (auto s : allSubsets2) {
        cout << endl << "One subset: ";
        for (auto i: s) {
            cout << i << ",";
        }
    }
}
*/