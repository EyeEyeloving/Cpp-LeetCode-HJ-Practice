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
        /*首先root节点单独判断*/
        if (p==NULL&&q==NULL) return true;
        if (p==NULL||q==NULL) return false;

        /*Board First Search*/
        /*经过上述判断，p和q都不为NULL*/
        std::queue<TreeNode*> myQueue_p, myQueue_q;
        myQueue_p.emplace(p);
        myQueue_q.emplace(q);
        
        while (!myQueue_p.empty()) {
            int init_size_p = myQueue_p.size();
            while (init_size_p--) {
                auto& front_p = myQueue_p.front();
                auto& front_q = myQueue_q.front();
                if (front_p->val!=front_q->val) return false; // 如果当前遍历的值不相等，则弹出false
                // 如果二叉树的结构不同，则弹出false
                if ((front_p->left==nullptr&&front_q->left!=nullptr)||(front_p->left!=nullptr&&front_q->left==nullptr)) return false;
                if ((front_p->right==nullptr&&front_q->right!=nullptr)||(front_p->right!=nullptr&&front_q->right==nullptr)) return false;
                if (front_p->left!=nullptr) { // 如果有左节点
                    myQueue_p.emplace(front_p->left); 
                    myQueue_q.emplace(front_q->left);                  
                }                
                if (front_p->right!=nullptr) { // 如果有右节点
                    myQueue_p.emplace(front_p->right);
                    myQueue_q.emplace(front_q->right);                 
                }
                // 别忘记弹出
                myQueue_p.pop();
                myQueue_q.pop(); 
            }
        }
        // 只有遍历到最后一刻，才弹出true
        return true;

        
    }
};