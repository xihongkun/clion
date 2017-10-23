//
// Created by xih on 2017/10/23.
//

#include <iostream>
#include <vector>

using namespace std;

/* Best Time to Buy and Sell Stock
 * Say you have an array for which the i-th element is the price of a given stock on day i.
 * If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the
 * stock), design an algorithm to find the maximum profit.
 * 贪心：分别找到价格最低和最高的一天，然后求差值。注意 低价的一天在高价一天之前
 */
int maxProfit(vector<int> &prices) {
    if (prices.size() < 2) return 0;
    int profit = 0; // 最大利润
    int cur_min_price = prices[0]; // 当前的最低价格

    for (size_t i = 1; i < prices.size(); i++) {
        profit = max(profit, prices[i] - cur_min_price);
        cur_min_price = min(cur_min_price, prices[i]);
    }
    return profit;
}

/* Best Time to Buy and Sell Stock II
 * Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie,
 * buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions
 * at the same time (ie, you must sell the stock before you buy again).
 * 贪心： 只要明天价格高于今天，就可以在今天买入，明天卖出
 */
int maxProfit2(vector<int> prices) {
    if (prices.size() < 2) return 0;
    int profit = 0;
    for (int i = 1; i < prices.size(); i++) {
        int diff = prices[i] - prices[i - 1];
        if (diff > 0)  profit += diff;
    }

    return profit;
}
