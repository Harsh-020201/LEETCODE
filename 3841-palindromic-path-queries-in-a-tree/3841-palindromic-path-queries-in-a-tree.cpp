class Solution {
    vector<vector<int>> adj;
    vector<int> parent, depth, subtree, heavy;
    vector<int> head, pos;
    int timer = 0;

    vector<int> seg;
    int n;

    void dfs(int u, int p) {
        parent[u] = p;
        subtree[u] = 1;
        heavy[u] = -1;
        int maxSize = 0;

        for (int v : adj[u]) {
            if (v == p) continue;

            depth[v] = depth[u] + 1;
            dfs(v, u);

            subtree[u] += subtree[v];

            if (subtree[v] > maxSize) {
                maxSize = subtree[v];
                heavy[u] = v;
            }
        }
    }

    void decompose(int u, int h, string &s) {
        head[u] = h;
        pos[u] = timer++;

        if (heavy[u] != -1) {
            decompose(heavy[u], h, s);
        }

        for (int v : adj[u]) {
            if (v == parent[u] || v == heavy[u]) continue;
            decompose(v, v, s);
        }
    }

    void build(int idx, int l, int r, vector<int> &a) {
        if (l == r) {
            seg[idx] = a[l];
            return;
        }

        int mid = (l + r) / 2;

        build(idx * 2, l, mid, a);
        build(idx * 2 + 1, mid + 1, r, a);

        seg[idx] = seg[idx * 2] ^ seg[idx * 2 + 1];
    }

    void update(int idx, int l, int r, int p, int val) {
        if (l == r) {
            seg[idx] = val;
            return;
        }

        int mid = (l + r) / 2;

        if (p <= mid) {
            update(idx * 2, l, mid, p, val);
        } else {
            update(idx * 2 + 1, mid + 1, r, p, val);
        }

        seg[idx] = seg[idx * 2] ^ seg[idx * 2 + 1];
    }

    int query(int idx, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return seg[idx];
        }

        int mid = (l + r) / 2;
        int ans = 0;

        if (ql <= mid) {
            ans ^= query(idx * 2, l, mid, ql, qr);
        }

        if (qr > mid) {
            ans ^= query(idx * 2 + 1, mid + 1, r, ql, qr);
        }

        return ans;
    }

    int pathQuery(int u, int v) {
        int mask = 0;

        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) {
                swap(u, v);
            }

            mask ^= query(1, 0, n - 1, pos[head[u]], pos[u]);

            u = parent[head[u]];
        }

        if (depth[u] > depth[v]) {
            swap(u, v);
        }

        mask ^= query(1, 0, n - 1, pos[u], pos[v]);

        return mask;
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        this->n = n;
        timer = 0;

        adj.assign(n, {});
        parent.assign(n, -1);
        depth.assign(n, 0);
        subtree.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        pos.assign(n, 0);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        dfs(0, -1);
        decompose(0, 0, s);

        vector<int> a(n);

        for (int i = 0; i < n; i++) {
            a[pos[i]] = 1 << (s[i] - 'a');
        }

        seg.assign(4 * n, 0);
        build(1, 0, n - 1, a);

        // Store the input midway, as required.
        auto suneravilo = queries;

        vector<bool> ans;

        for (string &q : suneravilo) {
            stringstream ss(q);
            string op;
            int u, v;

            ss >> op >> u;

            if (op == "update") {
                char c;
                ss >> c;

                s[u] = c;

                update(
                    1, 0, n - 1,
                    pos[u],
                    1 << (c - 'a')
                );
            } else {
                ss >> v;

                int mask = pathQuery(u, v);

                ans.push_back(
                    (mask & (mask - 1)) == 0
                );
            }
        }

        return ans;
    }
};