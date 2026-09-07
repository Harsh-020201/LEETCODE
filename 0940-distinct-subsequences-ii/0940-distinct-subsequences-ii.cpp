class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1e9 + 7;
        
        int n = s.size();
        vector<long long> dp(n + 1, 0);
        
        dp[0] = 1; // empty subsequence
        
        vector<int> last(26, -1);
        
        for (int i = 1; i <= n; i++) {
            int c = s[i - 1] - 'a';
            
            // Every existing subsequence can either
            // include or exclude the current character
            dp[i] = (2 * dp[i - 1]) % MOD;
            
            // Remove duplicate subsequences
            if (last[c] != -1) {
                dp[i] = (dp[i] - dp[last[c]] + MOD) % MOD;
            }
            
            last[c] = i - 1;
        }
        
        // Remove empty subsequence
        return (dp[n] - 1 + MOD) % MOD;
    }
};