#include <iostream>
#include <map>
#include <queue>
#include <string>

struct WordCheck {
    bool UpperWord = false;
    bool SmallWord = false;
    bool NumbericWord = false;
    bool CharSymbol = false;
    int PassNumber = 0;
};

int main() {
    std::string a;
    
    while (std::cin >> a) { // 注意 while 处理多个 case
        WordCheck word_check;
        std::map<std::string, int> string_same_emus;
        std::queue<char> myQueue;
        if (a.size()<9) {
            std::cout << "NG" << std::endl;
            continue;
        }
        for (auto it = a.begin(); it!=a.end(); it++ ) {
            if (myQueue.size()<2) {
                myQueue.push(*it);
            } else {
                myQueue.push(*it);
                std::string sub_string_element = "";
                std::string str_que_front;
                for (int i=0; i<3; i++) { // 长度大于2
                    str_que_front = myQueue.front();
                    sub_string_element = sub_string_element + str_que_front;
                    myQueue.pop();
                    myQueue.push(str_que_front[0]);//str_que_front直接是不行的
                }
                ++string_same_emus[sub_string_element];
                myQueue.pop();
            }

            int p1 = (*it)-'a';
            int p2 = (*it)-'A';
            int p3 = (*it)-'0';
            if (p1>-1&&p1<26) {
                if (!word_check.SmallWord) ++word_check.PassNumber;
                word_check.SmallWord = true;
                
            } else if (p2>-1&&p2<26) {
                if (!word_check.UpperWord) ++word_check.PassNumber;
                word_check.UpperWord = true;
            } else if (p3>-1&&p3<10) {
                if (!word_check.NumbericWord) ++word_check.PassNumber;
                word_check.NumbericWord = true;
            } else {
                if (!word_check.CharSymbol) ++word_check.PassNumber;
                word_check.CharSymbol = true;
            }
        }

        bool tmp = false;
        for (auto it=string_same_emus.begin(); it!=string_same_emus.end(); it++ ){
            if ((*it).second>1) {
                std::cout << "NG" << std::endl;
                tmp = true;
                break;
            }
        }
        if (tmp) continue;
        
        if (word_check.PassNumber>2) {
            std::cout << "OK" << std::endl;
        } else {
            std::cout << "NG" << std::endl;
        }
    }
    
}
// 64 位输出请用 printf("%lld")