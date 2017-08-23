//
// Created by xih on 2017/8/21.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <vector>
#include <unordered_map>
#include <assert.h>

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

// atoi
int myAtoi(const string &s) {
    int sign = 1;
    int i = 0;
    int num = 0;
    int n = s.size();
    while (i < n && s[i] == ' ') i++;

    if (i < n && ( s[i] == '+' || s[i] == '-')) { // 判断第一个非空字符是否为正负号
        if (s[i] == '-') sign = -1;
        i++;
    }

    for (; i < n; i++) {
        if (s[i] < '0' || s[i] > '9') break;
        if (num > INT32_MAX/10 || ( num == INT32_MAX/10 && (s[i] - '0') > INT32_MAX%10)) // 溢出
            return sign == 1 ? INT32_MAX : INT32_MIN;

        num = num * 10 + s[i] - '0';
    }

    return num * sign;
}

/*[LeetCode]35. Valid Parentheses 有效括号 http://www.cnblogs.com/grandyang/p/4424587.html
 *Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 * The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
 */
bool isValidParentheses(string &s) {
    if (s.empty()) return false;
    int n = s.size();
    if (n%2 != 0) return false;  // 奇数个字符

    stack<char> stack1;

    for (int i = 0; i < n; i++) {
        if ( s[i] == '(' || s[i] == '[' || s[i] == '{' ) {
            stack1.push(s[i]);
        } else {
            if (stack1.empty()) return false;
            if (s[i] == ')' && stack1.top() != '(') return false;
            if (s[i] == ']' && stack1.top() != '[') return false;
            if (s[i] == '}' && stack1.top() != '{') return false;
            stack1.pop();
        }
    }
    return stack1.empty(); // 最终栈中可能有元素，比如((
}

/* [LeetCode]50. Valid Anagram有效变位词
 * 思路： 因为题目限定字符在26个小写字母之间，因此以vector作为Hash Table，分别统计两个字符串字母出现次数，然后再比较即可。
 */
bool isAnagram(string s, string t) {
    int ss = s.size(), st = t.size();
    if (ss != st) return false;

    vector<int> vs(26, 0);
    vector<int> vt(26, 0);

    for (int i = 0; i < ss; i++) {
        vs[s[i] - 'a']++;
        vt[s[i] - 'a']++;
    }

    for (int j = 0; j < 26; j++){
        if (vs[j] != vt[j]) return false;
    }
    return true;
}

/* [LeetCode]56. Group Anagrams 变位词分组
 * Given an array of strings, group anagrams together.
 * For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
 * Return: [ ["ate", "eat","tea"], ["nat","tan"], ["bat"] ]
 * Note: For the return value, each inner list's elements must follow the lexicographic order.
 * All inputs will be in lower-case.
 */
vector< vector<string> > anagramGroup(vector<string>& strs) {
    int n = strs.size();
    unordered_map<string, vector<string>> group;

    for (int i = 0; i < n; i++) {
        string key = strs[i];
        sort(key.begin(), key.end());
        group[key].push_back(strs[i]);
    }

    vector<vector<string>> result;
    unordered_map<string, vector<string>>::iterator it;

    for(it = group.begin(); it != group.end(); it++) {
        vector<string> temp = it->second;
        sort(temp.begin(), temp.end()); // 重新排序，因为结果需要排序的输出
        result.push_back(temp);
    }
    return result;
}

/* [LeetCode]51. Ismorphic Strings 同构字符串
 * Refer: http://www.cnblogs.com/aprilcheny/p/4929679.html
 * 如果找到一对新的映射（s和t中的对应字符还没出现过），则将两个映射表的相应位置设为同一值，否则判断两个映射表的值是否相同即可。
 */
bool isIsomorphic(string s, string t) {
    int ss = s.size(), st = t.size();
    if (ss != st) return false;

    vector<int> vs(128, -1);
    vector<int> vt(128, -1);

    for (int i = 0; i < ss; i ++) {
        if (vs[s[i]] != vt[t[i]]) return  false;
        vs[s[i]] = i;
        vt[t[i]] = i;
    }
    return true;
}

// [LeetCode]44. Implement strStr() 实现strStr()函数. Refer http://www.cnblogs.com/grandyang/p/4606696.html
int strStr(string haystack, string needle) {
    if (needle.empty()) return 0;
    int m = haystack.size(), n = needle.size();
    if (n > m) return -1;

    for (int i = 0; i < m; i++) {   //这里可以把循环上界设置为m-n，减少循环次数
        int j = 0;
        for (; j < n; j++) {
            if (haystack[i+j] != needle[j]) break; //可以把j理解为待比较的字符在haystack和needle里的偏移
        }
        if (j == n) return i; // 匹配到了
    }
    return -1;
}

// Longest Common Prefix 最长共同前缀
string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) return "";

    for (int index = 0; index < strs[0].size(); index++) { //从位置0开始，逐个比较第一个字符，遇到不相等就退出
        for (int i = 1; i < strs.size(); i++) {
            if (index >= strs[i].size() || strs[i][index] != strs[0][index]) return strs[0].substr(0, index);
        }
    }
    return strs[0];
}

/* [LeetCode]36. Compare Version Numbers 版本号比较
 * Compare two version numbers version1 and version2.
 * If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.
 * You may assume that the version strings are non-empty and contain only digits and the . character.
 */
vector<string> split(const string &str, const char delim) {
    vector<string> result;

    int n = str.size();
    int start = 0;
    for (int i = 0; i < n; i++) {
        if (str[i] == delim) {
            string temp(str.begin() + start, str.begin() + i);
            if (!temp.empty()) result.push_back(temp);
            start = i + 1;
        }
    }

    // 最后一段
    string s(str.begin() + start, str.end());
    if (!s.empty()) result.push_back(s);
    return  result;
}

int compareVersion(string version1, string version2) {
    vector<string> vs1 = split(version1, '.');
    vector<string> vs2 = split(version2, '.');
    int s1 = vs1.size(), s2 = vs2.size();

    int i = 0, j =0;
    for (; i < s1 && j < s2; i++, j++) { // 注意：&& ！
        if (stoi(vs1[i]) < stoi(vs2[j])) return -1;  // stoi用来转哈string的，atoi转化的是char*. 如果要用atoi, 需要用string.c_str()转化成c字符串
        if (stoi(vs1[i]) > stoi(vs2[j])) return 1;
    }
    if (i < s1) return 1; // vs2已经遍历完
    if (j < s2) return -1;

    return 0;
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

    // Add two binary strings
    string binaryS1 = "110";
    string binaryS2 = "11";
    string result = addBinary(binaryS1, binaryS2);
    cout << endl << "Add binary string result: " << result << endl;

    // atoi
    string aString = "-3924x8fc";
    cout << endl << "atoi result: " << myAtoi(aString) << endl;

    // valid Parentheses
    vector<string> vs;
    vs.push_back(")[]{}"); vs.push_back("()[]{}");
    for (int i = 0; i < vs.size(); i++) {
        bool ifParenthese = isValidParentheses(vs[i]);
        if (ifParenthese) {
        cout << endl << vs[i] << " is Valid Parentheses." << endl;
        }
    }

    // Valid Anagram
    string test1 = "anagram", test2 = "nagaram";
    bool ifAnagram = isAnagram(test1, test2);
    if (ifAnagram)
        cout << endl << test1 << " and " << test2 << " is anagram." << endl;

    // Anagram group
    string str[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<string> testVs(str, str+6);

    vector<vector<string>> anagramResult = anagramGroup(testVs);
    int sizeGroup = anagramResult.size();
    for (int i = 0; i < sizeGroup; i++) {
        cout << "Group " << i << " :" << endl;
        int eachGroupSize = anagramResult[i].size();
        for (int j = 0; j < eachGroupSize; j++)
            cout << anagramResult[i][j] << " ";
        cout << endl;
    }

    // Ismorphic Strings 同构字符串
    string testA = "egg", testB = "add";
    bool ifMorphic = isIsomorphic(testA, testB);
    if (ifMorphic) cout << endl << testA << " and " << testB << " is morphic." << endl;

    string testC = "foo", testD = "bar";
    bool ifMorphic2 = isIsomorphic(testC, testD);
    if (ifMorphic2) cout << endl << testC << " and " << testD << " is morphic." << endl;

    // strStr
    int index = strStr("hello, world", "ll");
    cout << endl << "Index location: " << index << endl;

    // 最长公共前缀
    string strWithPrefix[] = {"geeksforgeeks", "geeks", "geek", "geezer"};
    vector<string> vStrWithPrefix(strWithPrefix, strWithPrefix+4);
    string commonPrefix = longestCommonPrefix(vStrWithPrefix);
    cout << endl << "The longest common prefix is: " << commonPrefix << endl;

    int compare = compareVersion("1.1.0", "1.1.0.1");
    assert(compare ==  -1);
    int compare2 = compareVersion("0.12.10.4", "0.12.9");
    assert(compare2 == 1);

}
