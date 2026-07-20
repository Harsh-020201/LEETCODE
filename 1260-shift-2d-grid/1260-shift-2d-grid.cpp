class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {

        int rows = grid.size();
        int cols = grid[0].size();

        int total = rows * cols;

        k %= total;

        vector<vector<int>> ans(rows, vector<int>(cols));

        for (int i = 0; i < rows; i++) {

            for (int j = 0; j < cols; j++) {

                int oldIndex = i * cols + j;

                int newIndex = (oldIndex + k) % total;

                int newRow = newIndex / cols;

                int newCol = newIndex % cols;

                ans[newRow][newCol] = grid[i][j];
            }
        }

        return ans;
    }
};