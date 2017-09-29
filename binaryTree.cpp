//
// Created by xih on 8/10/2017.
//
#include <iostream>
#include <queue>
#include <stack>
#include <assert.h>

using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    TreeNode(int x): val(x), left(nullptr), right(nullptr), parent(nullptr) {}
};

void visit(TreeNode *p){
    cout << p->val << " ";
}

//前序遍历 递归
void preOrder(TreeNode *root){
    if(root != nullptr){
        visit(root);
        preOrder(root->left);
        preOrder(root->right);
    }
}

//前序遍历 非递归
void preOrder2(TreeNode *root){
    TreeNode *p = root;
    stack<TreeNode *> s;

    while (p != nullptr || !s.empty()) {
        while (p != nullptr) {
            visit(p);
            s.push(p);
            p = p->left;
        }

        if (!s.empty()) {
            p = s.top();
            s.pop();
            p = p->right;
        }
    }
}

//中序遍历 递归
void inOrder(TreeNode *root) {
    if (root != nullptr){
        inOrder(root->left);
        visit(root);
        inOrder(root->right);
    }
}

//中序遍历 非递归
void inOrder2(TreeNode *root) {
    stack <TreeNode *> s;
    TreeNode *p = root;

    while (p != nullptr || !s.empty()) {
        while (p != nullptr) {
            s.push(p);
            p = p->left;
        }

        if (!s.empty()) {
            p = s.top();
            s.pop();
            visit(p);
            p = p->right;
        }
    }
}

//后序遍历 递归
void postOrder(TreeNode *root) {
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        visit(root);
    }
}

//后序遍历 非递归
void postOrder2(TreeNode *root) {
    stack<TreeNode *> s;
    TreeNode *p = root;
    TreeNode *pLastVisit = nullptr;

    while (p != nullptr) {
        s.push(p);
        p = p->left;
    }

    while (!s.empty()) {
        p = s.top();
        s.pop();

        if (p->right == nullptr || p->right == pLastVisit) {
            visit(p);
            pLastVisit = p;
        }
        else {
            s.push(p);

            p = p->right;
            while (p != nullptr) {
                s.push(p);
                p = p->left;
            }
        }
    }
}


//层序遍历 亦即广度遍历 BFS
void levelOrder(TreeNode *root) {
    TreeNode *p = root;
    queue<TreeNode *> que;

    if (p != nullptr) {
        que.push(p);
    }

    while (!que.empty()) {
        p = que.front();
        que.pop();

        visit(p);

        if (p->left != nullptr)
            que.push(p->left);
        if (p->right != nullptr)
            que.push(p->right);
    }
}

//求二叉树的最大高度 -- 递归方法
int maxDepthOfBT(TreeNode *root) {
    if (root == nullptr) return 0;
    return 1 + max(maxDepthOfBT(root->left), maxDepthOfBT(root->right));
}

//求二叉树的最大深度 -- 非递归
int maxDepthOfBT2(TreeNode *root) {
    if (root == nullptr) return 0;

    queue<TreeNode *> que;
    TreeNode *p = root;

    que.push(p);
    int depth = 0;
    int curLayerNum = 1;

    while (!que.empty()) {
        p = que.front();
        que.pop();
        visit(p); //顺便打印
        curLayerNum--;
        if (p->left) {
            que.push(p->left);
        }

        if (p->right) {
            que.push(p->right);
        }

        if (curLayerNum == 0) {
            cout << endl; //每一层遍历完后，换行输出
            depth++;
            curLayerNum = que.size();
        }
    }

    return depth;
}

// 由preorder序列和inorder序列重建树
TreeNode *buildTree(vector<int> &preorder, int pBegin, int pEnd, vector<int> &inorder, int iBegin, int iEnd) {
    // preorder的pBegin指向的是当前的root节点，首先在inorder序列里找到该节点
    if (pBegin > pEnd || iBegin > iEnd)  //递归结束条件
        return nullptr;

    int i = 0;
    while (i < inorder.size() && inorder[i] != preorder[pBegin]) i++;

    // 左子树的长度. 据此长度划分preorder序列，找到新的pBegin和pEnd
    int leftLength = i - iBegin; //[iBegin, i -1]
    int rightLength = iEnd - i; // [i + 1, iEnd]

    TreeNode *cur = new TreeNode(preorder[pBegin]);
    cur->left = buildTree(preorder, pBegin + 1, pBegin + leftLength,   // 对应preorder [pBegin + 1, (pBegin+1)+(leftLength-1)]
                          inorder, iBegin, i - 1);
    cur->right = buildTree(preorder, pBegin + leftLength + 1, pEnd,
                           inorder, i + 1, iEnd);

    return cur;
}

TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    int n = preorder.size();
    return buildTree(preorder, 0 , n - 1, inorder, 0, n - 1);
}


/* 由中序和后序序列重建二叉树.
 * 后序序列的最后一个元素是树的根。在此之前，分别是左子树和右子树
 */
TreeNode *buildTreeFromInAndPostOrder(vector<int> &inorder, int inBegin, int inEnd,
                                      vector<int> &postorder, int postBegin, int postEnd) {
    if (inBegin > inEnd || postBegin > postEnd) return nullptr;

    // 在中序序列中寻找根的位置. 后序序列的最后一个元素是树的根
    int i = 0;
    while (i < inorder.size() && inorder[i] != postorder[postEnd]) i++;

    int leftLength = i - inBegin;
    int rightLength = inEnd - i;

    TreeNode *cur = new TreeNode(postorder[postEnd]);
    cur->left = buildTreeFromInAndPostOrder(inorder, inBegin, i - 1,
                                            postorder, postBegin, postBegin + leftLength - 1);
    cur->right = buildTreeFromInAndPostOrder(inorder, i + 1, inEnd,
                                             postorder, postBegin + leftLength, postEnd - 1);
    return cur;
}

TreeNode *buildTreeFromInAndPostOrder(vector<int> &inorder, vector<int> &postorder) {
    int n = inorder.size();
    return buildTreeFromInAndPostOrder(inorder, 0, n - 1, postorder, 0, n - 1);
}

/* Unique Binary Search Trees
 * Given n, how many structurally unique BST’s (binary search trees) that store values 1,...n?
 * For example, Given n = 3, there are a total of 5 unique BST’s.
 * 思路：令状态f[i]表示[1,i]能表示的BST的数目(或者i个数能表示的BST个数)，则f[i]=
 *  f[i-1] * f[0]  // i为根. [1,i-1]为左子树,右子树为空
 * +f[i-2] * f[1]  // i-1为根. [1, i-2]为左子树, i为右子树.
 * + ...
 * +f[0] * f[i-1]  // 1为根. i-1个数都在右子树上.
 * 总结： f[i] = 求和(f[i-j]*f[j-1]), for j = 1; j <= i; j++
 */
int numTrees(int n) {
    int f[n+1] = {0};
    f[0] = 1;
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            f[i] += f[i-j] * f[j-1];
        }
    }
    return f[n];
}

/* Validate Binary Search Tree
 */
bool isValidBST(TreeNode *root, int lower, int higher) {
    if (root == nullptr) return true;
    return (root->val > lower && root->val < higher)
           && isValidBST(root->left, lower, root->val)
           && isValidBST(root->right, root->val, higher);
}
bool isValidBST(TreeNode *root) {
    return isValidBST(root, INT32_MIN, INT32_MAX);
}

/* 验证一个数组是否为一个二叉搜索树的后序遍历序列. 假设数组中没有重复值.
 * 例如： {5,7,6,9,11,10,8}是一个BST的后序序列；{7,4,6,5}则不是
 */
bool isSequenceOfBST(vector<int> &A, int start, int end) {
    if (start == end) return true;

    int root = A[end];
    // 1. 左子树的节点小于根节点 (注意：如果结果i==start, 则没有左子树, 如果i==end, 则没有右子树!!!)
    int i = start;
    for (; i < end; i++) {
        if (A[i] > root) break;
    }

    //2. 右子树的节点大于根节点. 但是如果有小于root的节点，立刻剪枝返回false
    int j = i;
    for (; j < end; j++) {
        if (A[j] < root) return false;
    }

    bool left = true;
    if (i > start)  //如果有左子树
        left = isSequenceOfBST(A, start, i - 1);

    bool right = true;
    if (i < end)    // 如果有右子树
        right = isSequenceOfBST(A, i, end - 1);

    return  (left && right);
}

bool isSequenceOfBST(vector<int> A) {
    return  isSequenceOfBST(A, 0, A.size() - 1);
}

/* Convert Sorted Array to Binary Search Tree.
 * Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
 */
TreeNode *sortedArrayToBST(vector<int> &num, int start, int end) {
    if (start > end) return nullptr;     // Start > end 时，不再构建cur及左右子树，直接返回nullptr. nullptr可以在长一层作为左右子树.
    int mid = (start + end) / 2;         // 这是二叉树的递归构建中常用的技巧.
    TreeNode *cur = new TreeNode(num[mid]);    //自顶向下构建 -- 先构建parent节点,然后递归构建左右子树.
    cur->left = sortedArrayToBST(num, start, end - 1);
    cur->right = sortedArrayToBST(num, end + 1, end);

    return cur;
}
TreeNode *sortedArrayToBST(vector<int> &num) {
    return sortedArrayToBST(num, 0, num.size() - 1);
}

/* Same Tree
 */
bool isSameTree(TreeNode *p, TreeNode *q) {
    if (p == nullptr || q == nullptr) {
        if (p == nullptr && q == nullptr) return true;
        else return false;
    }
    return (p->val == q->val)
           && isSameTree(p->left, q->left)
           && isSameTree(p->right, q->right);
}

/* Subtree. -- A tree T2 is a subtree of Tl if there exists a node n in Tl such that the subtree of n is identical to T2.
 * That is, if you cut off the tree at node n, the two trees would be identical.
 * 思路： 复用isSameTree的代码。/
 */
bool isSubtree(TreeNode *root1, TreeNode *root2) {
    if (root2 == nullptr) return true; //空树是任意树的子树
    if (root1 == nullptr) return false; //任何非空树不是空树的子树
    if (root1->val == root2->val) {
        if (isSameTree(root1, root2)) return true;
    }
    return isSubtree(root1->left, root2) || isSubtree(root1->right, root2);

}

/* Symmetric Tree -- 对称二叉树
 */
bool isSymmetric(TreeNode *left, TreeNode *right) {
    if (left == nullptr || right == nullptr) {
        if (left == nullptr && right == nullptr) return true;
        else return false;
    }

    return (left->val == right->val)
           && isSymmetric(left->left, right->right)
           && isSymmetric(left->right, right->left);
}

bool isSymmetric(TreeNode *root) {
    if (root == nullptr) return false;
    return isSymmetric(root->left, root->right);
}

/* 求二叉树的镜像, 要求原地置换.
 */
void getMirrorTree(TreeNode *root) {
    if (root == nullptr) return;
    if (root->left == nullptr && root->right == nullptr) return;

    // 交换root的左右子节点
    TreeNode *pTemp = root->left;
    root->left = root->right;
    root->right = pTemp;

    getMirrorTree(root->left);
    getMirrorTree(root->right);
}

/* 求二叉树中序序列的下一个节点. 树中的节点除了有左右子节点指针外，还有一个指向父节点的指针
 * 思路：1. 如果当前节点有右子树，则下一个节点就是其右子树的最左节点。
 *      2. 否则：
 *         2.1 如果当前节点是它的父节点的左子树，则下一个节点是父节点
 *         2.2 如果当前节点是它的父节点的右子树，则往上走，直到找到的节点是其父节点的左子树。
 */

TreeNode *nextNode(TreeNode *node) {
    if (node == nullptr) return nullptr;
    TreeNode *pNext = nullptr;

    if (node->right != nullptr) {
        TreeNode *pTemp = node->right;
        while (pTemp->left) pTemp = pTemp->left;
        pNext = pTemp;
    } else if (node->parent != nullptr) {
        if (node == node->parent->left)  pNext = node->right;
        else {
            while (node->parent != nullptr && node == node->parent->right) {
                node = node->parent;
            }
            pNext = node->parent;
        }
    }
    return pNext;
}

/* 和为某一值的所有路径. root-leaf !!!!
 */
void dfsPathSum(TreeNode *node, vector<int> &path, vector<vector<int>> &result, int gap) {
    if (node == nullptr) return;

    path.push_back(node->val);
    if (node->left == nullptr && node->right == nullptr) {  // leaf
        if (gap == node->val) {
            result.push_back(path);
            //return;   注意：这里不能return。 因为这里已经在扩展状态的代码中了，return会导致不能恢复状态。
            // 通常需要return的时候，是在递归函数开始的时刻，判断是否可以收敛。因为这个时候还没有开始扩展状态，所以可以直接return
        }
    }
    dfsPathSum(node->left, path, result, gap - node->val);
    dfsPathSum(node->right, path, result, gap - node->val);
    path.pop_back();
}

vector<vector<int>> pathSum(TreeNode *root, int target) {
    vector<vector<int>> result;
    vector<int> path;

    dfsPathSum(root, path, result, target);
    return result;
}

/* Path Sum -- Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the
 * values along the path equals the given sum.
 */
bool hasPathSum(TreeNode *root, int sum) {
    if (root == nullptr) return false;
    if (root->left == nullptr && root->right == nullptr) {  // leaf
        return sum == root->val;
    }
    return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
}

/*
int main(){
    //重建二叉树
    vector<int> preorder = {1,4,2,8,5,10,3,7};
    vector<int> inorder = {8,2,4,5,10,1,7,3};
    vector<int> postorder = {8,2,10,5,4,7,3,1};
    TreeNode *root = buildTree(preorder, inorder);
    cout << endl << "PostOrder New Constructed Tree from preOrder and Inorder: " << endl;
    postOrder2(root);

    TreeNode *root2 = buildTreeFromInAndPostOrder(inorder, postorder);
    cout << endl << "PreOrder New Constructed Tree from InOrder and postOrder: " << endl;
    preOrder2(root2);

    //层序遍历， 用队列实现
    cout << endl << "Level Order: " << endl;
    levelOrder(root);

    //树的最大深度
    cout << endl << "The depth of tree using recursive way: " << maxDepthOfBT(root) << endl;
    cout << endl << "The depth of tree using non-recursive way: " << maxDepthOfBT2(root) << endl;

    //Same Tree
    bool ifSameTree = isSameTree(root, root2);
    assert(ifSameTree);

    //Mirror of Tree
    getMirrorTree(root);
    cout << endl << "PreOrder the mirrored-Tree Non-recursively:" << endl;
    preOrder2(root);

    // 验证一个序列是否为一棵BST的后序序列
    vector<int> A1 = {5,7,6,9,11,10,8}, A2 = {7,4,6,5};
    bool isA1BST = isSequenceOfBST(A1), isA2BST = isSequenceOfBST(A2);
    assert(isA1BST && !isA2BST);
}
*/