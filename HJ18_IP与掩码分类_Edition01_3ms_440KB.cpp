#include <cmath>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

/*写在前面：-----------------------------------------
主要错在“非法子网掩码”的判断上，这可能涉及专业的知识（实例用例“255.255.2.0”是合法还是非法？）
实际上每一个字段“255/255/2/0”转换为二进制以后应该是“0000 0000”（而不是“例如 2=>10”便以为也符合条件）*/

struct Address {
    std::string ipaddr1 = "";
    std::string ipaddr2 = "";
    std::string ipaddr3 = "";
    std::string ipaddr4 = "";
};

struct IPRange {
    std::string iprange1 = "";
    std::string iprange2 = "";
};

/*把两个IP地址分开*/
IPRange separateIPRange(std::string& a) {
    int n_switch = 1;
    std::string iprange1, iprange2;
    for (auto it=a.begin(); it!=a.end(); it++) {
        if ((*it)=='~') {
            n_switch = 2;
            continue;
        }

        switch (n_switch) { 
            case 1: iprange1 = iprange1 + (*it); break; // switch 都要加 break
            case 2: iprange2 = iprange2 + (*it); break;
        }
        // if (n_switch == 1) iprange1 = iprange1 + (*it);
        // if (n_switch == 2) iprange2 = iprange2 + (*it);
    }
    return {iprange1, iprange2};
};

/*把每个IP地址的元素分开*/
Address getAddressElement(std::string& b) {
    int n_switch = 1;
    std::string ipaddr1, ipaddr2, ipaddr3, ipaddr4;
    for (auto it=b.begin(); it!=b.end(); it++) {
        if ((*it)=='.') { // if () statement // statement只能一句
            ++n_switch;
            continue;
        } 
        if (n_switch==5) { // 如果字段数多于4个
            if (*it!='\0') ipaddr1 = "256";
        }
        if (n_switch==5) return {ipaddr1, ipaddr2, ipaddr3, ipaddr4};
        switch (n_switch) {
            case 1: ipaddr1 = ipaddr1 + (*it); break;
            case 2: ipaddr2 = ipaddr2 + (*it); break;
            case 3: ipaddr3 = ipaddr3 + (*it); break;
            case 4: ipaddr4 = ipaddr4 + (*it); break;
        }
    }
    return {ipaddr1, ipaddr2, ipaddr3, ipaddr4};
};

/*是不是非法IP*/
bool subCheckAddressElement(std::string ipaddr) {
    if (ipaddr.empty()) return true; // 如果字段为空
    if (ipaddr.size()>3) return true; // 如果字段太长
    if (ipaddr.size()>1) { // '1.01.0.1'非法
        if (ipaddr[0]=='0') return true;
    }
    for (auto it=ipaddr.begin(); it!=ipaddr.end(); it++) { // 如果字段存在空格
        if ((*it)==' ') return true;
    }
    int int_ip; // 如果字段大于255
    if (ipaddr.size()==3) {
        int_ip = (ipaddr[0]-'0')*100+(ipaddr[1]-'0')*10+ipaddr[2]-'0';
        if (int_ip>255) return true;
    }
    /*如果出现非法字符*/
    for (auto it=ipaddr.begin(); it!=ipaddr.end(); it++) {
        int res = (*it)-'0';
        if (res<0 || res>9) return true;
    }
    return false;
};

bool checkAddressElement(Address& a){
    if (subCheckAddressElement(a.ipaddr1)) return true;

    if (subCheckAddressElement(a.ipaddr2)) return true;

    if (subCheckAddressElement(a.ipaddr3)) return true;

    if (subCheckAddressElement(a.ipaddr4)) return true;

    return false;
};

/*是不是私网IP*/
int checkPriviateAddress(Address& a) {
    if (a.ipaddr1.size()==2) {
        if (a.ipaddr1[0]!='1'||a.ipaddr1[1]!='0') return 0;// a.ipaddr1=='10'?报错
        return 1; 
    }
    if (a.ipaddr1.size()==3) {
        // if (a.ipaddr1[0]!='1'||a.ipaddr1[1]!='7'||a.ipaddr1[1]!='9'||a.ipaddr1[2]!='2') return 0; // 求互补集合理解错误
        if (a.ipaddr1[0]!='1'||(a.ipaddr1[1]!='7'&&a.ipaddr1[1]!='9')||a.ipaddr1[2]!='2') return 0;
        if (a.ipaddr2.size()==3) {
            if (a.ipaddr2[0]!='1'||a.ipaddr2[1]!='6'||a.ipaddr2[2]!='8') return 0;
            return 1;
        }
        if (a.ipaddr2.size()==2) {
            int subrange = (int)(a.ipaddr2[0]-'0')*10+(int)(a.ipaddr2[1]-'0')-16; //(a.ipaddr2[0]-'1')*10+a.ipaddr2[1]-'6';
            if ( subrange>15 || subrange<0 ) return 0;
            return 1;
        }
        // return 0;
    }
    return 0;
};

/*是不是非法子网掩码*/
int binarytoint(std::string& ipaddr) {
    int bit = -1;
    int bit_a;
    int int_a = 0;
    for (auto it=ipaddr.rbegin(); it!=ipaddr.rend(); it++) {
        ++bit;
        bit_a = std::pow(10, bit)*((int)(*it)-'0'); // 若bit_a为int类型,会溢出
        int_a = int_a + bit_a;
    }
    return int_a;
    //return sumBinary(inv_a, binary_sum);//sumBinary(int_a+1, ...)不能用公式替换传入参数,这是因为传入参数是"引用"而不是"拷贝"
};

struct EachBinary {
    bool first_enter = true;
    bool zero_stop = false;
    bool illegal = false;
};

EachBinary checkEachBinary(int& int_a, bool& first_enter, bool& zero_stop){
    int bit = 1;
    while (bit<9) { // while(int_a!=1)
        /*特别的,实际上每一位转换为二进制以后都是 0000 0000,其中2^8-1=255*/

        if (first_enter) { // 如果第一位进制就是1,肯定非法
            if (int_a%2==1) return {false, false, true};
            first_enter = false;
        }
        if (zero_stop) { // 0已经完全结束;如果再出现0,就非法
            if (int_a%2==0) return {first_enter, zero_stop, true};
        }
        if (int_a==0) {// strongen
            // zero_stop = true;
            break; 
        }
        if (int_a%2==1) zero_stop = true; // 第一次出现1,则0应当完全结束
        int_a = int_a/2;
        ++bit;
    }
    return {first_enter, zero_stop, false};
};

bool checkMaskCodeElement(Address& ipaddr) {
    // int inv_a = int_a+1;
    // int init_sum = 0;
    // int binary_sum = sumBinary(inv_a, init_sum); 
    // //sumBinary(int_a+1, 0)是不能的,"引用"不能是"具体值"而应该是"变量名"
    // //sumBinary需要在前方,否则就需要事先声明
    // if (binary_sum==1) return true;//是非法掩码
    
    EachBinary each_binary;
    int int_a;
    bool first_enter = true;
    bool zero_stop = false;

    int_a = binarytoint(ipaddr.ipaddr4);
    each_binary = checkEachBinary(int_a, first_enter, zero_stop);
    if(each_binary.illegal) return true;
    int_a = binarytoint(ipaddr.ipaddr3);
    each_binary = checkEachBinary(int_a, each_binary.first_enter, each_binary.zero_stop);
    if(each_binary.illegal) return true;
    int_a = binarytoint(ipaddr.ipaddr2);
    each_binary = checkEachBinary(int_a, each_binary.first_enter, each_binary.zero_stop);
    if(each_binary.illegal) return true;
    int_a = binarytoint(ipaddr.ipaddr1);
    each_binary = checkEachBinary(int_a, each_binary.first_enter, each_binary.zero_stop);
    if(each_binary.illegal) return true;
    if(!each_binary.zero_stop) return true; // 如果一直不停止0,则也是非法
    return false;
};

/*IP分类*/
std::vector<int> checkAddressClass(Address& a) {
    // int class_count_array[5];
    // int class_count_array[5] = {0, 0, 0, 0, 0};
    std::vector<int> class_count_array(5, 0);
    /*判断A类*/
    if (a.ipaddr1.size()==1&&(a.ipaddr1[0]-'0')>0) ++class_count_array[0];
    if (a.ipaddr1.size()==2) ++class_count_array[0];
    if (a.ipaddr1.size()==3) {
        int int_ip1 = (int)(a.ipaddr1[0]-'0')*100+(int)(a.ipaddr1[1]-'0')*10+(int)(a.ipaddr1[2]-'0');
        if (int_ip1<127) {
            ++class_count_array[0];
            return class_count_array;
        }
        /*判断B类*/
        if (int_ip1>127&&int_ip1<192) {
            ++class_count_array[1];
            return class_count_array;
        }
        /*判断C类*/
        if (int_ip1<224) {
            ++class_count_array[2];
            return class_count_array;
        } 
        /*判断D类*/
        if (int_ip1<240) {
            ++class_count_array[3];
            return class_count_array;
        } 
        /*判断E类*/
        if (int_ip1<256) {
            ++class_count_array[4];
            return class_count_array;
        }
    }
    return class_count_array;
};

int main() {
    int count_array[7] = {0,0,0,0,0,0,0}; // 统计A、B、C、D、E、错误IP地址或错误掩码、私有IP的个数
    std::string a;
    /*每行一个IP地址和掩码，用~隔开*/
    while (std::getline(std::cin, a)) { // 注意 while 处理多个 case
        /*只要IP地址不合法/错误或子网掩码非法/错误,都单独归类*/
        IPRange iprange = separateIPRange(a);
        Address ipa = getAddressElement(iprange.iprange1);
        Address ipb = getAddressElement(iprange.iprange2);

        if (ipa.ipaddr1.size()==1) {
            if (ipa.ipaddr1[0]-'0'==0) continue;
        }
        if (ipa.ipaddr1.size()==3) {
            int int_ip1 = (ipa.ipaddr1[0]-'0')*100+(ipa.ipaddr1[1]-'0')*10+ipa.ipaddr1[2]-'0';
            if (int_ip1==127) continue;
        }
        if (ipb.ipaddr1.size()==1) {
            if (ipb.ipaddr1[0]-'0'==0) continue;
        }
        if (ipb.ipaddr1.size()==3) {
            int int_ip1 = (ipb.ipaddr1[0]-'0')*100+(ipb.ipaddr1[1]-'0')*10+ipb.ipaddr1[2]-'0';
            if (int_ip1==127) continue;
        }

        if(checkAddressElement(ipa)||checkAddressElement(ipb)||checkMaskCodeElement(ipb)) { // 多判断了一个127
            ++count_array[5];
            continue;
        } 
        std::vector<int> sub_count_array = checkAddressClass(ipa);
        
        for (int i=0; i<5; i++) {
            count_array[i] = count_array[i] + sub_count_array[i];
        }
        count_array[6] = count_array[6] + checkPriviateAddress(ipa);
        
    }
    for (int i=0; i<7; i++) {
        std::cout << count_array[i];
        if (i<6) std::cout << ' ';
    }
}
// 64 位输出请用 printf("%lld")