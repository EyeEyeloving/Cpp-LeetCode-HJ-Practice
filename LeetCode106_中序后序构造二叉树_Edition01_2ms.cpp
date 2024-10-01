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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return establishTree(inorder, -1, inorder.size(), postorder, -1, postorder.size());
    }

    TreeNode* establishTree(vector<int>& inorder, int in_begin, int in_end, 
        vector<int>& postorder, int post_begin, int post_end) {
            /*传入的数组范围是左开右开区间*/
            if (in_begin+1==in_end) return nullptr; // 传入数组为空
            auto root = new TreeNode();
            root->val = postorder[post_end-1]; // 后序遍历数组可以知道根节点
            if (in_begin+2==in_end) return root; // 传入数组只有一个元素

            int idx_root;
            for (int i=in_begin+1; i<in_end; i++) {
                if (inorder[i]==root->val) {
                    idx_root = i; // 在中序遍历数组中查找该根节点
                }
            }
            // 由于子树分割递归导致中序后序数组不对齐，所以求得的root索引只能用于中序数组
            // 由中序遍历数组可以求当前根节点的右子树的长度，从而分割子树数组的左开右开区间
            int right_tree_size = in_end-idx_root-1; // 左开右开区间
            root->right = establishTree(inorder, idx_root, in_end, 
                postorder, post_end-1-right_tree_size-1, post_end-1);
            // 中序数组求得的root与后序数组没有索引对应关系，要通过子树长度来确定
            root->left = establishTree(inorder, in_begin, idx_root, 
                postorder, post_begin, post_end-1-right_tree_size);
            return root;
    }
};