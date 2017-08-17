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

/*
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

    //前序遍历 递归
    cout << endl << "PreOrder recursively:" << endl;
    preOrder(root);

    //前序遍历 非递归
    cout << endl << "PreOrder Non-recursively:" << endl;
    preOrder2(root);

    //中序遍历，递归
    cout << endl << "InOrder recursively:" << endl;
    inOrder(root);

    //中序遍历，非递归
    cout << endl << "InOrder Non-recursively:" << endl;
    inOrder2(root);

    //层序遍历， 用队列实现
    cout << endl << "Level Order: " << endl;
    levelOrder(root);

    //树的最大深度
    cout << endl << "The depth of tree using recursive way: " << maxDepthOfBT(root) << endl;
    cout << endl << "The depth of tree using non-recursive way: " << maxDepthOfBT2(root) << endl;
}
*/