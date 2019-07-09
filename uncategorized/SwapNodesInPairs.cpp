#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution{
    public:
        ListNode* swapPairs(ListNode* head) {
            if(head == nullptr || head->next == nullptr) return head;
            ListNode dummy(-1); dummy.next = head;
            auto cur = head, prev = &dummy;
            while(cur != nullptr && cur->next != nullptr){
                auto next_cur = cur->next->next;
                cur->next->next = cur;
                prev->next = cur->next;
                cur->next = next_cur;
                prev = cur;
                cur = next_cur;
            }
            return dummy.next;
        }
};