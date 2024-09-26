#include <cmath>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

struct NODE {
    int m;
    int n;
    int pre_m;
    int pre_n;
};



int main() {
    int size_row, size_col;
    std::vector<NODE> queue_save;
    while (std::cin >> size_row >> size_col) { // 注意 while 处理多个 case
        /*创建一个大一圈的矩阵，这样搜索就不用额外讨论边界*/
        int maze[size_row+2][size_col+2];
        std::memset(maze, 1, sizeof(maze));
        /*创建一个搜索矩阵*/
        bool searchlist[size_row+2][size_col+2];
        std::memset(searchlist, false, sizeof(searchlist));
        /*填充迷宫信息，从1开始*/
        for (int n = 1; n<size_row+1; n++) {
            for (int m = 1; m<size_col+1; m++) {
                std::cin >> maze[n][m];
                // std::cout << maze[n][m] << ' '; //数组
            }
            // std::cout << std::endl;
        }

        std::queue<NODE> myQueue;
        NODE head_node = {1, 1, NULL, NULL};
        NODE target_node = {size_row, size_col, NULL, NULL};  
        myQueue.push(head_node);
        searchlist[1][1] = true; // 因为起点已经访问
        int explore_step_rule[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        bool emptyqueue = false;
        while (!emptyqueue) {
            /*board first search*/
            int init_queue_size = myQueue.size();
            NODE node_now = myQueue.front(); // 首部
            for (int n_explore=0; n_explore<4; n_explore++ ) {
                int m_next = node_now.m + explore_step_rule[n_explore][0];
                int n_next = node_now.n + explore_step_rule[n_explore][1];
                if (maze[m_next][n_next]==0&&!searchlist[m_next][n_next]) {
                    myQueue.push({m_next, n_next, node_now.m, node_now.n});
                    searchlist[m_next][n_next] = true;
                    if (m_next==target_node.m&&n_next==target_node.n) {
                        target_node.pre_m=node_now.m;
                        target_node.pre_n=node_now.n;
                        emptyqueue = true;
                        break;
                    }
                }
            }
            queue_save.push_back(node_now);
            myQueue.pop(); // 出队

            /*输出队列*/
            if (emptyqueue) {
                queue_save.push_back(target_node);
                std::vector<NODE> output_path;
                output_path.push_back(target_node);
                for (auto it=queue_save.rbegin(); it!=queue_save.rend(); it++) {
                    if ((*it).m==queue_save.back().pre_m&&(*it).n==queue_save.back().pre_n) {
                        output_path.push_back(*it);
                        queue_save.back() = *it;
                    } 
                }
                for (auto it=output_path.rbegin(); it!=output_path.rend(); it++) {
                    std::cout << '(' << (*it).m-1 << ',' << (*it).n-1 << ')' << std::endl;
                }
            }
        }
    }
}
// 64 位输出请用 printf("%lld")