class Solution {
public:

    struct Node {
        char leftChar, rightChar;
        int leftCount, rightCount;
        int best, len;

        Node() {
            leftChar = rightChar = '#';
            leftCount = rightCount = best = len = 0;
        }
    };

    vector<Node> tree;
    string s;

    Node merge(Node a, Node b) {

        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;

        res.len = a.len + b.len;
        res.leftChar = a.leftChar;
        res.rightChar = b.rightChar;

        // Prefix
        res.leftCount = a.leftCount;

        if (a.leftCount == a.len &&
            a.rightChar == b.leftChar) {
            res.leftCount = a.len + b.leftCount;
        }

        // Suffix
        res.rightCount = b.rightCount;

        if (b.rightCount == b.len &&
            a.rightChar == b.leftChar) {
            res.rightCount = b.len + a.rightCount;
        }

        // Best inside either half
        res.best = max(a.best, b.best);

        // Combine suffix + prefix
        if (a.rightChar == b.leftChar) {
            res.best = max(
                res.best,
                a.rightCount + b.leftCount
            );
        }

        return res;
    }

    void build(int node, int l, int r) {

        if (l == r) {
            tree[node].leftChar = s[l];
            tree[node].rightChar = s[l];

            tree[node].leftCount = 1;
            tree[node].rightCount = 1;
            tree[node].best = 1;
            tree[node].len = 1;

            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);

        tree[node] =
            merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, char c) {

        if (l == r) {
            tree[node].leftChar = c;
            tree[node].rightChar = c;

            tree[node].leftCount = 1;
            tree[node].rightCount = 1;
            tree[node].best = 1;
            tree[node].len = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, c);
        else
            update(node * 2 + 1, mid + 1, r, idx, c);

        tree[node] =
            merge(tree[node * 2], tree[node * 2 + 1]);
    }

    vector<int> longestRepeating(
        string s,
        string queryCharacters,
        vector<int>& queryIndices
    ) {

        this->s = s;

        int n = s.size();

        tree.resize(4 * n + 5);

        build(1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryCharacters.size(); i++) {

            int idx = queryIndices[i];
            char c = queryCharacters[i];

            update(1, 0, n - 1, idx, c);

            ans.push_back(tree[1].best);
        }

        return ans;
    }
};