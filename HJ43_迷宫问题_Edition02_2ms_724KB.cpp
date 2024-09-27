#include <iostream>
#include <cstring> // std::memset
#include <queue>

/*未处理内存释放问题*/
/* std::queue<ListNode> myQueue 这个对象队列的话，同样的代码就无法实现预期的效果*/

struct Node {
    int m;
    int n;
};

/*创建一个链表*/
struct ListNode {
public:
    Node data;
    // bool visit; // 原意想替换搜索数组
    ListNode* next;
public:
    ListNode(): data({0, 0}), next(nullptr) {}
    ListNode(int m, int n): data({m, n}), next(nullptr) {}
};

int main() {
    int size_row, size_col;
    while (std::cin >> size_row >> size_col) { // 注意 while 处理多个 case
        /*创建地图*/
        int maze[size_row+2][size_col+2];
        std::memset(maze, 1, sizeof(maze));
        for (int mm=1; mm<size_row+1; mm++) {
            for (int nn=1; nn<size_col+1; nn++) {
                std::cin >> maze[mm][nn]; // 载入数据
            }
        }

        /*创建搜索确认*/
        bool ConfirmMap[size_row+2][size_col+2];
        std::memset(ConfirmMap, false, sizeof(ConfirmMap));

        /*创建搜索规则*/
        int explore_rule[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        /*Board First Search*/
        Node node_start = {1, 1};
        Node node_end = {size_row, size_col};
        std::queue<ListNode*> myQueue; // 指针队列
        // std::queue<ListNode> myQueue; // 这个对象队列的话，同样的代码就无法实现预期的效果
        auto Tail = new ListNode();
        Tail->data = node_end;
        Tail->next = nullptr;
        myQueue.push(Tail);
        ConfirmMap[size_row][size_col] = true;
        
        bool empty_queue = false;
        while (!empty_queue) {
            ListNode* listnode_now = myQueue.front(); // 返回的是值的拷贝？而不是原始值的地址或引用？这可能导致赋予的父节点被释放？
            for (int n_explore=0; n_explore<4; n_explore++) {               
                int m_next = listnode_now->data.m + explore_rule[n_explore][0];
                int n_next = listnode_now->data.n + explore_rule[n_explore][1];   
                if (maze[m_next][n_next]==0&&!ConfirmMap[m_next][n_next]) { // 不是墙且没有被搜索过
                    auto head_parent = new ListNode(); // 使用头插法
                    head_parent->data = {m_next, n_next};
                    head_parent->next = listnode_now;
                    myQueue.push(head_parent);
                    // 先不释放
                    if (m_next==node_start.m&&n_next==node_start.n) {
                        empty_queue = true;
                        break;
                    }
                }
                ConfirmMap[m_next][n_next] = true;
            }
            myQueue.pop(); // 已BFS的节点滑出

            if (empty_queue) {
                auto node_search = myQueue.back();
                while (node_search->next!=nullptr) { // node_search->next!=nullptr
                    std::cout << '(' << node_search->data.m-1 << ',' << node_search->data.n-1 << ')' << std::endl;
                    node_search = node_search->next;
                }
                std::cout << '(' << node_end.m-1 << ',' << node_end.n-1 << ')' << std::endl;
            }
        }


    }
}
// 64 位输出请用 printf("%lld")