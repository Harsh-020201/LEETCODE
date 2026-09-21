class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);

        // dp[r] = number of subarrays ending at current index
        // whose product % k == r
        vector<long long> dp(k, 0);

        for (int num : nums) {
            int mod = num % k;

            vector<long long> newDp(k, 0);

            // Start a new subarray with only nums[i]
            newDp[mod]++;

            // Extend all previous subarrays
            for (int r = 0; r < k; r++) {
                int newR = (1LL * r * mod) % k;
                newDp[newR] += dp[r];
            }

            // Add all subarrays ending here to the answer
            for (int r = 0; r < k; r++) {
                ans[r] += newDp[r];
            }

            dp = newDp;
        }

        return ans;
    }
};