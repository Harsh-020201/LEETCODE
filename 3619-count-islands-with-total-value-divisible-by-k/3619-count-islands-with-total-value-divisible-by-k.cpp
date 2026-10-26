class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;

        vector<pair<int, int>> dirs = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}
        };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] > 0) {
                    long long sum = 0;
                    stack<pair<int, int>> st;

                    st.push({i, j});
                    sum += grid[i][j];
                    grid[i][j] = 0;

                    while (!st.empty()) {
                        auto [x, y] = st.top();
                        st.pop();

                        for (auto [dx, dy] : dirs) {
                            int nx = x + dx;
                            int ny = y + dy;

                            if (nx >= 0 && nx < m &&
                                ny >= 0 && ny < n &&
                                grid[nx][ny] > 0) {

                                sum += grid[nx][ny];
                                grid[nx][ny] = 0;
                                st.push({nx, ny});
                            }
                        }
                    }

                    if (sum % k == 0) {
                        ans++;
                    }
                }
            }
        }

        return ans;
    }
};