class Solution {
public:
    string reverseParentheses(string s) {
        stack<string> st;
        string cur = "";

        for (char ch : s) {

            if (ch == '(') {
                st.push(cur);
                cur = "";
            }
            else if (ch == ')') {
                reverse(cur.begin(), cur.end());

                cur = st.top() + cur;
                st.pop();
            }
            else {
                cur += ch;
            }
        }

        return cur;
    }
};