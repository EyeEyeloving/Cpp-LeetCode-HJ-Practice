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
    std::vector<TreeNode*> myVector;
public:
    /*二叉搜索树的中序遍历是递增序列*/
    void middleTraversal(TreeNode* root) {
        if (root==NULL) return;
        
        middleTraversal(root->left);
        myVector.emplace_back(root);
        middleTraversal(root->right);
    }

    // void recoverTree(TreeNode* root)
    void recoverTree(TreeNode* root) {
        middleTraversal(root);
        if (myVector.empty()) return;
        if (myVector.size()==1) return;
        
        auto copy_Vector = myVector;
        std::sort(copy_Vector.begin(), copy_Vector.end(), [](TreeNode* a, TreeNode* b){
            return (a->val)<(b->val);
        });
        int a=-1, b=-1;
        for (int i=0; i<myVector.size(); i++) {
            if (myVector[i]!=copy_Vector[i]) {
                if (a==-1) {
                    a = i;
                    continue;
                }
                b = i;
                break;
            }
        }
        int tmp = myVector[a]->val;
        myVector[a]->val = myVector[b]->val;
        myVector[b]->val = tmp;
        return;

    }
};