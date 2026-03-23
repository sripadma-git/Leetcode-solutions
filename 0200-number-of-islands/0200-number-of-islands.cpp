#include <vector>

using namespace std;

class Solution {
public:
    void dfs(vector<vector<char>>& grid, int r, int c) {
        int nr = grid.size();
        int nc = grid[0].size();

        // Boundary checks and water check
        if (r < 0 || c < 0 || r >= nr || c >= nc || grid[r][c] == '0') {
            return;
        }

        // Mark the current cell as visited by setting it to '0'
        grid[r][c] = '0';

        // Visit all adjacent neighbors (Up, Down, Left, Right)
        dfs(grid, r - 1, c);
        dfs(grid, r + 1, c);
        dfs(grid, r, c - 1);
        dfs(grid, r, c + 1);
    }

    int numIslands(vector<vector<char>>& grid) {
        int nr = grid.size();
        if (nr == 0) return 0;
        int nc = grid[0].size();

        int num_islands = 0;
        for (int r = 0; r < nr; ++r) {
            for (int c = 0; c < nc; ++c) {
                if (grid[r][c] == '1') {
                    // Found a new island
                    ++num_islands;
                    // Use DFS to mark the entire island as visited
                    dfs(grid, r, c);
                }
            }
        }

        return num_islands;
    }
};