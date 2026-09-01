class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sx = 0, sy = 0;
        int litterCount = 0;

    
        vector<vector<int>> litterId(m, vector<int>(n, -1));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (classroom[i][j] == 'S') {
                    sx = i;
                    sy = j;
                }

                else if (classroom[i][j] == 'L') {
                    litterId[i][j] = litterCount++;
                }
            }
        }

        // No litter
        if (litterCount == 0)
            return 0;

        int targetMask = (1 << litterCount) - 1;

        // state = {row, col, remaining energy, collected mask}
        queue<tuple<int, int, int, int>> q;

        q.push({sx, sy, energy, 0});

        // visited[row][col][energy][mask]
        vector<vector<vector<vector<bool>>>> visited(
            m,
            vector<vector<vector<bool>>>(
                n,
                vector<vector<bool>>(
                    energy + 1,
                    vector<bool>(1 << litterCount, false)
                )
            )
        );

        visited[sx][sy][energy][0] = true;

        int moves = 0;

        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        while (!q.empty()) {

            int size = q.size();

            while (size--) {

                auto [x, y, currEnergy, mask] = q.front();
                q.pop();

                // Collected all litter
                if (mask == targetMask)
                    return moves;

                // Cannot move without energy
                if (currEnergy == 0)
                    continue;

                for (int d = 0; d < 4; d++) {

                    int nx = x + dx[d];
                    int ny = y + dy[d];

                    // Out of bounds
                    if (nx < 0 || nx >= m ||
                        ny < 0 || ny >= n)
                        continue;

                    // Obstacle
                    if (classroom[nx][ny] == 'X')
                        continue;

                    int newEnergy = currEnergy - 1;
                    int newMask = mask;

                    // Reset energy
                    if (classroom[nx][ny] == 'R') {
                        newEnergy = energy;
                    }

                    // Collect litter
                    if (classroom[nx][ny] == 'L') {

                        int id = litterId[nx][ny];

                        newMask |= (1 << id);
                    }

                    if (!visited[nx][ny][newEnergy][newMask]) {

                        visited[nx][ny][newEnergy][newMask] = true;

                        q.push({
                            nx,
                            ny,
                            newEnergy,
                            newMask
                        });
                    }
                }
            }

            moves++;
        }

        return -1;
    }
};