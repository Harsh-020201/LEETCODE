class Solution {
public:
    int n;
    vector<int> suffix;
    vector<vector<int>> dp;

    int solve(int i, int M) {
        if (i >= n)
            return 0;

        if (dp[i][M] != -1)
            return dp[i][M];

        // Can take all remaining stones
        if (2 * M >= n - i)
            return dp[i][M] = suffix[i];

        int ans = 0;

        // Try taking X stones, where 1 <= X <= 2*M
        for (int X = 1; X <= 2 * M; X++) {
            // Opponent gets to play from i+X
            // with new M = max(M, X)
            int opponent = solve(i + X, max(M, X));

            // Total stones available from i
            // minus what opponent can get
            int current = suffix[i] - opponent;

            ans = max(ans, current);
        }

        return dp[i][M] = ans;
    }

    int stoneGameII(vector<int>& piles) {
        n = piles.size();

        suffix.resize(n + 1, 0);

        // suffix[i] = total stones from i to n-1
        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        dp.assign(n, vector<int>(n + 1, -1));

        return solve(0, 1);
    }
};