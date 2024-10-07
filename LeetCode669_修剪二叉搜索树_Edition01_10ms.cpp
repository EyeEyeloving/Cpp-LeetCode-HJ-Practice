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
    /*However，后序遍历要递归所有的子树*/

    // 既然已经获得了修剪后的左右子树，那么左右子树就不必再判断
    // TreeNode* trimBST(TreeNode* root, int low, int high) {
    //     if (root==NULL) return root; // 如果遍历到空节点，则返回
    //     /*需要修剪的情况*/
    //     root->left = trimBST(root->left, low, high); 
    //     root->right = trimBST(root->right, low, high); 

    //     if (root->val<low) {
    //         if (root->right==nullptr) return nullptr;
    //         if (root->right->val<=high && root->right->val>=low) return root->right;
    //         return nullptr;
    //     }
    //     if (root->val>high) {
    //         if (root->left==nullptr) return nullptr;
    //         if (root->left->val<=high && root->left->val>=low) return root->left;
    //         return nullptr;
    //     }
    //     return root;
    // }

    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (root==NULL) return root; // 如果遍历到空节点，则返回
        /*需要修剪的情况*/
        root->left = trimBST(root->left, low, high); 
        root->right = trimBST(root->right, low, high); 

        if (root->val<low) return root->right;
        if (root->val>high) return root->left; 
        return root;
    }
};