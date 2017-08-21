//
// Created by xih on 2017/8/21.
//

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// [LeetCode]40. Valid Palinadrome 有效回文串  Refer: http://www.cnblogs.com/aprilcheny/p/4908273.html
// 两个指针从两头向中间靠拢，如果碰到非数字字母字符则跳过，然后一一比较即可。
bool isAlphaNumberic(const char c) {
    if (( c >= '0'&& c <= '9' ) || ( c >= 'a' && c <= 'z') || ( c >= 'A' && c <= 'Z'))  return true;
    return false;
}

bool isPalindrome(const string &s) {
    if (s.empty()) return true;

    int n = s.size();
    int i = 0, j = n-1;

    while (i <= j) {
        while (i < n && !isAlphaNumberic(s[i])) i++;
        while (j >= 0 && !isAlphaNumberic(s[j])) j--;
        if (i < n && j >= 0 && tolower(s[i]) != tolower(s[j])) return false;  // 注意：tolower
        i++; j--;
    }
    return true;
}


// [LeetCode]38. Length of Last Word最后单词长度
int lengthOfLastWord(string &s) {
    if (s.empty()) return 0;
    int n = s.size();

    int left = 0, right = n-1;

    while (left < n && s[left] == ' ') left++;
    while (right >= 0 && s[right] == ' ') right--;

    int len = 0;
    for (int i = left; i <= right; i++) {
        if (s[i] != ' ')  len++;
        else len = 0;
    }
    return len;

}

// Add binary strings

string addBinary(string a, string b) {
    string result;
    int n = a.size() > b.size() ? a.size() : b.size();
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int carry = 0;

    for (int i = 0; i < n; i++) {
        int ai = i < a.size() ? a[i] - '0' : 0; //a[i]的类型是char
        int bi = i< b.size() ? b[i] - '0' : 0;

        int temp = ai + bi + carry;
        result.insert(result.begin(), temp%2 + '0');
        carry = temp/2;
    }

    // 超出最大长度之后，还要检查carry的值。如果carry==1，需要增加一位
    if (carry  == 1)
        result.insert(result.begin(), '1');

    return result;
}


int main() {
    // Valid Palinadrome 有效回文串
    string s = "A man, a plan, a canal: Panama";
    bool ifPalindrome = isPalindrome(s);
    if (ifPalindrome)
        cout << endl << s << " Is Palinadrome" << endl;

    string s2 = "race a car";
    bool ifPalindrome2 = isPalindrome(s2);
    if (ifPalindrome2)
        cout << endl << s << " Is Palinadrome" << endl;


    string binaryS1 = "110";
    string binaryS2 = "11";
    string result = addBinary(binaryS1, binaryS2);
    cout << endl << "Add binary string result: " << result << endl;
}
