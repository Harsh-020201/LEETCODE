class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();

        vector<int> first(26, n);
        vector<int> last(26, -1);

        // Find first and last occurrence of every character
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            first[c] = min(first[c], i);
            last[c] = i;
        }

        vector<pair<int, int>> intervals;

        // Build the smallest valid interval for every character
        for (int c = 0; c < 26; c++) {
            if (last[c] == -1)
                continue;

            int left = first[c];
            int right = last[c];
            bool valid = true;

            for (int i = left; i <= right; i++) {
                int x = s[i] - 'a';

                // This character appeared before our left boundary
                if (first[x] < left) {
                    valid = false;
                    break;
                }

                // We must include ALL occurrences of this character
                right = max(right, last[x]);
            }

            if (valid) {
                intervals.push_back({right, left});
            }
        }

        // Sort by ending position
        sort(intervals.begin(), intervals.end());

        vector<string> ans;
        int prevEnd = -1;

        // Greedily choose intervals with earliest ending position
        for (auto [right, left] : intervals) {
            if (left > prevEnd) {
                ans.push_back(s.substr(left, right - left + 1));
                prevEnd = right;
            }
        }

        return ans;
    }
};