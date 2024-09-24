#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

struct ITEM { // 输入的商品
    int number = 0; // 商品编号
    int price = 0; // 商品价格
    int sig = 0; // 重要性
    int belong = 0; // 从属关系
    bool isprocessed = false; // 查看有没有被处理过
};

struct MajorItem { // 主件商品
    int price = 0; // 主件价格
    int sig = 0; // 主件重要度
    bool attach = false; // 有没有附件
    std::vector<ITEM> attachment; // 附件
};

class Solution {
public:
    std::vector<int> getSolu(std::map<int, MajorItem>& major_item, std::vector<int>& optimal_array) {
        int total_cash = optimal_array.size()-1; // 总体钱数
        int total_majoritem = major_item.size(); // 主件数目
        for (auto it=major_item.begin(); it!=major_item.end(); it++) {
            MajorItem item = (*it).second;
            if (item.price>total_cash) continue; // 如果主件都没钱买，就没有往下讨论的必要
            int put_cost = item.price; // 主件购买成本
            int stop_n_cash = put_cost;   

            // int optimal_array0[total_cash+1], optimal_array1[total_cash+1], optimal_array2[total_cash+1], optimal_array12[total_cash+1]
            std::vector<int> optimal_array0(total_cash+1, 0), optimal_array1(total_cash+1, 0);
            std::vector<int> optimal_array2(total_cash+1, 0), optimal_array12(total_cash+1, 0);
            for (int n_cash=total_cash; n_cash>=stop_n_cash; n_cash--) {
                optimal_array0 = getMajorItem(n_cash, item, optimal_array);
                switch (item.attachment.size()) {
                    case 1: {
                        if (put_cost+item.attachment[0].price<=n_cash) {
                            optimal_array1 = getMajorItem_withSingle(n_cash, item, item.attachment[0], optimal_array);
                        } 
                    }
                    case 2: {
                        if (put_cost+item.attachment[0].price+item.attachment[1].price<=n_cash) {
                            optimal_array12 = getMajorItem_withDouble(n_cash, item, optimal_array);
                        } 
                        if (put_cost+item.attachment[0].price<=n_cash) {
                            optimal_array1 = getMajorItem_withSingle(n_cash, item, item.attachment[0], optimal_array);
                        }
                        if (put_cost+item.attachment[1].price<=n_cash) {
                            optimal_array2 = getMajorItem_withSingle(n_cash, item, item.attachment[1], optimal_array);
                        }
                    }
                }
                // 有可能会出现主件+附件一+附件二+剩余容量的满意度<主件+附件一+剩余容量满意度的情况
                if (optimal_array0[n_cash]>optimal_array[n_cash]) optimal_array[n_cash] = optimal_array0[n_cash]; 
                if (optimal_array1[n_cash]>optimal_array[n_cash]) optimal_array[n_cash] = optimal_array1[n_cash];
                if (optimal_array12[n_cash]>optimal_array[n_cash]) optimal_array[n_cash] = optimal_array12[n_cash];  
                if (optimal_array2[n_cash]>optimal_array[n_cash]) optimal_array[n_cash] = optimal_array2[n_cash];
            }
        }
        return optimal_array;
    }

    std::vector<int> getMajorItem(int& n_cash, MajorItem& item, std::vector<int>& optimal_array){
        int put_satisfy = item.price*item.sig+optimal_array[n_cash-item.price];
        if (put_satisfy>optimal_array[n_cash]) optimal_array[n_cash] = put_satisfy;
        return optimal_array;
    }

    std::vector<int> getMajorItem_withSingle(int& n_cash, MajorItem& item, ITEM& attachment, std::vector<int>& optimal_array){
        int n = n_cash-item.price-attachment.price;
        int put_satisfy = item.price*item.sig + attachment.price*attachment.sig + optimal_array[n];
        if (put_satisfy>optimal_array[n_cash]) optimal_array[n_cash] = put_satisfy;
        return optimal_array;
    }

    std::vector<int> getMajorItem_withDouble(int& n_cash, MajorItem& item, std::vector<int>& optimal_array){
        int n = n_cash-item.price-item.attachment[0].price-item.attachment[1].price;
        int put_satisfy = item.price*item.sig + item.attachment[0].price*item.attachment[0].sig + item.attachment[1].price*item.attachment[1].sig + optimal_array[n];
        if (put_satisfy>optimal_array[n_cash]) optimal_array[n_cash] = put_satisfy;
        return optimal_array;
    }
};


int main() {
    /*首先知道总体钱数和总体物品数*/
    int totalCashNumber, totalAttachNumber;
    std::cin >> totalCashNumber >> totalAttachNumber;
    
    int n_scale = 10;
    totalCashNumber = totalCashNumber/n_scale;

    /*此外，这里有附件，但是购买附件必须先购买主件，所以要转变思路，即可讨论的商品近似只有主件，只是成本和收益有不同的情况*/
    /*优化目标=价格*重要性*/
    std::map<int, ITEM> packages;

    /*准备输入*/
    int v, p, q;
    int count_number = 0; // 商品编号
    while (std::cin >> v >> p >> q) { // 注意 while 处理多个 case
    // std::cin >> attachmentDict[count].price >> attachmentDict[count].sig >> attachmentDict[count].belong会多创建一个
        ++count_number;
        packages[count_number].price = v/n_scale;
        packages[count_number].sig = p;
        packages[count_number].belong = q;
        packages[count_number].number = count_number;
    }
    /*输入格式转换：转变为只有主件的情况*/  
    std::queue<ITEM> myQueue;// 通过一个队列，循环讨论
    std::map<int, MajorItem> major_item;
    for (int i=1; i<=count_number; i++) { // 查找附件，从1开始
        if (packages[i].belong==0) { // 当前不是附件，放入队列中
            myQueue.push(packages[i]); 
            continue;
        }
        int major_number = packages[i].belong; // 把对应的主件的编号找出来
        major_item[major_number].attach = true;
        major_item[major_number].price = packages[major_number].price; 
        major_item[major_number].sig = packages[major_number].sig;
        major_item[major_number].attachment.push_back(packages[i]); // 把这个附件放进去
        packages[major_number].isprocessed = true; // 说明这个主件已经被讨论并放入到major_item当中了
    }
    while (!myQueue.empty()) { // 如果队列里面还有主件
        auto item = myQueue.front();
        if (item.isprocessed==1) {
            myQueue.pop(); // 出队
            continue;
        }
        // 把剩余主件放入到字典当中
        major_item[item.number].price = item.price;
        major_item[item.number].sig = item.sig;
        myQueue.pop();
    }

    /*构建滚动一维数组*/
    std::vector<int> optimal_array(totalCashNumber+1, 0); // 初始化边界条件，要+1
    auto solu = new Solution();
    optimal_array = solu->getSolu(major_item, optimal_array);
    
    /*输出解决方案*/
    std::cout << optimal_array[totalCashNumber]*n_scale << std::endl;

}
// 64 位输出请用 printf("%lld")