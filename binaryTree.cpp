//
// Created by xih on 8/10/2017.
//
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
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

int main(){
    TreeNode *root = new TreeNode(1);
    TreeNode *layer2Left = new TreeNode(4);
    TreeNode *layer2Right = new TreeNode(3);
    TreeNode *layer3First = new TreeNode(2);
    TreeNode *layer3Second = new TreeNode(5);
    TreeNode *layer3Third = new TreeNode(7);
    TreeNode *layer4First = new TreeNode(8);
    TreeNode *layer4Second = new TreeNode(10);

    root->left = layer2Left;
    root->right = layer2Right;
    layer2Left->left = layer3First;
    layer2Left->right = layer3Second;
    layer2Right->left = layer3Third;
    layer3First->left = layer4First;
    layer3Second->right = layer4Second;

    //前序遍历 递归 [1,4,2,8,5,10,3,7]
    cout << endl << "PreOrder recursively:" << endl;
    preOrder(root);

    //前序遍历 非递归
    cout << endl << "PreOrder Non-recursively:" << endl;
    preOrder2(root);

    //中序遍历，递归 [8,2,4,5,10,1,7,3]
    cout << endl << "InOrder recursively:" << endl;
    inOrder(root);

    //中序遍历，非递归
    cout << endl << "InOrder Non-recursively:" << endl;
    inOrder2(root);

    //后序遍历，递归
    cout << endl << "PostOrder Recursively: " << endl;
    postOrder(root);

    //后序遍历，非递归
    cout << endl << "PostOrder Non-recursively: " << endl;
    postOrder2(root);

    //层序遍历， 用队列实现
    cout << endl << "Level Order: " << endl;
    levelOrder(root);

    //树的最大深度
    cout << endl << "The depth of tree using recursive way: " << maxDepthOfBT(root) << endl;
    cout << endl << "The depth of tree using non-recursive way: " << maxDepthOfBT2(root) << endl;

    //重建二叉树
    vector<int> preorder = {1,4,2,8,5,10,3,7};
    vector<int> inorder = {8,2,4,5,10,1,7,3};
    vector<int> postorder = {8,2,10,5,4,7,3,1};
    TreeNode *rootFromPreAndInorder = buildTree(preorder, inorder);
    cout << endl << "PostOrder New Constructed Tree from preOrder and Inorder: " << endl;
    postOrder2(rootFromPreAndInorder);

    TreeNode *rootFromInAndPostOrder = buildTreeFromInAndPostOrder(inorder, postorder);
    cout << endl << "PreOrder New Constructed Tree from InOrder and postOrder: " << endl;
    preOrder2(rootFromInAndPostOrder);



}
