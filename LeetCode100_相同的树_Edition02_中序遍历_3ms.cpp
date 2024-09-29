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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        /*中序遍历*/
        /*Base Case*/
        if (p==NULL&&q==NULL) { // 分析结构
            return true;
        } else if (p==NULL||q==NULL) {
            return false;
        }

        /*中序遍历*/
        if (!isSameTree(p->left, q->left)) { // 递归调用
            return false;
        }
        if (p->val!=q->val) {
            return false;
        }
        if (!isSameTree(p->right, q->right)) { // 递归调用
            return false;
        }

        return true;  // 前面都没问题，则递归到本层
        
        
    }
};