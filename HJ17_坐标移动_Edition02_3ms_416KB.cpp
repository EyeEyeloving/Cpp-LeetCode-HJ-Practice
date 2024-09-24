#include <iostream>
#include <string>

struct iterString {
    std::string a; // 剩余的字符串
    std::string b; // 当前需要讨论的字符串
    bool empty = false;
};

void Log(int& x, int& y){
    std::cout<<x<<","<<y<<std::endl;
};

iterString getInput(std::string& a){
    std::string b;
    int size_a = a.size();
    for (int i=0; i<size_a-1; i++) { // 不包含最后一个";"
        if (a[i]==';') return {a.erase(0, i+1), b, false};
        b = b + a[i];
    }
    return {a.erase(0), b, true};
};

int checkInput(std::string& a) {
    int size_a = a.size();
    if (size_a>3||size_a<2) return -1;
    if (a[1]<'0'||a[1]>'9') return -1;
    if (size_a==3&&(a[2]<'0'||a[2]>'9')) return -1;
    return 0;
};

int main() {
    std::string a;
    int x=0;
    int y=0;
    /*一行字符串,包括了完整的方向输入*/
    while (std::cin >> a ) { // 注意 while 处理多个 case
        iterString string_input;
        string_input.a = a;
        while (!string_input.empty) {
            string_input = getInput(string_input.a);
            int mesg = checkInput(string_input.b);
            if (mesg==-1) {
                // Log(x, y);
                continue;
            }

            int size_b = string_input.b.size();
            if (size_b==2) {
                /*Cpp字符串不能用switch...case*/
                if (string_input.b[0]=='A') x = x-(int)(string_input.b[1]-'0');
                if (string_input.b[0]=='D') x = x+(int)(string_input.b[1]-'0');
                if (string_input.b[0]=='W') y = y+(int)(string_input.b[1]-'0');
                if (string_input.b[0]=='S') y = y-(int)(string_input.b[1]-'0');
                // Log(x, y);
                if (string_input.a.empty()) {
                    Log(x, y);
                    break;
                }
                continue;
            }
            if (size_b==3) { 
                if (string_input.b[0]=='A') x = x-(int)(string_input.b[1]-'0')*10-(int)(string_input.b[2]-'0');
                if (string_input.b[0]=='D') x = x+(int)(string_input.b[1]-'0')*10+(int)(string_input.b[2]-'0');
                if (string_input.b[0]=='W') y = y+(int)(string_input.b[1]-'0')*10+(int)(string_input.b[2]-'0');
                if (string_input.b[0]=='S') y = y-(int)(string_input.b[1]-'0')*10-(int)(string_input.b[2]-'0');
                // Log(x, y);
                if (string_input.a.empty()) {
                    Log(x, y);
                    break;
                }
                continue;
            }

            
        }
    }
}
// 64 位输出请用 printf("%lld")