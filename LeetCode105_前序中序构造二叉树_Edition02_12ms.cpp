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
        return establishSolution(preorder, -1, preorder.size(), inorder, -1, inorder.size());
    }

    TreeNode* establishSolution(vector<int>& preorder, int ptra_pre, int ptrb_pre, 
        vector<int>& inorder, int ptra_inor, int ptrb_inor) {
            /*参数涵义：
            preorder: 左闭右闭区间为0-N-1；
            ptra_pre: 指向preorder数组的起始位置地址/索引，即-1；
            ptrb_pre: 指向preorder数组的末端位置地址/索引，即N*/
            if (ptra_pre+1==ptrb_pre) return nullptr; // inorder不需要判断，因为长度一致

            auto root = new TreeNode();
            root->val = preorder[ptra_pre+1];
            /*数组有一个元素*/
            if (ptra_pre+2==ptrb_pre) return root;

            /*数组至少有两个元素*/
            // 子树根节点一定存在
            int ptr_root; // = -1; // 则一定找得到
            for (int i=ptra_inor+1; i<ptrb_inor; i++) {
                if (inorder[i]==root->val) {
                    /*找到中序数组中该root的位置*/
                    ptr_root = i;
                    break;
                }
            }
            
            /*以下做法错误的原因：每一次进入递归的两个数组的索引并不对齐；因此其逻辑只有第一次分割左右子树才成立*/
            // root->left = establishSolution(preorder, ptra_pre, ptr_root+1, 
            //     inorder, ptra_inor, ptr_root);
            // root->right = establishSolution(preorder, ptr_root, ptrb_pre, 
            //     inorder, ptr_root, ptrb_inor);

            /*中序数组可以确定左子树的长度*/
            int left_tree_size = ptr_root-ptra_inor; // 左开右闭数组区间

            // 在前序数组和中序数组中分割左子树
            root->left = establishSolution(preorder, ptra_pre+1, ptra_pre+1+left_tree_size, 
                inorder, ptra_inor, ptr_root);

            // 在前序数组和中序数组中分割右子树
            root->right = establishSolution(preorder, ptra_pre+left_tree_size, ptrb_pre, 
                inorder, ptr_root, ptrb_inor);

            return root;

    }

    // TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    //     if (preorder.empty()) return nullptr;
    //     auto root = new TreeNode();
    //     root->val = preorder[0];
    //     if (preorder.size()==1) {
    //         root->left = nullptr;
    //         root->right = nullptr;
    //         return root;
    //     }

    //     /*在前序数组中确定根节点*/
    //     /*功能：服务于终须数组中划分左右子树*/
    //     int idx_root = 0;
    //     // root->val = preorder[idx_root];
    //     /*在中序数组中搜索根节点*/
    //     /*功能：划分左右子树*/
    //     int idx_right;
    //     for (int i=0; i<inorder.size(); i++) {
    //         if (inorder[i]==root->val) {
    //             idx_right = i+1;
    //             break;
    //         }
    //     }
    //     std::vector<int> preArray_left;
    //     std::vector<int> preArray;
    //     for (int i=idx_root+1; i<preorder.size(); i++) {
    //         if (i<idx_right) {
    //             preArray_left.emplace_back(preorder[i]);
    //             continue;
    //         }
    //         preArray.emplace_back(preorder[i]);
    //     }
    //     std::vector<int> inorderArray_right;
    //     std::vector<int> inorderArray;
    //     for (int i=0; i<inorder.size(); i++) {
    //         if (i==idx_right-1) continue;
    //         if (i<idx_right) {
    //             inorderArray.emplace_back(inorder[i]);
    //             continue;
    //         }
    //         inorderArray_right.emplace_back(inorder[i]);
    //     }
    //     root->left = buildTree(preArray_left, inorderArray);
    //     root->right = buildTree(preArray, inorderArray_right);
        
    //     /*前序和中序的特点是，根节点右子树的开始节点在数组中的序号是一致的*/
    //     return root;
    // }

    

};