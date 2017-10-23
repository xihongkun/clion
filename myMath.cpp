//
// Created by xih on 2017/8/23.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

/* 字符串相乘
 */
typedef vector<short> BigInt;

string toString(BigInt data) { // 将vector<int> 转换回string
    string result = "";
    reverse(data.begin(), data.end());
    size_t len = data.size();
    int i = 0;
    for (; i < len; i++) {
        if (data[i] != 0) break;
    }

    for (; i < len; i++) {
        result += (data[i] + '0');
    }
    return result;
}

string multiply(string num1, string num2) {
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    size_t len1 = num1.size(), len2 = num2.size();
    BigInt data(len1 + len2); // 用一个数组存储相乘后的结果，这样不会溢出

    for (size_t i = 0; i < len1; i++) {
        for (size_t j = 0; j < len2; j++) {
            data[i + j] += (num1[i] - '0') * (num2[j] - '0');
            data[i + j + 1] += data[i + j] / 10;
            data[i + j] %= 10;
        }
    }

    string res = toString(data);
    return res;
}

/* https://stackoverflow.com/questions/1761626/weighted-random-numbers 加权随机算法
 * There is a straightforward algorithm for picking an item at random, where items have individual weights:
 * 1) calculate the sum of all the weights
 * 2) pick a random number that is 0 or greater and is less than the sum of the weights
 * 3) go through the items one at a time, subtracting their weight from your random number, until you get the item where the random number is less than that item's weight
 * Pseudo-code illustrating this:
 */

  /*
    int sum_of_weight = 0;
    for(int i=0; i<num_choices; i++) {
       sum_of_weight += choice_weight[i];
    }
    int rnd = random(sum_of_weight);
    for(int i=0; i<num_choices; i++) {
      if(rnd < choice_weight[i])
        return i;
      rnd -= choice_weight[i];
    }
  */

// 例如： design a function rand_prob(unsigned int N, double prob[]), which returns integer i (0<=i<N) with probability prob[i]
int rand_prob(unsigned int N, double prob[]) {
    double total_prob = 0;
    for (int i = 0; i < N; i++) {
        total_prob += prob[i];
    }
    // 使用rand() / double(RAND_MAX) 取得0～1之间的浮点数. 再乘以total_prob， 可以获得(0-prob)之间的随机浮点数
    double rnd = rand() / double(RAND_MAX) * total_prob;
    for (int j = 0; j < N; j++) {
        if (rnd <  prob[j])
            return j;
        rnd -= prob[j];
    }
}

/* X的n次方. 二分法 n/2 n/2 n%2  当n是偶数时， n/2 * n/2, 奇数时, n/2 * n/2 * x1
 */
double power(double x, int n) {
    if (n == 0) return 1.0;
    double v = power(x, n/2);

    if (n % 2 == 0) return v * v;
    else return v * v * x;
}

double pow(double x, int n) {
    if (n < 0) return 1.0 / power(x, -n);
    else return power(x, n);
}

// 反转int
int reverseInt(int x) {
    long long num = 0; // 旋转后可能溢出，因此设置临时变量时应该为long long，然后判断并处理。
    while (x != 0) {
        num = num * 10 +  x % 10;
        x /= 10;
    }
    if (num > INT32_MAX || num < INT32_MIN) return 0;
    return num;
}

// 判断一个整数是否为回文数
bool isPalindrome(int x) {
    if (x < 0) return false; // 负数是否能被称为回文数？
    int  divisor = 1 ;
    while (x / divisor >= 10) divisor *= 10;

    while (x > 0) {
        int low = x % 10;
        int high = x / divisor;
        if (low != high) return false;

        x = x % divisor / 10; //取出中间的数值
        divisor /= 100; // 注意每次去掉两位，因此除数相应缩小100倍
    }
    return true;
}

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

// insert interval
vector<Interval> insertInterval(vector<Interval> &intervals, Interval newInterval) {
    vector<Interval>::iterator it = intervals.begin();
    while (it != intervals.end()) {
        if (newInterval.end < it->start) {
            intervals.insert(it, newInterval);
            return intervals;
        } else if (newInterval.start > it->end) {
            it++;
        } else {
            // 设置新的newInterval, 并把旧的元素删除。进入下一次循环
            newInterval.start = min(it->start, newInterval.start);
            newInterval.end = max(it->end, newInterval.end);
            it = intervals.erase(it);  // 注意：不能只用intervals.erase(it)。需要更新it的值
        }
    }
    // 最后一个newInterval
    intervals.insert(intervals.end(), newInterval);
    return intervals;
}

// merge intervals
vector<Interval> mergeIntervals(vector<Interval> &intervals) {
    vector<Interval> result;
    for (int i = 0; i < intervals.size(); i++) {
        insertInterval(result, intervals[i]);
    }
    return result;
}

/* Meeting rooms
 * Given [[0,30], [5,10], [15,20]] determine if a person could attend all meetings
 * 先按照开始时间排序，然后比较：如果后一个会议的开始时间<前一个会的结束时间，则返回false
 */
bool compareIntervals(const Interval &a, const Interval &b) {
    return a.start < b.start;
}

bool canAttendMeetings(vector<Interval> &intervals) {
    sort(intervals.begin(), intervals.end(), compareIntervals);

    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i].start < intervals[i-1].end) return false;
    }
    return true;
}

/* Meeting Rooms II
 * Find minimum number of meeting rooms.
 * 思路： 1. 将intervals按照会议开始时间排序
 * 2. 设置一个小顶堆，用来存储会议的时间。按结束时间排序，最小的结束时间总是会在前面
 * 3. 遍历时间：如果堆不为空，且当前会议的开始时间>=堆首元素，则去掉堆首元素,并将当前的结束时间入堆。表示上一个会议已经结束，可以用该会议室开始下一个会议了。
 *            不管如何，总是将当前的结束时间入堆。
 * [[0,5], [2,10], [7,8]]
 */
int minMeetingRooms(vector<Interval> &intervals) {
    sort(intervals.begin(), intervals.end(), compareIntervals);
    priority_queue<int, vector<int>, greater<int>> q; //小顶堆

    for (auto a:intervals) {
        if (!q.empty() && a.start >= q.top()) { q.pop();}
        q.push(a.end);
    }
    return q.size();
}

/*
int main() {
    // reverse integer
    int a = 12345;
    cout << endl << "After reversing " << a << ": " << reverseInt(a) << endl;

    // 字符串相乘
    string stringA = "123", stringB = "45";
    cout << endl << "Multiply strings: " << multiply(stringA, stringB) << endl;
    // palindrome number
    int palindromeInt = 123454321;
    if (isPalindrome(palindromeInt))
        cout << endl << palindromeInt << " is palindrome int." << endl;

    // insert interval
    vector<Interval> intervals = {Interval(1,2), Interval(3,5), Interval(6,7), Interval(8,10), Interval(12,16)};
    vector<Interval> updatedIntervals = insertInterval(intervals, Interval(4,9));
    for (vector<Interval>::iterator it = updatedIntervals.begin(); it != updatedIntervals.end(); it++) {
        cout << endl << "[" << it->start << "," << it->end << "]" << endl;
    }

    // merge intervals
    vector<Interval> intervals2 = {Interval(1,3), Interval(2,6), Interval(8,10), Interval(15,18)};
    vector<Interval> mergedIntervals2 = mergeIntervals(intervals2);
    for (int i = 0; i < mergedIntervals2.size(); i++) {
        cout << endl << "[" << mergedIntervals2[i].start << "," << mergedIntervals2[i].end << "]" << endl;
    }

    // meeting rooms
    vector<Interval> p ={Interval(5,10), Interval(0,30), Interval(15,20)};
    bool ifCanAttend = canAttendMeetings(p);
    if (ifCanAttend)
        cout << endl << "Can attend all meetings" << endl;

}
*/