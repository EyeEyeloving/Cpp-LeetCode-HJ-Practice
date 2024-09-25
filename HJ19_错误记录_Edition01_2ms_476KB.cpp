#include <iostream>
#include <queue>
#include <utility>
#include <vector>

struct MESG {
    std::string row_number = "";
    int count = 1;
};

int main() {
    std::queue<std::pair<std::string, MESG>> myQueue;

    std::string a="";
    while (std::getline(std::cin, a) ) { // std::cin >> a 有空格不可以
        std::pair<std::string, MESG> sub_mesg_log;
        std::pair<std::string, MESG> sub_mesg;
        std::string rev_b0="", rev_b1="";
        int n_switch = 0;

        for (auto it = a.rbegin(); it!=a.rend(); it++ ) {
            if ((*it)==' ') {
                n_switch = 1;
                continue;
            }
            if (n_switch==0) {
                rev_b0 = rev_b0 + (*it);
            } else if (n_switch==1) {
                if ((*it)=='\\') break;
                rev_b1 = rev_b1 + (*it);
                if (rev_b1.size()==16) break;
            }
        }
        for (auto it = rev_b0.rbegin(); it!=rev_b0.rend(); it++ ) { // 行号
            sub_mesg_log.second.row_number = sub_mesg_log.second.row_number + (*it);
        }
        for (auto it = rev_b1.rbegin(); it!=rev_b1.rend(); it++ ) { // 文件名
            sub_mesg_log.first = sub_mesg_log.first + (*it);
        }
        
        bool cmd_equal = false;
        int cmd = 0;
        if (myQueue.size()==0) {
            myQueue.push(sub_mesg_log);
            continue;
        }
        int sub_init_queue_size = myQueue.size();
        for (int i=0; i<sub_init_queue_size; i++) {
            sub_mesg = myQueue.front();
            if (!cmd_equal) {
                cmd = sub_mesg.first.compare(sub_mesg_log.first);  
                if (cmd==0) {
                    cmd = sub_mesg.second.row_number.compare(sub_mesg_log.second.row_number);
                    if (cmd==0) {
                        ++sub_mesg.second.count; // ==0 表示相等,其他值表示不相等
                        cmd_equal = true;
                    }                    
                } 
            }
            myQueue.pop();
            myQueue.push(sub_mesg);
        }
        if (!cmd_equal) myQueue.push(sub_mesg_log);  
    }

    int init_queue_size = myQueue.size();
    if (init_queue_size>8) {
        for (int i=0; i<init_queue_size-8; i++) {
            myQueue.pop();
        }
        init_queue_size = 8;
    }
    std::pair<std::string, MESG> sub_mesg_log;
    for (int i=0; i<init_queue_size; i++) {
        sub_mesg_log = myQueue.front();
        std::cout << sub_mesg_log.first << ' ' << sub_mesg_log.second.row_number << ' ' << sub_mesg_log.second.count << std::endl;
        myQueue.pop();
    }
}
// 64 位输出请用 printf("%lld")