/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    /*实际上，有序数组构成二叉搜索树，这个有序数组一定是这个二叉搜索树的中序遍历*/
    /*从绘图上来看，平衡二叉树的根节点可能不唯一，但是中序遍历的结果是确定的有序数组*/
    /*答案的遍历是前序遍历*/
    /*对于case 1，平衡二叉树[5, -3, 9, -10, 0, null, null]应该也是对的；多解；应试的话，就是根节点取0*/
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if (nums.empty()) return nullptr;
        return arrangeBST(nums, -1, nums.size());
        // 如果是引用，则不能传入具体数字，如-1，也不能传入表达式，如iMiddle-1
    }

    TreeNode* arrangeBST(vector<int>& nums, int iLeft, int iRight) {
        if (iLeft+1==iRight) return nullptr; // 终止条件
        // int iLeft = -1;
        // int iRight = nums.size();
        int iMiddle = (iLeft+iRight)/2; // 找中间节点
        auto root = new TreeNode();
        root->val = nums[iMiddle];
        root->left = arrangeBST(nums, iLeft, iMiddle); // 使用的是二分法搜索（初始左：-1；初始右：N）
        // 如此就没有什么左闭右开或左闭右闭的说法
        root->right = arrangeBST(nums, iMiddle, iRight);
        return root;
    }
};