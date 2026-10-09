
class Solution {
public:
    int minInsertions(string s) {
        int ans = 0;
        int open = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                open++;
            } 
            else {
                // Every ')' needs another ')' to form '))'
                if (i + 1 < s.size() && s[i + 1] == ')') {
                    i++;
                } 
                else {
                    ans++;
                }

                // Match the closing pair with an opening '('
                if (open > 0) {
                    open--;
                } 
                else {
                    ans++;
                }
            }
        }

        // Each remaining '(' needs two ')'
        ans += open * 2;

        return ans;
    }
};