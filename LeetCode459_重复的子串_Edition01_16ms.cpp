class Solution {
public:
    bool repeatedSubstringPattern(string s) {

        // 若next数组的最后一位不为0，则返回true

        int size_s = s.size(); // 字符串的长度
        int next[size_s]; // 配置next数组
        std::memset(next, 0, sizeof(next)); // 初始化

        int ptr_maxcomm_latt = 0; // 记录当前匹配的最长公共前缀末尾的下一位索引

        for (int ptr_newchar = 1; ptr_newchar < size_s; ptr_newchar++) { // ptr_newchar 是新纳入分析的字符
            // 如果新加入的字符与最长公共前缀末尾的下一位字符不匹配
            while (ptr_maxcomm_latt > 0 && s[ptr_newchar] != s[ptr_maxcomm_latt]) {
                ptr_maxcomm_latt = next[ptr_maxcomm_latt-1]; // 不匹配，找到最长公共前缀的末位对应的next数组，从而找到下一个最长公共前缀末尾的下一位
                //（next）数组就是找最长公共前缀的末位的下一位字符的索引
            }

            // 如果新加入的字符与最长公共前缀的下一位字符匹配
            if (s[ptr_newchar] == s[ptr_maxcomm_latt]) {
                ptr_maxcomm_latt++;
            }

            // 更新 next 数组
            next[ptr_newchar] = ptr_maxcomm_latt;
        }

        // for (int i = 0; i<size_s; i++) {
        //     std::cout << next[i] << ' ';
        // }
        // std::cout << std::endl;
        
        // 寻找最小重复子串
        if (next[size_s-1]==0) return false; // 排除没有最长公共前后缀的情况
        int min_common = size_s - next[size_s-1];
        if (size_s%min_common==0) return true; // 如果能被该最小重复子串整除，即余0
        return false;
    }
};