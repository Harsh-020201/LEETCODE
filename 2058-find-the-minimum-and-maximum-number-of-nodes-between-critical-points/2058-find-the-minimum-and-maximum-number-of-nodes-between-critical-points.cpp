class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int index = 1;

        int firstCritical = -1;
        int lastCritical = -1;

        int minDistance = INT_MAX;
        int maxDistance = -1;

        ListNode* prev = head;
        ListNode* curr = head->next;

        while (curr->next != NULL) {

            bool isCritical = false;

            if ((curr->val > prev->val && curr->val > curr->next->val) ||
                (curr->val < prev->val && curr->val < curr->next->val)) {
                
                isCritical = true;
            }

            if (isCritical) {

                if (firstCritical == -1) {
                    firstCritical = index;
                } 
                else {
                    minDistance = min(minDistance, index - lastCritical);
                    maxDistance = index - firstCritical;
                }

                lastCritical = index;
            }

            prev = curr;
            curr = curr->next;
            index++;
        }

        if (minDistance == INT_MAX) {
            return {-1, -1};
        }

        return {minDistance, maxDistance};
    }
};