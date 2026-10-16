
class Solution {
private:
    static const int MOD = 1000000007;

    struct Node {
        long long sum = 0;
        long long sqSum = 0;
        long long lazy = 0;
    };

    vector<Node> tree;
    int n;

    // Apply an increment to every value in this segment
    void apply(int node, int l, int r, long long val) {
        long long len = r - l + 1;

        // (x + val)^2 = x^2 + 2*x*val + val^2
        tree[node].sqSum =
            (tree[node].sqSum
             + 2 * val * tree[node].sum
             + val * val % MOD * len) % MOD;

        // Update the sum of values
        tree[node].sum =
            (tree[node].sum + val * len) % MOD;

        // Store the pending increment
        tree[node].lazy =
            (tree[node].lazy + val) % MOD;
    }

    // Pass pending updates to the children
    void push(int node, int l, int r) {
        if (tree[node].lazy == 0 || l == r)
            return;

        int mid = l + (r - l) / 2;
        long long val = tree[node].lazy;

        apply(node * 2, l, mid, val);
        apply(node * 2 + 1, mid + 1, r, val);

        tree[node].lazy = 0;
    }

    // Add val to all positions in [ql, qr]
    void update(int node, int l, int r,
                int ql, int qr, long long val) {

        if (qr < l || r < ql)
            return;

        if (ql <= l && r <= qr) {
            apply(node, l, r, val);
            return;
        }

        push(node, l, r);

        int mid = l + (r - l) / 2;

        update(node * 2, l, mid, ql, qr, val);
        update(node * 2 + 1, mid + 1, r,
               ql, qr, val);

        // Merge children
        tree[node].sum =
            (tree[node * 2].sum
             + tree[node * 2 + 1].sum) % MOD;

        tree[node].sqSum =
            (tree[node * 2].sqSum
             + tree[node * 2 + 1].sqSum) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n + 5, Node());

        // Last occurrence of each number
        vector<int> last(100001, -1);

        long long ans = 0;

        for (int r = 0; r < n; r++) {

            int prev = last[nums[r]];

            // Only subarrays starting after the
            // previous occurrence gain a new distinct value
            int l = prev + 1;

            update(1, 0, n - 1, l, r, 1);

            last[nums[r]] = r;

            // Root stores the sum of squares for
            // all subarrays ending at index r
            ans = (ans + tree[1].sqSum) % MOD;
        }

        return (int)ans;
    }
};
