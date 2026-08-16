class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0};

        for (int x : stones) {
            cnt[x % 3]++;
        }

        // Number of 0-mod-3 stones is even
        if (cnt[0] % 2 == 0) {
            return cnt[1] > 0 && cnt[2] > 0;
        }

        // Number of 0-mod-3 stones is odd
        return abs(cnt[1] - cnt[2]) > 2;
    }
};