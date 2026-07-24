class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048; // 2^11, sufficient for nums[i] <= 2000

        vector<bool> one(MAXX, false);
        vector<bool> two(MAXX, false);
        vector<bool> three(MAXX, false);

        // XOR of one element
        for (int x : nums)
            one[x] = true;

        // XOR of two elements
        for (int x : nums) {
            for (int v = 0; v < MAXX; v++) {
                if (one[v])
                    two[v ^ x] = true;
            }
        }

        // XOR of three elements
        for (int x : nums) {
            for (int v = 0; v < MAXX; v++) {
                if (two[v])
                    three[v ^ x] = true;
            }
        }

        int ans = 0;
        for (bool x : three)
            if (x) ans++;

        return ans;
    }
};