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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty()) return nullptr;
        auto root = new TreeNode();
        root->val = preorder[0];
        if (preorder.size()==1) {
            root->left = nullptr;
            root->right = nullptr;
            return root;
        }

        /*在前序数组中确定根节点*/
        /*功能：服务于终须数组中划分左右子树*/
        int idx_root = 0;
        // root->val = preorder[idx_root];
        /*在中序数组中搜索根节点*/
        /*功能：划分左右子树*/
        int idx_right;
        for (int i=0; i<inorder.size(); i++) {
            if (inorder[i]==root->val) {
                idx_right = i+1;
                break;
            }
        }
        std::vector<int> preArray_left;
        std::vector<int> preArray;
        for (int i=idx_root+1; i<preorder.size(); i++) {
            if (i<idx_right) {
                preArray_left.emplace_back(preorder[i]);
                continue;
            }
            preArray.emplace_back(preorder[i]);
        }
        std::vector<int> inorderArray_right;
        std::vector<int> inorderArray;
        for (int i=0; i<inorder.size(); i++) {
            if (i==idx_right-1) continue;
            if (i<idx_right) {
                inorderArray.emplace_back(inorder[i]);
                continue;
            }
            inorderArray_right.emplace_back(inorder[i]);
        }
        root->left = buildTree(preArray_left, inorderArray);
        root->right = buildTree(preArray, inorderArray_right);
        
        /*前序和中序的特点是，根节点右子树的开始节点在数组中的序号是一致的*/
        return root;
    }

};