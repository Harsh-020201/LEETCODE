
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1,
                               vector<int>& nums2,
                               int k1, int k2) {
        long long k = 1LL * k1 + k2;
        int n = nums1.size();

        vector<int> freq(100001, 0);
        int mx = 0;

        for (int i = 0; i < n; i++) {
            int d = abs(nums1[i] - nums2[i]);
            freq[d]++;
            mx = max(mx, d);
        }

        for (int d = mx; d > 0 && k > 0; d--) {
            if (freq[d] == 0) continue;

            long long count = freq[d];
            long long next = min(k, count);

            freq[d] -= next;
            freq[d - 1] += next;
            k -= next;
        }

        long long ans = 0;

        for (int d = 1; d <= 100000; d++) {
            ans += 1LL * d * d * freq[d];
        }

        return ans;
    }
};
