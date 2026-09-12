class Solution {
public:
    struct Node {
        long long weight;
        vector<int> ids;
    };

    bool better(const Node& a, const Node& b) {
        if (a.weight != b.weight)
            return a.weight > b.weight;

        return a.ids < b.ids;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {left, right, weight, original_index}
        vector<array<long long, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by starting point
        sort(a.begin(), a.end());

        // dp[i][k] = best answer using intervals from i onward,
        // choosing at most k intervals
        vector<vector<Node>> dp(n + 1, vector<Node>(5));

        for (int i = n - 1; i >= 0; i--) {

            for (int k = 1; k <= 4; k++) {

                // Option 1: skip current interval
                Node skip = dp[i + 1][k];

                // Option 2: take current interval
                long long right = a[i][1];

                // Find first interval whose left > current right
                int lo = i + 1;
                int hi = n;

                while (lo < hi) {
                    int mid = lo + (hi - lo) / 2;

                    if (a[mid][0] > right)
                        hi = mid;
                    else
                        lo = mid + 1;
                }

                int next = lo;

                Node take;
                take.weight = a[i][2] + dp[next][k - 1].weight;

                take.ids = dp[next][k - 1].ids;
                take.ids.push_back((int)a[i][3]);

                // Indices must be sorted for lexicographical comparison
                sort(take.ids.begin(), take.ids.end());

                dp[i][k] = better(take, skip) ? take : skip;
            }
        }

        return dp[0][4].ids;
    }
};