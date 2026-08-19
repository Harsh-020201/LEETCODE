class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {

        // row -> bitmask of reserved seats
        unordered_map<int, int> mp;

        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            mp[row] |= (1 << (col - 1));
        }

        int ans = 2 * (n - mp.size());

        // Masks for:
        // seats 2,3,4,5
        int left = (1 << 1) | (1 << 2) |
                   (1 << 3) | (1 << 4);

        // seats 4,5,6,7
        int middle = (1 << 3) | (1 << 4) |
                     (1 << 5) | (1 << 6);

        // seats 6,7,8,9
        int right = (1 << 5) | (1 << 6) |
                    (1 << 7) | (1 << 8);

        for (auto &[row, mask] : mp) {

            bool canLeft = (mask & left) == 0;
            bool canMiddle = (mask & middle) == 0;
            bool canRight = (mask & right) == 0;

            if (canLeft && canRight) {
                // Two non-overlapping groups:
                // 2,3,4,5 and 6,7,8,9
                ans += 2;
            }
            else if (canLeft || canMiddle || canRight) {
                ans += 1;
            }
        }

        return ans;
    }
};