class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size();
        int n = t.size();

        vector<vector<unsigned long long>> dp(
            m + 1,
            vector<unsigned long long>(n + 1, 0)
        );

        // Empty t can be formed in exactly 1 way
        for (int i = 0; i <= m; i++) {
            dp[i][0] = 1;
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {

                // Don't take s[i-1]
                dp[i][j] = dp[i - 1][j];

                // Take s[i-1] if it matches t[j-1]
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] += dp[i - 1][j - 1];
                }
            }
        }

        return dp[m][n];
    }
};