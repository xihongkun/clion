//
// Created by xih on 2017/9/25.
//

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class MinStack{
public:
    MinStack() {};
    void push(int x) {
        if (s2.empty() || x <= s2.top()) s2.push(x);   //s2.top()等价于getMin()
        s1.push(x);
    }

    void pop() {
        s1.pop();
        if (s2.top() == s1.top()) s2.pop(); //s2.top()等价于getMin()
    }

    int top() {
        return s1.top();
    }

    int getMin() {
        return s2.top();
    }

private:
    stack<int> s1, s2;
};

/* Implement Stack using Queues 用队列来实现栈
 * 在push()操作的时候，只要队列q中有元素，我们先将这些以前的元素搬到另一个队列tmp中暂存起来，然后再push当前元素到队列q中，
 * 最后将缓存队列tmp中的所有元素又搬回到q中来。这样最先进入队列的元素恰好要在最后才能取出来的
 */
class Stack{
public:
    Stack() {};
    void push(int x) {
        std::queue<int> tmp;
        while (!q.empty()) {
            tmp.push(int(q.front()));
            q.pop();
        }
        q.push(x);

        while(!tmp.empty()) {
            q.push(int(tmp.front()));
            tmp.pop();
        }
    }

    void pop() {
        q.pop();
    }

    bool empty() {
        return q.empty();
    }

    int top() {
        return q.front();
    }

private:
    std::queue<int> q;
};

/* Implement Queue using Stacks用栈实现队列
 * 在进行push()操作的时候，如果s中有元素，则将它们搬到辅助栈tmp中，然后再将x push到s中；接下来又将tmp中的所有元素搬回s中。这样最先进入的元素就在栈顶了。
 */
class Queue{
public:
    void push(int x) {
        stack<int> tmp;
        while (!s.empty()) {
            tmp.push(int(s.top()));
            s.pop();
        }

        s.push(x);

        while (!tmp.empty()) {
            s.push(int(tmp.top()));
            tmp.pop();
        }
    }

    void pop() {
        s.pop();
    }

    int front() {
        return s.top();
    }

    bool empty() {
        return s.empty();
    }
private:
    stack<int> s;
};

/* 中缀表达式 转 后缀表达式
 */
int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return  2;
    else return 0;
}

void infixToPostfix(const string &infix, queue<string> &postFixQueue) {  //postFixQueue 输出表达式.为了方便处理空格 整数 运算符，用一个队列来存储
    stack<char> opStack; //运算符栈

    for (int i = 0; i < infix.size(); i++) {
        if (infix[i] == ' ') continue;
        else if (infix[i] >= '0' && infix[i] <= '9') {   // 1. 数字直接输出
            int n = 0;
            while (i < infix.size() && infix[i] >= '0' && infix[i] <= '9') {
                n = n * 10 + (infix[i] - '0');
                i++;
            }
            --i;
            postFixQueue.push(to_string(n));   // int to string
        } else if (infix[i] == '(') {   //2. 左括号直接入运算符栈
            opStack.push(infix[i]);
        } else if (infix[i] == ')') {   // 3. 右括号，栈顶元素依次出栈并输出，直到( 出栈
            while (!opStack.empty() && opStack.top() != '(') {
                postFixQueue.push(string(1, opStack.top()));    //char to string
                opStack.pop();
            }
            opStack.pop(); //舍弃左括号
        }  else { //运算符
            // 4. 优先级小于等于栈顶元素，则依次出栈并输出；优先级高于栈顶元素则直接入栈。不管怎样总是将最后将当前符号入栈
            while (!opStack.empty() && priority(infix[i]) <= priority(opStack.top())) {
                postFixQueue.push(string(1, opStack.top()));
                opStack.pop();
            }
            opStack.push(infix[i]);
        }
    }

    while(!opStack.empty()) { // 5. 运算符栈中剩余运算符压入后缀表达式栈
        postFixQueue.push(string(1, opStack.top()));
        opStack.pop();
    }
}


int main() {
    string x = "9+ (3 - 1)*3+10/2";
    queue<string> postFixQueue;
    infixToPostfix(x, postFixQueue);
    while(!postFixQueue.empty()) {
        cout << postFixQueue.front() << " ";
        postFixQueue.pop();
    }

}