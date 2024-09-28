/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        auto Head = new ListNode();
        Head->val = 0;
        Head->next = nullptr;
        auto Ans = new ListNode();
        Ans = Head;
        Ans = iterateAddTwoNumbers(Ans, l1, l2, 0);

        return Head->next;
        // while (Ans!=nullptr) {
        //     std::
        // }
    }

    ListNode* iterateAddTwoNumbers(ListNode* Ans, ListNode* l1, ListNode* l2, int addin) {
        int& a = l1->val;
        int& b = l2->val;
        auto tmp = new ListNode();
        tmp->next = nullptr;
        if (a+b+addin>9) { // 如果需要进位
            tmp->val = a+b+addin-10;
            addin = 1;
        } else {
            tmp->val = a+b+addin;
            addin = 0;
        }
        Ans->next = tmp;
        Ans = Ans->next;

        if (l1->next==nullptr&&l2->next==nullptr) {
            if (addin==1) { // 看是否还需要进位
                auto tmp2 = new ListNode();
                tmp2->val = 1;
                tmp2->next = nullptr;
                Ans->next = tmp2;
                Ans = Ans->next;
            }
            return Ans;
        }

        if (l1->next==nullptr) { // 如果l1是最后一个节点
            l1->val = 0; 
        } else {
            l1 = l1->next;
        } 
        if (l2->next==nullptr) {
            l2->val = 0;
        } else {
            l2 = l2->next;
        }
        return iterateAddTwoNumbers(Ans, l1, l2, addin);// 不能传入nullptr
    }
};