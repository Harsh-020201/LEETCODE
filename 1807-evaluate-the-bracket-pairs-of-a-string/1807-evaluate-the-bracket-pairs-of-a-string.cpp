class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;

        // Store key -> value
        for (auto &p : knowledge) {
            mp[p[0]] = p[1];
        }

        string ans;

        for (int i = 0; i < s.size(); i++) {

            if (s[i] == '(') {
                string key;
                i++; // move past '('

                // Collect characters until ')'
                while (s[i] != ')') {
                    key += s[i];
                    i++;
                }

                // Replace key with value
                if (mp.count(key))
                    ans += mp[key];
                else
                    ans += "?";
            }
            else {
                ans += s[i];
            }
        }

        return ans;
    }
};