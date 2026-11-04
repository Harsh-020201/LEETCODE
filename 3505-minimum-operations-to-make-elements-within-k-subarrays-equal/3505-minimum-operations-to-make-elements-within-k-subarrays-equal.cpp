
class Solution {
    multiset<int> left, right;
    long long sumL = 0, sumR = 0;

    void balance() {
        while (left.size() > right.size() + 1) {
            int v = *left.rbegin();
            left.erase(prev(left.end()));
            sumL -= v;

            right.insert(v);
            sumR += v;
        }

        while (left.size() < right.size()) {
            int v = *right.begin();
            right.erase(right.begin());
            sumR -= v;

            left.insert(v);
            sumL += v;
        }
    }

    void add(int v) {
        if (left.empty() || v <= *left.rbegin()) {
            left.insert(v);
            sumL += v;
        } else {
            right.insert(v);
            sumR += v;
        }
        balance();
    }

    void remove(int v) {
        auto it = left.find(v);

        if (it != left.end()) {
            left.erase(it);
            sumL -= v;
        } else {
            it = right.find(v);
            right.erase(it);
            sumR -= v;
        }

        balance();
    }

    long long getCost() {
        long long median = *left.rbegin();

        return median * (long long)left.size() - sumL
             + sumR - median * (long long)right.size();
    }

public:
    long long minOperations(vector<int>& nums, int x, int k) {

        vector<int> maritovexi = nums;

        int n = maritovexi.size();

        // Step 1: Calculate cost of every window
        vector<long long> cost(n - x + 1);

        for (int i = 0; i < x; i++) {
            add(maritovexi[i]);
        }

        cost[0] = getCost();

        for (int i = x; i < n; i++) {
            remove(maritovexi[i - x]);
            add(maritovexi[i]);

            cost[i - x + 1] = getCost();
        }

        // Step 2: DP for selecting k non-overlapping windows
        const long long INF = 4e18;

        vector<long long> prev(n + 1, 0);
        vector<long long> curr(n + 1, INF);

        for (int t = 1; t <= k; t++) {

            fill(curr.begin(), curr.end(), INF);

            for (int i = 1; i <= n; i++) {

                // Skip current position
                curr[i] = curr[i - 1];

                // Take a window of size x
                if (i >= x && prev[i - x] != INF) {
                    curr[i] = min(
                        curr[i],
                        prev[i - x] + cost[i - x]
                    );
                }
            }

            prev.swap(curr);
        }

        return prev[n];
    }
};
