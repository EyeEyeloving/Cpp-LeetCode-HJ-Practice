#include <iostream>

/*用new的变量进行赋值就是有了另一个新的内存地址，那么之前的节点应该重新链接到这个新地址，否则会链表会断；
在有新增节点的时候必须用到new，因为目的就是开辟一个新的内存空间*/

struct ListNode {
    int data;
    ListNode* next;
};

ListNode* insertNodes(ListNode* node_insert, int nodedata_target, ListNode* head) {
    // auto tmp = new ListNode();
    // tmp = head;
    ListNode* tmp = head;
    while (tmp->data!=nodedata_target) {
        if (tmp->next==nullptr) break;
        tmp = tmp->next;
    }

    if (tmp->next==nullptr) { // 如果在节点末尾
        tmp->next = node_insert;
    } else if (tmp==head) { // 如果头节点是目标
        tmp = head->next;
        node_insert->next = tmp;
        head->next = node_insert;
    } else { // 如果在中间???
        // 应该插在tmp后面
        node_insert->next = tmp->next;
        tmp->next = node_insert;
    }
    return head;
};

ListNode* deleteNodes(ListNode* a, ListNode* head){
    // auto tmp = new ListNode();
    // auto tmp_before = new ListNode();

    ListNode* tmp = head;
    ListNode* tmp_before;
    while (tmp->data!=a->data) {
        if (tmp->next==nullptr) break;
        tmp_before = tmp;
        tmp = tmp->next;
    }

    if (tmp==head) {
        head = head->next;
    } else {
        tmp_before->next = tmp->next;
    }
    return head;
};

int main() {
    int listnode_number, head_data;
    while (std::cin >> listnode_number >> head_data) { // 注意 while 处理多个 case
        auto Head = new ListNode();
        Head->data = head_data;
        Head->next = nullptr;

        for (int i=1; i<listnode_number; i++) {
            int node_insert, pos_next_insert;
            std::cin >> node_insert >> pos_next_insert;
            
            auto tmp = new ListNode();
            tmp->data = node_insert;
            tmp->next = nullptr;
            Head = insertNodes(tmp, pos_next_insert, Head);
        }

        int pos_next_delete;
        std::cin >> pos_next_delete;
        auto tmp3 = new ListNode();
        tmp3->data = pos_next_delete;
        tmp3->next = nullptr;
        Head = deleteNodes(tmp3, Head);

        while (Head!=nullptr) {
            std::cout << Head->data << " ";
            Head = Head->next;
        }
    }
}
// 64 位输出请用 printf("%lld")