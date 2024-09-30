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
    bool isSymmetric(TreeNode* root) {
        if (root==NULL) return true;
        return isSubTreesSymmetric(root->left, root->right);
        // return isSubTreesSymmetric(root, root); // LeetCode Official Solution : 0ms
    }

    bool isSubTreesSymmetric(TreeNode* subTrees_left, TreeNode* subTrees_right) {
        if (subTrees_left==NULL&&subTrees_right==NULL) return true;
        if (subTrees_left==NULL||subTrees_right==NULL) return false;
        if (subTrees_left->val!=subTrees_right->val) return false;
        
        /*先是一个节点然后再向下遍历左右节点，但最后结果是从下往上返的，从获取结果的构成来说是后序的*/
        if (!isSubTreesSymmetric(subTrees_left->left, subTrees_right->right)) return false;
        if (!isSubTreesSymmetric(subTrees_left->right, subTrees_right->left)) return false;
        return true;

        /*合在一起return跳出false就慢了*/
        // return isSubTreesSymmetric(subTrees_left->left, subTrees_right->right) && 
        // isSubTreesSymmetric(subTrees_left->right, subTrees_right->left);
    }
};