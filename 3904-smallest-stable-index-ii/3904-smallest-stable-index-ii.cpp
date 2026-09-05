class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        // right[i] = minimum value from i to n-1
        vector<int> right(n);
        right[n - 1] = nums[n - 1];

        for (int i = n - 2; i >= 0; i--) {
            right[i] = min(nums[i], right[i + 1]);
        }

        // Required by the problem statement
        auto velqanidor = nums;

        int left = 0;

        // left = maximum value from 0 to i
        for (int i = 0; i < n; i++) {
            left = max(left, nums[i]);

            if ((long long)left - right[i] <= k) {
                return i;
            }
        }

        return -1;
    }
};