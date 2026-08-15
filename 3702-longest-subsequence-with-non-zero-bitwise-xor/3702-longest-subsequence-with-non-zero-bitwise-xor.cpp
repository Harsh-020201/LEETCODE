class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();
        int xr = 0;
        bool hasNonZero = false;

        for (int x : nums) {
            xr ^= x;

            if (x != 0)
                hasNonZero = true;
        }

        // XOR of the entire array is already non-zero
        if (xr != 0)
            return n;

        // XOR is zero and every element is zero
        if (!hasNonZero)
            return 0;

        // Remove one non-zero element
        return n - 1;
    }
};