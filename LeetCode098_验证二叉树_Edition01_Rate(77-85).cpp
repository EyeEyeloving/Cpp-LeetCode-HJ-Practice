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
    /*原自己编写的代码只能保证每一个子二叉树是有效的*/
    bool isValidBST(TreeNode* root) {
        if (root==NULL) return true; // 如果遍历到最后的空节点还没有false，则返回true
        
        if (!isValidBST(root->left)) return false;
        if (!isValidBST(root->right)) return false;

        if (root->left!=nullptr) {
            if (root->left->val >= root->val) return false;
        }
        if (root->right!=nullptr) {
            if (root->val >= root->right->val) return false;
        }

        return true;

        // return validateBST(root, LONG_MIN, LONG_MAX);
    }

    /*题目中的左子树应该视为一个整体，即左侧所有元素均小于根节点*/
    // bool validateBST(TreeNode* root, long long boundary_mmin, long long boundary_mmax) {
    //     if (root==NULL) return true; // 如果遍历到最后的空节点还没有false，则返回true
        
    //     /*当前节点的值应该在左右子节点的值组成的开区间当中*/
    //     if (root->val <= boundary_mmin || root->val >= boundary_mmax) return false; 

    //     return validateBST(root->left, boundary_mmin, root->val)&&validateBST(root->right, root->val, boundary_mmax);
    // }

};