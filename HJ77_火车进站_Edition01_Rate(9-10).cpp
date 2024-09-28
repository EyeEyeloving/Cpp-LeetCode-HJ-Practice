#include <algorithm>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>

/*这份代码使用递归方法求解全排列。全排列的生成没有问题，但之后的排序将超限*/

class Solution {
public:
    std::vector<int> intermediate;
    std::vector<std::vector<int>> solution;
    int check_index = 0;

public:
    /*递归法求解全排列*/
    void findFullArrange(std::vector<int>& inputNumbericArray, std::vector<bool>& checkConfirmArray) {
        if (intermediate.size()==inputNumbericArray.size()) { // Base Case: 当中间数组的长度等于输入数组的长度，说明该例下全排列已经找到
            solution.emplace_back(intermediate); // 把找到的答案存储下来
            return;
        }
        for (int i=0; i<inputNumbericArray.size(); i++) {
            if (checkConfirmArray[i]) continue;
            intermediate.emplace_back(inputNumbericArray[i]);
            checkConfirmArray[i] = true;
            findFullArrange(inputNumbericArray, checkConfirmArray); // 超级操作
            checkConfirmArray[i] = false; // 回溯
            intermediate.pop_back(); // 回溯
        }
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

        Solution mySolution;
        mySolution.findFullArrange(inputNumbericArray, checkConfirmArray);
        auto solution = mySolution.solution;

        /*这里的排序可能会超时*/
        std::sort(solution.begin(), solution.end(), [](std::vector<int> a, std::vector<int> b){
            int size_ab = a.size();
            for (int i=0; i<size_ab; i++) {
                if (a[i]<b[i]) {
                    return true;
                } else if (a[i]>b[i]) {
                    return false;
                }
            }
            return true;
        });

        for (auto& subAns : solution) {
            if (mySolution.validateAnswer(inputNumbericArray, subAns)) {
                for (auto& elements : subAns) {
                    std::cout << elements << ' ';
                }
                std::cout << std::endl;
            }
        }
       
    }
}
// 64 位输出请用 printf("%lld")