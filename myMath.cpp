//
// Created by xih on 2017/8/23.
//

#include <iostream>
#include <vector>

using namespace std;

int reverseInt(int x) {
    long long num = 0; // 旋转后可能溢出，因此设置临时变量时应该为long long，然后判断并处理。
    while (x != 0) {
        num = num * 10 +  x % 10;
        x /= 10;
    }
    if (num > INT32_MAX || num < INT32_MIN) return 0;
    return num;
}


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

/*
int main() {
    // reverse integer
    int a = 12345;
    cout << endl << "After reversing " << a << ": " << reverseInt(a) << endl;

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

}
 */