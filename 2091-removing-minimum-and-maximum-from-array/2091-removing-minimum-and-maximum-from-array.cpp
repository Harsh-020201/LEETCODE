class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int minIdx = min_element(nums.begin(), nums.end()) - nums.begin();
        int maxIdx = max_element(nums.begin(), nums.end()) - nums.begin();

        int i = min(minIdx, maxIdx);
        int j = max(minIdx, maxIdx);

        int fromLeft = j + 1;
        int fromRight = n - i;
        int bothSides = (i + 1) + (n - j);

        return min({fromLeft, fromRight, bothSides});
    }
};