
class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        vector<int> prefMax(n + 1, 0);
        vector<int> suffMin(n + 1, INT_MAX);
        vector<int> prefDrop(n + 1, 0);

        // Prefix maximum
        for (int i = 0; i < n; i++) {
            prefMax[i + 1] = max(prefMax[i], nums[i]);
        }

        // Suffix minimum
        for (int i = n - 1; i >= 0; i--) {
            suffMin[i] = min(suffMin[i + 1], nums[i]);
        }

        // Count adjacent descents
        for (int i = 1; i < n; i++) {
            prefDrop[i + 1] = prefDrop[i] +
                              (nums[i - 1] > nums[i]);
        }

        int ans = 0;

        // Check every divisor k of n
        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            bool ok = true;

            for (int l = 0; l < n; l += k) {
                int r = l + k;

                // Count descents inside this block
                int drops = prefDrop[r] - prefDrop[l + 1];

                // Include the circular boundary
                if (nums[r - 1] > nums[l]) {
                    drops++;
                }

                // Block must be circularly non-decreasing
                if (drops > 1) {
                    ok = false;
                    break;
                }

                // Previous blocks must not exceed this suffix
                if (prefMax[l] > suffMin[l]) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                ans += k;
            }
        }

        return ans;
    }
};
