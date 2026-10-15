class Solution {
public:
    int sumCounts(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            unordered_set<int> st;

            for (int j = i; j < n; j++) {
                st.insert(nums[j]);

                long long distinct = st.size();
                ans = (ans + distinct * distinct) % MOD;
            }
        }

        return ans;
    }
};