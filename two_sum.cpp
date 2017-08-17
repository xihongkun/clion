//
// Created by xih on 8/3/2017.
//

#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;


vector<int> two_sums(vector<int> nums, int target) {
    unordered_map<int, int> mapping;
    vector<int> result;
    for (int j=0; j<nums.size(); j++){
        const int gap = target - nums[j];

        if (mapping.find(gap) != mapping.end()) {

            result.push_back(mapping[gap]);
            result.push_back(j);
            return result;
        }

        else {
            mapping[nums[j]] = j;
        }
    }
}

/**
int main(){
    vector<int> nums = {3,2,4};
    int target = 6;
    vector<int> result = two_sums(nums, target);
    for (int i=0; i<result.size(); i++)
        cout << result[i];
}
*/
