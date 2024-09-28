#include <algorithm>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>

class Solution {
public:
    std::vector<int> intermediate;
    std::vector<std::vector<int>> solution;
    int check_index = 0;

public:
    // /*递归法求解全排列*/
    // void findFullArrange(std::vector<int>& inputNumbericArray, std::vector<bool>& checkConfirmArray) {
    //     if (intermediate.size()==inputNumbericArray.size()) { // Base Case: 当中间数组的长度等于输入数组的长度，说明该例下全排列已经找到
    //         solution.emplace_back(intermediate); // 把找到的答案存储下来
    //         return;
    //     }
    //     for (int i=0; i<inputNumbericArray.size(); i++) {
    //         if (checkConfirmArray[i]) continue;
    //         intermediate.emplace_back(inputNumbericArray[i]);
    //         checkConfirmArray[i] = true;
    //         findFullArrange(inputNumbericArray, checkConfirmArray); // 超级操作
    //         checkConfirmArray[i] = false; // 回溯
    //         intermediate.pop_back(); // 回溯
    //     }
    // }

    /* 使用字典序生成全排列 */
    void findFullArrange(std::vector<int>& inputNumbericArray, std::vector<int>& inputNumbericArray_raw) {
        std::sort(inputNumbericArray.begin(), inputNumbericArray.end()); // 初始排序，确保是字典序最小的排列
        do {
            if (validateAnswer(inputNumbericArray_raw, inputNumbericArray)) {
                for (auto& elements : inputNumbericArray) {
                    std::cout << elements << ' ';
                }
                std::cout << std::endl;
            }
            // solution.emplace_back(inputNumbericArray); // 将当前排列加入到解集中
        } while (std::next_permutation(inputNumbericArray.begin(), inputNumbericArray.end())); // 生成下一个字典序排列
    }

    bool validateAnswer(std::vector<int>& inputNumbericArray, std::vector<int>& subAnswer) {
        std::stack<int> myStack;
        int idx=0;
        for (int i=0; i<inputNumbericArray.size(); i++) {
            myStack.emplace(inputNumbericArray[i]);
            while (!myStack.empty()&&myStack.top()==subAnswer[idx]) {
                myStack.pop();
                ++idx;
            }
        }
        if (idx==subAnswer.size()) return true;
        return false;
    }
};


int main() {
    int trains_num;
    while (std::cin >> trains_num) { // 注意 while 处理多个 case
        std::vector<int> inputNumbericArray(trains_num, 0);
        std::vector<bool> checkConfirmArray(trains_num, false);
        for (int i=0; i<trains_num; i++) {
            std::cin >> inputNumbericArray[i];
        }

        auto inputNumbericArray_copy = inputNumbericArray;
        std::sort(inputNumbericArray_copy.begin(), inputNumbericArray_copy.end());
        Solution mySolution;
        // mySolution.findFullArrange(inputNumbericArray, checkConfirmArray); // 递归生成全排列
        mySolution.findFullArrange(inputNumbericArray_copy, inputNumbericArray); // std::next_permutation 字典序生成全排列/自动化；可以尝试递归实现字典序
       
    }
}
// 64 位输出请用 printf("%lld")