class Solution {
public:
    bool checkValidString(string s) {
        int low = 0;
        int high = 0;

        for (char c : s) {
            if (c == '(') {
                low++;
                high++;
            }
            else if (c == ')') {
                low--;
                high--;
            }
            else { // '*'
                low--;   // '*' acts as ')'
                high++;  // '*' acts as '('
            }

            // high < 0 means too many closing brackets
            if (high < 0)
                return false;

            // We cannot have negative minimum
            if (low < 0)
                low = 0;
        }

        // If zero opens are possible, the string can be valid
        return low == 0;
    }
};