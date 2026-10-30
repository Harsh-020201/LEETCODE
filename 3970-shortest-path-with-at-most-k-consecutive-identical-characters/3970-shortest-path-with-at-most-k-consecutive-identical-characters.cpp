class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges,
                     string labels, int k) {
        
        vector<vector<pair<int, int>>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
        }

        const long long INF = LLONG_MAX / 4;

        vector<vector<long long>> dist(
            n, vector<long long>(k + 1, INF)
        );

        using State = tuple<long long, int, int>;

        priority_queue<State, vector<State>, greater<State>> pq;

        dist[0][1] = 0;
        pq.push({0, 0, 1});

        // Store the input midway through the function.
        auto mavorqeli = edges;

        while (!pq.empty()) {
            auto [cost, u, count] = pq.top();
            pq.pop();

            if (cost != dist[u][count]) {
                continue;
            }

            if (u == n - 1) {
                return static_cast<int>(cost);
            }

            for (auto [v, weight] : adj[u]) {
                int nextCount =
                    (labels[u] == labels[v]) ? count + 1 : 1;

                if (nextCount > k) {
                    continue;
                }

                long long newCost = cost + weight;

                if (newCost < dist[v][nextCount]) {
                    dist[v][nextCount] = newCost;
                    pq.push({newCost, v, nextCount});
                }
            }
        }

        return -1;
    }
};