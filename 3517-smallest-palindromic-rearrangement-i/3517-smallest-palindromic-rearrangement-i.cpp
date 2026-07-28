class Solution {
public:
    string smallestPalindrome(string s) {
        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        string left = "";
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            left.append(cnt[i] / 2, char('a' + i));

            if (cnt[i] % 2)
                mid = char('a' + i);
        }

        string ans = left;

        if (mid)
            ans += mid;

        reverse(left.begin(), left.end());
        ans += left;

        return ans;
    }
};